#ifndef SRC_MODEL_STRUCT_H_
#define SRC_MODEL_STRUCT_H_

#include <vector>

typedef struct View {
  int v_count_;
  int f_count_;
  int t_count_;
  double far_;
  double near_;
  double max_coord_;
  std::vector<int> facets_;
  std::vector<double> vertexes_;
} Data;

enum Coord { X, Y, Z };

enum Action { RotX, RotY, RotZ, MoveX, MoveY, MoveZ, ScaleP, ScaleM };

#endif  // SRC_MODEL_STRUCT_H_
