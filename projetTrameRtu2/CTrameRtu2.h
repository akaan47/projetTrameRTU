#ifndef CTRAMERTU_H
#define CTRAMERTU_H

class CTrameRtu {
private:
    unsigned char codeInformationEmis[256];
    unsigned short crcEmis;
    unsigned char trameServiceEmis[260];
    int tailleCode;

public:
    CTrameRtu();
    unsigned char* fournirTrame();
    void memoriserCode(unsigned char* code, int taille);
    
private:
    void calculerCrc();
    void construireTrame();
};

#endif
