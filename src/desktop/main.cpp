#include "mainwindow.h"
#include "../obj/obj.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModelInfo *model_info = modelinfo();
    SettingInfo *setting_info = settinginfo();

    MainWindow w;
    w.show();

    return a.exec();
}
