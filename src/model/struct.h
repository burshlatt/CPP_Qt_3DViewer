#ifndef CPP_QT_3DVIEWER_MODEL_STRUCT_H_
#define CPP_QT_3DVIEWER_MODEL_STRUCT_H_

#include <vector>

typedef struct View {
  double far;
  double near;
  int v_count;
  int e_count;
  double max_coord;
  std::vector<int> facets;
  std::vector<double> vertexes;
} Data;

enum Coord { kX, kY, kZ };

enum Action { kRotX, kRotY, kRotZ, kMoveX, kMoveY, kMoveZ, kScaleP, kScaleM };

#endif  // CPP_QT_3DVIEWER_MODEL_STRUCT_H_
