#ifndef ANNONCE_H
#define ANNONCE_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMessageBox>

namespace Ui {
class Annonce;
}

class Annonce : public QDialog
{
    Q_OBJECT

public:
    explicit Annonce(QWidget *parent = 0);
    ~Annonce();

private:
    Ui::Annonce *ui;
    void loadTypes();
    void loadNbPieces();

private slots:
    void accept();
    void openImageFile();
};

#endif // ANNONCE_H
