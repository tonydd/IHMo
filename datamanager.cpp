#include "datamanager.h"

Datamanager *Datamanager::instance = new Datamanager;

Datamanager::Datamanager()
{
    this->annonces = new QList<ModelAnnonce>;

    // -- C'est ici qu'on récup le XML
    //this->loadFromXML();
}

QList<ModelAnnonce> *Datamanager::getAnnonces() {
    return this->annonces;
}

ModelAnnonce Datamanager::getAnnonce(int index) {
    return this->getAnnonces()->at(index);
}

void Datamanager::registerAnnonce(ModelAnnonce a) {
    this->getAnnonces()->append(a);
}

void Datamanager::updateAnnonce(ModelAnnonce a, int index) {
    this->getAnnonces()->replace(index, a);
}

void Datamanager::deleteAnnonce(int idx) {
    this->getAnnonces()->removeAt(idx);
}

// -- Persistance des données
void Datamanager::saveToXML() {

}

void Datamanager::loadFromXML() {

}

Datamanager *Datamanager::getInstance() {
    return instance;
}
