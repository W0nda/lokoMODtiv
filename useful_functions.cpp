#define CRC16 0x8005

#include <useful_functions.h>
#include <QDebug>

void returnReqSize(QString str, QString *size, QString *error){
    unsigned int UIntsize = str.length()/2;
    *size = "0"+QString::number(UIntsize,16);
}

void checkRegisterAddr(QString str, QString *error){
    bool ok = true;
    unsigned int registerAddr = str.toUInt(&ok,16);
    qDebug()<<"regAddr"<<registerAddr;
    if(registerAddr > 10 || registerAddr < 1){
        error->append("badRegAddr ");
    }
}

void checkSlaveAddr(QString str, QString *error){
    bool ok = true;
    unsigned int slaveAddr = str.toUInt(&ok,16);
    qDebug()<<"slaveAddr"<<slaveAddr;
    if(slaveAddr > 2 || slaveAddr < 1){
        error->append("badSlaveAddr");
    }
}

int genCRC16(QString str);
/*return 2 bytes, change "int" by something more appropriate*/
