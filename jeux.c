/*Deceuninck Cappelaere Lilian et Molinaro Antoine*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


typedef struct {
    char name[20];
    char gender[10];
    int pv;
} character;


void readLine(const char *fileName, int lineNumber)
/*Read the line number lineNumber*/
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", fileName);
        return;
    }

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

void readparagraph(const char *fileName, int lineNumber, int lineEnd)
/*Read the paragraph between lineNumber and lineEnd*/
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", fileName);
        return;
    }

    char buffer[1000];
    int currentLine = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (currentLine >= lineNumber && currentLine <= lineEnd)
        {
            printf("%s", buffer);
        }
        currentLine++;
    }

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

        if ((strcmp(language, "fr") == 0) || (strcmp(language, "FR") == 0) || (strcmp(language, "Fr") == 0) || (strcmp(language, "fR") == 0))
        {
            printf("****Jeux en Français****\n\n");
            ok = 1;
        }

        else if ((strcmp(language, "en") == 0) || (strcmp(language, "EN") == 0) || (strcmp(language, "En") == 0) || (strcmp(language, "eN") == 0))
        {
            printf("****Game in English****\n");
            ok = 1;
        }
        
        else
        {
            printf("Erreur, veuillez choisir entre 'fr' et 'en'! / Error, please choose between 'fr' and 'en'\n");
        }
    } while (ok == 0);

    return *language;
}



int Randomnum(int min, int max)
/*Random number generator function*/
{
    return rand() % (max - min + 1) + min;
}

void guess_the_number(char *fileName)
{
    int numbertofind, counter, userinputnumber;
    bool numfound, gamewin;

    numbertofind = Randomnum(1, 100);
    userinputnumber = 0;
    counter = 10;
    numfound = false;

    while ((numfound == false) && (counter > 0))
    {
        readLine(fileName, 9);
        scanf("%d", &userinputnumber);
        if (numbertofind == userinputnumber)
        {
            readLine(fileName, 17);
            numfound = true;
        }
        else if (userinputnumber < numbertofind)
        {
            readLine(fileName, 11);
            counter--;
            readLine(fileName, 15);
            printf("%d\n", counter);
        }
        else
        {
            readLine(fileName, 13);
            counter--;
            readLine(fileName, 15);
            printf("%d\n", counter);
        }
    }
    if (counter == 0 && numfound == false)
    {
        readLine(fileName, 19);
        guess_the_number(fileName);
    } 

}

bool fight(char *fileName, character *player, character *zombie, bool end) 
/*Fight between the player and the zombie*/
{
    int playerAttack, zombieAttack;
    while ((player->pv > 0) && (zombie->pv > 0))
    {
        playerAttack = rand() % 15 + 5;
        zombieAttack = rand() % 10;

        printf("%s", player->name);
        readLine(fileName, 32);
        printf("%d\n", playerAttack);
        readLine(fileName, 33);
        printf("%d\n", zombieAttack);

        player->pv -= zombieAttack;
        zombie->pv -= playerAttack;

        printf("%s", player->name);
        readLine(fileName, 35);
        printf("%d\n", player->pv);
        readLine(fileName, 36);
        printf("%d\n", zombie->pv);
    }
    
    if (player->pv == 0)
    {
        // readLine()
        end = true;
    }    

    return end;
}

void intro(char *fileName, character *player)
/*Introduction of the game*/
{
    readLine(fileName, 1);
    printf("\n");
    readLine(fileName, 5);
    scanf("%s", &player->name);
    readLine(fileName, 7);
    scanf("%s", &player->gender);
}

void chap1(char *fileName, character *player, character *zombie, int end)
/*Chapter 1 of story*/
{
    printf("\n");
    readLine(fileName, 1);
    printf("%s", player->name);
    readparagraph(fileName, 2, 6);
    srand(time(0));
    printf("\n");
    guess_the_number(fileName);
    printf("\n");
    readparagraph(fileName, 21, 26);
    /*Add roll of dice*/
    readparagraph(fileName, 29, 30);
    fight(fileName,player, zombie, end);
    if (end == false)
    {
        readLine(fileName, 31);
        end = true;
    }
}


int main(int argc, char *argv[])
{
    char language[3], fileName[20];
    int action, i, j;
    bool end;

    character player;
    player.pv = 100;
    character zombie;
    zombie.pv = 20;
    end = false;
    

    select_language(language);
    snprintf(fileName, sizeof(fileName), "%s/intro.txt", language);

    // while (end == false && player.pv > 0)
    // {
        intro(fileName, &player);
        snprintf(fileName, sizeof(fileName), "%s/chap1.txt", language);
        chap1(fileName, &player, &zombie, end);
    // }
    
    return 0;
}