#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->finger1->setMaximum(1023);
    ui->finger1->setValue(0);
    ui->finger2->setMaximum(1023);
    ui->finger2->setValue(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotTimerAlarm()
{
    QSerialPort serialPort;
    //QByteArray data;
    QString data;

    serialPort.setPortName(this->ui->inputPort->text());
    serialPort.setBaudRate(QSerialPort::Baud9600);

    if (!serialPort.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
        return;
    }

    serialPort.write("a");
    serialPort.waitForBytesWritten();

    while (serialPort.waitForReadyRead(10)) {
        data += serialPort.readAll();

    }
    int buf[2];
    int itera = 0, iterb = 0;

    int s = data.indexOf("s");
    int e = data.indexOf("e");
    if((s!=-1)&&(e!=-1)&&(s<e))
    {
        qDebug()<<"data = "<<data;

        for(int i = 0;i<2;i++)
        {
            int b = data.indexOf("b", iterb);
            int a = data.indexOf("a", itera);
            qDebug()<<"i = "<<i<<" b = "<<b<<" a = "<<a;

            buf[i] = (data.mid(b + 1, a-b - 1)).toInt();
            itera = a + 1;
            iterb = b + 1;
        }

    }

    ui->outputText->append("finger1 = "+QString::number(buf[0]));
    ui->finger1->setValue(buf[0]);

    ui->outputText->append("finger2 = "+QString::number(buf[1]));
    ui->finger2->setValue(buf[1]);
    ui->outputText->append("------------------------------------");
    serialPort.close();
}

void MainWindow::on_pushRead_clicked()
{
    timer->start(50);//change speed

}
