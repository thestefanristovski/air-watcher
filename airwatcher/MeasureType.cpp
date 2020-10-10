/*************************************************************************
                           MeasureType  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Réalisation de la classe <MeasureType> (fichier MeasureType.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "MeasureType.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type MeasureType::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//-------------------------------------------- Constructeurs - destructeur
MeasureType::MeasureType ( string unit, string description, string id )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <MeasureType>" << endl;
#endif

this->unit=unit;
this->description=description;
this->attributeID=id;
} //----- Fin de MeasureType (constructeur de copie)


MeasureType::MeasureType ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <MeasureType>" << endl;
#endif
this->unit="";
this->description="";
this->attributeID="";
} //----- Fin de MeasureType

string MeasureType::getUnit(){
    return this->unit;
}

string MeasureType::getID()
{
    return this->attributeID;
}

void MeasureType::setUnit(string unit){
    this->unit=unit;
}

string MeasureType::getDescription(){
    return this->description;
}

void MeasureType::setDescription(string description){
    this->description=description;
}


MeasureType::~MeasureType ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <MeasureType>" << endl;
#endif
} //----- Fin de ~MeasureType


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
