//
// Created by zgd on 2/1/23.
//

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <set>
#include <cstring>

using namespace std;

class Tensor;
using TensorPtr = std::shared_ptr<Tensor>;
using TensorList = std::vector<TensorPtr>;

class Tensor {
 public:
  Tensor() = default;
  Tensor(const std::initializer_list<int> &shape, const std::initializer_list<float> &data) : shape_(shape) {
    if (shape_.empty()) {
      data_ = nullptr;
      num_elems_ = 0;
      return;
    }

    num_elems_ = std::accumulate(shape_.begin(), shape_.end(), 1, std::multiplies<int>());
    if (data.size() != num_elems_) {
      throw std::exception();
    }

    data_ = new float[num_elems_];
    size_t i = 0;
    for (auto d: data) {
      data_[i++] = d;
    }
  }

  Tensor(const std::vector<int> &shape, const float *data) : shape_(shape) {
    if (shape_.empty()) {
      data_ = nullptr;
      num_elems_ = 0;
      return;
    }

    num_elems_ = std::accumulate(shape_.begin(), shape_.end(), 1, std::multiplies<int>());

    data_ = new float[num_elems_];
    size_t i = 0;
    memcpy(data_, data, sizeof(float) * num_elems_);
  }

  Tensor(const Tensor &) = delete;
  Tensor(const Tensor &&) = delete;
  Tensor &operator=(const Tensor &) = delete;
  Tensor &operator=(const Tensor &&) = delete;

  ~Tensor() {
    delete[] data_;
  }

  std::vector<int> shape() const { return shape_; }
  size_t ndims() const { return shape_.size(); }
  float *data() const { return data_; }

  std::string ToString() const {
    std::stringstream ss;
    ss << "{shape:[";
    for (size_t i = 0; i < shape_.size(); i++) {
      ss << shape_[i] << (i != shape_.size() - 1 ? "," : "");
    }
    ss << "],data:[";
    for (int i = 0; i < num_elems_; i++) {
      ss << data_[i] << (i != num_elems_ - 1 ? "," : "");
    }
    ss << "]}";
    return ss.str();
  }

  static TensorPtr CreateTensor(const std::initializer_list<int> &shape, const std::initializer_list<float> &data) {
    return std::make_shared<Tensor>(shape, data);
  }

  static TensorPtr CreateTensor(const std::vector<int> &shape, const float *data) {
    return std::make_shared<Tensor>(shape, data);
  }

 private:
  float *data_ = nullptr;
  std::vector<int> shape_ = {};
  int num_elems_ = 0;
};

class Broadcasting {
 public:
  Broadcasting(const TensorList &in_tensors) : in_tensors_(in_tensors) {}

  bool IsBroadcastable() {
    if (in_tensors_.size() <= 1) {
      return true;
    }

    size_t max_dims = 0;
    for (auto in_tensor: in_tensors_) {
      max_dims = std::max(in_tensor->ndims(), max_dims);
    }

    // construct the shapes aligned to the maximum dimension, fill missing shape size with value: 1.
    aligned_shapes_ = std::vector<std::vector<int>>(in_tensors_.size(), std::vector<int>(max_dims, 1));
    for (size_t i = 0; i < in_tensors_.size(); i++) {
      auto in_shape = in_tensors_[i]->shape();
      size_t offset_from_header = max_dims - in_shape.size();
      (void)std::copy(in_shape.begin(), in_shape.end(), aligned_shapes_[i].begin() + offset_from_header);
    }

    // apply broadcasting rules from tail dimension to header dimension.
    result_shape_ = std::vector<int>(max_dims, 0);
    for (int64_t k = max_dims - 1; k >= 0; k--) {
      std::set<int> size_set = {};
      for (size_t i = 0; i < aligned_shapes_.size(); i++) {
        size_set.emplace(aligned_shapes_[i][k]);
      }
      if (size_set.size() > 2) {
        return false;
      }
      if (size_set.size() == 2 && size_set.find(1) == size_set.end()) {
        return false;
      }
      result_shape_[k] = *size_set.rbegin();
    }

    return true;
  }

