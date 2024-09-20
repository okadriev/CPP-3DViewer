#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setWindowTitle("3D Viewer");
  ui->MainStackedWidget->setCurrentIndex(I_ONE);

  setupOpenGL();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_OpenFileButton_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "",
                                                  "OBJ files (*.obj)");
  controller.update_model_info(fileName);
  updateInfoLabel();
}

void MainWindow::on_SaveButton_clicked() { controller.update_setting_info(true); }

void MainWindow::on_ScreenButton_clicked() {
  QScreen *screen = QGuiApplication::primaryScreen();
  if (const QWindow *window = windowHandle()) screen = window->screen();
  if (screen) {
    QPixmap pixmap = screen->grabWindow(
        winId(), ui->openGLWidget->x(), ui->openGLWidget->y(),
        ui->openGLWidget->width(), ui->openGLWidget->height());

    QString defaultName =
        QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".png";
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Сохранить скриншот"), QDir::homePath() + "/" + defaultName,
        tr("Изображения (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty()) {
      pixmap.save(fileName);
    }
  }
}

void MainWindow::on_GifButton_clicked() {
  QString filename =
      QFileDialog::getSaveFileName(this, "Save GIF", "", "GIF Files (*.gif)");
  controller.gif_start(ui->openGLWidget, filename);
}

void MainWindow::on_BackgroundColorButton_clicked() {
  QColor color = QColorDialog::getColor();
  controller.update_setting_info(color);
}

void MainWindow::on_VertexButton_clicked() {
  ui->MainStackedWidget->setCurrentIndex(I_THREE);
}

void MainWindow::on_EdgesButton_clicked() {
  ui->MainStackedWidget->setCurrentIndex(I_TWO);
}

void MainWindow::on_TransposeScrollBar_x_valueChanged(int value) {
  ui->TransposeLineEdit_x->setText(QString::number(value));
  controller.update_model_info('t', 'x', value);
  updateInfoLabel();
}

void MainWindow::on_TransposeScrollBar_y_valueChanged(int value) {
  ui->TransposeLineEdit_y->setText(QString::number(value));
  controller.update_model_info('t', 'y', value);
  updateInfoLabel();
}

void MainWindow::on_TransposeScrollBar_z_valueChanged(int value) {
  ui->TransposeLineEdit_z->setText(QString::number(value));
  controller.update_model_info('t', 'z', value);
  updateInfoLabel();
}

void MainWindow::on_TransposeLineEdit_x_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->TransposeScrollBar_x->setValue(value);
    controller.update_model_info('t', 'x', value);
    updateInfoLabel();
  }
}

void MainWindow::on_TransposeLineEdit_y_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->TransposeScrollBar_y->setValue(value);
    controller.update_model_info('t', 'y', value);
    updateInfoLabel();
  }
}

void MainWindow::on_TransposeLineEdit_z_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->TransposeScrollBar_z->setValue(value);
    controller.update_model_info('t', 'z', value);
    updateInfoLabel();
  }
}

void MainWindow::on_RotateScrollBar_x_valueChanged(int value) {
  ui->RotateLineEdit_x->setText(QString::number(value));
  controller.update_model_info('z', 'x', value);
  updateInfoLabel();
}

void MainWindow::on_RotateScrollBar_y_valueChanged(int value) {
  ui->RotateLineEdit_y->setText(QString::number(value));
  controller.update_model_info('z', 'y', value);
  updateInfoLabel();
}

void MainWindow::on_RotateScrollBar_z_valueChanged(int value) {
  ui->RotateLineEdit_z->setText(QString::number(value));
  controller.update_model_info('z', 'z', value);
  updateInfoLabel();
}

void MainWindow::on_RotateLineEdit_x_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->RotateScrollBar_x->setValue(value);
    controller.update_model_info('z', 'x', value);
    updateInfoLabel();
  }
}

void MainWindow::on_RotateLineEdit_y_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->RotateScrollBar_y->setValue(value);
    controller.update_model_info('z', 'y', value);
    updateInfoLabel();
  }
}

void MainWindow::on_RotateLineEdit_z_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->RotateScrollBar_z->setValue(value);
    controller.update_model_info('z', 'z', value);
    updateInfoLabel();
  }
}

void MainWindow::on_ScaleScrollBar_valueChanged(int value) {
  ui->ScaleLineEdit->setText(QString::number(value));
  controller.update_model_info(int scale);
  updateInfoLabel();
}

void MainWindow::on_ScaleLineEdit_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->ScaleScrollBar->setValue(value);
    controller.update_model_info(int scale);
    updateInfoLabel();
  }
}

void MainWindow::on_CancelEdgesButton_clicked(QAbstractButton *button) {
  controller.controller.update_model_info(
      ui->CancelEdgesButton->standardButton(button) == QDialogButtonBox::Ok,
      ui->SolidEdgesRadioButton->isChecked(), temp,
      ui->SizeEdgesScrollBar->value());
  updateInfoLabel();
  ui->MainStackedWidget->setCurrentIndex(I_ONE);
}

