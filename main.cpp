#include "mainwindow.h"

#include <QApplication>
#include"downloadfile.h"
int decompress_GzipFile(const std::string& gzipFilePath , const std::string& extractPath,bool first) ;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
