#include "annonce.h"
#include "ui_annonce.h"
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
    qDebug(fileName.toLatin1());

    QImage image(fileName);
    this->ui->lbl_img->setPixmap(QPixmap::fromImage(image));
}

void Annonce::accept() {



}

char* Annonce::readFileBytes(const char *name)
{
    std::ifstream fl(name);
    fl.seekg( 0, std::ios::end );
    size_t len = fl.tellg();
    char *ret = new char[len];
    fl.seekg(0, std::ios::beg);
    fl.read(ret, len);
    fl.close();
    return ret;
}

//Constructeur
Annonce::Annonce(TYPE_BIEN peTypeBien,
                 TYPE_ANNONCE peTypeAnnonce,
                 double pdblSurfaceHabitable,
                 double pdblSuperficieTerrain,
                 int piNombrePiece,
                 std::string pstrAdresse1,
                 std::string pstrAdresse2,
                 std::string pstrDescription,
                 double pdblPrix,
                 char* ptbPhotoContractuelle
                 ){
    mTypeBien = peTypeBien;
    mTypeAnnonce = peTypeAnnonce;
    mSurfaceHabitable = pdblSurfaceHabitable;
    mSuperficieTerrain = pdblSuperficieTerrain;
    mNombrePiece = piNombrePiece;
    mAdresse1 = pstrAdresse1;
    mAdresse2 = pstrAdresse2;
    mDescription = pstrDescription;
    mPrix = pdblPrix;
    mPhotoContractuelle = ptbPhotoContractuelle;
}

Annonce::~Annonce()
{
    delete ui;
}
