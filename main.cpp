#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <input_file> <k> <L>" << std::endl;
    return 1;
  }

  std::string file = argv[1];
  int k_val = std::stoi(argv[2]);
  int L_val = std::stoi(argv[3]);
  std::string text;
  std::string line;

  std::ifstream origFile(file);
  if (!origFile.is_open()) {
    std::cerr << "Sorry the file could not be opened" << std::endl;
    return 1;
  }

  while (std::getline(origFile, line)) {
    text += line;
  }

  origFile.close();

  RandWriter rWriter(text, k_val, L_val);


  std::cout << rWriter << std::endl;


  return 0;
}
