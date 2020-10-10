/*************************************************************************
Main  -  description
-------------------
copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

#include <iostream>
#include <cstring>
#include <list>
#include "Decider.h"
#include "GestionCSV.h"
#include "Utilisateur.h"
#include <iterator>
#include <map>
#include <utility>
#include <chrono>

using namespace std;

#define INT_MAX 2147483647

//noms (chemins) de nos fichiers
const char* files[6] = {"attributes.csv", "sensors.csv", "cleaners.csv", "measurements.csv", "providers.csv", "users.csv" };
//listes globales accessibles partout
list<Measure> listMeasure;
list<MeasureType> listMeasureType;
list<Cleaner> listCleaners;
list<Provider> listProvider;
list<Sensor> listSensor;
list<UtilisateurPrive> listUP;
list<Sensor> listPrivateSensor;
list<UtilisateurPrive> listPrivateSensorUser;
list<Sensor> sensorsSimilaires;



struct sensCompare //operateur < pour sensor
{
  bool operator() (const Sensor& s1, const Sensor& s2) const
  {
    return s1.getID() < s2.getID();
  }
};

float rtod(float radians){ //rad to deg
  return radians*180.0/3.14;
}
void sensorsSimilairs(string lat, string lon, float rayonEnKm, int dureeEnMois, float precision){

  sensorsSimilaires.clear();
  const float earthRadiusInKm = 6371;

  //obtenir temps actuel
  time_t rawtime;
  struct tm * now;
  time (&rawtime);
  now = localtime (&rawtime); //right now in tm

  //obtenir nombre de mois et nombre d'annees de mesure
  int nbAnnees = (int)dureeEnMois/12+1;
  int nbMois = dureeEnMois%12;

  //obtenir rayon de mesure
  float radiusDegrees = rtod(rayonEnKm/earthRadiusInKm); //demi-taille de l'intervalle de lat/lon en degres
  float latitude = stof(lat);//string to float
  float longitude = stof(lon);
  map<Sensor, pair<float, unsigned int>, sensCompare> meanBySensor; //map des sensors avec leur moyenne de valeur et le nombre de valeurs ajoutees
  //(pour diviser apres), on profite de la boucle qui parcours deja les sensors
  for(Sensor s : listSensor)
  {
    //si sensor dans la bonne zone
    if((stof(s.getLatitude())<(latitude+radiusDegrees) && stof(s.getLatitude())>(latitude-radiusDegrees)) && (stof(s.getLongitude())<(longitude+radiusDegrees) && stof(s.getLongitude())>(longitude-radiusDegrees)))
    {
      pair<float, unsigned int> p = make_pair((float)0.0, (unsigned int)0);
      meanBySensor.insert({s, p});
    }
  }
  float mean=0;
  int totalMesures=0;
  for(Measure m : listMeasure)
  {
    if((now->tm_year-nbAnnees <= m.getTime().tm_year)&&(now->tm_mon-nbMois <= m.getTime().tm_mon)) //si la mesure a ete faite dans la duree predeterminee
    {
      ++totalMesures;
      mean+=m.getValue(); //ajouter sa valeur a la moyenne
      map<Sensor, pair<float, unsigned int>>::iterator it;
      for(it=meanBySensor.begin(); it!=meanBySensor.end(); ++it)
      {
        if(it->first.getID() == m.getSensorID()){
          it->second.first+=m.getValue();//on ajoute sa valeur a la moyenne du sensor
          ++it->second.second;//on incremente le nombre de mesures de ce sensor
        }
      }
    }
  }
  mean=mean/totalMesures;
  map<Sensor, pair<float, unsigned int>>::iterator it;
  for(it=meanBySensor.begin(); it!=meanBySensor.end(); ++it)
  {
    it->second.first/=it->second.second;
    if(it->second.first<mean*(1.0+precision) && it->second.first>mean*(1.0-precision))
    {
      sensorsSimilaires.push_back(it->first);
    }
  }
  return;
}
/////////////////////////Trouver les sensors d'utilisateurs privés////////////////////////////////
void labelliserMesure(bool affichage) {

  list<Sensor>::iterator it;
  string latitude;
  string longitude;
  bool found;
  int counter = -1;

  for(it=listPrivateSensor.begin(); it!= listPrivateSensor.end(); it++)
  {
    found = false;
    counter++;
    latitude = it->getLatitude();
    longitude = it->getLongitude();
    sensorsSimilairs(latitude, longitude, 150.0,12, 0.03);

    list<Sensor>::iterator it2;

    for(it2=sensorsSimilaires.begin(); it2!=sensorsSimilaires.end(); it2++) //on cherche l'utilisateur correspondant
    {
      if(it->getID().compare(it2->getID()) == 0)
      {
        found = true;
        break;
      }
    }

    if(!found) //s'il ne fait pas partie des sensors similaires dans sa zone
    {
      if(affichage)
      cout << "Le sensor privé d'ID : " << it->getID() << " fourni de fausses valeurs." << endl;
      list<UtilisateurPrive>::iterator up = listPrivateSensorUser.begin();
      advance(up, counter);
      if(affichage) {
        cout << "La précedente note de fiabilité de l'utilisateur: " << up->getNoteFiabilite();
        up->setNoteFiabilite(up->getNoteFiabilite()*0.5);
        cout << " devient : " << up->getNoteFiabilite() << endl;
        cout << "Les mesures provenant de ce sensor vont être supprimées. L'utilisateur n'est pas fiable." << endl;
      }

      list<Measure>::iterator m = listMeasure.begin();

      while(m!=listMeasure.end())
      {
        if(m->getSensorID().compare(it->getID())==0)
        {
          if(affichage) {
            listMeasure.erase(m++);
            list<UtilisateurPrive>::iterator pu;
            pu = listPrivateSensorUser.begin();
            advance(pu, counter);
            pu->setNbPoints(pu->getNbPoints()-1);
          } else {
            m++;
          }
        }else
        {
          m++;
        }
      }
    } else
    {
      if(affichage)
      cout << "Le sensor privé d'ID " << it->getID() << " ne semble pas fournir de fausses valeurs." << endl;
    }
  }

}

static void ParseSensorPrive()
{
  list<Sensor>::iterator it;
  for (it = listSensor.begin(); it != listSensor.end(); it++) {
    string id  = it->getID();
    list<UtilisateurPrive>::iterator up;
    for (up = listUP.begin() ; up!=listUP.end(); up++) {
      if (id.compare(up->getSensor())==0) {
        listPrivateSensor.push_back(*it);
        listPrivateSensorUser.push_back(*up);
        break;
      }
    }
  }
}

Sensor chercherSensorParId(string idSensor)
{
  list<Sensor>::iterator it;
  Sensor result;
  for (it=listSensor.begin(); it!=listSensor.end(); it++)
  {
    if(idSensor.compare(it->getID())==0)
    {
      result = *it;
      break;//on sort de la boucle si sensor trouvé
    }
  }
  return result;
}

void afficherNotesFiabilite()
{
  list<UtilisateurPrive>::iterator it;
  for (it=listPrivateSensorUser.begin(); it!=listPrivateSensorUser.end(); it++)
  {
    cout<<"Capteur: "+it->getSensor()<<" - note: "<<it->getNoteFiabilite()<<endl;
  }
}

void afficherNbPoints()
{
  list<UtilisateurPrive>::iterator it;
  for (it=listPrivateSensorUser.begin(); it!=listPrivateSensorUser.end(); it++)
  {
    cout<<"Capteur: "+it->getSensor()<<" - points: "<<it->getNbPoints()<<endl;
  }
}

bool supprimerCleaner(string id)
{
  bool res = false;
  list<Cleaner>::iterator it;
  for (it=listCleaners.begin(); it!=listCleaners.end(); it++)
  {
    if(id.compare(it->getID())==0)
    {
      listCleaners.erase(it);
      res = true;
      break;
    }
  }
  return res;
}

void aggregateInfo(string lat, string lon, int annee,int mois, bool affichage){
  annee = annee - 1900;
  const float earthRadiusInKm = 6371.0;
  const float rayonEnKm = 150.0;
  float radiusDegrees = rtod(rayonEnKm/earthRadiusInKm); //on calcule l'intervalle de coordonnees a considérer
  float latitude = stof(lat);
  float longitude = stof(lon);

  list <string> sensorsDansZone; //liste des sensors qui sont dans la zone choisie, seulement leurs ID sont dans la liste
  for(Sensor s : listSensor)
  {
    //si sensor dans la bonne zone
    if((stof(s.getLatitude())<(latitude+radiusDegrees) && stof(s.getLatitude())>(latitude-radiusDegrees)) && (stof(s.getLongitude())<(longitude+radiusDegrees) && stof(s.getLongitude())>(longitude-radiusDegrees)))
    {
      sensorsDansZone.push_back(s.getID());
    }
  }

  float moyPM10=0;
  float moySO2=0;
  float moyO3=0;
  float moyNO2=0;
  int totalMesuresPM10=0;
  int totalMesuresSO2=0;
  int totalMesuresO3=0;
  int totalMesuresNO2=0;

  for(Measure m : listMeasure)
  {
    //si la mesure a ete faite dans la duree predeterminee
    if((annee == m.getTime().tm_year)&&(mois == m.getTime().tm_mon+1))
    {
      list <string>::iterator debut, fin;
      debut = sensorsDansZone.begin();
      fin = sensorsDansZone.end();
      while(debut != fin){
        if((*debut).compare(m.getSensorID()) == 0){
          if(m.getMeasureType().getID().compare("PM10") == 0){
            totalMesuresPM10++;
            moyPM10 = moyPM10 + m.getValue();
          }else if(m.getMeasureType().getID().compare("SO2") == 0){
            totalMesuresSO2++;
            moySO2 = moySO2 + m.getValue();
          }else if(m.getMeasureType().getID().compare("O3") == 0){
            totalMesuresO3++;
            moyO3 = moyO3 + m.getValue();
          }else if(m.getMeasureType().getID().compare("NO2") == 0){
            totalMesuresNO2++;
            moyNO2 = moyNO2 + m.getValue();
          }
          break;
        }
        debut++;
      }
    }
  }
  //on calcule les moyennes
  moyPM10 = moyPM10/totalMesuresPM10;
  moySO2 = moySO2/totalMesuresSO2;
  moyO3 = moyO3/totalMesuresO3;
  moyNO2 = moyNO2/totalMesuresNO2;



  //Standard ATMO introduit par le prof
  int indicePM10;
  int indiceSO2;
  int indiceO3;
  int indiceNO2;
  if(moyPM10 <= 6){
    indicePM10 = 1;
  }else if (moyPM10 <= 13){
    indicePM10 = 2;
  }else if (moyPM10 <= 20){
    indicePM10 = 3;
  }else if (moyPM10 <= 27){
    indicePM10 = 4;
  }else if (moyPM10 <= 34){
    indicePM10 = 5;
  }else if (moyPM10 <= 41){
    indicePM10 = 6;
  }else if (moyPM10 <= 49){
    indicePM10 = 7;
  }else if (moyPM10 <= 64){
    indicePM10 = 8;
  }else if (moyPM10 <= 79){
    indicePM10 = 9;
  }else if (moyPM10 >= 80){
    indicePM10 = 10;
  }

  if(moySO2 <= 39){
    indiceSO2 = 1;
  }else if (moySO2 <= 79){
    indiceSO2 = 2;
  }else if (moySO2 <= 119){
    indiceSO2 = 3;
  }else if (moySO2 <= 159){
    indiceSO2 = 4;
  }else if (moySO2 <= 199){
    indiceSO2 = 5;
  }else if (moySO2 <= 249){
    indiceSO2 = 6;
  }else if (moySO2 <= 299){
    indiceSO2 = 7;
  }else if (moySO2 <= 399){
    indiceSO2 = 8;
  }else if (moySO2 <= 499){
    indiceSO2 = 9;
  }else if (moySO2 >= 500){
    indiceSO2 = 10;
  }

  if(moyO3 <= 29){
    indiceO3 = 1;
  }else if (moyO3 <= 54){
    indiceO3 = 2;
  }else if (moyO3 <= 79){
    indiceO3 = 3;
  }else if (moyO3 <= 104){
    indiceO3 = 4;
  }else if (moyO3 <= 129){
    indiceO3 = 5;
  }else if (moyO3 <= 149){
    indiceO3 = 6;
  }else if (moyO3 <= 179){
    indiceO3 = 7;
  }else if (moyO3 <= 209){
    indiceO3 = 8;
  }else if (moyO3 <= 239){
    indiceO3 = 9;
  }else if (moyO3 >= 240){
    indiceO3 = 10;
  }

  if(moyNO2 <= 29){
    indiceNO2 = 1;
  }else if (moyNO2 <= 54){
    indiceNO2 = 2;
  }else if (moyNO2 <= 84){
    indiceNO2 = 3;
  }else if (moyNO2 <= 109){
    indiceNO2 = 4;
  }else if (moyNO2 <= 134){
    indiceNO2 = 5;
  }else if (moyNO2 <= 164){
    indiceNO2 = 6;
  }else if (moyNO2 <= 199){
    indiceNO2 = 7;
  }else if (moyNO2 <= 274){
    indiceNO2 = 8;
  }else if (moyNO2 <= 399){
    indiceNO2 = 9;
  }else if (moyNO2 >= 400){
    indiceNO2 = 10;
  }

  int indiceAtmo = 1; //il est defini comme le plus grand des sous-indices calcule pour le dioxyde de soufre, le dioxyde d'azote, l'ozone et les particules fines
  indiceAtmo = (indicePM10 > indiceAtmo)?  indicePM10:indiceAtmo;
  indiceAtmo = (indiceSO2 > indiceAtmo)?  indiceSO2:indiceAtmo;
  indiceAtmo = (indiceO3 > indiceAtmo)?  indiceO3:indiceAtmo;
  indiceAtmo = (indiceNO2 > indiceAtmo)?  indiceNO2:indiceAtmo;

  if(affichage) {
    //Affichage des resultats
    cout << "----Get Aggregate Infomation Algorithm----\n";
    if(totalMesuresPM10 == 0 || totalMesuresSO2 == 0 || totalMesuresO3 == 0 || totalMesuresNO2 == 0 ){
      cout << "Source de data insuffisante \n";
    }else{
      cout << "PM10 : " <<  moyPM10   << "\n";
      cout << "SO2 : " <<  moySO2   << "\n";
      cout << "O3 : " <<  moyO3   << "\n";
      cout << "NO2 : " <<  moyNO2   << "\n";
      cout << "Indice de qualite de l'air : " <<  indiceAtmo   << "\n";
      if(indiceAtmo <= 2){
        cout << "Niveau : Tres bon\n";
      }else if(indiceAtmo <= 4){
        cout << "Niveau : Bon\n";
      }else if(indiceAtmo <= 5){
        cout << "Niveau : Moyen\n";
      }else if(indiceAtmo <= 7){
        cout << "Niveau : Mediocre\n";
      }else if(indiceAtmo <= 9){
        cout << "Niveau : Mauvais\n";
      }else if(indiceAtmo <= 10){
        cout << "Niveau : Tres Mauvais\n";
      }
    }

  }
}

void analyserPerformance(){
  auto start = chrono::steady_clock::now(); //debut du chrono

  sensorsSimilairs("45.0", "0.0", 250.0, 12, 0.50);//on fait tourner l'algo

  auto end = chrono::steady_clock::now(); //fin du chrono
  cout << "----Similar Sensors Algorithm----\n Elapsed time in milliseconds : "
  << chrono::duration_cast<chrono::milliseconds>(end - start).count()
  << " ms" << endl;

  cout<<"Warning: time may vary depending on function arguments\n";

  start = chrono::steady_clock::now();

  labelliserMesure(false);

  end = chrono::steady_clock::now();

  cout << "----Label Measures Algorithm----\n Elapsed time in milliseconds : "
  << chrono::duration_cast<chrono::milliseconds>(end - start).count()
  << " ms" << endl;

  cout<<"Warning: time may vary depending on the number of non-tested measures\n";

  start = chrono::steady_clock::now();

  aggregateInfo("45.0", "2.0", 2019, 2, false);

  end = chrono::steady_clock::now();


  cout << "----Obtenir aggregate info Algorithm----\n Elapsed time in milliseconds : "
  << chrono::duration_cast<chrono::milliseconds>(end - start).count()
  << " ms" << endl;

  cout<<"Warning: time may vary depending on the number of non-tested measures\n";




}



void menuDecider() {
  int choix = 0;
  cout<< "------------------- AirWatcher Decider ---------------------\n\n" <<endl;
  cout<<"Veillez choisir une fonctionnalité :"<<endl;
  cout<<"1) Afficher les données d’un sensor"<<endl;
  cout<<"2) Obtenir aggregate information"<<endl; //done
  cout<<"3) Afficher des capteurs ayant des comportements similaires"<<endl; //done
  cout<<"4) Afficher les nombres de points des utilisateurs privés"<<endl; //done
  cout<<"5) Analyser la performance des algorithmes"<<endl; //done
  cout<<"6) Afficher les notes de fiabilité des utilisateurs privés"<<endl; //done
  cout<<"7) Trouver les mesures fausses et les supprimer"<<endl; //done
  cout<<"8) Se déconnecter"<<endl; //done
  cout<<"Veillez saisir l’indice de la fonctionnalité que vous voulez choisir :"<<endl;

  while(!(cin >> choix)||choix>9||choix < 1)
  {
    cout << "Entrée incompatible avec l'information demandée. Veuillez réessayer." << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }

  string sensorId;
  string lat;
  string lon;
  int annee;
  int mois;
  float rayon;
  float precision;
  switch(choix)
  {
    case 1:
    {cout<<"Identifiant du sensor:"<<endl;
    cin>>sensorId;
    Sensor res = chercherSensorParId(sensorId);
    if (res.getLatitude()!="")//si le sensor existe
    cout<<"Latitude: "<<res.getLatitude()<<"; Longitude: "<<res.getLongitude()<<"; Label:"<<res.getLabel()<<endl;
    else
    cout << "Sensor inexistant." << endl;
    break;}
    case 2:
    cout<<"Latitude:"<<endl;
    cin>>lat;
    cout<<"Longitude:"<<endl;
    cin>>lon;
    cout<<"Annee:"<<endl;
    cin>>annee;
    cout<<"Mois:"<<endl;
    cin>>mois;
    aggregateInfo(lat, lon, annee, mois, true); //on recupere les infos sur la qualité de l'air dans la zone et au mois demandés
    break;
    case 3:
    {cout<<"Latitude:"<<endl;
    cin>>lat;
    cout<<"Longitude:"<<endl;
    cin>>lon;
    cout<<"Rayon de recherche:"<<endl;
    cin>>rayon;
    cout<<"Duree en mois:"<<endl;
    cin>>mois;
    cout<<"Precision de la recherche:"<<endl;
    cin>>precision;
    sensorsSimilairs(lat,lon,rayon, mois,precision); //on remplit la liste des sensors similaires dans la zone et sur la période demandés
    list<Sensor>::iterator it1;
    for (it1 = sensorsSimilaires.begin(); it1 != sensorsSimilaires.end(); it1++) {
      cout << it1->getID() << ";" << it1->getLatitude() << ";" << it1->getLongitude() << endl;
    }
    break;}
    case 4:
    afficherNbPoints();
    break;
    case 5:
    analyserPerformance();
    break;
    case 6:
    afficherNotesFiabilite();
    break;
    case 7:
    labelliserMesure(true);
    break;
    case 8:
    cout << "Déconnexion réussie" << endl;
    return;
  }

  menuDecider();
}

void affichageCleaner()
{
  list<Cleaner>::iterator it;
  for (it = listCleaners.begin(); it != listCleaners.end(); it++) {
    cout << it->getLatitude() << ";" << it->getLongitude() << ";" << it->getID() << ";" << it->getDescription() << endl;
  }
}


void menuProvider() {
  int choix = 0;
  cout<< "------------------- AirWatcher Provider ---------------------\n\n" <<endl;
  cout<<"Veillez choisir une fonctionnalité :"<<endl;
  cout<<"1) Ajouter un cleaner"<<endl;
  cout<<"2) Supprimer un cleaner"<<endl;
  cout<<"3) Afficher les cleaner existants"<<endl;
  cout<<"4) Se déconnecter"<<endl;
  cout<<"Veillez saisir l’indice de la fonctionnalité que vous voulez choisir :"<<endl;

  while(!(cin >> choix)||choix>4||choix < 1)
  {
    cout << "Entrée incompatible avec l'information demandée. Veuillez réessayer." << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }

  string id;
  string lat;
  string lon;
  string desc;
  tm timeStart;
  string start;
  tm timeStop;
  string stop;
  Cleaner c;
  string cleanerID;

  switch(choix)
  {
    case 1:
    cout<<"Saisissez dans l’ordre CleanerID, Latitude, Longitude, Description, Time-start et Time-stop. Gardez bien un espace entre deux mots :"<<endl;
    cout<<"Les dates doivent être sous la forme YYYY-MM-DD hh:mm:ss"<<endl;
    cin.ignore();

    std::getline(cin, id);

    std::getline(cin, lat);

    std::getline(cin, lon);

    std::getline(cin, desc);

    std::getline(cin, start);

    std::getline(cin, stop);

    timeStart = GestionCSV::gettimem(start);
    timeStop = GestionCSV::gettimem(stop);
    c=Cleaner(lat,lon,id,desc,&timeStop,&timeStart);
    listCleaners.push_back(c);
    cout << "Le cleaner a bien été ajouté" << endl;
    break;

    case 2:
    cout<<"Saisissez le cleanerID : "<<endl;
    cin>>cleanerID;
    if(supprimerCleaner(cleanerID)) {
      cout<<"Cleaner supprimé"<<endl;
    } else {
      cout << "Aucun cleaner ne correspond à cet ID." << endl; //s'il n'existe pas
    }

    break;

    case 3:
    cout<<"Voici les cleaners existant :"<<endl;
    affichageCleaner();
    break;
    case 4:
    cout<<"Déconnexion réussie "<<endl;
    return;
  }

  menuProvider();
}

////////////////////////////menu//////////////////////////////////
int menuPrincipal()
{
  int choix=0;

  cout<< "------------------- AirWatcher ---------------------\n\n" <<endl;
  cout << "Bonjour! Quel type d'utilisateur êtes vous" << endl;

  cout<<"1 - Decider\n2 - Provider\n3 - Sortir\n" << endl;
  while(!(cin >> choix) || choix>3 || choix < 1)
  {
    cout << "Entrée incompatible avec l'information demandée. Veuillez réessayer." << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }

  switch (choix)
  {
    case 1:
    menuDecider();
    break;
    case 2:
    menuProvider();
    case 3:
    cout << "\nA bientôt!\n" << endl;
    return 0;
  }

  return 0;
}


int main()
{
  //Appel aux fonctions pour remplir les listes à partir des CSV

  ////////////////////les types de mesures////////////////////////
  ifstream input(files[0]);
  // On affiche une erreur s'il est impossible d'ouvrir le fichier
  if (input.fail()) // diapo N°43
  {
    cout << "Impossible d'ouvrir le fichier" << endl;
    return 1;
  }
  GestionCSV::ParseMeasureType(input, listMeasureType);

  ///////////////////////les sensors//////////////////////////////////
  input.open(files[1]);

  // On affiche une erreur s'il est impossible d'ouvrir le fichier
  if (input.fail()) // diapo N°43
  {
    cout << "Impossible d'ouvrir le fichier" << endl;
    return 1;
  }
  GestionCSV::ParseSensor(input, listSensor);
  input.close();


  ////////////////////////////////les cleaners/////////////////////////////////////////:
  input.open(files[2]);

  // On affiche une erreur s'il est impossible d'ouvrir le fichier
  if (input.fail()) // diapo N°43
  {
    cout << "Impossible d'ouvrir le fichier" << endl;
    return 1;
  }
  GestionCSV::ParseCleaner(input, listCleaners);
  input.close();

  //////////////////////////////les utilisateurs privés////////////////////////////
  input.open(files[5]);

  // On affiche une erreur s'il est impossible d'ouvrir le fichier
  if (input.fail()) // diapo N°43
  {
    cout << "Impossible d'ouvrir le fichier" << endl;
    return 1;
  }

  GestionCSV::ParseUser(input, listUP);

  input.close();

  ParseSensorPrive();

  //////////////////////////////les mesures////////////////////////////
  input.open(files[3]);

  // On affiche une erreur s'il est impossible d'ouvrir le fichier
  if (input.fail()) // diapo N°43
  {
    cout << "Impossible d'ouvrir le fichier" << endl;
    return 1;
  }

  GestionCSV::ParseMeasure(input, listMeasure, listMeasureType, listPrivateSensorUser);
  input.close();

  //////////////////////////////les orovider////////////////////////////
  input.open(files[4]);

  // On affiche une erreur s'il est impossible d'ouvrir le fichier
  if (input.fail()) // diapo N°43
  {
    cout << "Impossible d'ouvrir le fichier" << endl;
    return 1;
  }

  GestionCSV::ParseProvider(input, listProvider);
  input.close();


  menuPrincipal();



  return 0;
}
