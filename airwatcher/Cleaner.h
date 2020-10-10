/*************************************************************************
                           Cleaner  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Interface de la classe <Cleaner> (fichier Cleaner.h) ----------------
#if ! defined ( CLEANER_H )
#define CLEANER_H

//--------------------------------------------------- Interfaces utilis�es
#include <string>
#include <ctime>
using namespace std;
using std::string;


class Cleaner
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- M�thodes publiques

    //getters
    string getID();
    string getLatitude();
    string getLongitude();
    struct tm* getDateDebut();
    struct tm* getDateFin();
    string getDescription();

    //setters
    void setID(string uncleanerID);
    void setLatitute(string uneLatitute);
    void setLongitude(string uneLongitude);
    void setDateDebut(struct tm* uneDateDebut);
    void setDateFin(struct tm* uneDateFin);
    void setDescription(string uneDescription);


    //-------------------------------------------- Constructeurs - destructeur
    Cleaner();

    Cleaner(string unelatitude,string unelongitude,string uncleanerID,string unedescription, struct tm* unedateFin, struct tm* unedateDebut);

    virtual ~Cleaner();

protected:
    //----------------------------------------------------- Attributs prot�g�s
    string latitude;
    string longitude;
    string cleanerID;
    string description;
    struct tm* dateFin; //date de desinstallation du Cleaner
    struct tm* dateDebut; //date d'installation du Cleaner
    string providerID;


};

#endif // CLEANER_H
