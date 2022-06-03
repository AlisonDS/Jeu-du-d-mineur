#include <stdio.h>
#include <stdlib.h>

char **GRILLE;
char **MINES;
int NbMines;
int TAILLE;
int NbMinesAutour=0;

void AffichageLancement() //Présentation du jeu et choix du niveau de jeux
{
    int choix,jeu;

    printf(" ________________________________\n");
    printf("|       Jeu du demineur          |\n");
    printf("|      Dos Santos Alison         |\n");
    printf("|________________________________|\n\n");


    printf("\n* * * * * * * * * * * * *\n");
    printf("*                       *\n");
    printf("*   JEU DU DEMINEUR     *\n");
    printf("*       Projet          *\n");
    printf("*                       *\n");
    printf("*     Dos Santos        *\n");
    printf("*       Alison          *\n");
    printf("* * * * * * * * * * * * *\n");

    printf("\nBienvenue dans le jeu du demineur, choisissez votre niveau de jeu : ");
    printf("\n1 : FACILE");
    printf("\n2 : NORMAL");
    printf("\n3 : DIFFICILE");
    printf("\n4 : EXTREME");
    printf("\n5 : PERSONNALISER\n\n");

    printf("Entrez le niveau de jeu choisi : ");
    scanf("%d", &jeu);
    printf("\n");

    if (jeu == 1)
    {
        printf("Vous jouez sur une grille de 5x5 avec 5 mines.\n\n");
        TAILLE = 5;
        NbMines = 5;
    }
    if (jeu == 2)
    {
        printf("Vous jouez sur une grille de 10x10 avec 20 mines.\n\n");
        TAILLE = 10;
        NbMines = 20;
    }
    if (jeu == 3)
    {
        printf("Vous jouez sur une grille de 20x20 avec 80 mines.\n\n");
        TAILLE = 20;
        NbMines = 80;
    }
    if (jeu == 4)
    {
        printf("Vous jouez sur une grille de 20x20 avec 120 mines.\n\n");
        TAILLE = 20;
        NbMines = 120;
    }
    if (jeu == 5)
    {
        printf("Saisir vos propres dimensions de la grille : ");

        do
        {
            scanf("%d", &TAILLE);
            printf("\n");
            if (TAILLE>50) printf("Dimensions trop grandes.\nVeuillez ressayer : ");
        } while (TAILLE>50);

        printf("Saisir le nombre de mines : ");

        do
        {
            scanf("%d", &NbMines);
            printf("\n");
            if (NbMines>=TAILLE*TAILLE) printf("Vous avez saisi un trop grand nombre de mines.\nSaisir à  nouveau le nombre de mines : ");
        } while (NbMines>=TAILLE*TAILLE);

        printf("Vous jouez sur une grille de %dx%d avec %d mines.\n\n", TAILLE, TAILLE, NbMines);
    }
    if ((jeu!=1)&&(jeu!=2)&&(jeu!=3)&&(jeu!=4)&&(jeu!=5)) printf("Tapez un nombre existant svp");
}

void **AffichageGrille() //Affichage de la grille
{
    int i, j;
    GRILLE = (char**)malloc(sizeof(char*)*TAILLE);

    for (i=0; i<TAILLE; i++)
    {
        GRILLE[i] = (char*)malloc(sizeof(char)*TAILLE);

        for (j=0; j<TAILLE; j++)
        {
            GRILLE[i][j] = '_';
        }
    }

    for (i=0; i<TAILLE; i++) printf(" _");
    for (i=0; i<=TAILLE-1; i++)
    {
        for (j=0; j<=TAILLE-1; j++)
        {
            if (j==0)
            {
                printf("\n|%c|", GRILLE[i][j]);
            }
            else {
                printf("%c|", GRILLE[i][j]);
            }
        }
    }
}

