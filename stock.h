#ifndef STOCK_H
#define STOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char marque[50];
    float contenance; // en Litres
    int quantite;
    float prix;
} Produit;

// Prototypes des fonctions
void ajouterProduit(const char* nomFichier);
void afficherStock(const char* nomFichier);
void vendreProduit(const char* nomFichier);
void verifierAlerte(const char* nomFichier, int seuil);

#endif