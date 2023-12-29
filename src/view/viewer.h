#ifndef CPP_QT_3DVIEWER_VIEW_VIEWER_H
#define CPP_QT_3DVIEWER_VIEW_VIEWER_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QScreen>
#include <QPixmap>
#include <QTimer>
#include <QLabel>

#include "opengl.h"

namespace Ui {
class Viewer;
}

namespace s21 {
class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  explicit Viewer(QWidget *parent = nullptr);
  Viewer(Viewer &&view) = delete;
  Viewer(const Viewer &view) = delete;
  ~Viewer();

  void LoadMaterial();
  void SetEnableComponent(bool is_enable) noexcept;
  void SetInfo(const QString& name, const QString& info);
  void SetImg(const Mtl& mtl, const QString& img_path, MapType map_type, int idx);

  void OpenFile();
  void MoveXL() noexcept;
  void MoveXR() noexcept;
  void MoveYD() noexcept;
  void MoveYU() noexcept;
  void MoveZC() noexcept;
  void MoveZF() noexcept;
  void ScaleMul() noexcept;
  void ScaleDiv() noexcept;
  void SetModelType() noexcept;
  void SetLineWidth() noexcept;
  void SetLineColor() noexcept;
  void SetMainColor() noexcept;
  void SetVertexType() noexcept;
  void ResetSettings() noexcept;
  void SetVertexColor() noexcept;
  void SetVertexWidth() noexcept;
  void SetShadingType() noexcept;
  void ShowModelPanel() noexcept;
  void CreateScreenshot() noexcept;
  void RotateX(int value) noexcept;
  void RotateY(int value) noexcept;
  void RotateZ(int value) noexcept;
  void SetProjectionType() noexcept;

 private:
  Ui::Viewer *ui_;

  int frame_count_{};
  int deg_x_{}, deg_y_{}, deg_z_{};
  int check_x_{}, check_y_{}, check_z_{};

  OpenGL *ogl_;
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_VIEW_VIEWER_H
