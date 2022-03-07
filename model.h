#pragma once
#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QListView>
#include <QTableWidget>
#include <QTableView>
#include <QApplication>
#include <QTreeView>
#include <QLayout>
#include <QModelIndex>
#include <QFileSystemModel>
#include "Oferta.h"
#include <vector>
using std::vector;

class ModelLista: public QAbstractListModel{

private:
    vector<Oferta>& lista_oferte;
public:
    ///constructor
    ModelLista(vector<Oferta>& lista,QObject* parent): QAbstractListModel(parent) ,lista_oferte{lista}{};

    ///rescrierea metodei din clasa de baza cu datele personalizate
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return lista_oferte.size();
    }

    ///rescrierea metodei din clasa de baza cu datele personalizate
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 1;
    }

    ///rescrierea metodei din clasa de baza cu datele personalizate
    ///ce sa se afiseze in lista
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            //qDebug() << "row:" << QString::fromStdString(lista_oferte.at(index.row()).get_denumire());
            //qDebug()<< " dim "<<QString::number(rowCount())<<" index "<<QString::number(index.row())<<"\n";
            return QString("%1").arg(QString::fromStdString(lista_oferte.at(index.row()).get_denumire()));
        }
        return QVariant();
    }

    /*
     * acesta functie se ocupa cu trimiterea unui semnal listei in cazul in care apar modificari in date
     * oferte este o noua lista de oferte
     * Nu returneaza nimic
     */
    void set_Oferte(const vector<Oferta>& oferte) {
        this->lista_oferte = oferte;
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight);
    }

    void modifica_culoare(const vector<Oferta>& lista) {
        this->lista_oferte = lista;
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight);
    }
};
/*
class ModelTabel: public QAbstractTableModel{

private:
    vector<Oferta>& lista_oferte;

public:
    ///constructor
    ModelTabel(vector<Oferta>& lista,QObject* parent): QAbstractTableModel(parent) ,lista_oferte{lista}{};

    ///rescrierea metodei din clasa de baza cu datele personalizate
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return lista_oferte.size();
    }

    ///rescrierea metodei din clasa de baza cu datele personalizate
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    ///rescrierea metodei din clasa de baza cu datele personalizate
    ///ce sa se afiseze in lista
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            //qDebug() << "row:" << QString::fromStdString(lista_oferte.at(index.row()).get_denumire());
            //qDebug()<< " dim "<<QString::number(rowCount())<<" index "<<QString::number(index.row())<<"\n";
            return QString("%1 %2 %3 %4").arg(QString::fromStdString(lista_oferte.at(index.row()).get_denumire())).arg(QString::fromStdString(lista_oferte.at(index.row()).get_destinatie())).arg(QString::fromStdString(lista_oferte.at(index.row()).get_tip())).arg(QString::number(lista_oferte.at(index.row()).get_pret()));
        }
        return QVariant();
    }

    /*
     * acesta functie se ocupa cu trimiterea unui semnal listei in cazul in care apar modificari in date
     * oferte este o noua lista de oferte
     * Nu returneaza nimic
     */
/*
    void set_Oferte(const vector<Oferta>& oferte) {
        this->lista_oferte = oferte;
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight);
    }
};
 */
