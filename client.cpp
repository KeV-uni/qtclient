#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    connect(ui->pBtn_close,&QAbstractButton::clicked,this,&QWidget::close);
    //Procesar datos recibidos
    connect(clientSocket,&QIODevice::readyRead,this,&Client::readMessage);
    //Boton conectar
    connect(ui->pBtn_connect,&QAbstractButton::clicked,this,&Client::requestMessage);
    //Capturando los errores de comunicacion

}

Client::~Client()
{
    delete ui;
}

//Este slot inicia la comunicacion con el servidor y se solicita un mensaje
void Client::requestMessage(){

    qDebug() <<"requestMessage() start ...";
    QString ipAddress = ui->lEdit_ip->text();
    QString port = ui->lEdit_port->text();
    qDebug() <<"IP : "<<ipAddress<<" , Port : "<<port;

    clientSocket->connectToHost(ipAddress,port.toInt());
    qDebug() <<"requestMessage() end ...";
}

//Este slot inicia la lectura del mensaje que ha llegado al cliente
void Client::readMessage(){
    qDebug() <<"readMessage() start...";
    in.startTransaction();
    QString message;
    in >>message;
    if(!in.commitTransaction()){
        qDebug() <<"Error in datastream";
        return;
    }
    qDebug() <<"message : "<<message;
    ui->lbl_message->setText(message);
    qDebug() <<"requestMessage() end ...";
}

void Client::showError(){
     qDebug() << "showError() start ...";
}
