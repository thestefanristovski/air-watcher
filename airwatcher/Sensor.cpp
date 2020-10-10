/*************************************************************************
                           Sensor  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- R�alisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <iostream>
#include <ctime>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques

string Sensor::getID() const{
    return sensorID;
}

string Sensor::getLatitude() {
    return latitude;
}

string Sensor::getLongitude() {
    return longitude;
}

bool Sensor::getLabel() {
    return label;
}

void Sensor::setID(string unID) {
    sensorID = unID;
}

void Sensor::setLatitude(string unLatitude) {
    latitude = unLatitude;
}

void Sensor::setLongitude(string unLongitude) {
    longitude = unLongitude;
}

void Sensor::setLabel(bool unLabel) {
    label = unLabel;
}

//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <Sensor>" << endl;
    #endif
    sensorID="";
    latitude="";
    longitude="";
    label=true;                                                                        //NULL?????????
} //----- Fin de Sensor

Sensor::Sensor (string unID, string unLatitude, string unLongitude)
{
    #ifdef MAP
        cout << "Appel au constructeur de <Sensor>" << endl;
    #endif
    sensorID = unID;
    latitude = unLatitude;
    longitude = unLongitude;
    label = true; //a priori tous les sensors sont fiables
} //----- Fin de Sensor



Sensor::~Sensor ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
} //----- Fin de ~Sensor



//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es
