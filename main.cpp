/* ---------------------------
 Laboratoire :  05
 Fichier :      main.cpp
 Auteur(s) :    Samy Ould Ahmed, Gaétan Zwick, Jonathan Stocchetti
 Date :         12.11.2019

 But :          Afficher un calendrier annuaire selon le choix de l'année par l'utilisateur.
				L'utilisateur peut également choisir un décalage pour afficher le lundi autre part que tout à gauche.

 Remarque(s) :

 Compilateur :  MinGW-g++ 6.3.0
 --------------------------- */

#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

bool isBis(int annee) {
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

int nbJourDuMois(int mois, int annee) {
	const int MOIS_30 = 30;
	const int MOIS_31 = 31;
	const int FEVRIER_BIS = 29;
	const int FEVRIER_NON_BIS = 28;
	//Sélectionne si le mois fait 30 ou 31 jours et pour février si il fait 28 ou 29
	if (mois < 7 && mois != 1) {
		if (mois % 2 == 0) {
			return MOIS_31;
		}
		else {
			return MOIS_30;
		}
	}
	else if (mois != 1) {
		if (mois % 2 == 0) {
			return MOIS_30;
		}
		else {
			return MOIS_31;
		}
	}
	else if (isBis(annee)) {
		return FEVRIER_BIS;
	}
	else {
		return FEVRIER_NON_BIS;
	}
}

void afficheLesDates(int nombreDeJours, int joursVide)

{
	for (int j = 0; j < nombreDeJours + joursVide + /*NOMBRE de jour "vide" après le dernier jours du mois ->*/(7 - (nombreDeJours + joursVide) % 7) % 7; j++) {
		// Si on a affiché le dernier jours de la semaine faire un retour à la ligne avant d'afficher le suivant
		if (j != 0 && (j % 7) == 0) {
			cout << endl;
		}
		//Avant le premier et après le dernier jour du mois affiche esapce
		if (joursVide != 7 && j < joursVide || j >= nombreDeJours + joursVide) {
			cout << setw(3) << " ";
		}
		else {
			cout << setw(3) << j - joursVide + 1;
		}
	}
}

void afficheLesJours(int NB_JOURS_SEMAINE, int positionLundi, const char JOURS_SEMAINE[]) {
	//affiche les jours de la semaine
	for (int i = 1; i <= NB_JOURS_SEMAINE; i++) {
		if (i - positionLundi < 0) {
			cout << setw(3) << JOURS_SEMAINE[i - positionLundi + 7];
		}
		else {
			cout << setw(3) << JOURS_SEMAINE[i - positionLundi];
		}

	}
}

void recursivDisplayMonth(int month, int nbJourVide, int numberOfMothToDisplay, const string MOIS[], const char JOURS_SEMAINE[], int NB_JOURS_SEMAINE, int annee, int positionLundi) {
	// Calcul le nombre de jour vide si le nombre de jour vide = 7 alors on met 0 pour eviter la ligne vide
	int decalage = (nbJourVide + positionLundi - 1) % 7;
	//corrige le décalage (je crois il y avait un bug avec l'an 2000 et lundi position 1 ça corrige ce bug
	if (decalage < 0) {
		decalage += 7;
	}
	int nombreJourDuMois = nbJourDuMois(month, annee);
	int center = int((21 - MOIS[month].length()) / 2) + MOIS[month].length();

	// affiche le mois
	cout << setw(center) << MOIS[month] << string(21 - center, ' ') << endl;

	afficheLesJours(NB_JOURS_SEMAINE, positionLundi, JOURS_SEMAINE);

	cout << endl;

	afficheLesDates(nombreJourDuMois, decalage);

	// tant qu'on a pas affiché décembre on continue !
	if (month < numberOfMothToDisplay - 1) {
		cout << endl << string(21, ' ') << endl;
		recursivDisplayMonth(month + 1, (nombreJourDuMois + nbJourVide) % 7, numberOfMothToDisplay, MOIS, JOURS_SEMAINE, NB_JOURS_SEMAINE, annee, positionLundi);
	}
}

int dayOfTheYear(int day, int month, int year) {
	if (month == 1 || month == 2) {
		month += 12;
		--year;
	}
	return (day + 2 * month + int(3 * (month + 1) / 5) + year + int(year / 4) - (year / 100) + int(year / 400) + 2) % 7;
}

void display(int numberOfMothToDisplay, const string MOIS[], const char JOURS_SEMAINE[], int NB_JOURS_SEMAINE, int annee, int positionLundi) {
	cout << setfill(' ') << setw(12) << annee << string(9, ' ') << endl << string(21, ' ') << endl;
	int premierJourAnnee = dayOfTheYear(1, 1, annee);
	recursivDisplayMonth(0, (premierJourAnnee - 2), numberOfMothToDisplay, MOIS, JOURS_SEMAINE, NB_JOURS_SEMAINE, annee, positionLundi);
}

void clearCin() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool verifEntry(int variable, int valueMin, int valueMax) {
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
	const int MIN_ANNEE = 1600;
	const int MAX_ANNEE = 3000;
	const int NB_MOIS = 12;
	const int JOUR_MINIMUM = 1;
	const string MESSAGE_ENTREE_ANNEE = "Quelle annee voulez-vous afficher? (1600-3000) ";
	const string MESSAGE_ENTREE_JOUR = "Quel jour de la semaine est le lundi? (1-7) ";
	const string MOIS[NB_MOIS] = { "Janvier", "Fevrier", "Mars", "Avril",
							  "Mai", "Juin", "Juillet", "Aout", "Septembre",
							  "Octobre", "Novembre", "Decembre" };
	const int NB_JOURS_SEMAINE = 7;
	const char JOURS_SEMAINE[NB_JOURS_SEMAINE] = { 'L', 'M', 'M', 'J', 'V', 'S', 'D' };
	/////////////////////////////////////// Variables ////////////////////////////////////////////////
	bool valid;
	int annee = 0;
	int positionLundi = 0;
	///////////////////////////////////////// Code //////////////////////////////////////////////////
	for (int demandeEntree = 1; demandeEntree <= 2; demandeEntree++) {
		do {
			switch (demandeEntree) {
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
	display(NB_MOIS, MOIS, JOURS_SEMAINE, NB_JOURS_SEMAINE, annee, positionLundi);
	return 0;
}