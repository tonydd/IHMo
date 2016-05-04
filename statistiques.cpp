#include "statistiques.h"
#include "ui_statistiques.h"

Statistiques::Statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistiques)
{
    ui->setupUi(this);
}

void Statistiques::setAnnonces(QList<ModelAnnonce> *annonces){
    QList<ModelAnnonce> loAppartement;
    QList<ModelAnnonce> loMaison;
    QList<ModelAnnonce> loChateau;
    QList<ModelAnnonce> loVilla;

    /*loAppartement = new QList<ModelAnnonce>;
    loMaison = new QList<ModelAnnonce>;
    loChateau = new QList<ModelAnnonce>;
    loVilla = new QList<ModelAnnonce>;*/

    for (int i = 0; i < annonces->count(); i++){
        ModelAnnonce a = annonces->at(i);
        if (a.mTypeBien.compare(QString("Maison")) == 0){
            loMaison.append(a);
            qDebug("Ajout Maison");
        } else if (a.mTypeBien.compare(QString("Appartement")) == 0){
            loAppartement.append(a);
            qDebug("Ajout Appartement");
        } else if (a.mTypeBien.compare(QString("Villa")) == 0){
            loVilla.append(a);
            qDebug("Ajout Villa");
        } else if (a.mTypeBien.compare(QString("Chateau")) == 0){
            loChateau.append(a);
            qDebug("Ajout Chateau");
        }
    }

    this->StatAppartement(&loAppartement);
    this->StatChateau(&loChateau);
    this->StatMaison(&loMaison);
    this->StatVilla(&loVilla);

    int nbLocation = this->ui->lblLocationAppartement->text().toInt() +
                     this->ui->lblLocationChateau->text().toInt() +
                     this->ui->lblLocationMaison->text().toInt() +
                     this->ui->lblLocationVilla->text().toInt();
    this->ui->lblLocationTotal->setText(QString::number(nbLocation));

    int nbVente = this->ui->lblVenteAppartement->text().toInt() +
            this->ui->lblVenteChateau->text().toInt() +
            this->ui->lblVenteMaison->text().toInt() +
            this->ui->lblVenteVilla->text().toInt();
    this->ui->lblVenteTotal->setText(QString::number(nbVente));

    int nbAttente = this->ui->lblAttenteAppartement->text().toInt() +
            this->ui->lblAttenteChateau->text().toInt() +
            this->ui->lblAttenteMaison->text().toInt() +
            this->ui->lblAttenteVilla->text().toInt();
    this->ui->lblAttenteTotal->setText(QString::number(nbAttente));

    this->ui->lblTotalTotal->setText(QString::number(nbLocation + nbVente + nbAttente));
}

void Statistiques::StatMaison(QList<ModelAnnonce> *loMaison){
    int nbVente = 0;
    int nbLocation = 0;
    int nbEnAttente = 0;
    int nbTotal = 0;

    for (int i = 0; i < loMaison->count(); i++){
        ModelAnnonce a = loMaison->at(i);
        if (a.mEstOccupe){
            if (a.mTypeAnnonce.compare(QString("Location")) == 0){
                nbLocation++;
                qDebug("Ajout Loc Maison");
            } else if (a.mTypeAnnonce.compare(QString("Vente")) == 0){
                nbVente++;
                qDebug("Ajout Vente Maison");
            }
        } else {
            nbEnAttente++;
            qDebug("Ajout En Attente Maison");
        }
    }

    nbTotal = nbLocation + nbVente + nbEnAttente;

    this->ui->lblLocationMaison->setText(QString::number(nbVente));
    this->ui->lblVenteMaison->setText(QString::number(nbLocation));
    this->ui->lblAttenteMaison->setText(QString::number(nbEnAttente));
    this->ui->lblTotalMaison->setText(QString::number(nbTotal));
}

void Statistiques::StatAppartement(QList<ModelAnnonce> *loAppartement){
    int nbVente = 0;
    int nbLocation = 0;
    int nbEnAttente = 0;
    int nbTotal = 0;

    for (int i = 0; i < loAppartement->count(); i++){
        ModelAnnonce a = loAppartement->at(i);
        if (a.mEstOccupe){
            if (a.mTypeAnnonce.compare(QString("Location")) == 0){
                nbLocation++;
                qDebug("Ajout Location Appartement");
            } else if (a.mTypeAnnonce.compare(QString("Vente")) == 0){
                nbVente++;
                qDebug("Ajout Vente Appartement");
            }
        } else {
            nbEnAttente++;
            qDebug("Ajout En Attente Appartement");
        }
    }

    nbTotal = nbLocation + nbVente + nbEnAttente;

    this->ui->lblLocationAppartement->setText(QString::number(nbLocation));
    this->ui->lblVenteAppartement->setText(QString::number(nbVente));
    this->ui->lblAttenteAppartement->setText(QString::number(nbEnAttente));
    this->ui->lblTotalAppartement->setText(QString::number(nbTotal));

}

void Statistiques::StatChateau(QList<ModelAnnonce> *loChateau){
    int nbVente = 0;
    int nbLocation = 0;
    int nbEnAttente = 0;
    int nbTotal = 0;

    for (int i = 0; i < loChateau->count(); i++){
        ModelAnnonce a = loChateau->at(i);
        if (a.mEstOccupe){
            if (a.mTypeAnnonce.compare(QString("Location")) == 0){
                nbLocation++;
                qDebug("Ajout Location Chateau");
            } else if (a.mTypeAnnonce.compare(QString("Vente")) == 0){
                nbVente++;
                qDebug("Ajout Vente Chateau");
            }
        } else {
            nbEnAttente++;
            qDebug("Ajout En Attente Chateau");
        }
    }

    nbTotal = nbLocation + nbVente + nbEnAttente;

    this->ui->lblLocationChateau->setText(QString::number(nbLocation));
    this->ui->lblVenteChateau->setText(QString::number(nbVente));
    this->ui->lblAttenteChateau->setText(QString::number(nbEnAttente));
    this->ui->lblTotalChateau->setText(QString::number(nbTotal));
}

void Statistiques::StatVilla(QList<ModelAnnonce> *loVilla){
    int nbVente = 0;
    int nbLocation = 0;
    int nbEnAttente = 0;
    int nbTotal = 0;

    for (int i = 0; i < loVilla->count(); i++){
        ModelAnnonce a = loVilla->at(i);
        if (a.mEstOccupe){
            if (a.mTypeAnnonce.compare(QString("Location")) == 0){
                nbLocation++;
                qDebug("Ajout Location Villa");
            } else if (a.mTypeAnnonce.compare(QString("Vente")) == 0){
                nbVente++;
                qDebug("Ajout Vente Villa");
            }
        } else {
            nbEnAttente++;
            qDebug("Ajout En Attente Villa");
        }
    }

    nbTotal = nbLocation + nbVente + nbEnAttente;

    this->ui->lblLocationVilla->setText(QString::number(nbLocation));
    this->ui->lblVenteVilla->setText(QString::number(nbVente));
    this->ui->lblAttenteVilla->setText(QString::number(nbEnAttente));
    this->ui->lblTotalVilla->setText(QString::number(nbTotal));
}

Statistiques::~Statistiques()
{
    delete ui;
}
