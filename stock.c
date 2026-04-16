#include "stock.h"

void ajouterProduit(const char* nomFichier) {
    FILE *file = fopen(nomFichier, "ab");
    if (!file) return;

    Produit p;
    printf("ID du produit : "); scanf("%d", &p.id);
    printf("Marque : "); scanf("%s", p.marque);
    printf("Contenance (ex: 1.5) : "); scanf("%f", &p.contenance);
    printf("Quantite initiale : "); scanf("%d", &p.quantite);
    printf("Prix unitaire : "); scanf("%f", &p.prix);

    fwrite(&p, sizeof(Produit), 1, file);
    fclose(file);
    printf("\nProduit ajoute avec succes !\n");
}

void afficherStock(const char* nomFichier) {
    FILE *file = fopen(nomFichier, "rb");
    if (!file) {
        printf("Le stock est vide ou inexistant.\n");
        return;
    }

    Produit p;
    printf("\n--- ETAT DU STOCK D'EAU ---\n");
    printf("%-5s | %-15s | %-10s | %-8s | %-6s\n", "ID", "Marque", "Format", "Stock", "Prix");
    printf("------------------------------------------------------------\n");

    while (fread(&p, sizeof(Produit), 1, file)) {
        printf("%-5d | %-15s | %-5.2f L   | %-8d | %-6.2f\n", 
                p.id, p.marque, p.contenance, p.quantite, p.prix);
    }
    fclose(file);
}

void vendreProduit(const char* nomFichier) {
    FILE *file = fopen(nomFichier, "rb+");
    if (!file) return;

    int idCherche, qteVendre, trouve = 0;
    Produit p;

    printf("ID du produit a vendre : "); scanf("%d", &idCherche);
    printf("Quantite vendue : "); scanf("%d", &qteVendre);

    while (fread(&p, sizeof(Produit), 1, file)) {
        if (p.id == idCherche) {
            trouve = 1;
            if (p.quantite >= qteVendre) {
                p.quantite -= qteVendre;
                // On remonte le curseur pour ecraser l'ancienne valeur
                fseek(file, -sizeof(Produit), SEEK_CUR);
                fwrite(&p, sizeof(Produit), 1, file);
                printf("Vente enregistree. Nouveau stock : %d\n", p.quantite);
            } else {
                printf("Erreur : Stock insuffisant (%d restant)\n", p.quantite);
            }
            break;
        }
    }
    if (!trouve) printf("Produit non trouve.\n");
    fclose(file);
}