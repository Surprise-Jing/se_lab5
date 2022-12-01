#include "confirm.h"

Confirm::Confirm()
{
    num = 0; test = 0;
}

Confirm::~Confirm()
{
    QVector<Pair>().swap(EqualPairs);
    QVector<Pair>().swap(InequalPairs);
    QVector<Pair>().swap(UncertainPairs);
}

bool Confirm::DataFileExist()
{
    QString filepath = "./output/equal.csv";
    QFile file(filepath);
    if(file.exists())
        return true;
    else
    {
        qDebug()<<"输入等价程序对文件不存在！";
        return false;
    }
}

void Confirm::ReadEqualData()
{
    QFile file("output/equal.csv");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;
    QString data;
    QStringList data_list;
    QTextStream in(&file);
    while(!in.atEnd())
    {
        data = in.readLine();
        data_list = data.split(",");
        EqualPairs.append({data_list[0], data_list[1], false});
    }
    num = EqualPairs.count();
    file.close();
}

void Confirm::WriteFile()
{
    QString dirpath = QDir::currentPath()+"/result";
    QDir dir(dirpath);
    if(!dir.exists())
    {
        dir.mkdir(dirpath);
        qDebug()<<"创建文件夹result";
    }
    QFile file1("result/equal.csv");
    file1.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!file1.isOpen()){
        qDebug()<<"112";
        return ;
    }
    QTextStream out1(&file1);
    for(int i = 0; i < EqualPairs.count(); i += 1)
    {
        out1 << EqualPairs[i].file1 << "," << EqualPairs[i].file2 << "\n";
    }
    file1.close();
    QFile file2("result/inequal.csv");
    file2.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!file2.isOpen())
        return ;
    QTextStream out2(&file2);
    for(int i = 0; i < InequalPairs.count(); i += 1)
    {
        out2 << InequalPairs[i].file1 << "," << InequalPairs[i].file2 << "\n";
    }
    file2.close();
    QFile file3("result/uncertain.csv");
    file3.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!file3.isOpen())
        return ;
    QTextStream out3(&file3);
    for(int i = 0; i < UncertainPairs.count(); i += 1)
    {
        out3 << UncertainPairs[i].file1 << "," << UncertainPairs[i].file2 << "\n";
    }
    file3.close();
}

int Confirm::ConfirmPair(QString file1, QString file2)
{
    if(file1 != "")
    {
        for(int i = 0; i < EqualPairs.count(); i += 1)
        {
            if(!EqualPairs[i].flag && (EqualPairs[i].file1 == file1 || EqualPairs[i].file2 == file2))
            {
                EqualPairs[i].flag = true;
                test += 1;
                return i;
            }
        }
    }
    srand(time(0));
    while(true)
    {
        int i = rand()%EqualPairs.count();
        if(!EqualPairs[i].flag)
        {
            EqualPairs[i].flag = true;
            test += 1;
            return i;
        }
    }
}

Pair Confirm::getPair(int index)
{
    return EqualPairs[index];
}

void Confirm::ChangeState(int index, Pair p, int state)
{
    if(index < EqualPairs.count())
        EqualPairs.removeAt(index);
    if(state == 1)
    {
        InequalPairs.append(p);
    }
    else if(state == 2)
    {
        UncertainPairs.append(p);
    }
    WriteFile();
}

bool Confirm::Finish()
{
    if(test > num/3)
        return true;
    return false;
}
