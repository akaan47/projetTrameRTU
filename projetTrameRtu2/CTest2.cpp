#include "CTest2.h"
#include "CTrameRtu2.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Exécute l'algorithme de test pour valider CTrameRtu
void CTest::executerTest() {
    CTrameRtu maTrame;


    // 0x09, 0x10, 0x00, 0x51, 0x00, 0x02, 0x04, 0x00, 0x56, 0x00, 0x57
    // Attendu: 0x09 0x10 0x00 0x51 0x00 0x02 0x04 0x00 0x56 0x00 0x57 0xBC 0xD1 -> Succès

    // 0x09, 0x03, 0x00, 0x22, 0x00, 0x02
    // Attendu: 0x09 0x03 0x00 0x22 0x00 0x02 0x65 0x49 -> Succès

    // 0x02, 0x07
    // Attendu: 0x02 0x07 0x41 0x12 -> Succès

    unsigned char message[] = {0x02, 0x07};
    int taille = 2;
    
    cout << "Debut du test CTrameRtu" << endl;
    cout << "Code a emettre : ";
    for(int i = 0; i < taille; i++) {
        cout << hex << uppercase << setw(2) << setfill('0') << (int)message[i] << " ";
    }
    cout << endl;

    // Étape 1 : Mémorisation
    maTrame.memoriserCode(message, taille);
    
    // Étape 2 : Calcul et Récupération de la trame
    unsigned char* trame = maTrame.fournirTrame();
    
    cout << "Trame resultante (Code + CRC) : ";
    // Affichage de la trame complète (Message + 2 octets CRC)
    for(int i = 0; i < taille + 2; i++) {
        cout << hex << uppercase << setw(2) << setfill('0') << (int)trame[i] << " ";
    }
    cout << endl;
}
