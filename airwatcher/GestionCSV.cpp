/*************************************************************************
                           GestionsCSV  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

// - Réalisation de la classe <GestionCSV> (fichier GestionCSV.cpp) --
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>
#include <iostream>
#include <utility>
#include <iterator>
#include <list>
//#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "GestionCSV.h"


tm GestionCSV::gettimem(string time){//methode qui renvoie un mt a partir d'un string
    int count=0;

    //les chaines de caractères contenant les dates ont toutes le même format donc on recupere des sous chaines
    string syear=time.substr(0,4);

    string smonth=time.substr(5,2);

    string sday=time.substr(8,2);

    string shour=time.substr(11,2);

    string smin=time.substr(14,2);

    string ssec=time.substr(17,2);



    int year=stoi(syear);
    int month=stoi(smonth);
    int day=stoi(sday);
    int hour=stoi(shour);
    int min=stoi(smin);
    int sec=stoi(ssec);

    tm timestamp;
    timestamp.tm_year=year-1900; //l'annee dans les tm correspond aux nombres d'annes depuis 1900
    timestamp.tm_mon=month-1; //les mois correspondent au nombre de mois depuis janvier
    timestamp.tm_hour=hour;
    timestamp.tm_mday=day;
    timestamp.tm_sec=sec;
    timestamp.tm_min=min;

    return timestamp;
}

//----------------------------------------------------------------- PUBLIC
void GestionCSV::ParseMeasure(ifstream &input, list<Measure>& listMeasure, const list<MeasureType>& listMeasureType, list<UtilisateurPrive>& sensorUP)
{
  int i=0;
    while (input.peek()!=EOF) // si le fichier est pas fini
    {
        i++;
        if(input.fail())
        {
          cout << "problem" << endl;
        }
            string time;
            string sensorId;
            string measureType;
            string value;
            string ntg;

            std::getline(input, time, ';');
            std::getline(input, sensorId, ';');
            std::getline(input, measureType, ';');
            std::getline(input, value, ';');
            std::getline(input, ntg, '\n');

            float v=stof(value); //string to float

           if(time=="" && sensorId =="" && measureType=="" && value=="")
            {
              break;
            }

             tm timestamp=gettimem(time);

             list<UtilisateurPrive>::iterator it;
             for(it=sensorUP.begin(); it!=sensorUP.end(); it++)
             {
               if(sensorId.compare(it->getSensor())==0)
               {
                 it->setNbPoints(it->getNbPoints()+1);
               }
             }
            for(MeasureType m : listMeasureType)
            {
                if (m.getID().compare(measureType)==0){
                    Measure measure(timestamp, v, m, sensorId);
                    listMeasure.push_back(measure);
                    break;
            }
          }
    }

    input.close();
}



void GestionCSV::ParseMeasureType(ifstream &input, list<MeasureType>& listMeasureType)
{

  string title;
  string inutile;
  std::getline(input, title); // pour enlever le titre du fichier

    while (input.peek()!=EOF) // si le fichier est pas fini
    {
            string attributeId;
            string unit;
            string description;

            std::getline(input, attributeId, ';');
            std::getline(input, unit, ';');
            std::getline(input, description, ';');
        std::getline(input, inutile); // pour enlever le retour a la ligne

            if(attributeId=="" || unit =="" || description=="")
            {
              break;
            }

            MeasureType m(unit, description, attributeId);

            listMeasureType.push_back(m);
    }


    input.close();
}

void GestionCSV::ParseCleaner(ifstream &input, list<Cleaner>& listCleaners)
{

    int i=0;
    while (input.peek()!=EOF) // si le fichier est pas fini
    {
            ++i;
            string cleanerId;
            string latitude;
            string longitude;
            string description;
            string dateDebut;
            string dateFin;


            std::getline(input, cleanerId, ';');
            std::getline(input, latitude, ';');
            std::getline(input, longitude, ';');
            std::getline(input, description, ';');
            std::getline(input, dateDebut, ';');
            std::getline(input, dateFin, ';');

            if(i>1)
            {
              cleanerId.replace(0,1,"");
            }

            //si on recupere un element vide on sort de la boucle
            if(cleanerId=="" || latitude =="" || longitude =="" || dateDebut == "" || dateFin == ""){
                break;
            }

            tm* dD = new tm();
            *dD=gettimem(dateDebut);
            tm* dF = new tm();
            *dF=gettimem(dateFin);
            Cleaner c(latitude, longitude, cleanerId, description, dD, dF);

            listCleaners.push_back(c);

            delete dD;
            delete dF;
    }

    input.close();
}

void GestionCSV::ParseProvider(ifstream &input, list<Provider>& listProvider)
{


    while (input.peek()!=EOF) // si le fichier est pas fini
    {

            string providerId;
            string cleanerId;


            std::getline(input, providerId, ';');
            std::getline(input, cleanerId, ';');

            Provider nouveauProvider(providerId, cleanerId);

            listProvider.push_back(nouveauProvider);

    }


    input.close();
}


void GestionCSV::ParseSensor(ifstream &input, list<Sensor>& listSensor)
{
    while (input.peek()!=EOF) // si le fichier est pas fini
    {

            string sensorId;
            string latitude;
            string longitude;
            string title;
            string inutile;

            std::getline(input, sensorId, ';');
            std::getline(input, latitude, ';');
            std::getline(input, longitude, ';');
            std::getline(input, inutile);

            if(sensorId=="" || latitude=="" || longitude=="")
            {
                break;
            }

            Sensor nouveauSensor(sensorId, latitude, longitude);

            listSensor.push_back(nouveauSensor);

    }


    input.close();
}
void GestionCSV::ParseUser(ifstream &input, list<UtilisateurPrive>& listUP)
{


   while (input.peek()!=EOF) // si le fichier est pas fini
   {

           string userId;
           string sensorId;


           std::getline(input, userId, ';');
           std::getline(input, sensorId, ';');

           if(userId=="" || sensorId=="")
           {
               break;
           }

           UtilisateurPrive nouveauUP(userId, sensorId);

           listUP.push_back(nouveauUP);

   }


   input.close();
}

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
