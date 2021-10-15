#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushRead_clicked();
    void slotTimerAlarm();
    void on_pushStop_clicked();

private:
    Ui::MainWindow *ui;

     QTimer *timer = new QTimer(this);
};
#endif // MAINWINDOW_H
