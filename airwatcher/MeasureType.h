/*************************************************************************
                           MeasureType  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Interface de la classe <MeasureType> (fichier MeasureType.h) ----------------
#if ! defined ( MeasureType_H )
#define MeasureType_H

#include <string.h>
using namespace std;



class MeasureType
{
//----------------------------------------------------------------- PUBLIC

public:

//-------------------------------------------- Constructeurs
    MeasureType (string unit, string description, string id);

    MeasureType ();

//-------------------------------------------- getters

    string getUnit();

    string getID();

    string getDescription();

//-------------------------------------------- setters

    void setUnit(string unit);

    void setDescription(string description);

    virtual ~MeasureType ( );



protected:

//----------------------------------------------------- Attributs protégés

string attributeID;
string unit;
string description;

};

//-------------------------------- Autres définitions dépendantes de <MeasureType>

#endif // MeasureType_H
