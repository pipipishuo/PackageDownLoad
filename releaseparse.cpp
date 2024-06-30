#include "releaseparse.h"
#include<QFile>
#include<QTextStream>
#include<QRegularExpression>
#include<QDebug>
#include <QSysInfo>
ReleaseParse::ReleaseParse()
{
    CPUArchitercture=QSysInfo::currentCpuArchitecture();

    if(CPUArchitercture=="x86_64"){
        CPUArchitercture="amd64";
    }
}

void ReleaseParse::process()
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream in(&file);
    bool flag=false;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(flag){
            parse(line);
        }
        if(line=="MD5Sum:"){
            flag=true;
        }
        if(line=="SHA256:"){
            break;
        }

    }
    return;
}

void ReleaseParse::parse(QString str)
{
    QRegularExpression re;
    re.setPattern("( *)(\\w*)( *)(\\w*)( *)(.*)");
    QRegularExpressionMatch match = re.match(str);
    if (match.hasMatch()) {
       QString url = match.captured(6);
       QString binary="binary-"+CPUArchitercture+"/Packages.gz";
       if(url.contains(binary)){
           QString com=url.split("/").at(0);

       }

    }


}
