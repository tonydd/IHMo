#include "recherche.h"
#include "ui_recherche.h"

Recherche::Recherche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recherche)
{
    ui->setupUi(this);
}

Recherche::~Recherche()
{
    delete ui;
}
