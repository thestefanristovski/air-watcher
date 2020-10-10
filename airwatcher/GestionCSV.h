/*************************************************************************
                           GestionCSV  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---- Interface de la classe <GestionCSV> (fichier GestionCSV.h) ----------
#if !defined(GestionCSV_H)
#define GestionCSV_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
#include <iostream>
#include<list>
#include "Measure.h"
#include "MeasureType.h"
#include "Cleaner.h"
#include "Provider.h"
#include "Sensor.h"
#include "UtilisateurPrive.h"
#include <string>

#include <time.h>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------------
// Rôle de la classe <GestionCSV>
// La classe GestionCSV permet de lire une liste de Trip à partir d'un fichier
// Elle est notamment utilisée pour gérer le filtrage (spécifications pour l'enregistrement
// ou chargement de fichiers)
//
// Cette classe contient tout le code nécessaire pour acquérir des trajets issus
// d'un fichier spécifié par l'utilisateur.
// La méthode Parse() est appelée lorsque l'utilisateur souhaite télécharger
// des trajets depuis un fichier.
// Les méthodes de filtrage (FiltreParType(), FiltreParIndex(),
// FiltreParNom()) sont optionnellement appelées si l'utilisateur indique
// vouloir appliquer des spécifications aux trajets qu'il sauvegarde ou
// télécharge.
//------------------------------------------------------------------------

class GestionCSV
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    static tm gettimem(string time); // methode qui transforme un string de date en un objet de type tm

    //methode pour recuperer les infos des mesures depuis les CSV
    static void ParseMeasure(ifstream &input, list<Measure>& listMeasure, const list<MeasureType>& listMeasureType, list<UtilisateurPrive>& sensorUP);

    //methode pour recuperer les infos des types de mesures depuis les CSV
    static void ParseMeasureType(ifstream &input, list<MeasureType>& listMeasureType);

    //methode pour recuperer les infos des Cleaners depuis les CSV
    static void ParseCleaner(ifstream &input, list<Cleaner>& listCleaners);

    //methode pour recuperer les infos des Providers depuis les CSV
    static void ParseProvider(ifstream &input, list<Provider>& listProvider);

    //methode pour recuperer les infos des Sensors depuis les CSV
    static void ParseSensor(ifstream &input, list<Sensor>& listSensor);

    //methode pour recuperer les infos des Utilisateurs privés depuis les CSV
    static void ParseUser(ifstream &input, list<UtilisateurPrive>& listUP);



    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};

#endif // GestionCSV_H
