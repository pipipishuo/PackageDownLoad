#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include<QString>
#include<QList>
class PackageData{
public:
    QString Package;
    QString Architecture;
    QString  Version;
    QString  Priority;
    QString Section;
    QString Maintainer;
    QString Original_Maintainer;
    QString Installed_Size;
    QString Depends;
    QString Recommends;
    QString Suggests;
    QString Filename;
    QString Size;
    QString MD5sum;
    QString SHA1;
    QString SHA256;
    QString SHA512;
    QString Homepage;
    QString Description;
    QString cert_subject_ou;
    QString cert_subject_o;
    QString cert_subject_cn;
    QStringList getDepends();
};
class DataManager
{
public:
    DataManager();
    QMap<QString,PackageData> datas;
    QString debName;
    static DataManager* ins;
    static DataManager* GetIns();
    void addData(PackageData pd);
    QStringList getUrls();
    void setDebName(QString name){debName=name;};
    void setUri(QString uri){this->uri=uri;}
    QString uri;
    ~DataManager();
};

#endif // DATAMANAGER_H
