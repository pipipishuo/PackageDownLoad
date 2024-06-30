#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H




#include <Qurl>
#include<QObject>
class QFile;
class QNetworkReply;
class QNetworkAccessManager;



class DownLoadFile : public QObject
{
    Q_OBJECT

public:
    DownLoadFile(QObject *parent = nullptr);
    void startRequst(QUrl url);
    ~DownLoadFile();
    void download(QString url,bool isDe);
    int decompress_GzipFile(const std::string& gzipFilePath);
    bool getFinish(){return finish;};
    bool decompress;
    bool finish;
    QString getFileName(){return mFileName;}
    QString mFileName;
    QString filename;
    QStringList urls;
    void downloadDeb(QStringList urls);
signals:
    void sig_finish();
    void download_finish();
private:

    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *file;
    QUrl url;

private slots:
    void httpFinished(); //文件接收完成
    void httpReadyRead();//接收数据中
    void updateDataReadProgress(qint64,qint64);//进度条更新
       //发送请求
};
#endif // DOWNLOADFILE_H
