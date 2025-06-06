#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_10, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_12, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_13, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_14, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_15, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_16, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_17, SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));
    entered_signs = "0";
    last_sign = "";
    result = "0";
    signs = "[/+/-///*]";
}


MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::get_last_sign(QString text)
{
    QString::reverse_iterator  it = text.rbegin();
    return QString(*it);
}
QString MainWindow::get_last_number(QString text, QString expr)
{
    int last_index = text.lastIndexOf(QRegularExpression(expr));
    int length = text.length();
    int last = last_index == length ? 0 : last_index;
    return text.right(last);
}

QString MainWindow::get_result(QString entered_values)
{
    double res = 0;
    QString num;
    QString sign = "";
    double res_count = 0;
    for (int i = 0; i < entered_values.length();i++) {
        QString digit = QString(entered_values[i]);
        bool ok = false;
        digit.toInt(&ok, 10);
        if(!ok && digit != '.'){
            sign = digit;
            if(res_count == 0)
            res = QVariant(num).toReal();
            res_count++;
            num.clear();
        }
        else if(ok || digit == '.' )
        {
            num.append(digit);
        }

        if(i == entered_values.length()-1 || sign !="" || digit != ".")
        {
            if(sign == "+")
                res = res + QVariant(num).toReal();
            if(sign == "-")
                res = res - QVariant(num).toReal();
            if(sign == "*")
                res = res * (num == ""?1:QVariant(num).toReal());
            if(sign == "/")
                res = res / (num == ""?1:QVariant(num).toReal());
         }
        if(!ok && digit != "."){
            num.clear();

        }

    }
    entered_values = QVariant(res).toString();
    return entered_values;
}

void MainWindow::on_pushButton_clicked()
{
    QPushButton *q = reinterpret_cast<QPushButton*>(sender());
    QString value = q->text();
    value = value != ","?value:".";
    QString last_number = get_last_number(entered_signs, signs);
    QString last_sign = get_last_sign(entered_signs);
    if(last_number.contains(".") && value == ".")
    {
        return;
    }

    if(entered_signs == "0" && !signs.contains(value) && value != ".")
    {
        entered_signs = value;
    }
    else if(value == "=")
    {
     result = get_result(entered_signs);
    }
    else
    {
      if(value != "=")
        entered_signs.append(value);
    }

    qDebug() <<"Plain_result: " << entered_signs<<", Result: "<<result;
    ui->lcdNumber->display(result);
    ui->textBrowser->setText(entered_signs);
}

