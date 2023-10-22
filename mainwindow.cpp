#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "useful_functions.h"

#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->master->setRowCount(10);
    ui->master->setColumnCount(1);
    ui->master->horizontalHeader()->setStretchLastSection(true);
    //adapte la largeur du tableau à la largeur du widget

    ui->slave1->setRowCount(10);
    ui->slave1->setColumnCount(1);
    ui->slave1->horizontalHeader()->setStretchLastSection(true);
    ui->slave1->setHorizontalHeaderLabels(QStringList("Slave 1"));

    ui->slave2->setRowCount(10);
    ui->slave2->setColumnCount(1);
    ui->slave2->horizontalHeader()->setStretchLastSection(true);
    ui->slave2->setHorizontalHeaderLabels(QStringList("Slave 2"));

    slaveTab[0] = ui->slave1;
    slaveTab[1] = ui->slave2;

    connect(ui->quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(sendValue()));
}

void MainWindow::sendValue(){
    QString error;
    checkRegisterAddr(ui->RTUregLineEdit->text(), &error);
    checkSlaveAddr(ui->RTUslaveLineEdit->text(), &error);
    if(error.length() == 0){
        QString size;
        returnReqSize(ui->RTUvalueLineEdit->text(),&size,&error);
        QString sendedReq;
        sendedReq.append(ui->RTUslaveLineEdit->text()+" ");
        sendedReq.append(ui->RTUregLineEdit->text()+" ");
        sendedReq.append(size+" ");
        sendedReq.append(ui->RTUvalueLineEdit->text()+" ");
        //CRC coming soon
        ui->labelReq->setText(sendedReq);
    }
    else{
        ui->labelReq->setText(error);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

