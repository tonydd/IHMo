#include "ihmo.h"
#include "ui_ihmo.h"
#include "annonce.h"
#include "statistiques.h"
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
#include <QShortcut>
#include <QKeySequence>
#include <QValidator>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QIcon>
#include <QDir>
#include <QUrl>
#include <QCloseEvent>

IHMo *IHMo::instance;

IHMo::IHMo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IHMo)
{
    ui->setupUi(this);
    IHMo::instance = this;

    // -- Préparation des validateurs
    ui->txt_search_pieceMin->setValidator(new QIntValidator);
    ui->txt_search_piecesMax->setValidator(new QIntValidator);

    QRegExpValidator* rxv = new QRegExpValidator(QRegExp("[+-]?\\d*[\\.,]?\\d+"), this);

    ui->txt_search_prixMax->setValidator(rxv);
    ui->txt_search_prixMin->setValidator(rxv);

    // -- Préparation du table widget
    ui->tw_annonces->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_annonces->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_annonces->setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList headers;
    headers << "Mise en ligne" << "Type de bien" << "Type d'annonce" << "Surface habitable" << "Superficie terrain" << "Nb pieces" << "Description" <<"Addresse" << "Prix" << "Photo";

    int nb_col = headers.count();

    ui->tw_annonces->setColumnCount( nb_col );
    ui->tw_annonces->setHorizontalHeaderLabels(headers);
    ui->tw_annonces->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    Datamanager::getInstance()->loadFromXML();


    // -- Bind "Delete" sur tableWidget
    QShortcut* shortcut = new QShortcut(QKeySequence(QKeySequence::Delete), ui->tw_annonces);
    connect(shortcut, SIGNAL(activated()), this, SLOT(deleteRow()));

    // -- Combobox type bien
    QStringList types=(QStringList()<<""<<"Maison"<<"Appartement"<<"Villa"<<"Chateau");
    this->ui->cb_search_typeBien->addItems(types);

    this->refreshTablewidget();
    ui->tw_annonces->resizeRowsToContents();

}

IHMo::~IHMo()
{
    delete ui;
}

// ********************************************
// Méthodes d'instance
// ********************************************

void IHMo::refreshTablewidget() {
    QList<ModelAnnonce> *annonces = Datamanager::getInstance()->getAnnonces();

    QTableWidget *tw_annonces = ui->tw_annonces;
    int col_index;

    tw_annonces->setRowCount( annonces->count() );

    for (int line = 0; line < annonces->count(); line++) {
        ModelAnnonce annonce = annonces->at(line);

        col_index = 0;
        tw_annonces->setItem(line, col_index, new QTableWidgetItem(annonce.mCreation.toString("dd/MM/yyyy")));
        col_index++;

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

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(annonce.mAdresse1 + "\n" + annonce.mAdresse2 + "\n" + annonce.mAdresse3));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(QString::number(annonce.mPrix)));
        col_index++;

        tw_annonces->setItem(line, col_index, new QTableWidgetItem(QIcon(annonce.mPhotoContractuelle), QString("")));
        col_index++;

        if (annonce.mEstOccupe) {
            for (int i = 0; i < col_index; i++) {
                tw_annonces->item(line, i)->setBackgroundColor(QColor("silver"));
            }
        }
    }

    tw_annonces->resizeRowsToContents();
}

// ********************************************
// Slots
// ********************************************

void IHMo::addAnnonce() {
    Annonce *annonce = new Annonce();
    annonce->setW(this);
    annonce->show();
}