void MainWindow::on_ColorEdgesButton_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    QString colorStr = color.name();
    ui->EdgesLineEdit->setText(colorStr);
    temp = std::make_unique<std::string>(colorStr.toStdString());
  }
}

void MainWindow::on_SizeEdgesScrollBar_valueChanged(int value) {
  ui->EdgesLineEdit->setText(QString::number(value));
}

void MainWindow::on_EdgesLineEdit_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->SizeEdgesScrollBar->setValue(value);
  }
}

void MainWindow::on_CancelVertexButton_clicked(QAbstractButton *button) {
  controller.controller.update_model_info(
      ui->CancelVertexButton->standardButton(button) == QDialogButtonBox::Ok,
      ui->NoneVertexRadioButton->isChecked(),
      ui->CercleVertexRadioButton->isChecked(),
      ui->SquareVertexRadioButton->isChecked(), temp,
      ui->SizeVertexScrollBar->value());
  updateInfoLabel();
  ui->MainStackedWidget->setCurrentIndex(I_ONE);
}

void MainWindow::on_ColorVertexButton_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    QString colorStr = color.name();
    ui->VertexLineEdit->setText(colorStr);
    temp = std::make_unique<std::string>(colorStr.toStdString());
  }
}

void MainWindow::on_SizeVertexScrollBar_valueChanged(int value) {
  ui->VertexLineEdit->setText(QString::number(value));
}

void MainWindow::on_VertexLineEdit_textChanged(const QString &text) {
  bool ok;
  int value = text.toInt(&ok);
  if (ok && value >= 0 && value <= 100) {
    ui->SizeVertexScrollBar->setValue(value);
  }
}

void MainWindow::on_ParallelButton_clicked() {
  controller.controller.update_model_info(V_PARALLEL);
  updateInfoLabel();
}

void MainWindow::on_CenterButton_clicked() {
  controller.controller.update_model_info(V_CENTER);
  updateInfoLabel();
}

void MainWindow::updateOpenGLWidget() {
  qDebug() << "updateOpenGLWidget1";
  openGLWidget->update();
  qDebug() << "updateOpenGLWidget2";
}

void MainWindow::updateInfoLabel() {
  QString info;
  info += QString("Файл: %1\n")
              .arg(model_info->filename ? [](const std::string &path) {
                std::filesystem::path filepath(path);
                return QString::fromStdString(filepath.filename().string());
              }(*model_info->filename)
                                        : "Не выбран");

  info += QString("Вершины: %1\n").arg(model_info->num_vertices);
  info += QString("Рёбра: %1\n\n").arg(model_info->num_edges);
  info += QString("Масштаб: %1\n").arg(model_info->scale);
  info += QString("Смещение: (%1, %2, %3)\n")
              .arg(model_info->trans_x)
              .arg(model_info->trans_y)
              .arg(model_info->trans_z);
  info += QString("Поворот: (%1, %2, %3)\n\n")
              .arg(model_info->rotate_x)
              .arg(model_info->rotate_y)
              .arg(model_info->rotate_z);
  info +=
      QString("Тип проекции: %1\n\n")
          .arg(!setting_info->projection_type ? "Параллельная" : "Центральная");

  info += QString("Тип рёбер: %1\n")
              .arg(!setting_info->edges_type ? "Сплошные" : "Пунктирные");
  info += QString("Толщина рёбер: %1\n\n").arg(setting_info->edge_thickness);

  info += QString("Тип вершин: %1\n")
              .arg(!setting_info->vertex_type            ? "Нет"
                   : setting_info->vertex_type == CERCLE ? "Круг"
                                                         : "Квадрат");
  info += QString("Размер вершин: %1\n").arg(setting_info->vertex_size);

  ui->InfoLabel->setText(info);
}

