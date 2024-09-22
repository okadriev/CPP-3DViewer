#pragma once

#include <gif_lib.h>
#include <QImage>
#include <QOpenGLWidget>
#include <QMessageBox>

#define FRAME_DELAY 100
#define DURATION 5000

class GifRecorder {
public:
    GifRecorder(QOpenGLWidget* openGLWidget);
    ~GifRecorder();

    void startRecord(const QString& filename);

private:
    QOpenGLWidget* m_openGLWidget;
    GifFileType* m_gif;
    int m_error;
    int m_frameCount;

    ColorMapObject* getColorMap();
    bool recordFrame();
    void initializeColorBuffers(const QImage* image, GifByteType** red,
                                GifByteType** green, GifByteType** blue);
    void recordFrameToGif(const QImage* image);
};
