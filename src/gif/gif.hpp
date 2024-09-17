#pragma once

#include <gif_lib.h>

#include <QBuffer>
#include <QImage>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QTimer>

#define FRAME_DELAY 100
#define DURATION 5000

struct UserData {
  GifFileType* gif;
  int* error;
  int frame_count;
  QOpenGLWidget* openGLWidget;
};

ColorMapObject* get_color_map();
void start_record(const QString& filename, QOpenGLWidget* openGLWidget);
bool record_screencast_loop(UserData* data);
void initialize_color_buffers(const QImage* image, GifByteType** red,
                              GifByteType** green, GifByteType** blue);
void record_frame(GifFileType* gif, const QImage* image);