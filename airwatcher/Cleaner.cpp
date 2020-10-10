/*************************************************************************
                           Cleaner  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Realisation de la classe Cleaner > (fichier Cleaner.cpp) ------

//----------------------------------------------------------Include Systeme
#include <string>
#include <ctime>
using namespace std;
//----------------------------------------------------------Include Personnel
#include "Cleaner.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------------

//------------------------------------------------------------------------

	//----------------------------------------------------------------- PUBLIC
	//----------------------------------------------------- Methodes publiques
	//-------------------------------------------- Constructeurs - destructeur
Cleaner::Cleaner() {
	latitude="";
	longitude="";
	cleanerID="";
	description="";
	dateFin = 0;
	dateDebut = 0;
}//----- Fin de Cleaner

Cleaner::Cleaner(string unelatitude, string unelongitude, string uncleanerID, string unedescription, struct tm* unedateDebut, struct tm* unedateFin) {
	latitude = unelatitude;
	longitude = unelongitude;
	cleanerID = uncleanerID;
	description = unedescription;
	dateFin = unedateFin;
	dateDebut = unedateDebut;
}//----- Fin de Cleaner

Cleaner::~Cleaner() {
}//----- Fin de~Cleaner



string Cleaner:: getID() {
	return cleanerID;
}
string Cleaner:: getLatitude() {
	return latitude;
}
string Cleaner::getLongitude() {
	return longitude;
}
struct tm* Cleaner::getDateDebut() {
	return dateDebut;
}
struct tm* Cleaner::getDateFin() {
	return dateFin;
}
string Cleaner::getDescription() {
	return description;
}

void Cleaner::setID(string uncleanerID) {
	cleanerID = uncleanerID;
}
void Cleaner::setLatitute(string uneLatitute) {
	latitude = uneLatitute;
}
void Cleaner::setLongitude(string uneLongitude) {
	longitude = uneLongitude;
}
void Cleaner::setDateDebut(tm* uneDateDebut) {
	dateDebut = uneDateDebut;
}
void Cleaner::setDateFin(tm* uneDateFin) {
	dateDebut = uneDateFin;
}
void Cleaner::setDescription(string uneDescription) {
	description = uneDescription;
}



//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protected

//------------------------------------------------------- Methodes privees
