/* ---------------------------
 Laboratoire : 05
 Fichier :     main.cpp
 Auteur(s) :   Samy Ould Ahmed, Gaétan Zwick, Jonathan Stocchetti
 Date :        12.11.2019

 But :         Afficher un calendrier annuaire selon le choix de l'année par l'utilisateur.
				L'utilisateur peut également choisir un décalage pour afficher le lundi autre part que tout à gauche.

 Remarque(s) :

 Compilateur :  MinGW-g++ 6.3.0
 --------------------------- */

#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

const int MOIS_30 = 30;
const int MOIS_31 = 31;
const int FEVRIER_BIS = 29;
const int FEVRIER_NON_BIS = 28;
const int NB_MOIS = 12;
const int NB_JOURS_SEMAINE = 7;
const int MIN_ANNEE = 1600;
const int MAX_ANNEE = 3000;

const char JOURS_SEMAINE[NB_JOURS_SEMAINE] = { 'L', 'M', 'M', 'J', 'V', 'S', 'D' };
const string MOIS[NB_MOIS] = { "Janvier", "Fevrier", "Mars", "Avril",
							  "Mai", "Juin", "Juillet", "Aout", "Septembre",
							  "Octobre", "Novembre", "Decembre" };

int annee = 2015;
int positionLundi;

bool isBis() {
	if (annee % 4 != 0) {
		return false;
	}
	else if (annee % 100 != 0) {
		return true;
	}
	else {
		return (annee % 400 == 0);
	}
}

void displayOneMonth(int month, int nbJourVide) {
	int decalage = (nbJourVide + positionLundi - 1) % 7;
	if (decalage < 0)
	{
		decalage += 7;
	}
	int nombreJourDuMois;
	int center = int((21 - MOIS[month].length()) / 2) + MOIS[month].length();

	if (month < 7 && month != 1)
	{
		if (month % 2 == 0)
		{
			nombreJourDuMois = MOIS_31;
		}
		else
		{
			nombreJourDuMois = MOIS_30;
		}
	}
	else if (month != 1)
	{
		if (month % 2 == 0)
		{
			nombreJourDuMois = MOIS_30;
		}
		else
		{
			nombreJourDuMois = MOIS_31;
		}
	}
	else if (isBis())
	{
		nombreJourDuMois = FEVRIER_BIS;
	}
	else
	{
		nombreJourDuMois = FEVRIER_NON_BIS;
	}

	// affiche le mois
	cout << setw(center) << MOIS[month] << string(21 - center, ' ') << endl;

	//affiche les jours de la semaine
	for (int i = 1; i <= NB_JOURS_SEMAINE; i++) {
		if (i - positionLundi < 0)
		{
			cout << setw(3) << JOURS_SEMAINE[i - positionLundi + 7];
		}
		else
		{
			cout << setw(3) << JOURS_SEMAINE[i - positionLundi];
		}

	}

	cout << endl;

	for (int j = 0; j < nombreJourDuMois + decalage + (7 - (nombreJourDuMois + decalage) % 7) % 7; j++) {
		if (j != 0 && (j % 7) == 0)
		{
			cout << endl;
		}

		if (decalage != 7 && j < decalage || j >= nombreJourDuMois + decalage) {
			cout << setw(3) << " ";
		}
		else {
			cout << setw(3) << j - decalage + 1;
		}
	}

	if (month < 11)
	{
		cout << endl << string(21, ' ') << endl;
		displayOneMonth(month + 1, (nombreJourDuMois + nbJourVide) % 7);
	}
}

int dayOfTheYear(int day, int month, int year) {
	if (month == 1 || month == 2) {
		month += 12;
		--year;
	}
	return (day + 2 * month + int(3 * (month + 1) / 5) + year + int(year / 4) - (year / 100) + int(year / 400) + 2) % 7;
}

void display() {
	cout << setfill(' ') << setw(12) << annee << string(9, ' ') << endl << string(21, ' ') << endl;
	int premierJourAnnee = dayOfTheYear(1, 1, annee);
	displayOneMonth(0, (premierJourAnnee - 2));
}





void clearCin() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool verifEntry(int variable, int valueMin, int valueMax)
{
	if (cin.fail()) {
		clearCin();
	}

	if (variable < valueMin || variable > valueMax) {
		cout << "Entree non valide" << endl;
		clearCin();
		return false;
	}
	else {
		return true;
	}
}

int main() {
	/////////////////////////////////////// Constantes ////////////////////////////////////////////////
	const int JOUR_MINIMUM = 1;
	const string MESSAGE_ENTREE_ANNEE = "Quelle annee voulez-vous afficher? (1600-3000) ";
	const string MESSAGE_ENTREE_JOUR = "Quel positionLundi de la semaine est le lundi? (1-7) ";
	/////////////////////////////////////// Variables ////////////////////////////////////////////////
	bool valid;
	///////////////////////////////////////// Code //////////////////////////////////////////////////
	for (int demandeEntree = 1; demandeEntree <= 2; demandeEntree++)
	{
		do {
			switch (demandeEntree)
			{
			case 1:
				cout << MESSAGE_ENTREE_ANNEE;
				cin >> annee;
				valid = verifEntry(annee, MIN_ANNEE, MAX_ANNEE);
				continue;
			case 2:
				cout << MESSAGE_ENTREE_JOUR;
				cin >> positionLundi;
				valid = verifEntry(positionLundi, JOUR_MINIMUM, NB_JOURS_SEMAINE);
				continue;
			}
		} while (!valid);
	}
	cout << endl;
	display();
	return 0;
}