/*************************************************************************
                           Provider  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Realisation de la classe <Provider > (fichier Provider.cpp) ------

//----------------------------------------------------------Include Systeme
#include <string>
#include <list>
#include<iostream>

using namespace std;
//----------------------------------------------------------Include Personnel
#include "Provider.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------------

//------------------------------------------------------------------------

	//----------------------------------------------------------------- PUBLIC
	//----------------------------------------------------- Methodes publiques
	//-------------------------------------------- Constructeurs - destructeur
	Provider::Provider() {
		providerID = "";
		cleanerID ="" ;
		std::list<string> cleanerIDs;
	}//----- Fin de Provider

	Provider::Provider(string unproviderID, string uncleanerID) {
		providerID = unproviderID;
		cleanerID = uncleanerID;
		std::list<string> cleanerIDs;
	}//----- Fin de Provider

	Provider::~Provider() {
	}//----- Fin de~Provider


	bool Provider::ajouterCleaner(Cleaner Newcleaner, list <Cleaner> & cleaners) {
	        cleaners.push_back(Newcleaner);
	        list <Cleaner> :: iterator debut, fin;
	        debut = cleaners.begin();
	        fin = cleaners.end();
	        while(debut != fin){
	            if((debut -> getID()).compare(Newcleaner.getID()) == 0 ){
	                return true;  //Return true si le cleaner est ajoute
	            }
	        debut++;
	        }
	    return false; ////Return false dans le cas contraire
	    }

	    bool Provider::supprimerCleaner(string cleanerId, list <Cleaner> & cleaners) {
	        list <Cleaner> :: iterator debut, fin;
	        debut = cleaners.begin();
	        fin = cleaners.end();
	        while(debut != fin){
	            if((debut -> getID()).compare(cleanerId) == 0 ){
	                cleaners.erase(debut);
	                return true;  //Return true si le cleaner est supprime
	            }
	        debut++;
	        }
	    return false; ////Return false dans le cas contraire
	    }




	string Provider::getID() {
		return providerID;
	}
	string Provider::getcleanerID () {
		return cleanerID;
	}


	void Provider::setcleanerID(string uncleanerID) {
		cleanerID = uncleanerID;
	}
	void Provider::setID(string unID) {
		providerID = unID;

	}



	//------------------------------------------------------------------ PRIVE

	//----------------------------------------------------- Methodes protected

	//------------------------------------------------------- Methodes privees
