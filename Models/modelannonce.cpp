#include "modelannonce.h"

char* ModelAnnonce::readFileBytes(const char *name)
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
ModelAnnonce::ModelAnnonce(QString peTypeBien,
                 QString peTypeAnnonce,
                 double pdblSurfaceHabitable,
                 double pdblSuperficieTerrain,
                 int piNombrePiece,
                 QString pstrAdresse1,
                 QString pstrAdresse2,
                 QString pstrAdresse3,
                 QString pstrDescription,
                 double pdblPrix,
                 QString ptbPhotoContractuelle
                 ){
    mTypeBien = peTypeBien;
    mTypeAnnonce = peTypeAnnonce;
    mSurfaceHabitable = pdblSurfaceHabitable;
    mSuperficieTerrain = pdblSuperficieTerrain;
    mNombrePiece = piNombrePiece;
    mAdresse1 = pstrAdresse1;
    mAdresse2 = pstrAdresse2;
    mAdresse3 = pstrAdresse3;
    mDescription = pstrDescription;
    mPrix = pdblPrix;
    mPhotoContractuelle = ptbPhotoContractuelle;

    mCreation = QDate::currentDate();
    mLastUpdate = QDate::currentDate();
}

void ModelAnnonce::toString() {
   ModelAnnonce::qPrint(this->mTypeBien);
   ModelAnnonce::qPrint(this->mTypeAnnonce);

   ModelAnnonce::qPrint(this->mAdresse1);
   ModelAnnonce::qPrint(this->mAdresse2);
   ModelAnnonce::qPrint(this->mAdresse3);
   ModelAnnonce::qPrint(this->mDescription);
   ModelAnnonce::qPrint(this->mPhotoContractuelle);

   ModelAnnonce::qPrint(QString::number(this->mSurfaceHabitable));
   ModelAnnonce::qPrint(QString::number(this->mSuperficieTerrain));
   ModelAnnonce::qPrint(QString::number(this->mNombrePiece));
   ModelAnnonce::qPrint(QString::number(this->mPrix));
}

void ModelAnnonce::qPrint(QString s) {
    qDebug(s.toStdString().c_str());
}

ModelAnnonce::~ModelAnnonce() {

}