void PlacementMines() //Affichage des différentes mines en fonction du nombres de mines choisis au début de la partie (avec le niveau)
{
    int x, y,i, j;

    MINES = (char**)malloc(sizeof(char*)*TAILLE);

    for (i=0; i<TAILLE; i++)
    {
        MINES[i] = (char*)malloc(sizeof(char)*TAILLE);

        for (j=0; j<TAILLE; j++)
        {
            MINES[i][j] = '_';
        }
    }

    for (i=0; i<NbMines; i++)
    {
        x = rand()%TAILLE;
        y = rand()%TAILLE;

        if (MINES[x][y] == '_') MINES[x][y] = '@';
        else NbMines++;
    }

   /* printf("\n\n");
    for (i=0; i<=TAILLE-1; i++)
    {
        for (j=0; j<=TAILLE-1; j++)
        {
            if (j==0)
            {
                printf("\n|%c|", MINES[i][j]);
            }
            else {
                printf("%c|", MINES[i][j]);
            }
        }
    }*/
}

void MineVerif (int x, int y) //vérifie dans le tableau mine si on tombe sur une mine ou sinon nous indique le nombre de mimines à proximité
{
    if (MINES[x][y] == '@')
    {
        NbMines=0;
        printf("Dommage, tu as perdu! Retentes une partie ! \n");
    }

    if(x>0 && y>0)
    {
        if (MINES[x - 1][y] == '@')
            NbMinesAutour++;
        if (MINES[x + 1][y] == '@')
            NbMinesAutour++;
        if (MINES[x][y - 1] == '@')
            NbMinesAutour++;
        if (MINES[x][y + 1] == '@')
            NbMinesAutour++;
        if (MINES[x - 1][y - 1] == '@')
            NbMinesAutour++;
        if (MINES[x + 1][y - 1] == '@')
            NbMinesAutour++;
        if (MINES[x + 1][y + 1] == '@')
            NbMinesAutour++;
        if (MINES[x - 1][y + 1] == '@')
            NbMinesAutour++;
    }
    else
    {
        if (x == 0)
        {
            if (y == 0)
            {
                if (MINES[x][y + 1] == '@')
                    NbMinesAutour++;
                if (MINES[x + 1][y + 1] == '@')
                    NbMinesAutour++;
                if (MINES[x + 1][y] == '@')
                    NbMinesAutour++;
            }
            if (y == TAILLE-1)
            {
                if (MINES[x][y - 1] == '@')
                    NbMinesAutour++;
                if (MINES[x + 1][y - 1] == '@')
                    NbMinesAutour++;
                if (MINES[x + 1][y] == '@')
                    NbMinesAutour++;
            }
            else
            {
                if (MINES[x][y - 1] == '@')
                    NbMinesAutour++;
                if (MINES[x][y + 1] == '@')
                    NbMinesAutour++;
                if (MINES[x + 1][y] == '@')
                    NbMinesAutour++;
                if (MINES[x + 1][y - 1] == '@')
                    NbMinesAutour++;
                if (MINES[x + 1][y + 1] == '@')
                    NbMinesAutour++;
            }
        }
        if (x == TAILLE-1)
        {
            if (y == 0)
            {
                if (MINES[x - 1][y] == '@')
                    NbMinesAutour++;
                if (MINES[x - 1][y + 1] == '@')
                    NbMinesAutour++;
                if (MINES[x][y + 1] == '@')
                    NbMinesAutour++;
            }
            if (y == TAILLE-1)
            {
                if (MINES[x][y - 1] == '@')
                    NbMinesAutour++;
                if (MINES[x - 1][y - 1] == '@')
                    NbMinesAutour++;
                if (MINES[x - 1][y] == '@')
                    NbMinesAutour++;
            }
            else
            {
                if (MINES[x][y - 1] == '@')
                    NbMinesAutour++;
                if (MINES[x][y + 1] == '@')
                    NbMinesAutour++;
                if (MINES[x - 1][y] == '@')
                    NbMinesAutour++;
                if (MINES[x - 1][y - 1] == '@')
                    NbMinesAutour++;
                if (MINES[x - 1][y + 1] == '@')
                    NbMinesAutour++;
            }
        }
        if (y == 0 && x != 0 && x != TAILLE-1)
        {
            if (MINES[x - 1][y] == '@')
                NbMinesAutour++;
            if (MINES[x + 1][y] == '@')
                NbMinesAutour++;
            if (MINES[x][y + 1] == '@')
                NbMinesAutour++;
            if (MINES[x - 1][y + 1] == '@')
                NbMinesAutour++;
            if (MINES[x + 1][y + 1] == '@')
                NbMinesAutour++;
        }
        if (y == TAILLE-1 && x != 0 && x != TAILLE-1)
        {
            if (MINES[x][y - 1] == '@')
                NbMinesAutour++;
            if (MINES[x + 1][y] == '@')
                NbMinesAutour++;
            if (MINES[x + 1][y - 1] == '@')
                NbMinesAutour++;
            if (MINES[x - 1][y] == '@')
                NbMinesAutour++;
            if (MINES[x - 1][y - 1] == '@')
                NbMinesAutour++;
        }
    }

    if (MINES[x][y] != '@') printf("\nIl y a %d mines autour ", NbMinesAutour);
}

