/*************************************************************************
                           Utilisateur  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Interface de la classe <Utilisateur> (fichier Utilisateur.h) ------
#if ! defined ( UTILISATEUR_H )
#define UTILISATEUR_H
//--------------------------------------------------- Interfaces utilisees
#include <cstring>
#include <string>
using std::string;
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------

//------------------------------------------------------------------------

class Utilisateur{

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Methodes publiques
public:
	Utilisateur ();

	Utilisateur (string login, string mdp);

//getters
	long getId ();

	string getLogin ();

	string getMdp ();
//setters
	void setLogin (string login);

	void setMdp (string mdp);

	virtual ~Utilisateur();


//---------------------------------------------------- Attributs publiques
	static long IdCompteur;
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protected
	long utilisateurID;
	string login;
	string mdp;
private:
//------------------------------------------------------- Attributs prives

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes prives

//----------------------------------------------------------- Types prives
};
//----------------------------------------- Types dependants de <Utilisateur.h>
#endif // UTILISATEUR_H
