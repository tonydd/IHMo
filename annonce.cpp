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

    QRegExpValidator* rxv = new QRegExpValidator(QRegExp("[+-]?\\d*[\\.,]?\\d+"), this);

    // -- Validateurs

    ui->txt_prix->setValidator(rxv);
    ui->txt_surface->setValidator(rxv);
    ui->txt_surface_terrain->setValidator(rxv);

    ui->btn_Vendu->setVisible(false);
    ui->lblVendu->setVisible(false);

    edition = false; // De base on est pas en mode edition
    editing_index = -1;

    ui->lbl_date->setVisible(false);
}

// Récupérer les différents types de bien du XMl et initialiser la comboBox
void Annonce::loadTypes() {
    // A remplacer par les données du XML
    QStringList types=(QStringList()<<"Maison"<<"Appartement"<<"Villa"<<"Chateau");


    this->ui->combo_type->addItems(types);

}

void Annonce::loadNbPieces() {
    for (int i = 1; i <= 30; i++) {
        this->ui->combo_pieces->addItem(QString::number(i), QVariant(i));
    }
}

void Annonce::openImageFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choisir le fichier image","/home");


    QFile f(fileName);

    QFileInfo fileInfo(f.fileName());
    QString fileNameCut(fileInfo.fileName());
    QString finalPath(QDir::currentPath() + QDir::separator() + "img" + QDir::separator() + fileNameCut);

    //QFile img = QFile(fileName);
    QFile::copy(fileName, finalPath);

    imageFile = finalPath;
    QImage image(imageFile);
    this->ui->lbl_img->setPixmap(QPixmap::fromImage(image));
}

void Annonce::accept() {
    this->mAnnonce.mPrix = ui->txt_prix->text().toDouble();
    this->mAnnonce.mSurfaceHabitable = ui->txt_surface->text().toDouble();
    this->mAnnonce.mSuperficieTerrain = ui->txt_surface_terrain->text().toDouble();


    this->mAnnonce.mTypeBien = ui->combo_type->currentText();
    mAnnonce.mNombrePiece = ui->combo_pieces->currentText().toInt();

    mAnnonce.mAdresse1 = ui->txt_addr1->text();
    mAnnonce.mAdresse2 = ui->txt_addr2->text();
    mAnnonce.mAdresse3 = ui->txt_addr3->text();

    mAnnonce.mDescription = ui->txt_desc->toPlainText();

    QString type_annonce;

    if (ui->rdb_location->isChecked()) {
        type_annonce = ui->rdb_location->text();
    }
    else if (ui->rdb_vente->isChecked()) {
        type_annonce = ui->rdb_vente->text();
    }

    mAnnonce.mTypeAnnonce = type_annonce;
    //mAnnonce.mEstOccupe = ui->chkOccupe->isChecked();
    mAnnonce.mPhotoContractuelle = imageFile;

    mAnnonce.setLastUpdate(QDate::currentDate());
    if (!edition){
        mAnnonce.mEstOccupe = false;
        mAnnonce.mIdAnnonce = Datamanager::getInstance()->getNewIdAnnonce();
        mAnnonce.setCreationDate(QDate::currentDate());
    }


    w->setEditAnnonce(mAnnonce, edition);
    this->close();
}

void Annonce::setValues(int index, QString typeBien, QString typeAnnonce, double surfaceHabitable, double superficieTerrain, int nbPieces, QString description, QString adr1, QString adr2, QString adr3, double prix, QString photo, QDate crea) {
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

    ui->lbl_date->setText("Mise en ligne le : " + crea.toString("dd/MM/yyyy"));
    ui->lbl_date->setVisible(true);

    edition = true; // On est en mode edition
    editing_index = index;

}

void Annonce::setAnnonce(ModelAnnonce a){
    this->mAnnonce = a;
    ui->combo_type->setCurrentIndex( ui->combo_type->findText(a.mTypeBien) );
    ui->combo_pieces->setCurrentIndex( a.mNombrePiece - 1);

    ui->txt_addr1->setText(a.mAdresse1);
    ui->txt_addr2->setText(a.mAdresse2);
    ui->txt_addr3->setText(a.mAdresse3);

    ui->txt_desc->append(a.mDescription);

    ui->txt_prix->setText( QString::number(a.mPrix) );
    ui->txt_surface->setText( QString::number(a.mSurfaceHabitable) );
    ui->txt_surface_terrain->setText( QString::number(a.mSuperficieTerrain) );

    QImage image(a.mPhotoContractuelle);
    ui->lbl_img->setPixmap(QPixmap::fromImage(image));
    imageFile = a.mPhotoContractuelle;

    if (a.mTypeAnnonce == "Vente") {
        ui->rdb_vente->setChecked(true);
        ui->btn_Vendu->setText("Vendu");
    }
    else if (a.mTypeAnnonce == "Location") {
        ui->rdb_location->setChecked(true);
        ui->btn_Vendu->setText("Loué");
    }

    ui->lbl_date->setText("Mise en ligne le : " + a.mCreation.toString("dd/MM/yyyy"));
    ui->lbl_date->setVisible(true);

    edition = true; // On est en mode edition

    if (a.mEstOccupe){
        ui->lblVendu->setText(QString(ui->btn_Vendu->text() + " à " + a.mNomAcheteur + " le " + a.mFin.toString("dd/MM/yyyy")));
        ui->lblVendu->setVisible(true);
    }else {
        ui->btn_Vendu->setVisible(true);
    }


    //ui->chkOccupe->setChecked(a.mEstOccupe);
}

void Annonce::setVendu(){
    bool ok;
    QString desc = QString("");
    if (mAnnonce.mTypeAnnonce.compare("Location") == 0){
        desc = QString("Nom du locataire :");
    }else if (mAnnonce.mTypeAnnonce.compare("Vente") == 0){
        desc = QString("Nom de l'acheteur' :");
    }
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                      desc, QLineEdit::Normal,
                                      QDir::home().dirName(), &ok);


    this->mAnnonce.mNomAcheteur = text;
    this->mAnnonce.setEstOccupe(true);
    this->accept();
}

void Annonce::setW(IHMo *w) {
    this->w = w;
}

Annonce::~Annonce()
{
    delete ui;
}

// Validateurs string
class QEmptyStringValidator : public QValidator
{
   Q_OBJECT
public:
   explicit QEmptyStringValidator(QObject *parent = 0);
   virtual State validate ( QString & input, int & pos ) const
   {
       if (input.isEmpty())
           return Invalid;

       return Acceptable;

   }
};
