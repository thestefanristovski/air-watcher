/*************************************************************************
                           Sensor  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------
#if ! defined ( SENSOR_H )
#define SENSOR_H

//--------------------------------------------------- Interfaces utilis�es
#include <ctime>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <Sensor>
//
//
//------------------------------------------------------------------------

class Sensor
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
//getters
    string getID() const;
    string getLatitude();
    string getLongitude();
    bool getLabel();

//setters
    void setLatitude(string unLatitude);
    void setLongitude(string unLongitude);
    void setLabel(bool unLabel);
    void setID(string unID);

//-------------------------------------------- Constructeurs - destructeur
    Sensor ( );

    Sensor (string unID, string unLatitude, string unLongitude);

    virtual ~Sensor ( );


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- M�thodes prot�g�es

//----------------------------------------------------- Attributs prot�g�s
string sensorID; //identifiant
//coordonnees
string latitude;
string longitude;
//label sur la fidelite du sensor
bool label;

};

//-------------------------------- Autres d�finitions d�pendantes de <Sensor>

#endif // Sensor_H
