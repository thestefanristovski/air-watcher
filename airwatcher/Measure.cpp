/*************************************************************************
                           Measure  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Réalisation de la classe <Measure> (fichier Measure.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Measure.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Measure::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//-------------------------------------------- Constructeurs - destructeur
Measure::Measure(tm Timestamp, float value, MeasureType mt, string sensId)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Measure>" << endl;
#endif
  //  this->measureID=CSVgetLastID()+1; //il faut creer une fonction dans gestion csv pour recup le dernier ID
    this->Timestamp=Timestamp;
    this->value=value;
    this->mt=mt;
    this->sensorID=sensId;
} //----- Fin de Measure (constructeur de copie)

Measure::Measure ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Measure>" << endl;
#endif
  //  this->measureID=CSVgetLastID()+1; //il faut creer une fonction dans gestion csv pour recup le dernier ID
    this->Timestamp=Timestamp;
    this->value=0;
    this->mt=MeasureType();
} //----- Fin de Measure


Measure::~Measure ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Measure>" << endl;
#endif
} //----- Fin de ~Measure


tm Measure::getTime(){
    return this->Timestamp;
}

string Measure::getSensorID(){
    return this->sensorID;
}

MeasureType Measure::getMeasureType(){
    return this->mt;
}

float Measure::getValue(){
    return this->value;
}

void Measure::setTime(tm time){
    this->Timestamp=time;
}

void Measure::setValue(float value){
    this->value=value;
}

void Measure::setMeasureType(MeasureType mt)
{
    this->mt=mt;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
