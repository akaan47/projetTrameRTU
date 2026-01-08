#include "CTrameRtu2.h"

// Constructeur : initialise la taille du code et le CRC par défaut
CTrameRtu::CTrameRtu() {
    tailleCode = 0;
    crcEmis = 0xFFFF;
}

// Mémorise le code fourni en paramètre dans le tableau codeInformationEmis
void CTrameRtu::memoriserCode(unsigned char* code, int taille) {
    tailleCode = taille;
    for(int i = 0; i < taille; i++) {
        codeInformationEmis[i] = code[i];
    }
    calculerCrc();
    construireTrame();
}

// Calcule le CRC 16 bits à partir de codeInformationEmis selon l'algorithme fourni
void CTrameRtu::calculerCrc() {
    crcEmis = 0xFFFF; // Initialisation du CRC
    unsigned short poly = 0xA001; // Polynôme générateur
    
    for (int i = 0; i < tailleCode; i++) {
        crcEmis ^= codeInformationEmis[i]; // XOR -> OU Exclusif avec l'octet de donnée
        for (int n = 0; n < 8; n++) {
            unsigned char c = crcEmis & 0x01; // Récupération du bit de poids faible (retenue sortante)
            crcEmis >>= 1; // Décalage à droite
            if (c == 1) {
                crcEmis ^= poly; // OU Exclusif avec le polynôme si retenue
            }
        }
    }
}

// Construit trameServiceEmis à partir de codeInformationEmis et de crcEmis
void CTrameRtu::construireTrame() {
    // Copie de l'information
    for(int i = 0; i < tailleCode; i++) {
        trameServiceEmis[i] = codeInformationEmis[i];
    }
    // Ajout du CRC (poids faible en premier)
    trameServiceEmis[tailleCode] = (unsigned char)(crcEmis & 0xFF);
    trameServiceEmis[tailleCode + 1] = (unsigned char)((crcEmis >> 8) & 0xFF);
}

// Lance la procédure complète et retourne la trame finale
unsigned char* CTrameRtu::fournirTrame() {
    return trameServiceEmis;
}
