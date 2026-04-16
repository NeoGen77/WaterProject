#include "stock.h"

int main() {
    int choix;
    const char* DATA_FILE = "stock_eau.dat";

    do {
        printf("\n===============================\n");
        printf("   GESTION DE STOCK D'EAU\n");
        printf("===============================\n");
        printf("1. Ajouter un nouveau produit\n");
        printf("2. Afficher l'etat du stock\n");
        printf("3. Enregistrer une vente\n");
        printf("4. Modifier un produit existant\n");
        printf("5. Voir l'historique des ventes\n");
        printf("6. Quitter\n");
        printf("-------------------------------\n");
        printf("Votre choix : ");
        
        // Sécurité pour la saisie
        if (scanf("%d", &choix) != 1) {
            printf("Erreur de saisie. Veuillez entrer un nombre.\n");
            while(getchar() != '\n'); // Vide le tampon
            continue;
        }

        switch (choix) {
            case 1:
                ajouterProduit(DATA_FILE);
                break;
            case 2:
                afficherStock(DATA_FILE);
                break;
            case 3:
                vendreProduit(DATA_FILE);
                break;
            case 4:
                modifierProduit(DATA_FILE);
                break;
            case 5:
                afficherHistorique();
                break;
            case 6:
                printf("Fermeture du programme. Au revoir !\n");
                break;
            default:
                printf("Option invalide, réessayez.\n");
        }
    } while (choix != 6);

    return 0;
}