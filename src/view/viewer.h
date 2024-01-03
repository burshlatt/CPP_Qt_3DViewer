#ifndef CPP_QT_3DVIEWER_VIEW_VIEWER_H
#define CPP_QT_3DVIEWER_VIEW_VIEWER_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QScreen>
#include <QSettings>
#include <QTimer>
#include <memory>

#include "../lib/parser.h"
#include "opengl.h"
#include "qgifimage.h"

namespace Ui {
class Viewer;
}

namespace s21 {
class Viewer : public QMainWindow {
    Q_OBJECT

    public:
        explicit Viewer(QWidget *parent = nullptr);
        Viewer(Viewer &&) = delete;
        Viewer(const Viewer &) = delete;
        ~Viewer();

        void SaveGIF();
        void OpenFile();
        void CreateGIF();
        void LoadSettings();
        void SetModelType();
        void SetLineWidth();
        void SetLineColor();
        void SetMainColor();
        void LoadMaterial();
        void SaveSettings();
        void SetVertexType();
        void ResetSettings();
        void SetVertexColor();
        void SetVertexWidth();
        void SetShadingType();
        void ShowModelPanel();
        void Move(Action act);
        void Scale(Action act);
        void CreateScreenshot();
        void RotateX(int value);
        void RotateY(int value);
        void RotateZ(int value);
        void SetProjectionType();
        void SetEnableComponent(bool is_enable);
        void SetInfo(const QString &name, const QString &info);
        void SetImg(const Mtl &mtl, const QString &img_path, MapType map_type, int idx);

    private:
        Ui::Viewer *ui_;
        std::unique_ptr<Parser> parser_;

        OpenGL *ogl_;
        QTimer *timer_;
        QGifImage *frame_;
        QString gif_name_;

        int frame_count_{};
        int deg_x_{}, deg_y_{}, deg_z_{};
        int check_x_{}, check_y_{}, check_z_{};
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_VIEW_VIEWER_H
