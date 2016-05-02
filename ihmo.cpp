#include "ihmo.h"
#include "ui_ihmo.h"
#include "annonce.h"
#include <Qt>
#include <QString>
#include <QStringList>
#include <QPixmap>
#include <QPalette>
#include <QMessageBox>
#include <QDesktopServices>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QIcon>
#include <QDir>
#include <QUrl>

IHMo *IHMo::instance;

IHMo::IHMo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IHMo)
{
    ui->setupUi(this);
    IHMo::instance = this;

    // -- Background
    this->setStyleSheet("QMainWindow {background-image: url('../Ressources/background.png')}");

    // -- C'est ici qu'on init le Datamanager
    Datamanager *d = new Datamanager;
    this->manager = d;

    // -- Préparation du table widget
    ui->tw_annonces->setStyleSheet("QTableView {selection-background-color: silver;}");
    ui->tw_annonces->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_annonces->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_annonces->setSelectionMode(QAbstractItemView::SingleSelection);

    this->refreshTablewidget();

}

IHMo::~IHMo()
{
    delete ui;
}

// ********************************************
// Méthodes d'instance
// ********************************************

void IHMo::refreshTablewidget() {
    QList<ModelAnnonce> *annonces = IHMo::getInstance()->getManager()->getAnnonces();
    QStringList headers;
    headers << "Type de bien" << "Type d'annonce" << "Surface habitable" << "Superficie terrain" << "Nb pieces" << "Description" <<"Addresse" << "Prix" << "Photo";

    QTableWidget *tw_annonces = ui->tw_annonces;
    int nb_col = headers.count();
    int col_index;

    tw_annonces->setRowCount( annonces->count() );
    tw_annonces->setColumnCount( nb_col );
    tw_annonces->setHorizontalHeaderLabels(headers);
    tw_annonces->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    for (int line = 0; line < annonces->count(); line++) {
        ModelAnnonce annonce = annonces->at(line);

        col_index = 0;
        tw_annonces->setItem(line, col_index, new QTableWidgetItem(annonce.mTypeBien));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(annonce.mTypeAnnonce));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(QString::number(annonce.mSurfaceHabitable)));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(QString::number(annonce.mSuperficieTerrain)));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(QString::number(annonce.mNombrePiece)));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(annonce.mDescription));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(annonce.mAdresse1 + ", " + annonce.mAdresse2 + ", " + annonce.mAdresse3));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(QString::number(annonce.mPrix)));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(QIcon(annonce.mPhotoContractuelle), QString("")));
        col_index++;
    }

    tw_annonces->resizeRowsToContents();
}

Datamanager *IHMo::getManager() {
    return this->manager;
}

// ********************************************
// Slots
// ********************************************

void IHMo::addAnnonce() {
    Annonce *annonce = new Annonce;
    annonce->show();
}

void IHMo::searchAnnonce() {

}

void IHMo::showAPropos() {
    QMessageBox::information(this,"A propos","Version 1.0\nAnthony Den Drijver & Thomas Stocker\nIHM L3IS6P 2016");
}

void IHMo::showAide() {
    QDesktopServices::openUrl(QUrl("../Aide.pdf"));
}

void IHMo::showAnnonce(QModelIndex index) {
    int row = index.row();

    ModelAnnonce a = this->getManager()->getAnnonce(row);


    // -- Création, remplissage, affichage du form d'édition
    Annonce *disp = new Annonce;
    disp->setValues(row,
                a.mTypeBien, a.mTypeAnnonce, a.mSurfaceHabitable,
                a.mSuperficieTerrain, a.mNombrePiece, a.mDescription,
                a.mAdresse1, a.mAdresse2, a.mAdresse3,
                a.mPrix, a.mPhotoContractuelle);

    disp->show();
}


// ********************************************
// Méthodes de classe
// ********************************************

IHMo *IHMo::getInstance() {
return IHMo::instance;
}
