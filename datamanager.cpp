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

int Datamanager::getNewIdAnnonce(){
    int ret = 1;
    if (this->annonces->length() > 0){
        this->annonces->last().mIdAnnonce + 1;
    }
    return ret;
}

void Datamanager::updateAnnonce(ModelAnnonce a, int index) {
    this->getAnnonces()->replace(index, a);
}

void Datamanager::deleteAnnonce(int idx) {
    this->getAnnonces()->removeAt(idx);
}

// -- Persistance des données
bool Datamanager::saveToXML() {
    QDomDocument *doc = new QDomDocument("ListeAnnonceXML");
    QDomElement root = doc->createElement("ListeAnnonce");
    doc->appendChild(root);
    QDomText var;


    for (int i = 0; i < this->annonces->count(); i++){
        ModelAnnonce a = this->annonces->at(i);
        root.appendChild(a.annonceToXml(*doc));
    }

    QFile fichier("annonces.xml");

    if(!fichier.open(QIODevice::WriteOnly))
    {
        fichier.close();
        return false;
    }

    QString write_doc = doc->toString();
    QTextStream stream(&fichier);
    stream << write_doc;
    fichier.close();
    return true;
}

QString Datamanager::loadFromXML() {
    QDomDocument *doc = new QDomDocument("ListeAnnonceXML");
    QFile fichier("annonces.xml");
    if(!fichier.open(QIODevice::ReadOnly))// Si l'on n'arrive pas à ouvrir le fichier XML.
    {
         return "Erreur lors de l'ouverture du fichier";
    }

    if (!doc->setContent(&fichier)) // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.
    {
         fichier.close();

         return "Erreur lors du chargement du XML";
    }

    QDomElement dom_element = doc->documentElement();

    QDomElement element = dom_element.firstChildElement();


    qDebug(QString("Test").toStdString().c_str());
    while(!element.isNull())// Tant que le nœud n'est pas vide.
    {
        ModelAnnonce *a = new ModelAnnonce();
        a->annonceFromXml(element);
        this->annonces->append(*a);
        element = element.nextSiblingElement();
    }

    fichier.close();
    return "Chargement effectué avec succès";
}

Datamanager *Datamanager::getInstance() {
    return instance;
}
