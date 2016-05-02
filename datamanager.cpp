#include "datamanager.h"

Datamanager::Datamanager()
{
}

QList<ModelAnnonce> Datamanager::getAnnonces() {
    return this->annonces;
}

ModelAnnonce Datamanager::getAnnonce(int index) {
    return this->getAnnonces().at(index);
}

void Datamanager::registerAnnonce(ModelAnnonce a) {
    this->getAnnonces().append(a);
}