void MinesRestantes (x,y)
{
    if (MINES[x][y] == '@')
    {
        NbMines--;
        GRILLE[x][y] = '*';
        printf("Votre case est marquer. Il reste %d mines a decouvrir\n",NbMines);
    }
    else
    {
        printf("Il n'y a pas de mines\n");
    }
}

void MinesVoisines(x,y)
{
    if (NbMinesAutour == 0) GRILLE[x][y] = '0';
    if (NbMinesAutour == 1) GRILLE[x][y] = '1';
    if (NbMinesAutour == 2) GRILLE[x][y] = '2';
    if (NbMinesAutour == 3) GRILLE[x][y] = '3';
    if (NbMinesAutour == 4) GRILLE[x][y] = '4';
    if (NbMinesAutour == 5) GRILLE[x][y] = '5';
    if (NbMinesAutour == 6) GRILLE[x][y] = '6';
    if (NbMinesAutour == 7) GRILLE[x][y] = '7';
    if (NbMinesAutour == 8) GRILLE[x][y] = '8';

}
void NouvelleGrille(x,y)
{
    int i,j;
    for (i=0; i<=TAILLE-1; i++)
    {
        for (j=0; j<=TAILLE-1; j++)
        {
            if (j==0)
            {
                printf("\n|%c|", GRILLE[i][j]);
            }
            else {
                printf("%c|", GRILLE[i][j]);
            }
        }
    }
}

int main ()
{
    int x,y,choix;
    AffichageLancement();
    AffichageGrille();
    PlacementMines();
    do
    {
        printf("\nSi vous voulez decouvrir une case taper 1, si vous voulez placer un drapeau taper 2 :\n\n");
        scanf("%d", &choix);

         if (choix == 1)
         {
            printf("Entrez les coordonnees x pour les lignes et y pour les colonnes\n");
            scanf("\n%d %d",&x,&y);
            MineVerif(x,y);
            MinesVoisines(x,y);
            NouvelleGrille(x,y);
         }
         if (choix == 2)
         {
            printf("Entrez les coordonnees x pour les lignes et y pour les colonnes\n");
            scanf("\n%d %d",&x,&y);
            MinesRestantes(x,y);
            NouvelleGrille(x,y);
         }

    } while (NbMines != 0);

    if(NbMines==0)
    {
        printf(" ________________________________\n");
        printf("|              BRAVO !!          |\n");
        printf("|          Vous avez gagnez !    |\n");
        printf("|  Vous etes le/la meilleur(e)!  |\n");
        printf("|________________________________|\n\n");
    }

    return 0;
}
