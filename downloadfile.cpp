#include "downloadfile.h"

#include <QtNetwork>
#include <QSslSocket>
#include <QDebug>
#include <zlib.h>
#include<iostream>
#include <fstream>
//需要引入这两个
DownLoadFile::DownLoadFile(QObject *parent)
    : QObject(parent)

{

    //构建一个QNetworkAccessManager对象，通过这个对象实现各种请求
    manager = new QNetworkAccessManager(this);
    //未下载时先隐藏进度条
    finish=false;
}

DownLoadFile::~DownLoadFile()
{

}

void DownLoadFile::startRequst(QUrl url)
{

    //get请求，返回QNetworkReply类型，当有新数据到达时会触发readyRead信号
    reply = manager->get(QNetworkRequest(url));
    //触发readyRead信号时，处理新到的数据
    connect(reply,&QNetworkReply::readyRead,this,&DownLoadFile::httpReadyRead);

    //触发finished信号时，表示文件接收完成
    connect(reply,&QNetworkReply::finished,this,&DownLoadFile::httpFinished);
    //信号原型QNetworkReply::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)

    //bytesReceived表示发送的字节数，bytesTotal表示总字节数。
   // connect(reply,&QNetworkReply::downloadProgress,this,&DownLoadFile::updateDataReadProgress);
}
//接收响应数据
void DownLoadFile::httpReadyRead()
{
    //将接收的数据写入文件
    if(file) { file->write(reply->readAll()); }
}
void DownLoadFile::httpFinished()
{
    //文件接收完成清理资源

    if(file)
    {
        file->close();
        delete file;
        file  = 0;
    }
    //销毁QNetworkReply对象
    reply->deleteLater();
    reply= 0;
    finish=true;
    if(decompress){
        decompress_GzipFile(filename.toStdString());
        emit sig_finish();
    }
    if(urls.count()>0){
        QString url=urls.front();
        urls.pop_front();
        download(url,false);
    }else{
        emit download_finish();
    }
}
//更新进度条
void DownLoadFile::updateDataReadProgress(qint64 byteRead,qint64 totalBytes)
{

}
void DownLoadFile::download(QString urlStr,bool isDe)
{
    decompress=isDe;
    //获取URL
    url = urlStr;
    QFileInfo info(url.path());
    //解析URL文件名，以改文件名作为接收文件名

   filename=QCoreApplication::applicationDirPath()+"/deb/"+info.fileName();
    if(filename.isEmpty()) {
        //为空创建空文件
         filename = "index.html";
    }
    //创建QFile对象
    file = new QFile(filename);
    if(!file->open(QIODevice::WriteOnly))
    {
        delete  file;
        file = 0;
        return;
    }
    //发送请求
    startRequst(url);

}


int DownLoadFile::decompress_GzipFile(const std::string& gzipFilePath ) {
    gzFile gzFile = gzopen(gzipFilePath.c_str(), "rb");
    if (gzFile == nullptr) {
        return -1;
    }
    std::string dst_path =QCoreApplication::applicationDirPath().toStdString();
    if (access(dst_path.c_str(), F_OK))
    {
        //if (!boost::filesystem::create_directories(dst_path))
        {
            return -1;
        }
    }
    // 获取压缩文件的名称
    int pos = -1;
    std::string src_tarfileName;

    pos = gzipFilePath.rfind("/");
    src_tarfileName = gzipFilePath.substr(pos,gzipFilePath.length()-pos -3);  //-1是去除$1和.gz扩展名

    // cout<<"------ src_tarfileName = "<<src_tarfileName<<","<<src_tarfileName.length()<<endl;
    // 循环解压缩每个文件
    char buffer[16384];
    int uncompressedBytes;
    std::string currentFileName;
    if (currentFileName.empty()) {
        currentFileName = dst_path  + src_tarfileName;
        mFileName=QString::fromStdString(currentFileName);
    }

    QFile outFile(QString::fromStdString(currentFileName));
    if (!outFile.open(QIODevice::WriteOnly)) {
           return -1; // 无法打开文件
      }
    while ((uncompressedBytes = gzread(gzFile, buffer, sizeof(buffer))) > 0) {
        // 如果还没有设置当前文件的名称，则读取压缩文件的原始名称

        // cout<< "------currentFileName = "<<currentFileName<<endl;
        // 解压缩数据写入目标文件

        outFile.write(buffer, uncompressedBytes);

        // 如果已经读取完一个文件，则重置当前文件名称用于解压缩下一个文件
        if (gzeof(gzFile)) {
            currentFileName.clear();
        }
    }
    outFile.close();
    // 关闭压缩文件
    gzclose(gzFile);
    return 0;
}

void DownLoadFile::downloadDeb(QStringList urls)
{
    this->urls=urls;

}
