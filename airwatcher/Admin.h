/*************************************************************************
Admin
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Interface de la classe <Admin> (fichier Admin.h) ------
#if ! defined ( ADMIN_H )
#define ADMIN_H
//--------------------------------------------------- Interfaces utilisees
#include <cstring>
#include <string>
using std::string;
using namespace std;
#include "Utilisateur.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------

//------------------------------------------------------------------------
class Admin:public Utilisateur {

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Methodes publiques
public:
	Admin ();

	Admin (string prenom, string nom);

	void setPrenom (string prenom);

	string getNom ();

	void setNom (string nom);

	string getPrenom ();

	bool ajouterUtilisateur (long Id);

	bool supprimerUtilisateur (long Id);

	bool modifierUtilisateur (long Id);

	~Admin ();


//---------------------------------------------------- Attributs publiques

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Methodes protected

private:
//------------------------------------------------------- Methodes prives

protected:
//----------------------------------------------------- Attributs protected

private:
//------------------------------------------------------- Attributs prives
	string prenom;
	string nom;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes prives

//----------------------------------------------------------- Types prives
};
//----------------------------------------- Types dependants de <Admin.h>
#endif // ADMIN_H
