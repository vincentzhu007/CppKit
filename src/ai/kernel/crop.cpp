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
  Tensor(const float *data, vector<int> shape) {
    int num_elems = 1;
    for (auto s: shape) {
      num_elems *= s;
    }
    data_ = (float *)malloc(sizeof(float) * num_elems);
    memcpy(data_, data, sizeof(float) * num_elems);
    shape_ = shape;
  }
  ~Tensor() {
    free(data_);
  }
  float *data() { return data_; }
  size_t dim() { return shape_.size(); }
  vector<int> shape() { return shape_; }

  std::string ToString() const;

 private:
  float *data_ = nullptr;
  vector<int> shape_ = {};
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

static vector<int> FlatIndex2NDimIndex(int x, const vector<int> &shape) {
  vector<int> idx(shape.size(), 0);
  idx[shape.size() - 1] = x % shape.back();
  for (int dim = shape.size() - 2; dim >= 0; dim--) {
    x = x / shape[dim + 1];
    idx[dim] = x % shape[dim];
  }
  return idx;
}

static int NDimIndex2FlatIndex(const vector<int> &idx, const vector<int> &shape) {
  vector<int> stride(shape.size(), 1);
  for (int dim = shape.size() - 2; dim >= 0; dim--) {
    stride[dim] = stride[dim + 1] * shape[dim + 1];
  }

  int x = 0;
  for (int dim = 0; dim < shape.size(); dim++) {
    x += idx[dim] * stride[dim];
  }
  return x;
}

class CropKernel {
 public:
  TensorList Run(const TensorList &tensors, const vector<int> &offset) {
    const TensorPtr &in_tensor = tensors[0];
    const TensorPtr &shape_tensor = tensors[1];
    auto in_data = in_tensor->data();
    auto in_shape = in_tensor->shape();
    auto out_shape = shape_tensor->shape();
    int num_dim = out_shape.size();

    auto out_num_elems = 1;
    for (int dim = 0; dim < num_dim; dim++) {
      out_num_elems *= out_shape[dim];
    }
    cout << "out_num_elems: " << out_num_elems << endl;

    float *out_data = (float *)malloc(sizeof(float) * out_num_elems);
    for (int y = 0; y < out_num_elems; y++) {
      auto out_idx = FlatIndex2NDimIndex(y, out_shape);
      vector<int> in_index(num_dim);
      for (int i = 0; i < num_dim; i++) {
        in_index[i] = out_idx[i] + offset[i];
      }

      auto x = NDimIndex2FlatIndex(in_index, in_shape);
      cout << "output y: " << y << ", out index: " << out_idx[0] << out_idx[1] << out_idx[2]
           << ", in index: "<< in_index[0] << in_index[1] << in_index[2]
           << " in x:" << x << ", in data:" << in_data[x] << endl;
      out_data[y] = in_data[x];
    }
    return TensorList{TensorPtr(new Tensor(out_data, out_shape))};
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
  TensorPtr data(new Tensor(data_buf, {4, 5, 6}));
  cout << data->ToString() << endl;

  float shape_buf[2 * 3 * 4];
  TensorPtr shape(new Tensor(shape_buf, {2, 3, 4}));

  CropKernel crop_kernel;
  TensorList input_tensors = {data, shape};
  auto output_tensors = crop_kernel.Run(input_tensors, {0, 1, 2});

  for (const auto &tensor: output_tensors) {
    cout << tensor->ToString() << endl;
  }
}
