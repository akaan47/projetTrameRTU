// CTrameRtu4.h

#ifndef CTRAMERTU4_H
#define CTRAMERTU4_H

class CTrameRtu4 {

private:
    // emission
    unsigned char codeInformationEmis[256];
    unsigned short crcEmis;
    unsigned char trameServiceEmis[260];
    int tailleCodeEmis;

    // reception
    unsigned char trameReponseRecu[260];
    unsigned char codeInformationRecu[256];
    unsigned short crcRecu;
    int tailleTrameRecu;

    // methodes internes
    void calculerCrc();
    void construireTrame();
    unsigned short calculercrcDuMessage(unsigned char* message, int taille);

public:
    CTrameRtu4();

    // emission
    void memoriserCode(unsigned char* code, int taille);
    unsigned char* fournirTrame();
    int getTailleTrameEmise();

    // reception
    void memoriserTrameRecu(unsigned char* trame, int taille);
    void extraireInfoRecu();
    unsigned char* fournirInfoRecu();
    int getTailleInfoRecu();
};

#endif
