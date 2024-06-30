#ifndef RELEASEPARSE_H
#define RELEASEPARSE_H

#include<QString>
#include<QMap>

//好像没什么用
class ReleaseParse
{
public:
    ReleaseParse();
    void process();
    void parse(QString data);
    void setfileName(QString name){this->fileName=name;};
    QString fileName;
    QString CPUArchitercture;
    QMap<QString,QString> data;
};

#endif // RELEASEPARSE_H
