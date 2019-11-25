/// \file main.cpp
/// \authors Samy Ould Ahmed, Gaétan Zwick, Jonathan Stocchetti
/// \date 12.11.2019
///
/// \brief \b Laboratoire \b 05
/// \brief Afficher un calendrier annuaire selon le choix de l'année par l'utilisateur.
/// L'utilisateur peut également choisir un décalage pour afficher le lundi autre part que tout à gauche.
///
/// Remarque(s) :
///
/// Compilateur :  MinGW-g++ 6.3.0

	#include <iostream>
	#include <limits>
	#include <iomanip>

	using namespace std;

/**
 * \name isBis
 *
 * \brief Savoir si l'année séléctionnée est bissextile
 *
 * \param @param annee, entier entre 1600-3000
 *
 * \param @return true/false si l'annee est bissextile ou pas
 */
	bool isBis(int annee) {
    ///////////////////////////////////////// Code //////////////////////////////////////////////////
	    /// Formules permettant de savoir si une année est bissextile ou non
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

/**
* \name nbJourDuMois
*
* \brief Connaitre le nombre de jour dans un mois
*
* \param @param mois, entier représentant le mois entre 1-12
* \param @param annee, entier représentant l'année séléctionnée entre 1600-3000
*
* \return @return MOIS_30/MOIS_31/FEVRIER_BIS/FEVRIER_NON_BIS le nombre de jour constituant 1 mois en particulier
*/
	int nbJourDuMois(int mois, int annee) {
    /////////////////////////////////////// Constante ////////////////////////////////////////////////
		const int MOIS_30 = 30;
		const int MOIS_31 = 31;
		const int FEVRIER_BIS = 29;
		const int FEVRIER_NON_BIS = 28;

    ///////////////////////////////////////// Code //////////////////////////////////////////////////
		///Sélectionne si le mois fait 30 ou 31 jours et pour février si il fait 28 ou 29
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

/**
* \name afficheLesJours
*
* \brief Affiche les jours de la semaine selon la position du lundi
*
* \param @param nbJoursSemaine, entier qui indique le nombre de jours contenu dans une semaine
* \param @param positionLundi, entier qui indique la position du lundi dans les jours de la semaine ( display : L M M J V S D, ou S D L M M J V)
*
*/
	void afficheLesJours(int nbJoursSemaine, int positionLundi) {
    /////////////////////////////////////// Variable ////////////////////////////////////////////////
		static const char JOURS_SEMAINE[7] = { 'L', 'M', 'M', 'J', 'V', 'S', 'D' };

    ///////////////////////////////////////// Code //////////////////////////////////////////////////
		///affiche les jours de la semaine
		for (int i = 1; i <= nbJoursSemaine; i++) {
			if (i - positionLundi < 0) {
				cout << setw(3) << JOURS_SEMAINE[i - positionLundi + nbJoursSemaine];
			}
			else {
				cout << setw(3) << JOURS_SEMAINE[i - positionLundi];
			}

		}
	}

/**
* \name afficheLesDates
*
* \brief Affiche les différentes dates du mois
*
* \param @param nombreDeJours, entier qui indique le nombre de jours dans 1 mois en particulier
* \param @param joursVide, entier représentant combien il y a de jours de la semaine "vides" après le 31 (Si le 31 est un jeudi, le vendredi, samedi et dimanche sont "vides" => joursVide=3)
* \param @param nbJoursSemaine, entier qui indique le nombre de jours contenu dans une semaine
*
*/
	void afficheLesDates(int nombreDeJours, int joursVide, int nbJoursSemaine) {
    ///////////////////////////////////////// Code //////////////////////////////////////////////////
    ///NOMBRE de jour "vide" après le dernier jours du mois ->*/(nbJoursSemaine - (nombreDeJours + joursVide) % nbJoursSemaine) % nbJoursSemaine
	    for (int j = 0; j < nombreDeJours + joursVide + (nbJoursSemaine - (nombreDeJours + joursVide) % nbJoursSemaine) % nbJoursSemaine; j++) {
			/// Si on a affiché le dernier jours de la semaine faire un retour à la ligne avant d'afficher le suivant
			if (j != 0 && (j % nbJoursSemaine) == 0) {
				cout << endl;
			}
			///Avant le premier et après le dernier jour du mois affiche espace
			if (joursVide != nbJoursSemaine && j < joursVide || j >= nombreDeJours + joursVide) {
				cout << setw(3) << " ";
			}
			else {
				cout << setw(3) << j - joursVide + 1;
			}
		}
	}

/**
* \name recursivDisplayMonth
* \brief FONCTION RECURSIVE
* \brief Affiche les 12 mois du calendrier avec les jours, les jours de la semaine, etc...
*
* \param @param nbJourVide, entier représentant le mois entre 1-12
* \param @param annee, entier représentant l'année séléctionnée entre 1600-3000
* \param @param positionLundi, entier qui indique la position du lundi dans les jours de la semaine ( display : L M M J V S D, ou S D L M M J V)
* \param @param monthToDisplay, entier du mois à afficher, s'incrémente avec la récursivité
* \param @param nbJoursSemaine, entier qui indique le nombre de jours contenu dans une semaine
* \param @param numberOfMothToDisplay, entier qui indique combien de mois il faut afficher
*
*/
	void recursivDisplayMonth(int nbJourVide, int annee, int positionLundi, int monthToDisplay = 0 , int nbJoursSemaine = 7, int numberOfMothToDisplay = 12) {
    /////////////////////////////////////// Variable ////////////////////////////////////////////////
	    static const string MOIS[12] = { "Janvier", "Fevrier", "Mars", "Avril",
								  "Mai", "Juin", "Juillet", "Aout", "Septembre",
								  "Octobre", "Novembre", "Decembre" };

    //////////////////////////////////////// Code //////////////////////////////////////////////////
		/// Calcul le nombre de jour vide si le nombre de jour vide = nbJoursSemaine alors on met 0 pour eviter la ligne vide
		int decalage = (nbJourVide + positionLundi - 3) % nbJoursSemaine;
		///corrige le décalage (je crois il y avait un bug avec l'an 2000 et lundi position 1 ça corrige ce bug
		if (decalage < 0) {
			decalage += nbJoursSemaine;
		}
		int nombreJourDuMois = nbJourDuMois(monthToDisplay, annee);
		int center = int((21 - MOIS[monthToDisplay].length()) / 2) + MOIS[monthToDisplay].length();

		/// affiche le mois
		cout << setw(center) << MOIS[monthToDisplay] << string(21 - center, ' ') << endl;

		afficheLesJours(nbJoursSemaine, positionLundi);

		cout << endl;

		afficheLesDates(nombreJourDuMois, decalage, nbJoursSemaine);

		/// tant qu'on a pas affiché décembre on continue !
		if (monthToDisplay < numberOfMothToDisplay - 1) {
			cout << endl << string(21, ' ') << endl;
			recursivDisplayMonth(((nombreJourDuMois + nbJourVide) % nbJoursSemaine), annee, positionLundi, (monthToDisplay + 1), nbJoursSemaine, numberOfMothToDisplay);
		}
	}

/**
* \name dayOfTheMonth
*
* \brief Connaitre le jour de la semaine du premier jour de l'année (le 1er janvier)
*
* \param @param day, entier la date du jour
* \param @param month, entier représentant le mois entre 1-12
* \param @param year, entier représentant l'année séléctionnée entre 1600-3000
*
* \return @return le nombre de la date du premier jour de l'année séléctionnée (le 01 janvier de l'année)
*/
	int dayOfTheMonth(int day, int month, int year) {
    ///////////////////////////////////////// Code //////////////////////////////////////////////////
		if (month == 1 || month == 2) {
			month += 12;
			--year;
		}
		return (day + 2 * month + int(3 * (month + 1) / 5) + year + int(year / 4) - (year / 100) + int(year / 400) + 2) % 7;
	}

/**
* \name display
* \brief Affiche le calandrier en appelant les différentes fonctions d'affichage
*
* \param @param annee, entier représentant l'année séléctionnée entre 1600-3000
* \param @param positionLundi, entier qui indique la position du lundi dans les jours de la semaine ( display : L M M J V S D, ou S D L M M J V)
* \param @param firstMonthToDisplay, le mois à afficher
*
*/
	void display(const int annee, int positionLundi, int firstMonthToDisplay = 1) {
    ///////////////////////////////////////// Code //////////////////////////////////////////////////
		cout << setfill(' ') << setw(12) << annee << string(9, ' ') << endl << string(21, ' ') << endl;
		int firstDayMonth = dayOfTheMonth(1, firstMonthToDisplay, annee);
		recursivDisplayMonth(firstDayMonth, annee, positionLundi);
	}

/**
* \name clearCin
* \brief Nettoie le buffer au cas d'une erreur de l'utilisateur
*
*/
	void clearCin() {
    ///////////////////////////////////////// Code //////////////////////////////////////////////////
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

/**
* \name verifEntry
* \brief Vérifie la validité des entrées de l'utilisateur
*
* \param @param VALUE_MIN, entier minimum que l'utilisateur peut entrer
* \param @param VALUE_MAX, entier maximum que l'utilisateur peut entrer
* \param @param MESSSAGE_TO_DISPLAY, string du message à afficher
*
*/
	int verifEntry(int VALUE_MIN, int VALUE_MAX, const string& MESSAGE_TO_DISPLAY) {
    /////////////////////////////////////// Variable ////////////////////////////////////////////////
		bool test = false;
		int variable = 0;

    ///////////////////////////////////////// Code //////////////////////////////////////////////////
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

/**
* \name main
* \brief Programme affichant le calendrier d'une année saisie par l'utilisateur
*
* \return @return EXIT_SUCCESS
*/
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
		display(annee, positionLundi);
		return EXIT_SUCCESS;
	}