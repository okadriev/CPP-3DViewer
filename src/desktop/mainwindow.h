#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QColorDialog>
#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QGuiApplication>
#include <QMainWindow>
#include <QPixmap>
#include <QScreen>
#include <QScrollBar>
#include <QWindow>

// #include <iostream>
#include <filesystem>
#include <string>

#include "../gif/gif.hpp"
#include "../obj/obj.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();


 private slots:
  void on_OpenFileButton_clicked();
  void on_SaveButton_clicked();
  void on_ScreenButton_clicked();
  void on_GifButton_clicked();
  void on_BackgroundColorButton_clicked();
  void on_VertexButton_clicked();
  void on_EdgesButton_clicked();
  void on_TransposeScrollBar_x_valueChanged(int value);
  void on_TransposeLineEdit_x_textChanged(const QString &text);
  void on_TransposeScrollBar_y_valueChanged(int value);
  void on_TransposeLineEdit_y_textChanged(const QString &text);
  void on_TransposeScrollBar_z_valueChanged(int value);
  void on_TransposeLineEdit_z_textChanged(const QString &text);
  void on_RotateScrollBar_x_valueChanged(int value);
  void on_RotateLineEdit_x_textChanged(const QString &text);
  void on_RotateScrollBar_y_valueChanged(int value);
  void on_RotateLineEdit_y_textChanged(const QString &text);
  void on_RotateScrollBar_z_valueChanged(int value);
  void on_RotateLineEdit_z_textChanged(const QString &text);
  void on_ScaleScrollBar_valueChanged(int value);
  void on_ScaleLineEdit_textChanged(const QString &text);
  void on_CancelEdgesButton_clicked(QAbstractButton *button);
  void on_ColorEdgesButton_clicked();
  void on_SizeEdgesScrollBar_valueChanged(int value);
  void on_EdgesLineEdit_textChanged(const QString &text);
  void on_CancelVertexButton_clicked(QAbstractButton *button);
  void on_ColorVertexButton_clicked();
  void on_SizeVertexScrollBar_valueChanged(int value);
  void on_VertexLineEdit_textChanged(const QString &text);
  void on_ParallelButton_clicked();
  void on_CenterButton_clicked();

 private:
  Ui::MainWindow *ui;
  ModelInfo *model_info;
  SettingInfo *setting_info;
  std::unique_ptr<std::string> temp;
  QOpenGLWidget *openGLWidget;

  void setupConnections();
  void MainWindow::updateOpenGLWidget();
  void updateInfoLabel();
  void printDebugInfo();  ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
};

typedef enum { I_ONE, I_TWO, I_THREE } IndexType;

#endif  // MAINWINDOW_H
