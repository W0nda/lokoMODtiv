#include <useful_functions.h>

#include <QDebug>

void checkSize(QString str, QString *error){
    bool ok = true;
    unsigned int expectedSize = str.midRef(4,2).toUInt(&ok,16) * 2;
    expectedSize = expectedSize + 10; //5 "bytes" * 2 char
    if(expectedSize != str.length()){
        error->append("badSize ");
    }
}

void checkRegisterAddr(QString str, QString *error){
    bool ok = true;
    unsigned int registerAddr = str.midRef(2,2).toUInt(&ok,16);
    qDebug()<<"regAddr"<<registerAddr;
    if(registerAddr > 10 || registerAddr < 1){
        error->append("badRegAddr ");
    }
}

void checkSlaveAddr(QString str, QString *error){
    bool ok = true;
    unsigned int slaveAddr = str.midRef(0,2).toUInt(&ok,16);
    qDebug()<<"slaveAddr"<<slaveAddr;
    if(slaveAddr != 1){
        error->append("badSlaveAddr");
    }
}
