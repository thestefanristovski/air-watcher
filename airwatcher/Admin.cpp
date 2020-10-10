/*************************************************************************
Admin  -  description
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/
//---------- Realisation de la classe <Admin> (fichier Admin.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
#include <cstring>
#include <string>
using std::string;
using namespace std;
//------------------------------------------------------ Include personnel
#include "Admin.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M��thodes publiques
Admin::Admin (){}

Admin::Admin (string prenom, string nom){
	this->prenom = prenom;
	this->nom = nom;
}

string Admin::getPrenom (){
	return prenom;
}

string Admin::getNom (){
	return nom;
}

void Admin::setPrenom (string prenom){
	this->prenom = prenom;
}

void Admin::setNom (string nom){
	this->nom = nom;
}

Admin::~Admin(){}

bool Admin::ajouterUtilisateur (long Id){
	return true;      //S'il reste de temps, on peut le completer
}

bool Admin::supprimerUtilisateur (long Id){
	return true;      //S'il reste de temps, on peut le completer
}

bool Admin::modifierUtilisateur (long Id){
	return true;      //S'il reste de temps, on peut le completer
}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protected

//------------------------------------------------------- Methodes privees
