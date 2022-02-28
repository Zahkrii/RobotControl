#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialogsettings.h"
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>

QString hostIP;
quint16 hostPort;
QTcpSocket *socket;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonsEnabled()
{
    ui->action1Button->setEnabled(true);
    ui->action2Button->setEnabled(true);
    ui->action3Button->setEnabled(true);
    ui->upButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->standButton->setEnabled(true);
}

void MainWindow::on_SettingsButton_clicked()
{
    DialogSettings *dialog = new DialogSettings(this);
    int result = dialog->exec();
    if(result == QDialog::Accepted)
    {
        hostIP = dialog->HostIP();
        hostPort = dialog->HostPort();
        ui->connectButton->setEnabled(true);
    }
    delete dialog;
}

void MainWindow::on_connectButton_clicked()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(hostIP,hostPort);
    socket->waitForConnected(5000);
    if(socket->state() == QAbstractSocket::ConnectedState)
        setButtonsEnabled();
    else
        QMessageBox::warning(this,"Error","Connect Failed!");
}

void MainWindow::on_standButton_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("p",1);
}

void MainWindow::on_upButton_pressed()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("w",1);
}

void MainWindow::on_upButton_released()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("t",1);
}

void MainWindow::on_rightButton_pressed()
{
}

void MainWindow::on_upButton_clicked()
{
}

void MainWindow::on_downButton_clicked()
{
}

void MainWindow::on_rightButton_released()
{
}

void MainWindow::on_downButton_pressed()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("s",1);
}

void MainWindow::on_downButton_released()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("g",1);
}

void MainWindow::on_leftButton_pressed()
{
}

void MainWindow::on_leftButton_released()
{
}

void MainWindow::on_action1Button_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("1",1);
}

void MainWindow::on_action2Button_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("2",1);
}

void MainWindow::on_action3Button_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("3",1);
}

void MainWindow::on_rightButton_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("d",1);
}


void MainWindow::on_leftButton_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("a",1);
}


void MainWindow::on_pushButton_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("4",1);
}


void MainWindow::on_pushButton_2_clicked()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->write("5",1);
}

