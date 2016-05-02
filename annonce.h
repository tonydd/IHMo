#ifndef ANNONCE_H
#define ANNONCE_H

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
    void setValues(int index,
            QString typeBien, QString typeAnnonce, double surfaceHabitable,
            double superficieTerrain, int nbPieces, QString description,
            QString adr1, QString adr2, QString adr3, double prix, QString photo);
    ~Annonce();

private:
    QString imageFile;
    Ui::Annonce *ui;
    bool edition;
    int editing_index = -1;

    void loadTypes();
    void loadNbPieces();

private slots:
    void accept();
    void openImageFile();
};

#endif // ANNONCE_H
