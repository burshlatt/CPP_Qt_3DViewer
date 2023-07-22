#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QGuiApplication>
#include <QImage>
#include <QPainter>
#include <QScreen>
#include <QUrl>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QPushButton>

#include "myopengl.h"
#include "../model/model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

    public:
        Widget(QWidget *parent = nullptr);
        ~Widget();

    public slots:
        void on_openFile_clicked();
        void on_show_panel_clicked();

    private:
        Ui::Widget *ui;
        MyOpenGL *myogl;
        s21::model model_;
};

#endif  // WIDGET_H