  static std::vector<int> SingleDimIndexToMultiDimIndex(int index_1d, std::vector<int> shape) {
    std::vector<int> stride(shape.size(), 1);
    for (int i = shape.size() - 1; i > 0; i--) {
      stride[i - 1] = stride[i] * shape[i];
    }

    std::vector<int> out_multi_index(shape.size(), 0);
    for (int i = 0; i < shape.size(); i++) {
      out_multi_index[i] = index_1d / stride[i];
      index_1d %= stride[i];
    }
    return out_multi_index;
  }

  static int MultiDimIndexToSingleDimIndex(std::vector<int> multi_index, std::vector<int> shape) {
    std::vector<int> stride(shape.size(), 1);
    for (int i = shape.size() - 1; i > 0; i--) {
      stride[i - 1] = stride[i] * shape[i];
    }

    int index = 0;
    for (int i = 0; i < shape.size(); i++) {
      index += multi_index[i] * stride[i];
    }
    return index;
  }

  static std::vector<int> OutMaped2InIndex(std::vector<int> out_multi_index, std::vector<int> in_shape) {
    std::vector<int> in_multi_index = out_multi_index;
    for (int i = 0; i < in_shape.size(); i++) {
      if (in_shape[i] == 1) {
        in_multi_index[i] = 0;
      }
    }
    return in_multi_index;
  }

  TensorPtr CreateResultTensor(const TensorPtr &in_tensor, std::vector<int> in_shape, std::vector<int> out_shape) {
    auto num_elems = std::accumulate(out_shape.begin(), out_shape.end(), 1, std::multiplies<int>());
    float *out_data = new float[num_elems];
    auto in_data = in_tensor->data();
    for (int out_i = 0; out_i < num_elems; out_i++) {
      std::vector<int> out_multi_index = SingleDimIndexToMultiDimIndex(out_i, out_shape);
      std::vector<int> in_multi_index = OutMaped2InIndex(out_multi_index, in_shape);
      int in_index = MultiDimIndexToSingleDimIndex(in_multi_index, in_shape);
      out_data[out_i] = in_data[in_index];
    }
    return Tensor::CreateTensor(out_shape, out_data);
  }

  TensorList CreateBroadcastedTensors() {
    if (in_tensors_.size() <= 1) {
      return in_tensors_;
    }

    if (!IsBroadcastable()) {
      return {};
    }

    TensorList out_tensors;
    for (size_t i = 0; i < in_tensors_.size(); i++) {
      auto out_tensor = CreateResultTensor(in_tensors_[i], aligned_shapes_[i], result_shape_);
      out_tensors.push_back(out_tensor);
    }
    return out_tensors;
  }

 private:
  TensorList in_tensors_;
  TensorList out_tensors_;
  std::vector<std::vector<int>> aligned_shapes_;
  std::vector<int> result_shape_; // result shape after broadcasting
};

int main() {
//  TensorList in_tensors = {
//      Tensor::CreateTensor({4}, {1, 2, 3, 4}),
//      Tensor::CreateTensor({1}, {1}),
//      Tensor::CreateTensor({4}, {1, 2, 2, 2})
//  };

//  TensorList in_tensors = {
//      Tensor::CreateTensor({2, 3}, {1, 2, 3, 4, 5, 6}),
//      Tensor::CreateTensor({2, 1}, {1, 2})
//  };

  TensorList in_tensors = {
      Tensor::CreateTensor({2, 3}, {1, 2, 3, 4, 5, 6}),
      Tensor::CreateTensor({3}, {1, 2, 3})
  };

  for (auto in_tensor: in_tensors) {
    cout << "in tensor: " << in_tensor->ToString() << endl;
  }

  Broadcasting broadcasting(in_tensors);
  auto ok = broadcasting.IsBroadcastable();
  if (!ok) {
    cout << "Not broadcastable." << endl;
    return -1;
  }
  cout << "Is broadcastable." << endl;

  cout << "Perform broadcasting..." << endl;
  auto out_tensors = broadcasting.CreateBroadcastedTensors();
  for (auto out: out_tensors) {
    cout << out->ToString() << endl;
  }
  return 0;
}


