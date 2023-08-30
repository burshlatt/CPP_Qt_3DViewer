#ifndef CPP_QT_3DVIEWER_MODEL_PARSER_PARSER_H_
#define CPP_QT_3DVIEWER_MODEL_PARSER_PARSER_H_

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
  void ProcessLine(std::string line);
  void ParseFacet(std::string &line);
  void ParseVertex(std::string &line);
  void Parse(const std::string &path);
  void DelNum(std::string &line) const;
  void DelSpace(std::string &line) const;

 private:
  Data &data_;
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_MODEL_PARSER_PARSER_H_
