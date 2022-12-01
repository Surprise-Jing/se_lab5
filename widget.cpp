#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    if(c.DataFileExist())
    {
        this->hide();
        i.show();
    }
    else
    {
        QMessageBox::warning(this, "提示", "输入等价程序对文件./output/equal.csv不存在！");
    }
}

