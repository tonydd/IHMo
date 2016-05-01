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
    enum TYPE_BIEN{
        MAISON,
        APPARTEMENT,
        CHATEAU,
        FERME,
        BUREAU,
        COMMERCE,
        LOCAL
    };


    enum TYPE_ANNONCE{
        VENTE,
        LOCATION
    };
    Annonce(TYPE_BIEN peTypeBien,
             TYPE_ANNONCE peTypeAnnonce,
             double pdblSurfaceHabitable,
             double pdblSuperficieTerrain,
             int piNombrePiece,
             std::string pstrAdresse1,
             std::string pstrAdresse2,
             std::string pstrDescription,
             double pdblPrix,
             char* ptbPhotoContractuelle
             );
    char* readFileBytes(const char *name);

    explicit Annonce(QWidget *parent = 0);
    ~Annonce();

private:
    TYPE_BIEN mTypeBien;
    TYPE_ANNONCE mTypeAnnonce;
    double mSurfaceHabitable;
    double mSuperficieTerrain;
    int mNombrePiece;
    std::string mAdresse1;
    std::string mAdresse2;
    std::string mDescription;

    double mPrix;

    char* mPhotoContractuelle;
    std::vector<char*> mGallerie;

    Ui::Annonce *ui;
    void loadTypes();
    void loadNbPieces();

private slots:
    void accept();
    void openImageFile();
};

#endif // ANNONCE_H
