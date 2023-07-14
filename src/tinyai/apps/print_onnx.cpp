//
// Created by zgd on 2023/7/13.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "google/protobuf/text_format.h"
#include "onnx.pb.h"

void PrintModel(const onnx::ModelProto &model) {
  std::cout << "ir_version: " << model.ir_version() << std::endl;
  std::cout << "producer_name: " << model.producer_name() << std::endl;
  std::cout << "producer_version: " << model.producer_version() << std::endl;
  std::cout << "model_version: " << model.model_version() << std::endl;
  std::cout << "domain: " << model.domain() << std::endl;
  std::cout << "doc_string: " << model.doc_string() << std::endl;
}

void SaveAsJson(const onnx::ModelProto &model, const std::string &out_path) {
  std::string content;
  google::protobuf::TextFormat::PrintToString(model, &content);

  std::ofstream ofs(out_path);
  ofs << content;
  ofs.flush();
}

void PrintGraphBrief(const onnx::ModelProto &model) {
  if (!model.has_graph()) {
    std::cout << "model has no graph.";
    return;
  }

  const auto &graph = model.graph();
  printf("graph \"%s\" has:\n", graph.name().c_str());
  printf("  %8d node(s)\n", graph.node_size());
  printf("  %8d weight(s)\n", graph.initializer_size());
  printf("  %8d sparse weight(s)\n", graph.sparse_initializer_size());
  printf("  %8d input(s)\n", graph.input_size());
  printf("  %8d output(s)\n", graph.output_size());
  printf("  %8d value(s)\n", graph.value_info_size());
  printf("  %8d quant(s)\n", graph.quantization_annotation_size());
}

std::string NamesToString(
    const google::protobuf::RepeatedPtrField<std::string> &names) {
  std::stringstream ss;
  ss << "[";
  for (int i = 0; i < names.size(); i++) {
    ss << "\"" << names.at(i) << "\"";
    ss << (i < names.size() - 1 ? ", " : "]");
  }
  return ss.str();
}

void PrintNode(const onnx::NodeProto &node) {
  printf("name      : %s\n", node.name().c_str());
  printf("op_type   : %s\n", node.op_type().c_str());
  printf("input     : %s\n", NamesToString(node.input()).c_str());
  printf("output    : %s\n", NamesToString(node.output()).c_str());
  printf("attribute : %d\n", node.attribute_size());
}

std::string DataTypeToString(int data_type) {
  static std::map<onnx::TensorProto_DataType, std::string> kDataTypeNames = {
      {onnx::TensorProto_DataType_UNDEFINED, "UNDEFINED"},
      {onnx::TensorProto_DataType_FLOAT, "FLOAT"},
      {onnx::TensorProto_DataType_UINT8, "UINT8"},
      {onnx::TensorProto_DataType_INT8, "INT8"},
      {onnx::TensorProto_DataType_UINT16, "UINT16"},
      {onnx::TensorProto_DataType_INT32, "INT32"},
      {onnx::TensorProto_DataType_INT64, "INT64"},
      {onnx::TensorProto_DataType_STRING, "STRING"},
      {onnx::TensorProto_DataType_BOOL, "BOOL"},
      {onnx::TensorProto_DataType_FLOAT16, "FLOAT16"},
      {onnx::TensorProto_DataType_DOUBLE, "DOUBLE"},
      {onnx::TensorProto_DataType_UINT32, "UINT32"},
      {onnx::TensorProto_DataType_UINT64, "UINT64"},
  };

  if ((data_type < onnx::TensorProto_DataType_UNDEFINED) ||
    (data_type > onnx::TensorProto_DataType_UINT64)) {
    return "UNKNOWN";
  }
  return kDataTypeNames[static_cast<onnx::TensorProto_DataType>(data_type)];
}

std::string ShapeToString(const onnx::TensorShapeProto &shape) {
  std::stringstream ss;
  ss << "[";
  for (int i = 0; i < shape.dim_size(); i++) {
    const auto value = shape.dim().at(i);
    if (value.has_dim_value()) {
      ss << value.dim_value();
    } else {
      ss << value.dim_value();
    }
    ss << (i < shape.dim_size() - 1 ? ", " : "]");
  }
  return ss.str();
}

std::string TensorToString(const onnx::TypeProto_Tensor &tensor) {
  std::stringstream ss;
  ss << "elem_type: " << DataTypeToString(tensor.elem_type()) << ", ";
  ss << "shape: " << ShapeToString(tensor.shape());
  return ss.str();
}

void PrintValueInfo(const onnx::ValueInfoProto &value_info) {
  printf("name     : %s\n", value_info.name().c_str());
  if (value_info.has_type() && value_info.type().has_tensor_type()) {
    printf("type     : tensor {%s}\n", TensorToString(value_info.type().tensor_type()).c_str());
  }
}

void PrintGraphStructure(const onnx::GraphProto &graph) {
  printf("===  %8d node(s)   ===\n\n", graph.node_size());
  for (int i = 0; i < graph.node_size(); i++) {
    PrintNode(graph.node().at(i));
    printf("\n");
  }

  printf("\n\n===  %8d input(s)  ===\n\n", graph.input_size());
  for (int i = 0; i < graph.input_size(); i++) {
    PrintValueInfo(graph.input().at(i));
    printf("\n");
  }

  printf("\n\n===  %8d output(s) ===\n\n", graph.output_size());
  for (int i = 0; i < graph.output_size(); i++) {
    PrintValueInfo(graph.output().Get(i));
    printf("\n");
  }
}


void PrintGraphData() {


}

int main(int argc, const char *argv[]) {
  std::cout << "*** print onnx ***" << std::endl;

  if (argc != 2) {
    std::cerr << "usage: ./print_onnx path_to_your_onnx_model" << std::endl;
    return EXIT_FAILURE;
  }

  std::string path = argv[1];

  std::cout << "model: " << path << std::endl;

  // Read model file
  std::ifstream ifs(path, std::ios::binary);
  if (!ifs.good()) {
    std::cerr << "read model failed." << std::endl;
    return EXIT_FAILURE;
  }

  onnx::ModelProto model;
  bool ok = model.ParseFromIstream(&ifs);
  if (!ok) {
    std::cerr << "parse model failed." << std::endl;
    return EXIT_FAILURE;
  }

//  PrintGraphBrief(model);

  PrintGraphStructure(model.graph());

//  PrintModel(model);

//  SaveAsJson(model, path + ".out");
  return 0;
}

