// CTest4.cpp

#include "CTest4.h"
#include <iostream>
#include <iomanip>

using namespace std;

CTest4::CTest4() {
}

void CTest4::afficherMenu() {
    cout << endl;
    cout << "----- Menu :" << endl;
    cout << "1. Test Emission (02 07)" << endl;
    cout << "2. Test Reception Valide" << endl;
    cout << "3. Test Reception Invalide" << endl;
    cout << "Choix : ";
}

void CTest4::executerMenu() {
    int choix = -1;
    
    while(choix != 0) {
        afficherMenu();
        cin >> choix;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << endl;
        
        switch(choix) {
            case 1: testEmission(); break;
            case 2: testReceptionValide(); break;
            case 3: testReceptionInvalide(); break;
        }
    }
}

void CTest4::afficherOctets(unsigned char* donnees, int taille) {
    for(int i = 0; i < taille; i++) {
        cout << hex << uppercase << setw(2) << setfill('0') << (int)donnees[i] << " ";
    }
    cout << dec;
}

void CTest4::testEmission() {
    cout << "Test Emission" << endl;
    
    unsigned char message[] = {0x02, 0x07};
    int tailleMsg = 2;
    
    maTrame.memoriserCode(message, tailleMsg);
    
    unsigned char* trameFinale = maTrame.fournirTrame();
    int tailleTrame = maTrame.getTailleTrameEmise();
    
    cout << "Message : ";
    afficherOctets(message, tailleMsg);
    cout << endl;
    
    cout << "Trame   : ";
    afficherOctets(trameFinale, tailleTrame);
    cout << endl;
    
    cout << "Attendu : 02 07 41 12" << endl;
}

void CTest4::testReceptionValide() {
    cout << "Test Reception Valide" << endl;
    
    unsigned char trameRecue[] = {0x02, 0x07, 0x41, 0x12};
    int tailleRecu = 4;
    
    maTrame.memoriserTrameRecu(trameRecue, tailleRecu);
    maTrame.extraireInfoRecu();
    unsigned char* codeExtrait = maTrame.fournirInfoRecu();
    int tailleInfo = maTrame.getTailleInfoRecu();
    
    cout << "Trame recue : ";
    afficherOctets(trameRecue, tailleRecu);
    cout << endl;
    
    cout << "Code extrait : ";
    afficherOctets(codeExtrait, tailleInfo);
    cout << endl;
    
    cout << "Attendu : 02 07" << endl;
}

void CTest4::testReceptionInvalide() {
    cout << "Test Reception Invalide" << endl;
    
    unsigned char trameFausse[] = {0x02, 0x07, 0xFF, 0xFF};
    int tailleRecu = 4;
    
    maTrame.memoriserTrameRecu(trameFausse, tailleRecu);
    maTrame.extraireInfoRecu();
    unsigned char* codeFaux = maTrame.fournirInfoRecu();
    int tailleInfo = maTrame.getTailleInfoRecu();
    
    cout << "Trame recue : ";
    afficherOctets(trameFausse, tailleRecu);
    cout << endl;
    
    cout << "Code extrait : ";
    afficherOctets(codeFaux, tailleInfo);
    cout << endl;
    
    cout << "Attendu : 00 00 (CRC faux)" << endl;
}
