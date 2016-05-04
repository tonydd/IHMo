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
ModelAnnonce::ModelAnnonce(int piIdAnnonce,
                         QString peTypeBien,
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
    mIdAnnonce = piIdAnnonce;
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
    mEstOccupe = false;
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

QDomElement ModelAnnonce::annonceToXml(QDomDocument &d){
    QDomElement a = d.createElement("Annonce");

    a.setAttribute("mIdAnnonce", this->mIdAnnonce);
    a.setAttribute("mTypeBien", this->mTypeBien);
    a.setAttribute("mTypeAnnonce", this->mTypeAnnonce);
    a.setAttribute("mSurfaceHabitable", QString::number(this->mSurfaceHabitable, ','));
    a.setAttribute("mSuperficieTerrain", QString::number(this->mSuperficieTerrain, ','));
    a.setAttribute("mNombrePiece", QString::number(this->mNombrePiece));
    a.setAttribute("mAdresse1", this->mAdresse1);
    a.setAttribute("mAdresse2", this->mAdresse2);
    a.setAttribute("mAdresse3", this->mAdresse3);
    a.setAttribute("mDescription", this->mDescription);
    a.setAttribute("mPrix", QString::number(this->mPrix, ','));
    a.setAttribute("mPhotoContractuelle", this->mPhotoContractuelle);
    a.setAttribute("mCreation", QString(this->mCreation.toString("dd/MM/yyyy")));
    a.setAttribute("mLastUpdate", QString(this->mLastUpdate.toString("dd/MM/yyyy")));
    a.setAttribute("mFin", QString(this->mFin.toString("dd/MM/yyyy")));
    a.setAttribute("mEstOccupe", QString::number(this->mEstOccupe));
    a.setAttribute("mNomAcheteur", QString(this->mNomAcheteur));

    return a;
}

void ModelAnnonce::annonceFromXml(QDomElement &d){
    this->mIdAnnonce = d.attribute("mIdAnnonce","").toInt();
    this->mTypeBien = d.attribute("mTypeBien","");
    this->mTypeAnnonce = d.attribute("mTypeAnnonce", "");
    this->mSurfaceHabitable = d.attribute("mSurfaceHabitable","").toDouble();
    this->mSuperficieTerrain = d.attribute("mSuperficieTerrain","").toDouble();
    this->mNombrePiece = d.attribute("mNombrePiece","").toInt();
    this->mAdresse1 = d.attribute("mAdresse1","");
    this->mAdresse2 = d.attribute("mAdresse2","");
    this->mAdresse3 = d.attribute("mAdresse3","");
    this->mDescription = d.attribute("mDescription","");
    this->mPrix = d.attribute("mPrix","").toDouble();
    this->mPhotoContractuelle = d.attribute("mPhotoContractuelle","");

    this->mCreation = QDate::fromString(d.attribute("mCreation",""), "dd/MM/yyyy");
    this->mLastUpdate = QDate::fromString(d.attribute("mLastUpdate",""), "dd/MM/yyyy");
    this->mFin = QDate::fromString(d.attribute("mFin",""), "dd/MM/yyyy");
    this->mEstOccupe = d.attribute("mEstOccupe","").toInt() != 0;
    this->mNomAcheteur = d.attribute("mNomAcheteur","");
    this->toString();
}

ModelAnnonce::ModelAnnonce(){
    mIdAnnonce = 0;
    mTypeBien = "";
    mTypeAnnonce = "";
    mSurfaceHabitable = 0;
    mSuperficieTerrain = 0;
    mNombrePiece = 0;
    mAdresse1 = "";
    mAdresse2 = "";
    mAdresse3 = "";
    mDescription = "";
    mPrix = 0;
    mPhotoContractuelle = "";
}

void ModelAnnonce::qPrint(QString s) {
    qDebug(s.toStdString().c_str());
}

void ModelAnnonce::setCreationDate(QDate d) {
    mCreation = d;
}

void ModelAnnonce::setLastUpdate(QDate d) {
    mLastUpdate = d;
}

void ModelAnnonce::setEstOccupe(bool b){
    if(b){
        mEstOccupe = b;
        mFin = QDate::currentDate();
        mLastUpdate = mFin = QDate::currentDate();
    } else {
        mEstOccupe = b;
        mFin = QDate();
        mFin = QDate::currentDate();
    }
}

ModelAnnonce::~ModelAnnonce() {

}
