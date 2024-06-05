#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "save.h"

void save(int valeur_score)
{
    FILE *saveF = NULL;
    saveF = fopen("sauvegarde.txt", "w+"); // Ouverture en écriture du fichier sauvegarde.txt

    if (saveF != NULL)
    { // Ecriture dans le fichier des positions du joueur et score

        fprintf(saveF, "%d\n", valeur_score);
    }

    fclose(saveF); // Fermeture du fichier
}

/*------ Fonction de chargement --------*/

void load(int valeur_score)
{

    FILE *saveF = NULL;
    saveF = fopen("sauvegarde.txt", "r"); // Ouverture du fichier sauvegarde en lecture

    if (saveF != NULL)
    {

        fscanf(saveF, "%d", &valeur_score);
    }

    fclose(saveF); // Fermeture du fichier
}
