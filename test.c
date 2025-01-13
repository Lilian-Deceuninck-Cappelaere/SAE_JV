#include <stdio.h>
#include <stdlib.h>

void lireLigne(const char *nomFichier, int numeroLigne)
{
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    int ligneActuelle = 1;

    while (fgets(buffer, sizeof(buffer), fichier) != NULL)
    {
        if (ligneActuelle == numeroLigne)
        {
            printf("Ligne %d: %s", numeroLigne, buffer);
            fclose(fichier);
            return;
        }
        ligneActuelle++;
    }

    printf("La ligne %d n'a pas été trouvée dans le fichier.\n", numeroLigne);
    fclose(fichier);
}

int main()
{
    const char *nomFichier = "intro_fr.txt";
    int numeroLigne = 2; // Numéro de la ligne que vous voulez lire

    lireLigne(nomFichier, numeroLigne);

    return 0;
}
