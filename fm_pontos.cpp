#include "fm_pontos.h"
#include "ui_fm_pontos.h"
#include <QMessageBox>
#include <QtSql>
#include <QDir>
#include <QTime>

fm_pontos::fm_pontos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_pontos)
{
    ui->setupUi(this);

    QSqlDatabase bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");
    bancoDeDados.setDatabaseName(QDir::homePath()+"/qt/FPonto/banco.db");
    if(!bancoDeDados.open()){
        QMessageBox::warning(this,"ERRO","Não foi possível abrir o banco de dados");

    }

    ui->tb_pontos->setColumnCount(6);
    QStringList cabecalho={"ID","Nome","Data","Entrada","Saida","Total"};
    ui->tb_pontos->setHorizontalHeaderLabels(cabecalho);
    ui->tb_pontos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tb_pontos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tb_pontos->verticalHeader()->setVisible(false);

    QSqlQuery query;
    query.prepare("select p.id_colab,c.nome_colab,p.data,p.entrada,p.saida,p.total "
                  "from ponto as p inner join colaborador as c on p.id_colab=c.id_colab");
    if(query.exec()){
        int linha=0;
        while(query.next()){
            ui->tb_pontos->insertRow(linha);
            ui->tb_pontos->setItem(linha,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tb_pontos->setItem(linha,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tb_pontos->setItem(linha,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tb_pontos->setItem(linha,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tb_pontos->setItem(linha,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tb_pontos->setItem(linha,5,new QTableWidgetItem(query.value(5).toString()));
            linha++;
        }
    }else{
        QMessageBox::warning(this,"ERRO","Erro ao mostrar pontos");
    }

}


fm_pontos::~fm_pontos()
{

    delete ui;
}
