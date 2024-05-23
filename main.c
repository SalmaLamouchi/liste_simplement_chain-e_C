#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition des structures
typedef struct {
    char nom[50];
    char prenom[50];
    float moyenne;
} Etud;

typedef Etud Tab_Etud[200];

typedef struct maillon {
    Etud valeur;
    struct maillon* suivant;
} Maillon;

typedef Maillon* L_etud;

// Prototypes des fonctions et procédures
void Remplir_Etud(Tab_Etud T, int* N);
void TriBulle_Etudiant(Tab_Etud T, int N);
L_etud Creer_liste(Tab_Etud T, int N);
L_etud Rechercher(L_etud L, Etud E);
void Eclater(L_etud L1, L_etud* L2, L_etud* L3);
void AfficheListe(L_etud L);
void Menu();

int main() {
    Tab_Etud A;
    int N = 0; // Initialisation à 0 pour garantir que l'utilisateur entre la taille.
    L_etud L = NULL, L2 = NULL, L3 = NULL;

    // Remplir le tableau d'étudiants
    do {
        printf("Entrez le nombre d'etudiants : ");
        scanf("%d", &N);
    } while (N <= 0); // Assurez-vous que l'utilisateur entre un nombre positif

    Remplir_Etud(A, &N);

    // Trier les étudiants par moyenne
    TriBulle_Etudiant(A, N);
    printf("Liste triee des etudiants :\n");
    for (int i = 0; i < N; i++) {
        printf("Nom : %s, Prenom : %s, Moyenne : %.2f\n", A[i].nom, A[i].prenom, A[i].moyenne);
    }

    // Créer une liste à partir du tableau
    L = Creer_liste(A, N);
    printf("Liste des etudiants apres creation de la liste chainee :\n");
    AfficheListe(L);

    // Recherche d'un étudiant spécifique
    Etud etudiantRecherche;
    printf("Entrez les informations de l'etudiant a rechercher :\n");
    printf("Nom : ");
    scanf("%s", etudiantRecherche.nom);
    printf("Prenom : ");
    scanf("%s", etudiantRecherche.prenom);
    printf("Moyenne : ");
    scanf("%f", &etudiantRecherche.moyenne);

    L_etud resultat = Rechercher(L, etudiantRecherche);
    if (resultat != NULL) {
        printf("Etudiant trouve :\n");
        printf("Nom : %s, Prenom : %s, Moyenne : %.2f\n", resultat->valeur.nom, resultat->valeur.prenom, resultat->valeur.moyenne);
    } else {
        printf("Etudiant non trouve.\n");
    }

    // Éclater la liste des étudiants selon leur moyenne
    Eclater(L, &L2, &L3);
    printf("Liste des etudiants ayant une moyenne < 10 :\n");
    AfficheListe(L2);
    printf("Liste des etudiants ayant une moyenne >= 10 :\n");
    AfficheListe(L3);

    // Affichage des étudiants admis (moyenne >= 10)
    printf("Liste des etudiants admis (moyenne >= 10) :\n");
    AfficheListe(L3);

    // Nettoyage des listes créées pour éviter les fuites de mémoire
    free(L);
    free(L2);
    free(L3);

    return 0;
}

// Procédure pour remplir le tableau d'étudiants
void Remplir_Etud(Tab_Etud T, int* N) {
    for (int i = 0; i < *N; i++) {
        printf("Etudiant %d\n", i + 1);
        printf("Nom : ");
        scanf("%s", T[i].nom);
        printf("Prenom : ");
        scanf("%s", T[i].prenom);
        printf("Moyenne : ");
        scanf("%f", &T[i].moyenne);
    }
}

// Procédure de tri à bulle selon la moyenne
void TriBulle_Etudiant(Tab_Etud T, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (T[j].moyenne > T[j + 1].moyenne) {
                Etud temp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = temp;
            }
        }
    }
}

// Fonction de création de liste chainee à partir du tableau d'étudiants
L_etud Creer_liste(Tab_Etud T, int N) {
    L_etud L = NULL;
    for (int i = 0; i < N; i++) {
        Maillon* nv = (Maillon*)malloc(sizeof(Maillon));
        nv->valeur = T[i];
        nv->suivant = L;
        L = nv;
    }
    return L;
}

// Fonction de recherche d'un étudiant dans la liste
L_etud Rechercher(L_etud L, Etud E) {
    L_etud p = L;
    while (p != NULL) {
        if (strcmp(p->valeur.nom, E.nom) == 0 &&
            strcmp(p->valeur.prenom, E.prenom) == 0 &&
            p->valeur.moyenne == E.moyenne) {
            return p;
        }
        p = p->suivant;
    }
    return NULL;
}

// Procédure pour éclater la liste selon la moyenne
void Eclater(L_etud L1, L_etud* L2, L_etud* L3) {
    *L2 = NULL;
    *L3 = NULL;
    while (L1 != NULL) {
        if (L1->valeur.moyenne < 10) {
            Maillon* nv = (Maillon*)malloc(sizeof(Maillon));
            nv->valeur = L1->valeur;
            nv->suivant = *L2;
            *L2 = nv;
        } else {
            Maillon* nv = (Maillon*)malloc(sizeof(Maillon));
            nv->valeur = L1->valeur;
            nv->suivant = *L3;
            *L3 = nv;
        }
        L1 = L1->suivant;
    }
}

// Procédure pour afficher la liste des étudiants
void AfficheListe(L_etud L) {
    while (L != NULL) {
        printf("Nom : %s\n", L->valeur.nom);
        printf("Prenom : %s\n", L->valeur.prenom);
        printf("Moyenne : %.2f\n", L->valeur.moyenne);
        L = L->suivant;
    }
}

// Procédure pour afficher le menu
void Menu() {
    printf("\nMenu :\n");
    printf("1. Remplir le tableau d'etudiants\n");
    printf("2. Trier les etudiants par moyenne\n");
    printf("3. Creer la liste des etudiants\n");
    printf("4. Rechercher un etudiant\n");
    printf("5. Eclater la liste des etudiants selon la moyenne\n");
    printf("6. Afficher la liste des etudiants dont la moyenne est superieure ou egale a 10\n");
    printf("0. Quitter\n");
}
