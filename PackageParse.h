#ifndef PARSE_H
#define PARSE_H
#include<QString>
#include"datamanager.h"

class PackageGzParse
{
public:
    PackageGzParse();
    void process();
    void parseData(QString content);
    void match(QString content,QString reg,QString& package);
    QString fileName;
    void setFileName(QString fileName);
    ~PackageGzParse();
};

#endif // PARSE_H
