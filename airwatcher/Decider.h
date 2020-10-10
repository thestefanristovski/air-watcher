/*************************************************************************
                           Decider  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Interface de la classe <Decider > (fichier Decider.h) ------
#if ! defined ( DECIDER_H )
#define DECIDER_H
//--------------------------------------------------- Interfaces utilisees
#include <cstring>
#include <string>
#include <list>
using std::string;
using namespace std;
#include "Utilisateur.h"
#include "UtilisateurPrive.h"

class Decider:public Utilisateur {

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Methodes publiques
public:

	Decider ();

	float fiabiliteUtilisateur (long Id, list <UtilisateurPrive> & users); //retourne la note de fiabilité d'un utilisateur passé en paramètre

	~Decider ();

};
//----------------------------------------- Types dependants de <Decider.h>
#endif // DECIDER_H
