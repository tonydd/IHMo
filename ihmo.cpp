#include "ihmo.h"
#include "ui_ihmo.h"

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
