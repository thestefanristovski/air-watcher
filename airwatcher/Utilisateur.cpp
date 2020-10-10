/*************************************************************************
                           Utilisateur  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/
//---------- Realisation de la classe <Utilisateur> (fichier Utilisateur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
#include <iostream>
#include <cstring>
#include <string>
using std::string;
using namespace std;
//------------------------------------------------------ Include personnel
#include "Utilisateur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M��thodes publiques
long Utilisateur::IdCompteur = 1; // Initialisation de compteur Id

Utilisateur::Utilisateur (){}

Utilisateur::Utilisateur (string login, string mdp){
	this->login = login;
	this->mdp = mdp;
	this->utilisateurID = IdCompteur;
	IdCompteur++;
}

long Utilisateur::getId (){
	return utilisateurID;
}

string Utilisateur::getLogin (){
	return login;
}

string Utilisateur::getMdp (){
	return mdp;
}

void Utilisateur::setLogin (string login){
	this->login = login;
}

void Utilisateur::setMdp (string mdp){
	this->mdp = mdp;
}

Utilisateur::~Utilisateur(){
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protected

//------------------------------------------------------- Methodes privees
