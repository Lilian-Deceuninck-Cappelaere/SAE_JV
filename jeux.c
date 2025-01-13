/*Deceuninck Cappelaere Lilian et Molinaro Antoine*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct
{
    char name;
    int pv;
    char gender;
    int attaque;
        
} character;


void readLine(const char *fileName, int lineNumber)
/*Read the line number lineNumber*/
{
    FILE *file = fopen(fileName, "r");

    char buffer[1000];
    int currentLine = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (currentLine == lineNumber)
        {
            printf("%s", buffer);
            fclose(file);
            return;
        }
        currentLine++;
    }

    printf("Line %d not found in the file.\n", lineNumber);
    fclose(file);
}


char select_language(char *language)
/*Choose the language of the game*/
{
    int ok;  /*Boolean for check the language*/
    ok = 0;
    do
    {
        printf("Choisir la langue (fr) / Select language (en) : ");
        scanf("%s", language);

        if (strcmp(language, "fr") == 0)
        {
            printf("****Jeux en Français****\n\n");
            ok = 1;
        }

        else if (strcmp(language, "en") == 0)
        {
            printf("****Game in English****\n");
            ok = 1;
        }
    } while (ok == 0);

    return *language;
}

void intro(char *fileName, character *player)
/*Introduction of the game*/
{
    readLine(fileName, 1);
    printf("\n");
    readLine(fileName, 5);
    scanf("%s", player->name);
    readLine(fileName, 7);
    scanf("%s", player->gender);
}

int main(int argc, char *argv[])
{
    char language[3], fileName[20], name[15], gender[6];
    int end;
    character player; 
    end = 0;

    while (end == 0)
    {
        select_language(language);

        snprintf(fileName, sizeof(fileName), "intro_%s.txt", language);

        intro(fileName, *player);
    }
    
    return 0;
}