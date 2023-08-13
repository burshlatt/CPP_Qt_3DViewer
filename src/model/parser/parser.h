#ifndef SRC_MODEL_PARSER_PARSER_H_
#define SRC_MODEL_PARSER_PARSER_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../struct.h"

namespace s21 {
class Parser {
 public:
  Parser(Data &data);
  ~Parser() = default;

  void Clear() noexcept;
  void SetPerspectiveData() noexcept;
  void ProcessLine(std::string line) noexcept;
  void ParseFacet(std::string &line) noexcept;
  void ParseVertex(std::string &line) noexcept;
  void Parse(const std::string &path) noexcept;
  void DelNum(std::string &line) const noexcept;
  void DelSpace(std::string &line) const noexcept;

 private:
  Data &data_;
};
}  // namespace s21

#endif  // SRC_MODEL_PARSER_PARSER_H_
