/*************************************************************************
                           UtilisateurPrive  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- R�alisation de la classe <UtilisateurPrive> (fichier UtilisateurPrive.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <iostream>
#include <ctime>
using namespace std;

//------------------------------------------------------ Include personnel
#include "UtilisateurPrive.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques

int UtilisateurPrive::getNbPoints() {
    return nbPoints;
}

string UtilisateurPrive::getSensor() {
    return sensorID;
}

float UtilisateurPrive::getNoteFiabilite() {
    return noteFiabilite;
}

void UtilisateurPrive::setNoteFiabilite(float uneNote) {
    noteFiabilite = uneNote;
}

void UtilisateurPrive::setSensor(string unSensorID) {
    sensorID = unSensorID;
}

void UtilisateurPrive::setNbPoints(int unNbPoints) {
    nbPoints = unNbPoints;
}

//-------------------------------------------- Constructeurs - destructeur
UtilisateurPrive::UtilisateurPrive ( ) : Utilisateur()
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <UtilisateurPrive>" << endl;
    #endif
    sensorID = "";
    noteFiabilite = 100.0;//a priori un utilisateur est tres fiable
    nbPoints = 0;
} //----- Fin de UtilisateurPrive


UtilisateurPrive::UtilisateurPrive (string unLogin, string unSensorID):Utilisateur(unLogin, "password")
{
    #ifdef MAP
        cout << "Appel au constructeur de <UtilisateurPrive>" << endl;
    #endif
    sensorID = unSensorID;
    noteFiabilite = 100.0;
    nbPoints = 0;
} //----- Fin de UtilisateurPrive



UtilisateurPrive::~UtilisateurPrive ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <UtilisateurPrive>" << endl;
#endif
} //----- Fin de ~UtilisateurPrive


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es
