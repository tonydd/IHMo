#ifndef ANNONCE_H
#define ANNONCE_H

#include "ihmo.h"
#include "Models/modelannonce.h"
#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace Ui {
class Annonce;
}

class Annonce : public QDialog
{
    Q_OBJECT

public:
    explicit Annonce(QWidget *parent = 0);
    void setW(IHMo *w);
    void setValues(int index,
            QString typeBien, QString typeAnnonce, double surfaceHabitable,
            double superficieTerrain, int nbPieces, QString description,
            QString adr1, QString adr2, QString adr3, double prix, QString photo, QDate crea);
    void setAnnonce(ModelAnnonce a);
    int editing_index;
    ModelAnnonce mAnnonce;
    ~Annonce();

private:
    QString imageFile;
    Ui::Annonce *ui;
    bool edition;

    IHMo *w;

    void loadTypes();
    void loadNbPieces();

private slots:
    void accept();
    void openImageFile();
    void setEstOccupe(bool b);
};

#endif // ANNONCE_H
