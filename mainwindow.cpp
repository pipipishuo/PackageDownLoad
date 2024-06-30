#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"parse.h"
#include"downloadfile.h"
#include<QDebug>
#include<QThread>
#include<QDir>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dl=new DownLoadFile;
    connect(dl,&DownLoadFile::sig_finish,this,&MainWindow::sltPackageDownloadFinish);

    connect(dl,&DownLoadFile::download_finish,this,&MainWindow::sltDebDownloadFinish);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearPackage()
{
   QString dirPath=QApplication::applicationDirPath()+"/deb";

   QDir folder(dirPath);
   if (!folder.exists())
   {
       folder.mkdir(dirPath);
       return;
   }

   QStringList files = folder.entryList(QDir::Files);
   for (const QString& file : files)
   {
       QString filePath = folder.filePath(file);
       QFile::remove(filePath);
   }
}

void MainWindow::sltDebDownloadFinish()
{
    QMessageBox::information(this,"","下载完成");
}

void MainWindow::sltPackageDownloadFinish()
{

    p=new Parse;
    p->setFileName(dl->getFileName());
    p->process();
    DataManager::GetIns()->setDebName(debName);
    QStringList urls=DataManager::GetIns()->getUrls();
    dl->downloadDeb(urls);
}


void MainWindow::on_pushButton_2_clicked(bool checked)
{
     clearPackage();
     dl->download("http://archive.kylinos.cn/kylin/KYLIN-ALL/dists/10.0/main/binary-amd64/Packages.gz",true);
     debName=ui->lineEdit->text();
}
