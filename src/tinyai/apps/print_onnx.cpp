//
// Created by zgd on 2023/7/13.
//

#include <iostream>
#include <string>
#include <fstream>
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

int main(int argc, const char *argv[]) {
  std::cout << "*** print onnx ***" << std::endl;

  if (argc != 2) {
    std::cerr << "usage: ./print_onnx path_to_your_onnx_model" << std::endl;
    return EXIT_FAILURE;
  }

  std::string path = argv[1];

  std::cout << "model path: " << path << std::endl;

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

  std::cout << "model content:\n" << std::endl;

  PrintModel(model);

  SaveAsJson(model, path + ".out");
  return 0;
}

