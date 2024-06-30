#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"PackageParse.h"
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
    PackageGzParse* p;
    DownLoadFile* dl;
    QString debName;
    void clearPackage();
    QStringList urls;
    QString sourceList;
    QString CPUArchitercture;
    int next=0;
public slots:
    void sltDebDownloadFinish();
    void sltPackageDownloadFinish();
private slots:
    void on_pushButton_2_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
