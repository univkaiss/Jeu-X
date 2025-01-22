#include <stdio.h>
#include <stdlib.h>

typedef int bool; // type bolleen
#define true 1
#define false 0

struct platoto {
  int ligne;
  int col;
  int tab[9][9];
};

struct Joueur {
  char Pseudo[20];
  int Couleur;
  int ScoreTotal;
  int scorePartieEnCours;
} Joueur1, Joueur2;

struct platoto varplat;
// Initialisation du tableau
void IntiJeu() {
  int C, L;
  bool ligneT = false;
  while (!ligneT) {
    printf("Entrez le nombre de lignes\n");
    scanf("%d", &L);
    switch (L) {
    case 3:
    case 5:
    case 7:
    case 9: {
      ligneT = true;
      break;
    }
    default:
      printf("Nombres de ligne invalide !\n");
      break;
    }
  }
  bool colT = false;
  while (!colT) {
    printf("Entrez le nombre de colonnes\n");
    scanf("%d", &C);
    switch (C) {
    case 3:
    case 5:
    case 7:
    case 9: {
      colT = true;
      break;
    }
    default:
      printf("Nombres de colonnes invalides !\n");
      break;
    }
  }
    varplat.ligne = L;
    varplat.col = C;
    for (int ligne = 0; ligne < varplat.ligne; ligne++) 
    {
    for (int col = 0; col < varplat.col; col++) 
    {
      varplat.tab[ligne][col] = 0;
    }
  }

  for (int ligne = 0; ligne < varplat.ligne; ligne++) {
    for (int col = 0; col < varplat.col; col++) {
      printf("%3d", varplat.tab[ligne][col]);
    }
    printf("\n");
  }
}
// affichage du tableau
void AfficherTableau() {
  for (int ligne = 0; ligne < varplat.ligne; ligne++) {
    for (int col = 0; col < varplat.col; col++) {
      printf("%3d", varplat.tab[ligne][col]);
    }
    printf("\n");
  }
}
// affichage des pions dans le tableau
void Jeu(struct Joueur PremierJoueur, struct Joueur DeuxiemeJoueur) 
{
  int jeton, cj1, lj1, i, tjeton = 1;
  jeton = (varplat.ligne * varplat.col - 1) / 2;
  printf("Nombres de jetons: %d \n", jeton);
  for (i = 0; i < jeton; i++) {
    int valeurJeton = i+1;
    printf("Au tour de %s !\n", PremierJoueur.Pseudo);
    bool coordoneesOk = false;
   
    while (!coordoneesOk){
      printf("Entrez la ligne ");
      scanf("%d", &lj1);
      printf("Entrez la colonne ");
      scanf("%d", &cj1);
      if (cj1 == 0 || lj1 == 0 || cj1 > varplat.col || lj1 > varplat.ligne ||
          varplat.tab[lj1 - 1][cj1 - 1] != 0) {
        printf("Cette case n'est pas disponible \n");
        coordoneesOk = false;
      } else {
        varplat.tab[lj1 - 1][cj1 - 1] = valeurJeton;
        AfficherTableau();
        coordoneesOk = true;
      }
    }
    coordoneesOk = false;
    while (!coordoneesOk) {
      printf("Au tour de %s !\n", DeuxiemeJoueur.Pseudo);
      printf("Veuillez entrer la ligne: ");
      scanf("%d", &lj1);
      printf("Veuillez entrer la colonne: ");
      scanf("%d", &cj1);
      if (cj1 == 0 || lj1 == 0 || cj1 > varplat.col || lj1 > varplat.ligne ||
          varplat.tab[lj1 - 1][cj1 - 1] != 0) {
        printf("Cette case n'est pas disponible \n");
        coordoneesOk = false;
      } else {
        varplat.tab[lj1 - 1][cj1 - 1] = -valeurJeton;
        AfficherTableau();
        coordoneesOk = true;
      }
    }
  }
}

// calcul des scores des joueurs
void calculerScoresPartieEnCours(struct Joueur *premierJoueur,
                                 struct Joueur *deuxiemeJoueur) 
{
  int score = 0;
  int colCaseVide, ligneCaseVide;
  // cherche les coordonnées de la case vide
  for (int i = 0; i < varplat.ligne; i++) {
    for (int j = 0; j < varplat.col; j++) {
      if (varplat.tab[i][j] == 0) {
        ligneCaseVide = i;
        colCaseVide = j;
      }
    }
  }
 
  //Définition des limites des lignes et colonnes pour ne pas sortir du tableau
  int limiteLignePrecedente, limiteLigneSuivante, limiteColPrecedente, limiteColSuivante;

