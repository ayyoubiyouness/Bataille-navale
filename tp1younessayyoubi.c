#include <stdio.h>
#include <stdlib.h>
// Déclaration des fonctions qu'on va utiliser par la suite
int **allocation_tableau2D_int(int idim, int jdim);
void desallocation_tab2D_int(int **im, int idim) ;
void initialiser_tableau(int **tableau, int nb_lignes, int nb_colonnes);
void afficher_tableau(int **tableau, int nb_lignes, int nb_colonnes);
int nombre_voisines_vivantes(int **tableau, int idim, int jdim,  int i, int j );
// La fonction main
int main(int argc, char ** argv) {
  int n;
  int m;
  int k;
  // On vérifie si le nombre de paramètres est correct
  if ( argc !=4) {
    printf("Erreur de declaration des parametres Essayer de nouveau,\n");
    exit(EXIT_FAILURE);
  }
  // On transforme les paramètres en des entiers
  n= atoi(argv[1]);
  m= atoi(argv[2]);
  k= atoi(argv[3]);
  printf("n:%d, m:%d, k:%d\n", n,m,k);
  int **tableau;
  // on alloue la mémoire pour un tableau 2D
  tableau = allocation_tableau2D_int(n,m);
  // On initialise un tableau vide
  initialiser_tableau(tableau, n, m);
  // On remplit quelques cases du tableau
  tableau[3][3]=1;
  tableau[3][4]=1;
  tableau[2][3]=1;
  tableau[1][3]=1;
  afficher_tableau(tableau, n , m);
  printf("Application des regles de jeu de la vie \n ");
  
  int **nouveau_tableau;
  nouveau_tableau = allocation_tableau2D_int(n,m);
  int nb_voisines ;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      nb_voisines = nombre_voisines_vivantes(tableau, n, m, i, j);
      if (tableau[i][j] == 1 && (nb_voisines == 2 || nb_voisines == 3)) {
	nouveau_tableau[i][j] = 1; // La cellule reste vivante
      }
      else if (tableau[i][j] == 0 && nb_voisines == 3){
	nouveau_tableau[i][j] = 1; // La cellule devient vivante
      }
      else {
	nouveau_tableau[i][j] = 0;// La cellule reste morte
      }
    }
  }
  afficher_tableau(nouveau_tableau,n,m);
  desallocation_tab2D_int(tableau, n);
  return 0;
}


// Declaration des fonctions utilisées dans le main

int **allocation_tableau2D_int(int idim, int jdim) {
  int **im = NULL ;
  im = malloc( idim*sizeof(int *));
  int i;
  for ( i =0; i<idim; i++) {
    im[i] = malloc(jdim*sizeof(int));
  }
  return im;
}
void desallocation_tab2D_int(int **im, int idim) {
  for (int i = 0; i<idim; i++) {
    free(im[i]);
  }
  free(im);
}

void initialiser_tableau(int **tab, int idim, int jdim) {
    int i, j;

    for (i = 0; i < idim; i++) {
        for (j = 0; j < jdim; j++) {
            tab[i][j] = 0; 
        }
    }
}
void afficher_tableau(int **tableau, int idim, int jdim) {
  
    int i, j;

    for (i = 0; i < idim; i++) {
        for (j = 0; j < jdim; j++) {
            printf("%d ", tableau[i][j]); 
        }
        printf("\n"); 
    }
}

int nombre_voisines_vivantes(int **tableau, int idim, int jdim, int i, int j) {
  int nb_voisines = 0;
  int x, y;
  for (x = i-1; x <= i+1; x++) {
    for (y = j-1; y <= j+1; y++) {
      if (x >= 0 && x < idim && y >= 0 && y < jdim && (x != i || y != j)) {
	nb_voisines += tableau[x][y];
      }
    }
  }
  return nb_voisines;
}

