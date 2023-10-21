#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    RTUreq.remove(" ");
    QString sendedReq;
    //MEMENTO: mid(int position,int nbr_char)
    sendedReq.append(RTUreq.mid(0,2)+" "); //slave
    sendedReq.append(RTUreq.mid(2,2)+" "); //register
    sendedReq.append(RTUreq.mid(4,2)+" "); //nbrBytes
    bool ok = true;
    unsigned int nbrBytes = RTUreq.mid(4,2).toUInt(&ok,16);
    sendedReq.append(RTUreq.mid(6,nbrBytes*2)+" "); //data
    sendedReq.append(RTUreq.mid(nbrBytes*2+6,4));

    ui->labelReq->setText(sendedReq);
}

MainWindow::~MainWindow()
{
    delete ui;
}

