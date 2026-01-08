#include "CTrameRtu3.h"

// Constructeur : initialise les variables à 0
CTrameRtu3::CTrameRtu3() {
    tailleCodeEmis = 0;
    crcEmis = 0xFFFF; // Valeur initiale standard pour CRC-16 Modbus
    tailleTrameRecu = 0;
    crcRecu = 0;
}

// ---------------------------------------------------------
// PARTIE EMISSION
// ---------------------------------------------------------

// Etape 1 : On mémorise le message que l'on veut envoyer
void CTrameRtu3::memoriserCode(unsigned char* code, int taille) {
    tailleCodeEmis = taille;
    // Copie octet par octet
    for(int i = 0; i < taille; i++) {
        codeInformationEmis[i] = code[i];
    }
    
    // Une fois mémorisé, on lance le calcul du CRC et la construction
    calculerCrc();
    construireTrame();
}

// Etape 2 : On calcule le CRC sur les données à émettre
void CTrameRtu3::calculerCrc() {
    // Calcul du CRC sur 'codeInformationEmis'
    crcEmis = calculercrcDuMessage(codeInformationEmis, tailleCodeEmis);
}

// Etape 3 : On assemble le message et le CRC dans la trame finale
void CTrameRtu3::construireTrame() {
    // 1. Copier les données
    for(int i = 0; i < tailleCodeEmis; i++) {
        trameServiceEmis[i] = codeInformationEmis[i];
    }
    
    // 2. Ajouter le CRC à la fin (Low byte d'abord, High byte ensuite)
    trameServiceEmis[tailleCodeEmis] = (unsigned char)(crcEmis & 0xFF);         // Partie basse
    trameServiceEmis[tailleCodeEmis + 1] = (unsigned char)((crcEmis >> 8) & 0xFF); // Partie haute
}

// Etape 4 : On retourne le tableau final
unsigned char* CTrameRtu3::fournirTrame() {
    return trameServiceEmis;
}

// ---------------------------------------------------------
// PARTIE RECEPTION
// ---------------------------------------------------------

// Etape 1 : On mémorise la trame brute reçue
void CTrameRtu3::memoriserTrameRecu(unsigned char* trame, int taille) {
    tailleTrameRecu = taille;
    for(int i = 0; i < taille; i++) {
        trameReponseRecu[i] = trame[i];
    }
}

// Etape 2 : On sépare les données utiles et le CRC reçu
void CTrameRtu3::extraireInfoRecu() {
    // Protection basique : il faut au moins 2 octets pour le CRC
    if (tailleTrameRecu < 2) return;

    // Les données utiles sont tout sauf les 2 derniers octets
    int tailleInfo = tailleTrameRecu - 2;
    
    // Copie des données utiles
    for(int i = 0; i < tailleInfo; i++) {
        codeInformationRecu[i] = trameReponseRecu[i];
    }

    // Récupération du CRC reçu (les 2 derniers octets)
    unsigned char crcLow = trameReponseRecu[tailleTrameRecu - 2];
    unsigned char crcHigh = trameReponseRecu[tailleTrameRecu - 1];
    
    // Reconstitution du mot de 16 bits (High << 8 | Low)
    crcRecu = (unsigned short)(crcLow | (crcHigh << 8));
}

// Etape 3 : On vérifie le CRC et on retourne les infos
unsigned char* CTrameRtu3::fournirInfoRecu() {
    int tailleInfo = tailleTrameRecu - 2;

    // On recalcule le CRC théorique sur les données reçues
    unsigned short crcCalcule = calculercrcDuMessage(codeInformationRecu, tailleInfo);
    
    // On compare le CRC calculé avec celui reçu
    if (crcCalcule == crcRecu) {
        // C'est valide : on retourne les données telles quelles
        return codeInformationRecu;
    } else {
        // C'est invalide : on remplit le code de 0
        for(int i = 0; i < tailleInfo; i++) {
            codeInformationRecu[i] = 0;
        }
        return codeInformationRecu;
    }
}

// ---------------------------------------------------------
// ALGORITHME DE CALCUL DE CRC (Commun)
// ---------------------------------------------------------
unsigned short CTrameRtu3::calculercrcDuMessage(unsigned char* message, int taille) {
    unsigned short crc = 0xFFFF; // Initialisation à 1 (tous les bits à 1)
    unsigned short poly = 0xA001; // Polynôme générateur pour Modbus
    
    for (int i = 0; i < taille; i++) {
        crc ^= message[i]; // XOR avec l'octet courant
        
        for (int j = 0; j < 8; j++) { // Pour chaque bit
            unsigned char retenue = crc & 0x01; // On regarde le bit sortant
            crc >>= 1; // Décalage à droite
            
            if (retenue == 1) {
                crc ^= poly; // Si retenue, XOR avec polynôme
            }
        }
    }
    return crc;
}
