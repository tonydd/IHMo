#include "annonce.h"
#include "ui_annonce.h"
#include "ihmo.h"
#include "Models/modelannonce.h"
#include <QDoubleValidator>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>

Annonce::Annonce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Annonce)
{
    ui->setupUi(this);
    loadTypes();
    loadNbPieces();

    // -- Validateurs
    ui->txt_prix->setValidator(new QDoubleValidator);
    ui->txt_surface->setValidator(new QDoubleValidator);
    ui->txt_surface_terrain->setValidator(new QDoubleValidator);

    edition = false; // De base on est pas en mode edition
    editing_index = -1;

}

// Récupérer les différents types de bien du XMl et initialiser la comboBox
void Annonce::loadTypes() {
    // A remplacer par les données du XML
    QStringList types=(QStringList()<<"Maison"<<"Appartement"<<"Villa"<<"Poubelle");


    this->ui->combo_type->addItems(types);

}

void Annonce::loadNbPieces() {
    for (int i = 1; i <= 30; i++) {
        this->ui->combo_pieces->addItem(QString::number(i), QVariant(i));
    }
}

void Annonce::openImageFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir le fichier image","/home");
    imageFile = fileName;

    QImage image(fileName);
    this->ui->lbl_img->setPixmap(QPixmap::fromImage(image));
}

void Annonce::accept() {
    // -- Récupération des données
    double prix = ui->txt_prix->text().toDouble();
    double surface_habitable = ui->txt_surface->text().toDouble();
    double surface_terrain = ui->txt_surface_terrain->text().toDouble();


    QString type_bien = ui->combo_type->currentText();
    int nb_pieces = ui->combo_pieces->currentText().toInt();

    QString addr1 = ui->txt_addr1->text();
    QString addr2 = ui->txt_addr2->text();
    QString addr3 = ui->txt_addr3->text();

    QString desc = ui->txt_desc->toPlainText();

    QString type_annonce;

    if (ui->rdb_location->isChecked()) {
        type_annonce = ui->rdb_location->text();
    }
    else if (ui->rdb_vente->isChecked()) {
        type_annonce = ui->rdb_vente->text();
    }

    ModelAnnonce a = ModelAnnonce(type_bien, type_annonce, surface_habitable, surface_terrain, nb_pieces, addr1, addr2, addr3, desc, prix, imageFile);

    if (edition) {
        Datamanager::getInstance()->updateAnnonce(a, editing_index);
    }
    else {
        Datamanager::getInstance()->registerAnnonce(a);
    }

    w->refreshTablewidget();
    this->close();
}

void Annonce::setValues(int index, QString typeBien, QString typeAnnonce, double surfaceHabitable, double superficieTerrain, int nbPieces, QString description, QString adr1, QString adr2, QString adr3, double prix, QString photo) {
    ui->combo_type->setCurrentIndex( ui->combo_type->findText(typeBien) );
    ui->combo_pieces->setCurrentIndex( nbPieces - 1);

    ui->txt_addr1->setText(adr1);
    ui->txt_addr2->setText(adr2);
    ui->txt_addr3->setText(adr3);

    ui->txt_desc->append(description);

    ui->txt_prix->setText( QString::number(prix) );
    ui->txt_surface->setText( QString::number(surfaceHabitable) );
    ui->txt_surface_terrain->setText( QString::number(superficieTerrain) );

    QImage image(photo);
    ui->lbl_img->setPixmap(QPixmap::fromImage(image));
    imageFile = photo;

    if (typeAnnonce == "Vente") {
        ui->rdb_vente->setChecked(true);
    }
    else if (typeAnnonce == "Location") {
        ui->rdb_location->setChecked(true);
    }

    edition = true; // On est en mode edition
    editing_index = index;

}

void Annonce::setW(IHMo *w) {
    this->w = w;
}

Annonce::~Annonce()
{
    delete ui;
}
