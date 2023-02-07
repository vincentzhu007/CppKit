//
// Created by zgd on 11/9/22.
//

#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <sstream>

using namespace std;

class Tensor {
 public:
  Tensor() = default;
  Tensor(const vector<int> &shape, const float *data = nullptr) {
    if (shape.empty()) {
      return;
    }
    num_elem_ = shape.back();
    stride_.resize(shape.size(), 1);
    for (int dim = shape.size() - 2; dim >= 0; dim--) {
      stride_[dim] = stride_[dim + 1] * shape[dim + 1];
      num_elem_ *= shape[dim];
    }
    data_ = (float *)malloc(sizeof(float) * num_elem_);
    if (data != nullptr) {
      memcpy(data_, data, sizeof(float) * num_elem_);
    } else {
      bzero(data_, sizeof(float) * num_elem_);
    }
    shape_ = shape;
  }
  ~Tensor() {
    free(data_);
  }
  float *data() { return data_; }
  size_t dim() { return shape_.size(); }
  size_t num_elem() { return num_elem_; }
  vector<int> shape() { return shape_; }
  vector<int> stride() { return stride_; }

  int flat_index(const vector<int> &ndim_index) const {
    int idx = 0;
    for (int dim = 0; dim < stride_.size(); dim++) {
      idx += stride_[dim] * ndim_index[dim];
    }
    return idx;
  }

  vector<int> ndim_index(int flat_index) const {
    vector<int> idx(shape_.size(), 0);
    idx[shape_.size() - 1] = flat_index % shape_.back();
    for (int dim = shape_.size() - 2; dim >= 0; dim--) {
      flat_index /= shape_[dim + 1];
      if (flat_index == 0) {
        break;
      }
      idx[dim] = flat_index % shape_[dim];
    }
    return idx;
  }

  float at(const vector<int> &ndim_index) const {
    return data_[flat_index(ndim_index)];
  }

  float at(int flat_index) const {
    return data_[flat_index];
  }

  std::string ToString() const;

 private:
  float *data_ = nullptr;
  size_t num_elem_ = 0;
  vector<int> shape_ = {};
  vector<int> stride_ = {};
};

std::string Tensor::ToString() const {
  ostringstream oss;
  if (shape_.size() == 1) {
    oss << "[";
    for (int i = 0; i < shape_[0]; i++) {
      oss << data_[i] << " ";
    }
    oss << "]";
    return oss.str();
  }

  if (shape_.size() == 2) {
    oss << "[" << endl;
    for (int i = 0; i < shape_[0]; i++) {
      oss << " [";
      for (int j = 0; j < shape_[1]; j++) {
        oss << data_[i * shape_[1] + j] << " ";
      }
      oss << "]" << endl;
    }
    oss << "]";
    return oss.str();
  }

  if (shape_.size() == 3) {
    oss << "[" << endl;
    for (int i = 0; i < shape_[0]; i++) {
      oss << " [" << endl;
      for (int j = 0; j < shape_[1]; j++) {
        oss << "  [";
        for (int k = 0; k < shape_[2]; k++) {
          oss << data_[i * shape_[2] * shape_[1] + j * shape_[2] + k] << " ";
        }
        oss << "]" << endl;
      }
      oss << " ]" << endl;
    }
    oss << "]";
    return oss.str();
  }
  return "not support";
}

using TensorPtr = std::shared_ptr<Tensor>;
using TensorList = std::vector<TensorPtr>;

static vector<int> IndexAdd(const vector<int> &a, const vector<int> &b) {
  vector<int> result(a.size());
  for (int i = 0; i < a.size(); i++) {
    result[i] = a[i] + b[i];
  }
  return result;
}

class CropKernel {
 public:
  TensorList Run(const TensorList &tensors, const vector<int> &offset) {
    const TensorPtr &in_tensor = tensors[0];
    const TensorPtr &shape_tensor = tensors[1];
    auto in_data = in_tensor->data();
    auto in_shape = in_tensor->shape();
    auto out_shape = shape_tensor->shape();

    TensorPtr out_tensor(new Tensor(out_shape));
    for (int y = 0; y < out_tensor->num_elem(); y++) {
      auto out_index = out_tensor->ndim_index(y);
      auto in_index = IndexAdd(out_index, offset);
      out_tensor->data()[y] = in_tensor->at(in_index);
      cout << "output y: " << y << ", out index: " << out_index[0] << out_index[1] << out_index[2]
           << ", in index: "<< in_index[0] << in_index[1] << in_index[2]
           << " in x:" << in_tensor->flat_index(in_index) << ", in data:" << in_tensor->at(in_index) << endl;
    }
    return TensorList{out_tensor};
  }
};

int main()
{
  // generate input data
  constexpr int N = 4 * 5 * 6;
  float data_buf[N];
  for (int i = 0; i < N ; i++) {
    data_buf[i] = i;
  }
  TensorPtr data(new Tensor({4, 5, 6}, data_buf));
  cout << data->ToString() << endl;

  float shape_buf[2 * 3 * 4];
  TensorPtr shape(new Tensor({2, 3, 4}, shape_buf));

  CropKernel crop_kernel;
  TensorList input_tensors = {data, shape};
  auto output_tensors = crop_kernel.Run(input_tensors, {0, 1, 2});

  for (const auto &tensor: output_tensors) {
    cout << tensor->ToString() << endl;
  }
}
