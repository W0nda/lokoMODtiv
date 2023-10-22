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

    connect(ui->quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(sendValue()));
}

void MainWindow::sendValue(){
    QString RTUreq = ui->RTUreq->text();
    QString error;
    checkSize(RTUreq, &error);
    checkRegisterAddr(RTUreq, &error);
    checkSlaveAddr(RTUreq, &error);
    if(error.length() == 0){
        RTUreq.remove(" ");
        QString sendedReq;
        //MEMENTO: mid(int position,int nbr_char)
        sendedReq.append(RTUreq.midRef(0,2)+" "); //slave
        sendedReq.append(RTUreq.midRef(2,2)+" "); //register
        sendedReq.append(RTUreq.midRef(4,2)+" "); //nbrBytes
        bool ok = true;
        //check to see if we can put "true" directly in toUint()
        unsigned int nbrBytes = RTUreq.midRef(4,2).toUInt(&ok,16);
        sendedReq.append(RTUreq.midRef(6,nbrBytes*2)+" "); //data
        sendedReq.append(RTUreq.midRef(nbrBytes*2+6,4));

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