void IHMo::searchAnnonce() {
    // -- Récupération de toutes les données de recherche
    QString typeAnnonce = "";
    if (ui->ckb_search_locations->isChecked()) {
        typeAnnonce = "Location";
    }
    else if (ui->ckb_search_ventes->isChecked()) {
        typeAnnonce = "Vente";
    }

    QString typeBien = ui->cb_search_typeBien->currentText();
    QString adr = ui->txt_search_adresse->text();

    double prixMin = ui->txt_search_prixMin->text().toDouble();
    double prixMax = ui->txt_search_prixMax->text().toDouble();

    int piecesMin = ui->txt_search_pieceMin->text().toInt();
    int piecesMax = ui->txt_search_piecesMax->text().toInt();

    bool avecPhoto = ui->ckb_search_photo->isChecked();
    bool vendusUniquement = ui->ckb_search_vendus->isChecked();
    bool louesUniquement = ui->ckb_search_loues->isChecked();

    // -- Application de la recherche
    QList<ModelAnnonce> *annonces = Datamanager::getInstance()->getAnnonces();
    QTableWidget *tw_annonces = ui->tw_annonces;

    // -- On part du principe qu'avant application de la recherche toute sle slignes sont affichées
    for (int i = 0; i < tw_annonces->rowCount(); i++) {
        tw_annonces->setRowHidden(i, false);
    }

    for (int i = 0; i < annonces->count(); i++) {
        ModelAnnonce ann = annonces->at(i);

        // ----- Gestion type annonce
        if (typeAnnonce != "") {
            if (ann.mTypeAnnonce != typeAnnonce) {
                qDebug("Caché par type annonce");
                tw_annonces->setRowHidden(i, true);
            }
        }

        // ----- gestion type bien
        if (typeBien != "") {
            if (ann.mTypeBien != typeBien) {
                qDebug("Caché par type bien");
                tw_annonces->setRowHidden(i, true);
            }
        }

        // -- Vendus
        if (vendusUniquement) {
            if (!(ann.mEstOccupe && ann.mTypeAnnonce == "Vente")) {
                tw_annonces->setRowHidden(i, true);
            }
        }

        // -- Loues
        if (louesUniquement) {
            if (!(ann.mEstOccupe && ann.mTypeAnnonce == "Location")) {
                tw_annonces->setRowHidden(i, true);
            }
        }

        // ----- Gestion choix prix
        if (ann.mPrix <= prixMin) {
            qDebug("Caché par prix mib");
            tw_annonces->setRowHidden(i, true);
        }
        if (prixMax > 0 && ann.mPrix > prixMax) {
            qDebug("Caché par prix max");
            tw_annonces->setRowHidden(i, true);
        }

        // ----- Gestion nombre de pièces
        if (ann.mNombrePiece <= piecesMin) {
            qDebug("Caché par pieces min");
            tw_annonces->setRowHidden(i, true);
        }
        if (piecesMax > 0 && ann.mNombrePiece >= piecesMax) {
            qDebug("Caché par pieces max");
            tw_annonces->setRowHidden(i, true);
        }

        // ----- Adresse
        if (adr != "") {
            QString fullAddress = ann.mAdresse1 + ann.mAdresse2 + ann.mAdresse3;
            qDebug(fullAddress.toStdString().c_str());

            if (! fullAddress.contains(adr, Qt::CaseInsensitive)) {
                qDebug("Caché par adr");
                tw_annonces->setRowHidden(i, true);
            }
        }

        // ----- Date de mise en ligne
        if (ui->ckb_search_enableDate->isChecked()) {
            if (ann.mCreation < ui->date_search->date()) {
                tw_annonces->setRowHidden(i, true);
            }
        }

        // ----- Gestion photo
        if (avecPhoto && ann.mPhotoContractuelle == "") {
            qDebug("Caché par photo");
            tw_annonces->setRowHidden(i, true);
        }

    }


}

void IHMo::emptySearch() {
    ui->ckb_search_locations->setChecked(false);
    ui->ckb_search_ventes->setChecked(false);

    ui->ckb_search_vendus->setChecked(false);
    ui->ckb_search_loues->setChecked(false);

    ui->ckb_search_photo->setChecked(false);
    ui->ckb_search_enableDate->setChecked(false);

    ui->cb_search_typeBien->setCurrentIndex(0);
    ui->txt_search_adresse->setText("");

    ui->txt_search_prixMin->setText("");
    ui->txt_search_prixMax->setText("");

    ui->txt_search_pieceMin->setText("");
    ui->txt_search_piecesMax->setText("");

    searchAnnonce();
}

void IHMo::enableDateSearch(bool enable) {
    ui->date_search->setEnabled(enable);
}

void IHMo::showAPropos() {
    QMessageBox::information(this,"A propos","Version 1.0\nAnthony Den Drijver & Thomas Stocker\nIHM L3IS6P 2016");
}

void IHMo::setEditAnnonce(ModelAnnonce a, bool ed){
    if (ed){
        Datamanager::getInstance()->annonces->replace(editing_index, a);
    } else {
        Datamanager::getInstance()->registerAnnonce(a);
    }
    this->refreshTablewidget();
}

void IHMo::showAide() {
    QDesktopServices::openUrl(QUrl("../Aide.pdf"));
}

void IHMo::showAnnonce(QModelIndex index) {
    editing_index = index.row();

    ModelAnnonce a = Datamanager::getInstance()->getAnnonce(editing_index);


    // -- Création, remplissage, affichage du form d'édition
    Annonce *disp = new Annonce;
    disp->setAnnonce(a);
    disp->setW(this);
    disp->show();
}

void IHMo::saveAnnonces(){
    if (Datamanager::getInstance()->saveToXML()){
        QMessageBox q;
        q.setText("Enregistrement effectué avec succès !");
        q.exec();
    }else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'enregistrement");
    }
}

void IHMo::deleteRow() {
    QModelIndex idx = ui->tw_annonces->currentIndex();
    if (idx.isValid()) {
        switch( QMessageBox::information( this, "Confirmation de l'action",
                                          "Voulez-vous vraiment supprimer cette annonce ?"
                                          "", "Oui", "Non",
                                          0, 1 ) ) {
        case 0:
            Datamanager::getInstance()->deleteAnnonce(idx.row());
            this->refreshTablewidget();
            break;
        case 1:
        default: // just for sanity
            break;
        }


    }
}

void IHMo::showStatistiques(){
    Statistiques *s = new Statistiques;
    s->setAnnonces(Datamanager::getInstance()->annonces);

    s->show();
}

void IHMo::closeEvent (QCloseEvent *event)
{
    Datamanager::getInstance()->saveToXML();
}

