#include "ihmo.h"
#include "ui_ihmo.h"
#include "annonce.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>

IHMo::IHMo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IHMo)
{
    ui->setupUi(this);
}

IHMo::~IHMo()
{
    delete ui;
}

void IHMo::addAnnonce() {
    Annonce *annonce = new Annonce;
    annonce->show();
}

void IHMo::searchAnnonce() {

}

void IHMo::showAPropos() {
    QMessageBox::information(this,"A propos","Version 1.0\nAnthony Den Drijver & Thomas Stocker\nIHM L3IS6P 2016");
}

void IHMo::showAide() {
    QDir dirObj = QDir::current();
    dirObj.cdUp();
    QString path = dirObj.path();


    QString helpFile = path+"/Aide.pdf";

    QDesktopServices::openUrl(QUrl("file://" +  helpFile));
}

void IHMo::registerAnnonce(ModelAnnonce a) {
    IHMo::annonces.append(a);
}
