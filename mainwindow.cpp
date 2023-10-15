#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fm_pontos.h"
#include <QtSql>
#include <QDir>
#include <QMessageBox>
#include <QTime>
#include <QDate>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");
    bancoDeDados.setDatabaseName(QDir::homePath()+"/qt/FPonto/banco.db");

    if(!bancoDeDados.open()){
        QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    QString txt;
    QString id=ui->lineEdit->text();
    QString data=QDate::currentDate().toString("yyyy-MM-dd");

    query.prepare("select * from ponto where id_colab="+id+" and data='"+data+"' order by data DESC LIMIT 1");
    if(query.exec()){
        query.first();
        if(!query.value(3).isNull() && !query.value(4).isNull()){
            QMessageBox::warning(this,"Erro","Ponto ja foi batido duas vezes");
            return;
        }else{
        txt=query.value(3).toString();
        }
    }

    if(txt!=""){
        QString saida=QTime::currentTime().toString("hh:mm:ss");
        query.prepare("update ponto set saida='"+saida+"' where id_colab="+id+"");
    }else{
        QString entr=QTime::currentTime().toString("hh:mm:ss");
        query.prepare("insert into ponto (id_colab,data,entrada,saida) values "
                      "("+id+",'"+data+"','"+entr+"',NULL)");
    }

    if(query.exec()){
        QMessageBox::information(this,"Sucesso","Ponto batido com sucesso !");
    }else{
        QMessageBox::warning(this,"Erro","Erro ao bater ponto ");
    }

}


void MainWindow::on_actionGerenciar_pontos_triggered()
{
    fm_pontos f_pontos;
    f_pontos.exec();
}
