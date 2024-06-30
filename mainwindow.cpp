#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"PackageParse.h"
#include"downloadfile.h"
#include<QDebug>
#include<QThread>
#include<QDir>
#include<QMessageBox>
#include"releaseparse.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CPUArchitercture=QSysInfo::currentCpuArchitecture();

    if(CPUArchitercture=="x86_64"){
        CPUArchitercture="amd64";
    }
    dl=new DownLoadFile;
    connect(dl,&DownLoadFile::sig_finish,this,&MainWindow::sltPackageDownloadFinish);

    connect(dl,&DownLoadFile::download_finish,this,&MainWindow::sltDebDownloadFinish);
    QString fileName=QApplication::applicationDirPath()+"/sources.list";
    QFile file(fileName);
    if(file.exists()){
        if(file.open(QIODevice::ReadOnly)){
            sourceList=file.readLine();
        }

    }else{
        file.open(QIODevice::WriteOnly);
    }
    qDebug()<<sourceList;

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

    p=new PackageGzParse;
    p->setFileName(dl->getFileName());
    p->process();
    DataManager::GetIns()->setDebName(debName);
    QStringList urlls=DataManager::GetIns()->getUrls();
    if(urlls.count()>1){

        dl->downloadDeb(urlls);
    }else{
        next++;
        if(next<urls.count()){
            dl->download(urls.at(next),true);
        }
    }

}


void MainWindow::on_pushButton_2_clicked(bool checked)
{
    if(sourceList.count()==0){
        QMessageBox::information(this,"","请配置软件源在sources.list文件中");
        return;
    }
    clearPackage();
    QStringList formatStr=sourceList.split(" ");
    QString uri_dis=formatStr.at(1)+"/dists/"+formatStr.at(2);
    DataManager::GetIns()->setUri(formatStr.at(1));
    for(int i=3;i<formatStr.count();i++){
        QString url=uri_dis+"/"+formatStr.at(i)+"/binary-"+CPUArchitercture+"/Packages.gz";
        urls.append(url);
    }
    next=0;
    dl->download(urls.at(next),true);
    debName=ui->lineEdit->text();
}


