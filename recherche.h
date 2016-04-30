#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <QDialog>

namespace Ui {
class Recherche;
}

class Recherche : public QDialog
{
    Q_OBJECT

public:
    explicit Recherche(QWidget *parent = 0);
    ~Recherche();

private:
    Ui::Recherche *ui;
};

#endif // RECHERCHE_H
