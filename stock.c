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
void modifierProduit(const char* nomFichier) {
    FILE *file = fopen(nomFichier, "rb+");
    if (!file) return;

    int idCherche, trouve = 0;
    Produit p;

    printf("ID du produit a modifier : "); scanf("%d", &idCherche);

    while (fread(&p, sizeof(Produit), 1, file)) {
        if (p.id == idCherche) {
            trouve = 1;
            printf("Nouvelle marque (actuelle: %s) : ", p.marque); scanf("%s", p.marque);
            printf("Nouveau prix (actuel: %.2f) : ", p.prix); scanf("%f", &p.prix);
            
            fseek(file, -(long)sizeof(Produit), SEEK_CUR);
            fwrite(&p, sizeof(Produit), 1, file);
            printf("Modification enregistree !\n");
            break;
        }
    }
    if (!trouve) printf("Produit introuvable.\n");
    fclose(file);
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
                fseek(file, -(long)sizeof(Produit), SEEK_CUR);
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

void enregistrerHistorique(Vente v) {
    FILE *file = fopen("historique.dat", "ab");
    if (file) {
        fwrite(&v, sizeof(Vente), 1, file);
        fclose(file);
    }
}

void afficherHistorique() {
    FILE *file = fopen("historique.dat", "rb");
    if (!file) {
        printf("Aucun historique disponible.\n");
        return;
    }

    Vente v;
    printf("\n--- HISTORIQUE DES VENTES ---\n");
    printf("ID Vente | ID Prod | Qte | Total | Date\n");
    while (fread(&v, sizeof(Vente), 1, file)) {
        printf("%-8d | %-7d | %-3d | %-5.2f | %s\n", 
                v.idVente, v.idProduit, v.quantiteVendue, v.montantTotal, v.date);
    }
    fclose(file);
}
