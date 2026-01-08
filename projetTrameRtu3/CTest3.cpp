#include "CTest3.h"
#include <iostream>
#include <iomanip> // Pour std::hex, std::setw...

using namespace std;

// Fonction principale de test
void CTest3::executerTest() {
    CTrameRtu3 maTrame;
    
    // ---------------------------------------------------------
    // TEST 1 : EMISSION (On crée une trame)
    // ---------------------------------------------------------
    cout << "=== TEST 1 : EMISSION ===" << endl;
    
    // Données à envoyer
    unsigned char message[] = {0x02, 0x07}; 
    int tailleMsg = 2;
    
    // 1. Mémorisation et calcul
    maTrame.memoriserCode(message, tailleMsg);
    
    // 2. Récupération du résultat
    unsigned char* trameFinale = maTrame.fournirTrame();
    
    // Affichage
    cout << "Message a envoyer : 02 07" << endl;
    cout << "Trame générée (avec CRC) : ";
    for(int i = 0; i < tailleMsg + 2; i++) {
        // Affiche chaque octet en hexadécimal
        cout << hex << uppercase << setw(2) << setfill('0') << (int)trameFinale[i] << " ";
    }
    cout << endl << endl;
    
    // ---------------------------------------------------------
    // TEST 2 : RECEPTION VALIDE (On reçoit une trame correcte)
    // ---------------------------------------------------------
    cout << "=== TEST 2 : RECEPTION CORRECTE ===" << endl;
    
    // Trame simulant une réponse valide (CRC OK)
    // CRC calculé pour 02 07 est 41 12 (Low=41, High=12)
    unsigned char trameRecue[] = {0x02, 0x07, 0x41, 0x12};
    int tailleRecu = 4;
    
    // 1. Mémorisation de la réception
    maTrame.memoriserTrameRecu(trameRecue, tailleRecu);
    
    // 2. Extraction des infos
    maTrame.extraireInfoRecu();
    
    // 3. Vérification et récupération du code
    unsigned char* codeRecu = maTrame.fournirInfoRecu();
    
    // Affichage
    cout << "Code extrait (attendu 02 07) : ";
    for(int i = 0; i < tailleRecu - 2; i++) {
        cout << hex << uppercase << setw(2) << setfill('0') << (int)codeRecu[i] << " ";
    }
    cout << endl << endl;

    // ---------------------------------------------------------
    // TEST 3 : RECEPTION INVALIDE (Erreur de CRC)
    // ---------------------------------------------------------
    cout << "=== TEST 3 : RECEPTION ERRONEE ===" << endl;
    
    // Trame simulant une réponse corrompue (Le CRC FF FF est faux)
    unsigned char trameFausse[] = {0x02, 0x07, 0xFF, 0xFF};
    
    // 1. Mémorisation
    maTrame.memoriserTrameRecu(trameFausse, tailleRecu);
    
    // 2. Extraction
    maTrame.extraireInfoRecu();
    
    // 3. Vérification (le CRC sera mauvais)
    unsigned char* codeFaux = maTrame.fournirInfoRecu();
    
    // Affichage (On s'attend à des 00 00)
    cout << "Code extrait (attendu 00 00 car CRC faux) : ";
    for(int i = 0; i < tailleRecu - 2; i++) {
        cout << hex << uppercase << setw(2) << setfill('0') << (int)codeFaux[i] << " ";
    }
    cout << endl << endl;
}
