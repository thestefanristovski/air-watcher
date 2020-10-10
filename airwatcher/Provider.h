/*************************************************************************
                           Provider  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Interface de la classe <Provider> (fichier Provider.h) ----------------
#if ! defined ( Provider_H )
#define PROVIDER_H

//--------------------------------------------------- Interfaces utilis閑s
#include <string>
#include "Cleaner.h"
#include <list>
using namespace std;
using std::string;



class Provider
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques

    //methode pour ajouter un nouveau cleaner a la liste
    bool ajouterCleaner(Cleaner Newcleaner, list <Cleaner> & cleaners);

    //methode pour supprimer un cleaner existant dans la liste
    bool supprimerCleaner(string cleanerId, list <Cleaner> & cleaners);

    //getters
    string getID();

    string getcleanerID();

    //setters
    void setcleanerID(string uncleanerID);

    void setID(string unproviderID);

    //-------------------------------------------- Constructeurs - destructeur
    Provider();

    Provider(string providerID, string cleanerID);

    virtual ~Provider();


//------------------------------------------------------------------ PRIVE

protected:

    string providerID;
    string cleanerID;

};



#endif // PROVIDER_H
