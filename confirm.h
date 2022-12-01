#ifndef CONFIRM_H
#define CONFIRM_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <ctime>

struct Pair
{
    QString file1;
    QString file2;
    bool flag; //是否被人工确认过
};

class Confirm
{
public:
    Confirm();
    ~Confirm();

    bool DataFileExist();
    void ReadEqualData();

    void WriteFile();
    int ConfirmPair(QString file1, QString file2); //自动生成等待判断的等价对，返回需要修改的等价对的下标
    Pair getPair(int index);
    void ChangeState(int index, Pair p, int state); //state=1表示不等价，2表示存疑
    bool Finish();


private:
    QVector<Pair> EqualPairs;
    QVector<Pair> InequalPairs;
    QVector<Pair> UncertainPairs;
    int num;
    int test;
};

#endif // CONFIRM_H