void MainWindow::setupConnections() {
  connect(ui->BackgroundColorButton, &QPushButton::clicked, this,
          &MainWindow::on_BackgroundColorButton_clicked);
  connect(ui->OpenFileButton, &QPushButton::clicked, this,
          &MainWindow::on_OpenFileButton_clicked);
  connect(ui->SaveButton, &QPushButton::clicked, this,
          &MainWindow::on_SaveButton_clicked);
  connect(ui->ScreenButton, &QPushButton::clicked, this,
          &MainWindow::on_ScreenButton_clicked);
  connect(ui->GifButton, &QPushButton::clicked, this,
          &MainWindow::on_GifButton_clicked);
  connect(ui->VertexButton, &QPushButton::clicked, this,
          &MainWindow::on_VertexButton_clicked);
  connect(ui->EdgesButton, &QPushButton::clicked, this,
          &MainWindow::on_EdgesButton_clicked);

  connect(ui->TransposeScrollBar_x, &QScrollBar::valueChanged, this,
          &MainWindow::on_TransposeScrollBar_x_valueChanged);
  connect(ui->TransposeLineEdit_x, &QLineEdit::textChanged, this,
          &MainWindow::on_TransposeLineEdit_x_textChanged);
  connect(ui->TransposeScrollBar_y, &QScrollBar::valueChanged, this,
          &MainWindow::on_TransposeScrollBar_y_valueChanged);
  connect(ui->TransposeLineEdit_y, &QLineEdit::textChanged, this,
          &MainWindow::on_TransposeLineEdit_y_textChanged);
  connect(ui->TransposeScrollBar_z, &QScrollBar::valueChanged, this,
          &MainWindow::on_TransposeScrollBar_z_valueChanged);
  connect(ui->TransposeLineEdit_z, &QLineEdit::textChanged, this,
          &MainWindow::on_TransposeLineEdit_z_textChanged);

  connect(ui->RotateScrollBar_x, &QScrollBar::valueChanged, this,
          &MainWindow::on_RotateScrollBar_x_valueChanged);
  connect(ui->RotateLineEdit_x, &QLineEdit::textChanged, this,
          &MainWindow::on_RotateLineEdit_x_textChanged);
  connect(ui->RotateScrollBar_y, &QScrollBar::valueChanged, this,
          &MainWindow::on_RotateScrollBar_y_valueChanged);
  connect(ui->RotateLineEdit_y, &QLineEdit::textChanged, this,
          &MainWindow::on_RotateLineEdit_y_textChanged);
  connect(ui->RotateScrollBar_z, &QScrollBar::valueChanged, this,
          &MainWindow::on_RotateScrollBar_z_valueChanged);
  connect(ui->RotateLineEdit_z, &QLineEdit::textChanged, this,
          &MainWindow::on_RotateLineEdit_z_textChanged);

  connect(ui->ScaleScrollBar, &QScrollBar::valueChanged, this,
          &MainWindow::on_ScaleScrollBar_valueChanged);
  connect(ui->ScaleLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::on_ScaleLineEdit_textChanged);

  connect(ui->CancelEdgesButton, &QDialogButtonBox::clicked, this,
          &MainWindow::on_CancelEdgesButton_clicked);
  connect(ui->ColorEdgesButton, &QPushButton::clicked, this,
          &MainWindow::on_ColorEdgesButton_clicked);
  connect(ui->SizeEdgesScrollBar, &QScrollBar::valueChanged, this,
          &MainWindow::on_SizeEdgesScrollBar_valueChanged);
  connect(ui->EdgesLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::on_EdgesLineEdit_textChanged);

  connect(ui->CancelVertexButton, &QDialogButtonBox::clicked, this,
          &MainWindow::on_CancelVertexButton_clicked);
  connect(ui->ColorVertexButton, &QPushButton::clicked, this,
          &MainWindow::on_ColorVertexButton_clicked);
  connect(ui->SizeVertexScrollBar, &QScrollBar::valueChanged, this,
          &MainWindow::on_SizeVertexScrollBar_valueChanged);
  connect(ui->VertexLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::on_VertexLineEdit_textChanged);

  connect(ui->ParallelButton, &QPushButton::clicked, this,
          &MainWindow::on_ParallelButton_clicked);
  connect(ui->CenterButton, &QPushButton::clicked, this,
          &MainWindow::on_CenterButton_clicked);
}

void MainWindow::printDebugInfo() {
  qDebug() << "ModelInfo:";
  qDebug() << "  filename:"
           << (model_info->filename ? model_info->filename->c_str()
                                    : "nullptr");
  qDebug() << "  num_vertices:" << model_info->num_vertices;
  qDebug() << "  num_edges:" << model_info->num_edges;
  qDebug() << "  trans_x:" << model_info->trans_x;
  qDebug() << "  trans_y:" << model_info->trans_y;
  qDebug() << "  trans_z:" << model_info->trans_z;
  qDebug() << "  rotate_x:" << model_info->rotate_x;
  qDebug() << "  rotate_y:" << model_info->rotate_y;
  qDebug() << "  rotate_z:" << model_info->rotate_z;
  qDebug() << "  scale:" << model_info->scale;

  qDebug() << "SettingInfo:";
  qDebug() << "  projection_type:" << setting_info->projection_type;
  qDebug() << "  edges_type:" << setting_info->edges_type;
  qDebug() << "  edge_color:"
           << (setting_info->edge_color ? setting_info->edge_color->c_str()
                                        : "nullptr");
  qDebug() << "  edge_thickness:" << setting_info->edge_thickness;
  qDebug() << "  background_color:"
           << (setting_info->background_color
                   ? setting_info->background_color->c_str()
                   : "nullptr");
  qDebug() << "  vertex_type:" << setting_info->vertex_type;
  qDebug() << "  vertex_color:"
           << (setting_info->vertex_color ? setting_info->vertex_color->c_str()
                                          : "nullptr");
  qDebug() << "  vertex_size:" << setting_info->vertex_size;
}

void MainWindow::setupOpenGL() {
  openGLWidget = ui->openGLWidget;

  if (openGLWidget) {
    m_renderer = new MyOpenGLRenderer(openGLWidget, this);
    connect(openGLWidget, &QOpenGLWidget::aboutToCompose, m_renderer,
            &MyOpenGLRenderer::initializeGL);
    connect(openGLWidget, &QOpenGLWidget::frameSwapped, m_renderer,
            &MyOpenGLRenderer::paintGL);
    // connect(openGLWidget, &QOpenGLWidget::resized, m_renderer,
    //         &MyOpenGLRenderer::resizeGL);
  }
}