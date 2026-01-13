// CTest4.h

#ifndef CTEST4_H
#define CTEST4_H

#include "CTrameRtu4.h"

class CTest4 {

private:
    CTrameRtu4 maTrame;

    void testEmission();
    void testReceptionValide();
    void testReceptionInvalide();

    void afficherMenu();
    void afficherOctets(unsigned char* donnees, int taille);

public:
    CTest4();
    void executerMenu();
};

#endif
