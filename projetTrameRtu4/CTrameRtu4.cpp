// CTrameRtu4.cpp

#include "CTrameRtu4.h"

CTrameRtu4::CTrameRtu4() {
    tailleCodeEmis = 0;
    crcEmis = 0xFFFF;
    tailleTrameRecu = 0;
    crcRecu = 0;
}

// on memorise le code et on prepare la trame
void CTrameRtu4::memoriserCode(unsigned char* code, int taille) {
    tailleCodeEmis = taille;
    
    for(int i = 0; i < taille; i++) {
        codeInformationEmis[i] = code[i];
    }
    
    calculerCrc();
    construireTrame();
}

unsigned char* CTrameRtu4::fournirTrame() {
    return trameServiceEmis;
}

int CTrameRtu4::getTailleTrameEmise() {
    return tailleCodeEmis + 2;
}

// calcule le crc
void CTrameRtu4::calculerCrc() {
    crcEmis = calculercrcDuMessage(codeInformationEmis, tailleCodeEmis);
}

// assemble donnees + crc
void CTrameRtu4::construireTrame() {
    for(int i = 0; i < tailleCodeEmis; i++) {
        trameServiceEmis[i] = codeInformationEmis[i];
    }
    
    // crc en little endian
    trameServiceEmis[tailleCodeEmis] = (unsigned char)(crcEmis & 0xFF);
    trameServiceEmis[tailleCodeEmis + 1] = (unsigned char)((crcEmis >> 8) & 0xFF);
}

// stocke la trame recue
void CTrameRtu4::memoriserTrameRecu(unsigned char* trame, int taille) {
    tailleTrameRecu = taille;
    for(int i = 0; i < taille; i++) {
        trameReponseRecu[i] = trame[i];
    }
}

// separe les donnees et le crc
void CTrameRtu4::extraireInfoRecu() {
    if (tailleTrameRecu < 2) return;

    int tailleInfo = tailleTrameRecu - 2;
    
    for(int i = 0; i < tailleInfo; i++) {
        codeInformationRecu[i] = trameReponseRecu[i];
    }

    unsigned char crcBas = trameReponseRecu[tailleTrameRecu - 2];
    unsigned char crcHaut = trameReponseRecu[tailleTrameRecu - 1];
    crcRecu = (unsigned short)(crcBas | (crcHaut << 8));
}

// verifie le crc et retourne les donnees
unsigned char* CTrameRtu4::fournirInfoRecu() {
    int tailleInfo = tailleTrameRecu - 2;

    unsigned short crcCalcule = calculercrcDuMessage(codeInformationRecu, tailleInfo);
    
    if (crcCalcule == crcRecu) {
        return codeInformationRecu;
    } else {
        // crc faux, on met 0
        for(int i = 0; i < tailleInfo; i++) {
            codeInformationRecu[i] = 0;
        }
        return codeInformationRecu;
    }
}

int CTrameRtu4::getTailleInfoRecu() {
    return tailleTrameRecu - 2;
}

// calcul crc modbus
unsigned short CTrameRtu4::calculercrcDuMessage(unsigned char* message, int taille) {
    unsigned short crc = 0xFFFF;
    unsigned short poly = 0xA001;
    
    for (int i = 0; i < taille; i++) {
        crc ^= message[i];
        
        for (int j = 0; j < 8; j++) {
            unsigned char retenue = crc & 0x01;
            crc >>= 1;
            
            if (retenue == 1) {
                crc ^= poly;
            }
        }
    }
    return crc;
}
