#include "gif.hpp"
#include <QThread>

GifRecorder::GifRecorder(QOpenGLWidget* openGLWidget)
    : m_openGLWidget(openGLWidget), m_gif(nullptr), m_error(0), m_frameCount(0) {}

GifRecorder::~GifRecorder() {
    if (m_gif) {
        EGifCloseFile(m_gif, &m_error);
    }
}

void GifRecorder::startRecord(const QString& filename) {
    m_gif = EGifOpenFileName(filename.toUtf8().constData(), false, &m_error);
    if (m_gif) {
        EGifSetGifVersion(m_gif, true);
        int width = m_openGLWidget->width();
        int height = m_openGLWidget->height();

        ColorMapObject* colorMap = getColorMap();
        EGifPutScreenDesc(m_gif, width, height, 8, 0, colorMap);

        while (recordFrame()) {
            QThread::msleep(FRAME_DELAY);
        }

        EGifCloseFile(m_gif, &m_error);
        m_gif = nullptr;
        QMessageBox::information(nullptr, "Уведомление", "Запись завершена");
    }
}

ColorMapObject* GifRecorder::getColorMap() {
    static ColorMapObject color;
    static GifColorType colors[256] = {0};
    for (int i = 0; i < 256; i++) {
        colors[i].Red = colors[i].Green = colors[i].Blue = (i * 255) / 255;
    }
    color.ColorCount = 256;
    color.Colors = colors;
    return &color;
}

bool GifRecorder::recordFrame() {
    QPixmap pixmap = m_openGLWidget->grab();
    QImage image = pixmap.toImage();
    recordFrameToGif(&image);

    m_frameCount++;
    return m_frameCount < DURATION / FRAME_DELAY;
}

void GifRecorder::initializeColorBuffers(const QImage* image, GifByteType** red,
                                         GifByteType** green, GifByteType** blue) {
    int width = image->width();
    int height = image->height();

    *red = (GifByteType*)malloc(width * height);
    *green = (GifByteType*)malloc(width * height);
    *blue = (GifByteType*)malloc(width * height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            QColor color = image->pixelColor(x, y);
            int bufferOffset = y * width + x;
            (*red)[bufferOffset] = color.red();
            (*green)[bufferOffset] = color.green();
            (*blue)[bufferOffset] = color.blue();
        }
    }
}

void GifRecorder::recordFrameToGif(const QImage* image) {
    int width = image->width();
    int height = image->height();

    GifByteType *red, *green, *blue;
    initializeColorBuffers(image, &red, &green, &blue);

    GifByteType* outputBuffer = (GifByteType*)malloc(width * height);
    ColorMapObject* colorMap = GifMakeMapObject(256, NULL);

    if (outputBuffer && colorMap) {
        int colorMapSize = 256;
        GifQuantizeBuffer(width, height, &colorMapSize, red, green, blue,
                          outputBuffer, colorMap->Colors);

        EGifPutImageDesc(m_gif, 0, 0, width, height, false, colorMap);
        EGifPutLine(m_gif, outputBuffer, width * height);

        free(outputBuffer);
        GifFreeMapObject(colorMap);
    }

    free(red);
    free(green);
    free(blue);
}
