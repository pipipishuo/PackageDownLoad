#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"parse.h"
#include"downloadfile.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Parse* p;
    DownLoadFile* dl;
    QString debName;
    void clearPackage();
public slots:
    void sltDebDownloadFinish();
    void sltPackageDownloadFinish();
private slots:
    void on_pushButton_2_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
