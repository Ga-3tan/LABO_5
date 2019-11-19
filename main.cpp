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

	void afficheLesJours(int NB_JOURS_SEMAINE, int positionLundi) {
		static const char JOURS_SEMAINE[7] = { 'L', 'M', 'M', 'J', 'V', 'S', 'D' };
		//affiche les jours de la semaine
		for (int i = 1; i <= NB_JOURS_SEMAINE; i++) {
			if (i - positionLundi < 0) {
				cout << setw(3) << JOURS_SEMAINE[i - positionLundi + NB_JOURS_SEMAINE];
			}
			else {
				cout << setw(3) << JOURS_SEMAINE[i - positionLundi];
			}

		}
	}

	void afficheLesDates(int nombreDeJours, int joursVide, int NB_JOURS_SEMAINE) {
		for (int j = 0; j < nombreDeJours + joursVide + /*NOMBRE de jour "vide" après le dernier jours du mois ->*/(NB_JOURS_SEMAINE - (nombreDeJours + joursVide) % NB_JOURS_SEMAINE) % NB_JOURS_SEMAINE; j++) {
			// Si on a affiché le dernier jours de la semaine faire un retour à la ligne avant d'afficher le suivant
			if (j != 0 && (j % NB_JOURS_SEMAINE) == 0) {
				cout << endl;
			}
			//Avant le premier et après le dernier jour du mois affiche esapce
			if (joursVide != NB_JOURS_SEMAINE && j < joursVide || j >= nombreDeJours + joursVide) {
				cout << setw(3) << " ";
			}
			else {
				cout << setw(3) << j - joursVide + 1;
			}
		}
	}

	void recursivDisplayMonth(int nbJourVide, int annee, int positionLundi, int monthToDisplay = 0 , int NB_JOURS_SEMAINE = 7, int numberOfMothToDisplay = 12) {
		static const string MOIS[12] = { "Janvier", "Fevrier", "Mars", "Avril",
								  "Mai", "Juin", "Juillet", "Aout", "Septembre",
								  "Octobre", "Novembre", "Decembre" };
		// Calcul le nombre de jour vide si le nombre de jour vide = NB_JOURS_SEMAINE alors on met 0 pour eviter la ligne vide
		int decalage = (nbJourVide + positionLundi - 3) % NB_JOURS_SEMAINE;
		//corrige le décalage (je crois il y avait un bug avec l'an 2000 et lundi position 1 ça corrige ce bug
		if (decalage < 0) {
			decalage += NB_JOURS_SEMAINE;
		}
		int nombreJourDuMois = nbJourDuMois(monthToDisplay, annee);
		int center = int((21 - MOIS[monthToDisplay].length()) / 2) + MOIS[monthToDisplay].length();

		// affiche le mois
		cout << setw(center) << MOIS[monthToDisplay] << string(21 - center, ' ') << endl;

		afficheLesJours(NB_JOURS_SEMAINE, positionLundi);

		cout << endl;

		afficheLesDates(nombreJourDuMois, decalage, NB_JOURS_SEMAINE);

		// tant qu'on a pas affiché décembre on continue !
		if (monthToDisplay < numberOfMothToDisplay - 1) {
			cout << endl << string(21, ' ') << endl;
			recursivDisplayMonth(((nombreJourDuMois + nbJourVide) % NB_JOURS_SEMAINE), annee, positionLundi, (monthToDisplay + 1),NB_JOURS_SEMAINE, numberOfMothToDisplay);
		}
	}


	int dayOfTheMonth(int day, int month, int year) {
		if (month == 1 || month == 2) {
			month += 12;
			--year;
		}
		return (day + 2 * month + int(3 * (month + 1) / 5) + year + int(year / 4) - (year / 100) + int(year / 400) + 2) % 7;
	}

	void display(int NB_JOURS_SEMAINE, const int annee, int positionLundi, int firstMonthToDisplay = 1) {
		cout << setfill(' ') << setw(12) << annee << string(9, ' ') << endl << string(21, ' ') << endl;
		int firstDayMonth = dayOfTheMonth(1, firstMonthToDisplay, annee);
		recursivDisplayMonth(firstDayMonth, annee, positionLundi);
	}

	void clearCin() {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	int verifEntry(int VALUE_MIN, int VALUE_MAX, const string& MESSAGE_TO_DISPLAY) {
		bool test = false;
		int variable = 0;
		do {
			cout << MESSAGE_TO_DISPLAY;
			cin >> variable;
			if (cin.fail()) {
				clearCin();
			}
			if (variable < VALUE_MIN || variable > VALUE_MAX) {
				std::cout << "Entree non valide" << endl;
				clearCin();
			}
			else {
				test = true;
			}
		} while (!test);
		return variable;
	}

	int main() {
		/////////////////////////////////////// Constantes ////////////////////////////////////////////////
		const int MIN_ANNEE = 1600;
		const int MAX_ANNEE = 3000;
		const int JOUR_MINIMUM = 1;
		const string MESSAGE_ENTREE_ANNEE = "Quelle annee voulez-vous afficher? (1600-3000) ";
		const string MESSAGE_ENTREE_JOUR = "Quel jour de la semaine est le lundi? (1-7) ";

		const int NB_JOURS_SEMAINE = 7;
	
		///////////////////////////////////////// Code //////////////////////////////////////////////////

		int annee = verifEntry(MIN_ANNEE, MAX_ANNEE, MESSAGE_ENTREE_ANNEE);
		int positionLundi = verifEntry(JOUR_MINIMUM, NB_JOURS_SEMAINE, MESSAGE_ENTREE_JOUR);

		cout << endl;
		display(NB_JOURS_SEMAINE, annee, positionLundi);
		return 0;
	}