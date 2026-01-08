#ifndef CTRAMERTU3_H
#define CTRAMERTU3_H

class CTrameRtu3 {
public: // Tout est public pour faciliter le test comme demandé
    // --- Membres pour l'émission (Exercice 2) ---
    unsigned char codeInformationEmis[256]; // Stocke les données à envoyer
    unsigned short crcEmis;                 // Stocke le CRC calculé pour l'émission
    unsigned char trameServiceEmis[260];    // Stocke la trame finale (Données + CRC)
    int tailleCodeEmis;                     // Taille des données à émettre

    // --- Membres pour la réception (Exercice 3) ---
    unsigned char trameReponseRecu[260];    // Stocke la trame brute reçue
    unsigned char codeInformationRecu[256]; // Stocke les données extraites de la trame reçue
    unsigned short crcRecu;                 // Stocke le CRC extrait de la trame reçue
    int tailleTrameRecu;                    // Taille totale de la trame reçue

public:
    CTrameRtu3(); // Constructeur

    // --- Méthodes pour l'émission ---
    void memoriserCode(unsigned char* code, int taille); // Enregistre les données à envoyer
    void calculerCrc();                                  // Calcule le CRC sur codeInformationEmis
    void construireTrame();                              // Assemble codeInformationEmis + crcEmis
    unsigned char* fournirTrame();                       // Retourne la trame prête à l'envoi

    // --- Méthodes pour la réception ---
    void memoriserTrameRecu(unsigned char* trame, int taille); // Enregistre la trame reçue
    void extraireInfoRecu();                                   // Sépare données et CRC de la trame reçue
    unsigned char* fournirInfoRecu();                          // Vérifie le CRC et retourne les données si OK
    
    // --- Méthode utilitaire ---
    // Calcule un CRC sur un tableau donné (utile pour vérifier la réception)
    unsigned short calculercrcDuMessage(unsigned char* message, int taille);
};

#endif
