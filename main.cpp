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

using namespace std;

const int MOIS_30 = 30;
const int MOIS_31 = 31;
const int FEVRIER_BIS = 29;
const int FEVRIER_NON_BIS = 28;
const int NB_MOIS = 12;
const int NB_JOURS_SEMAINE = 7;
const int MIN_ANNEE = 1600;
const int MAX_ANNEE = 3000;

const char JOURS_SEMAINE[NB_JOURS_SEMAINE] = {'L', 'M', 'M', 'J', 'V', 'S', 'D'};
const string MOIS[NB_MOIS] = {"Janvier", "Fevrier", "Mars", "Avril",
                              "Mai", "Juin", "Juillet", "Aout", "Septembre",
                              "Octobre", "Novembre", "Decembre"};

int annee = 0;
int jour;

int dayOfTheYear(int day, int month, int year) {
    if (month == 1 || month == 2) {
        month += 12;
        --year;
    }
    return (day + 2 * month + int(3 * (month + 1) / 5) + year + int(year / 4) - (year / 100) + int(year / 400) + 2) % 7;
}

bool isBis() {
    if (annee % 4 != 0) {
        return false;
    } else if (annee % 100 != 0) {
        return true;
    } else {
        return (annee % 400 == 0);
    }
}

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

bool verifEntry(string message, int valueMin, int valueMax)
{
	cout << message;
	cin >> annee;
	if (cin.fail()) {
		clearCin();
	}
	if (annee < valueMin || annee > valueMax) {
		cout << "Entree non valide" << endl;
		clearCin();
		return false;
	}
	else {
		return true;
	}
}

int main() {
    bool valid = false;
	const int JOUR_MINIMUM = 1;
	;
	const string MESSAGE_ENTREE_ANNEE = "Quelle annee voulez-vous afficher? (1600 - 3000)";
	const string MESSAGE_ENTREE_JOUR = "Quel jour de la semaine est le lundi ? (1 - 7)";
	for (int i = 1; i <= 2; i++)
	{
		do {
			if (i == 1)
			{
				valid = verifEntry(MESSAGE_ENTREE_ANNEE, MIN_ANNEE, MAX_ANNEE);
			}
			else {
				valid = verifEntry(MESSAGE_ENTREE_JOUR, JOUR_MINIMUM, NB_JOURS_SEMAINE);
			}
		} while (!valid);
	}
    valid = false;
    
	cout << "Jour du 1.1.2015" << dayOfTheYear(1, 1, 2015);
    return 0;
}