#include "stock.h"

int main() {
    int choix;
    const char* DATA_FILE = "stock_eau.dat";

    do {
        printf("\n=== GESTION DE DEPOT D'EAU ===\n");
        printf("1. Ajouter une reference\n");
        printf("2. Afficher le stock complet\n");
        printf("3. Enregistrer une vente\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterProduit(DATA_FILE); break;
            case 2: afficherStock(DATA_FILE); break;
            case 3: vendreProduit(DATA_FILE); break;
            case 4: printf("Fermeture du programme...\n"); break;
            default: printf("Choix invalide !\n");
        }
    } while (choix != 4);

    return 0;
}