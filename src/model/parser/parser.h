#ifndef SRC_MODEL_PARSER_PARSER_H_
#define SRC_MODEL_PARSER_PARSER_H_

#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <string_view>

#include "../struct.h"

namespace s21 {
  class Parser {
    public:
      Parser();
      ~Parser();

      const Data& get_data() const noexcept;

      void Clear() noexcept;
      void ProcessLine(std::string line) noexcept;
      void ParseFacet(std::string &line) noexcept;
      void ParseVertex(std::string &line) noexcept;
      void Parse(const std::string &path) noexcept;
      void DelNum(std::string &line) const noexcept;
      void DelSpace(std::string &line) const noexcept;

    private:
      Data data_;
  };
}

#endif // SRC_MODEL_PARSER_PARSER_H_
