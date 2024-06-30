#ifndef PARSE_H
#define PARSE_H
#include<QString>
#include"datamanager.h"

class Parse
{
public:
    Parse();
    void process();
    void parseData(QString content);
    void match(QString content,QString reg,QString& package);
    QString fileName;
    void setFileName(QString fileName);
    ~Parse();
};

#endif // PARSE_H
