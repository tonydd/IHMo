#ifndef MODELANNONCE_H
#define MODELANNONCE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <QString>
#include <QStringList>
#include <QDate>


class ModelAnnonce
{
public:

    // -- Méthodes

    ModelAnnonce(QString peTypeBien,
             QString peTypeAnnonce,
             double pdblSurfaceHabitable,
             double pdblSuperficieTerrain,
             int piNombrePiece,
             QString pstrAdresse1,
             QString pstrAdresse2,
             QString pstrAddresse3,
             QString pstrDescription,
             double pdblPrix,
             QString ptbPhotoContractuelle
        );


    char* readFileBytes(const char *name);
    void toString();
    static void qPrint(QString s);

    // -- Attributs
    QString mTypeBien;
    QString mTypeAnnonce;
    double mSurfaceHabitable;
    double mSuperficieTerrain;
    int mNombrePiece;
    QString mAdresse1;
    QString mAdresse2;
    QString mAdresse3;
    QString mDescription;

    double mPrix;

    QString mPhotoContractuelle;
    QStringList mGallerie;

    QDate mCreation;
    QDate mLastUpdate;
    QDate mFin;

    // -- Méthodes
    void setCreationDate(QDate d);
    void setLastUpdate(QDate d);

    ~ModelAnnonce();
protected:


};

#endif // MODELANNONCE_H
