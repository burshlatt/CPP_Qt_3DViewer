#ifndef CPP4_3DVIEWER_V2_0_3_SRC_MODEL_PARSER_PARSER_H_
#define CPP4_3DVIEWER_V2_0_3_SRC_MODEL_PARSER_PARSER_H_

#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef std::pair<int, int> Pairs;

namespace s21 {
class Parser {
 public:
  Parser();
  void Parse(const std::string& fileName);

  std::vector<int> get_facet() const noexcept { return facets_; }
  std::vector<double> get_vertex() const noexcept { return vertexes_; }
  int get_countF() const noexcept { return countPolygons_; }
  int get_countV() const noexcept { return countVertexes_; }

 private:
  std::vector<double> vertexes_;
  std::vector<int> facets_;
  int countVertexes_;
  int countPolygons_;
  double maxCoordinate_;

  bool ParseConditions(std::string& fileLine, char type);
  void ParseVertexes(std::string& fileLine);
  void ParseFacets(std::string& fileLine);
  int ParseEdges();
  std::vector<double> ParseLine(std::string& fileLine);
  void DelSpace(std::string& fileLine);
  void Clear();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_3_SRC_MODEL_PARSER_PARSER_H_
