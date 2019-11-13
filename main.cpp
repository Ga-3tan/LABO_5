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

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

int main() {
    bool valid = false;
    do {
        cout << "Quelle annee voulez-vous afficher? (1600-3000) " << endl;
        cin >> annee;
        if (cin.fail()) {
            clearCin();
        }
        if (annee < 1600 || annee > 3000) {
            cout << "Entree non valide" << endl;
            clearCin();
        } else {
            valid = true;
        }
    } while (!valid);
    valid = false;
    do {
        cout << "Quel jour de la semaine est le lundi? (1-7)" << endl;
        cin >> jour;
        if (cin.fail()) {
            clearCin();
        }
        if (jour <= 0 || jour > 7) {
            cout << "Entree non valide" << endl;
            clearCin();
        } else {
            valid = true;
        }
    } while (!valid);
    return 0;
}