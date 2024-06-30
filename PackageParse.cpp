#include "PackageParse.h"
#include"datamanager.h"
#include <QFile>
#include<QTextStream>
#include<QDebug>
#include <QRegularExpressionMatch>
PackageGzParse::PackageGzParse()
{

}

void PackageGzParse::process()
{

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream in(&file);
    QString sum;
    int count=0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(line.isEmpty()){
            parseData(sum);
            sum.clear();
        }else{
            sum=sum+line+"\n";
        }

    }
}

void PackageGzParse::parseData(QString content)
{
    struct PackageData pd;
    match(content,("(Package: )(.*)"),pd.Package);
    match(content,("(Architecture: )(.*)"),pd.Architecture);
    match(content,("(Version: )(.*)"),pd.Version);
    match(content,("(Priority: )(.*)"),pd.Priority);
    match(content,("(Section: )(.*)"),pd.Section);
    match(content,("(Maintainer: )(.*)"),pd.Maintainer);
    match(content,("(Original-Maintainer: )(.*)"),pd.Original_Maintainer);
    match(content,("(Installed-Size: )(.*)"),pd.Installed_Size);
    match(content,("(Depends: )(.*)"),pd.Depends);
    match(content,("(Recommends: )(.*)"),pd.Recommends);
    match(content,("(Suggests: )(.*)"),pd.Suggests);
    match(content,("(Filename: )(.*)"),pd.Filename);
    match(content,("(Size: )(.*)"),pd.Size);
    match(content,("(MD5sum: )(.*)"),pd.MD5sum);
    match(content,("(SHA1: )(.*)"),pd.SHA1);
    match(content,("(SHA256: )(.*)"),pd.SHA256);
    match(content,("(SHA512: )(.*)"),pd.SHA512);
    match(content,("(Homepage: )(.*)"),pd.Homepage);
    match(content,("(cert_subject_ou: )(.*)"),pd.cert_subject_ou);
    match(content,("(cert_subject_o: )(.*)"),pd.cert_subject_o);
    match(content,("(cert_subject_cn: )(.*)"),pd.cert_subject_cn);
    //Description 这个用正则好像不太好处理 暂不处理
    DataManager::GetIns()->addData(pd);
    //qDebug()<<pd.Package;
}

void PackageGzParse::match(QString content,QString reg, QString& field)
{
    QRegularExpression re;
    re.setPattern(reg);
    QRegularExpressionMatch match = re.match(content);
    if (match.hasMatch()) {
        field = match.captured(2);

    }
}

void PackageGzParse::setFileName(QString fileName)
{
    this->fileName=fileName;
}

PackageGzParse::~PackageGzParse()
{

}