  if (ligneCaseVide - 1 < 0)
    limiteLignePrecedente = ligneCaseVide;
  else
    limiteLignePrecedente = ligneCaseVide-1;

  if (colCaseVide - 1 < 0)
        limiteColPrecedente = colCaseVide;
  else
    limiteColPrecedente = colCaseVide -1;


  //check avec = car le numéro de lignes/colonnes commence à 0 dans le tableau
  if (ligneCaseVide +1 == varplat.ligne)
    limiteLigneSuivante = ligneCaseVide;
  else
    limiteLigneSuivante = ligneCaseVide+1;
  if (colCaseVide + 1 == varplat.col)
    limiteColSuivante = colCaseVide;
  else
    limiteColSuivante = colCaseVide +1;

  // compte le score des cases autour de la case vide
  for (int i = limiteLignePrecedente; i <= limiteLigneSuivante; i++) {
    for (int j = limiteColPrecedente; j <= limiteColSuivante; j++) {
      if (varplat.tab[i][j] > 0) {
        premierJoueur -> scorePartieEnCours += varplat.tab[i][j];
      }
      if (varplat.tab[i][j] < 0) {
        deuxiemeJoueur -> scorePartieEnCours += abs(varplat.tab[i][j]);
      }
    }
  }
 
  printf("scores calculés\n");
}

void calculerScoresTotaux() {
  Joueur1.ScoreTotal = Joueur1.ScoreTotal + Joueur1.scorePartieEnCours;
  Joueur2.ScoreTotal = Joueur2.ScoreTotal + Joueur2.scorePartieEnCours;
}

int main() {
  // saisie du pseudo de chaque joueur
  printf("Entrez le pseudo du joueur 1:\n");
  scanf("%s", &Joueur1.Pseudo);

  printf("Entrez le pseudo du joueur 2:\n");
  scanf("%s", &Joueur2.Pseudo);

  // init des scores totaux à 0
  Joueur1.ScoreTotal = 0;
  Joueur2.ScoreTotal = 0;

  // init des scores de la partie en cours à 0
  Joueur1.scorePartieEnCours = 0;
  Joueur2.scorePartieEnCours = 0;

  bool continuerPartie = true;
  int numPartie = 1;

  while (continuerPartie == 1) {
    printf("Partie numéro %d\n", numPartie);

    IntiJeu();
    //test permettant d'alterner l'ordre des joueurs
    if (numPartie % 2 == 1) {
      Jeu(Joueur1, Joueur2);
      calculerScoresPartieEnCours(&Joueur1, &Joueur2);
      printf("Score de %s : %d\n", Joueur1.Pseudo, Joueur1.scorePartieEnCours);
      printf("Score de %s : %d\n", Joueur2.Pseudo, Joueur2.scorePartieEnCours);

      calculerScoresTotaux();
      printf("Score total de %s : %d\n", Joueur1.Pseudo, Joueur1.ScoreTotal);
      printf("Score total de %s : %d\n", Joueur2.Pseudo, Joueur2.ScoreTotal);
    } else {
      Jeu(Joueur2, Joueur1);

      calculerScoresPartieEnCours(&Joueur2, &Joueur1);
      printf("Score de %s : %d\n", Joueur2.Pseudo, Joueur2.scorePartieEnCours);
      printf("Score de %s : %d\n", Joueur1.Pseudo, Joueur1.scorePartieEnCours);

      calculerScoresTotaux();
      printf("Score total de %s : %d\n", Joueur2.Pseudo, Joueur2.ScoreTotal);
      printf("Score total de %s : %d\n", Joueur1.Pseudo, Joueur1.ScoreTotal);
    }

    if (Joueur2.scorePartieEnCours != Joueur1.scorePartieEnCours)
        printf("Bravo %s ! Tu as gagné cette partie !\n", Joueur2.scorePartieEnCours < Joueur1.scorePartieEnCours ? Joueur2.Pseudo : Joueur1.Pseudo);
    else
        printf("Oh, match nul! Vous pouvez réessayer de vous départager en commençant une nouvelle partie si vous le souhaité");
    bool enteredValueCorrect = false;
    char continuer;
    do {
      printf("Voulez vous rejouer une partie ? o/n\n");
      scanf(" %c", &continuer);
      if (continuer == 'n' || continuer == 'N') {
        continuerPartie = false;
        enteredValueCorrect = true;
      }
      else if (continuer == 'o' || continuer == 'O') {
        continuerPartie = true;
        numPartie ++;
        enteredValueCorrect = true;
      } else {
        printf("Valeur saisie non valide. Veuillez saisir o pour OUI et n pour "
               "NON");
      }
    } while (!enteredValueCorrect);
  }
  return 0;
}