#include "gif.hpp"
ColorMapObject* get_color_map() {
  static ColorMapObject color;
  static GifColorType colors[256] = {0};
  for (int i = 0; i < 256; i++) {
    colors[i].Red = colors[i].Green = colors[i].Blue = (i * 255) / 255;
  }
  color.ColorCount = 256;
  color.Colors = colors;
  return &color;
}

void start_record(const QString& filename, QOpenGLWidget* openGLWidget) {
  int error = 0;
  GifFileType* gif =
      EGifOpenFileName(filename.toUtf8().constData(), false, &error);
  if (gif) {
    EGifSetGifVersion(gif, true);
    int width = openGLWidget->width();
    int height = openGLWidget->height();

    ColorMapObject* color_map = get_color_map();
    EGifPutScreenDesc(gif, width, height, 8, 0, color_map);

    UserData* data = new UserData{gif, &error, 0, openGLWidget};
    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [data, timer]() {
      if (!record_screencast_loop(data)) {
        timer->stop();
        timer->deleteLater();
        delete data;
      }
    });
    timer->start(FRAME_DELAY);
  }
}

bool record_screencast_loop(UserData* data) {
  QPixmap pixmap = QPixmap::grabWidget(data->openGLWidget);
  QImage image = pixmap.toImage();
  record_frame(data->gif, &image);

  data->frame_count++;
  if (data->frame_count >= DURATION / FRAME_DELAY) {
    if (data->gif) {
      EGifCloseFile(data->gif, data->error);
      QMessageBox::information(nullptr, "Уведомление", "Запись завершена");
    }
    return false;
  }
  return true;
}

void initialize_color_buffers(const QImage* image, GifByteType** red,
                              GifByteType** green, GifByteType** blue) {
  int width = image->width();
  int height = image->height();

  *red = (GifByteType*)malloc(width * height);
  *green = (GifByteType*)malloc(width * height);
  *blue = (GifByteType*)malloc(width * height);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      QColor color = image->pixelColor(x, y);
      int buffer_offset = y * width + x;
      (*red)[buffer_offset] = color.red();
      (*green)[buffer_offset] = color.green();
      (*blue)[buffer_offset] = color.blue();
    }
  }
}

void record_frame(GifFileType* gif, const QImage* image) {
  int width = image->width();
  int height = image->height();

  GifByteType *red, *green, *blue;
  initialize_color_buffers(image, &red, &green, &blue);

  GifByteType* output_buffer = (GifByteType*)malloc(width * height);
  ColorMapObject* color_map = GifMakeMapObject(256, NULL);

  if (output_buffer && color_map) {
    int color_map_size = 256;
    GifQuantizeBuffer(width, height, &color_map_size, red, green, blue,
                      output_buffer, color_map->Colors);

    EGifPutImageDesc(gif, 0, 0, width, height, false, color_map);
    EGifPutLine(gif, output_buffer, width * height);

    free(output_buffer);
    GifFreeMapObject(color_map);
  }

  free(red);
  free(green);
  free(blue);
}