#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <vector>
#include <string>
#include <iostream>

typedef struct View {
  int v_count_;
  int f_count_;
  double max_coord_;
  std::vector<int> facets_;
  std::vector<double> vertexes_;
} Data;

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
      const long& GetSize(FILE *file) const noexcept;

    private:
      Data data_;
  };
}

#endif // SRC_MODEL_PARSER_H_
