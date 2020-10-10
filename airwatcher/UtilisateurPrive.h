
/*************************************************************************
                           UtilisateurPrive  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Interface de la classe <UtilisateurPrive> (fichier UtilisateurPrive.h) ----------------
#if ! defined ( UTILISATEURPRIVE_H )
#define UTILISATEURPRIVE_H

//--------------------------------------------------- Interfaces utilis�es
#include <ctime>
#include "Utilisateur.h"


class UtilisateurPrive : public Utilisateur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
//getters
    int getNbPoints();
    string getSensor();
    float getNoteFiabilite();

//setters
    void setNoteFiabilite(float uneNote);
    void setSensor(string unSensorID);
    void setNbPoints(int unNbPoints);

//-------------------------------------------- Constructeurs - destructeur
    UtilisateurPrive ( );

    UtilisateurPrive (string unLogin, string unSensorID);

    virtual ~UtilisateurPrive ( );


protected:

//----------------------------------------------------- Attributs prot�g�s
int nbPoints; //les utilisateurs gagnent des points au fur et a mesure qu'ils font des mesures
float noteFiabilite; //la note de fiablite qui lui est affectée en fonction de l'exactitude de ses mesures
string sensorID;

};


#endif // UTILISATEURPRIVE_H
