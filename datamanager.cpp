#include "datamanager.h"
#include<QDebug>
DataManager * DataManager::ins=NULL;
DataManager::DataManager()
{

}

DataManager *DataManager::GetIns()
{
    if(ins==NULL){
        ins=new DataManager;
    }
    return ins;
}

void DataManager::addData(PackageData pd)
{
    if(datas.contains(pd.Package)){
        return;
    }
    datas.insert(pd.Package,pd);
}

QStringList DataManager::getUrls()
{
    QStringList debNames;
    QStringList urls;
    QList<QString>debsQueue;
    debsQueue.append(debName);
    //层次遍历即可
    while(!debsQueue.isEmpty()){
        QString name=debsQueue.front();
        QString origin=name;
        if(name.contains(" (")){
            int index=name.indexOf(" (");
            name=name.mid(0,index);
        }
        if(!name.isEmpty()){
            debNames.append(name);
        }

        debsQueue.pop_front();

        if(!datas.contains(name)){
            qDebug()<<"not have package："<<name;
            continue;
        }
        PackageData pk=datas.value(name);
        QStringList depends=pk.getDepends();
        for(int i=0;i<depends.count();i++){
            QString debName=depends.at(i);
            if(!debNames.contains(debName)){
                debsQueue.append(debName);
            }

        }
    }
    debNames=debNames.toSet().toList();

    for(int i=0;i<debNames.count();i++){
        QString name=debNames.at(i);
        PackageData pk=datas.value(name);
        QString url=uri+"/"+pk.Filename;

        urls.append(url);
    }
    return urls;
}

DataManager::~DataManager()
{

}


QStringList PackageData::getDepends()
{
    QStringList ls=Depends.split(", ");
    return ls;
}
