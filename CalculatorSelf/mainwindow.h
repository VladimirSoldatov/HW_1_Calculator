#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QString get_last_sign(QString text);
    QString get_last_number(QString text, QString expr);
    QString get_result(QString currentResult);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString entered_signs;
    QString last_sign;
    QString result;
    QString signs;
};
#endif // MAINWINDOW_H
