#include "annonce.h"
#include "ui_annonce.h"

Annonce::Annonce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Annonce)
{
    ui->setupUi(this);
}

Annonce::~Annonce()
{
    delete ui;
}
