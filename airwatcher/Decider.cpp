/*************************************************************************
                           Decider  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/
//---------- Realisation de la classe <Decider> (fichier Decider.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
#include <cstring>
#include <string>
#include <list>
using std::string;
using namespace std;
//------------------------------------------------------ Include personnel
#include "Decider.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques
Decider::Decider (){}

float Decider::fiabiliteUtilisateur (long Id, list <UtilisateurPrive> & users){
	list<UtilisateurPrive> :: iterator debut, fin;
	debut = users.begin();
	fin = users.end();
	while(debut != fin){
		if(debut -> getId() == Id){
		return debut -> getNoteFiabilite();
		}
		debut++;
	}
	return -1.0; //Si ce Id n'existe pas, on envoie -1.0.
}

Decider::~Decider(){
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protected

//------------------------------------------------------- Methodes privees
