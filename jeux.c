/*Deceuninck Cappelaere Lilian et Molinaro Antoine*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>    /*For stopt temporary execution*/

/*The player and zombie statistics*/
typedef struct {
    char name[20];
    int pv;
    int tools;
} character;

void print_stats(char *filestats, char *language, character *player)
{
    snprintf(filestats, sizeof(filestats), "%s/stats.txt", language);
    FILE *file = fopen(filestats, "w");

    if ((strcmp(language, "fr") == 0) || (strcmp(language, "FR") == 0) || (strcmp(language, "Fr") == 0) || (strcmp(language, "fR") == 0))
    {
        fprintf(file, "**** Vos statistiques ****\n\tNom : %s\n\tPoints de vie : %d\n\tPoints d'attaque outils : %d", player->name, player->pv, player->tools);
    }
    else
    {
        fprintf(file, "**** Your statistics ****\n\tName : %s\n\tHealth points : %d\n\tTools attack  : %d", player->name, player->pv, player->tools);
    }
    fclose(file);
}


void readLine(const char *fileName, int lineNumber)
/*Read the line number lineNumber*/
{
    FILE *file = fopen(fileName, "r");  /*Open the file in read rights*/

    char buffer[1000];    /*Containts the caracters of the text*/
    int currentLine = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL) /*While line not find*/
    {
        if (currentLine == lineNumber)
        {
            printf("%s", buffer);
            fclose(file);       /*Close file*/
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

        if ((strcmp(language, "fr") == 0) || (strcmp(language, "FR") == 0) || (strcmp(language, "Fr") == 0) || (strcmp(language, "fR") == 0)) /*compares strings*/
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

int roll_dice(char *fileName)
/*Roll of dice up to result*/
{
    int dice;
    dice = 0;
    while (dice <= 5)
    {
        if (dice < 5)
        {
            printf("\n");
            readLine(fileName, 30);
            dice = Randomnum(1, 6);
            printf("%d", dice);
        }

        if (dice >= 5)
        {
            printf("\n");
            readLine(fileName, 32);
        }
    }
}




void guess_the_number(char *fileName)           /*A mini game to find a number*/
{
    int numbertofind, counter, userinputnumber;
    bool numfound, gamewin;

    numbertofind = Randomnum(1, 100);
    userinputnumber = 0;
    counter = 10;
    numfound = false;

    while ((numfound == false) && (counter > 0))
    {
        readLine(fileName, 9);                  /*Read line 9 in file*/
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
        playerAttack = rand() % 15 + player->tools;
        zombieAttack = rand() % 15;

        printf("%s", player->name);
        readLine(fileName, 42);
        printf("%d\n", playerAttack);
        readLine(fileName, 43);
        printf("%d\n", zombieAttack);

        player->pv -= zombieAttack;
        zombie->pv -= playerAttack;

        printf("%s", player->name);
        readLine(fileName, 45);
        printf("%d\n", player->pv);
        readLine(fileName, 46);
        printf("%d\n", zombie->pv);
        sleep(3);
        printf("\n");                       /*Stopt 4 sec execution*/
    }
    
    if (player->pv == 0)
    {
        end = true;
    }    

    return end;
}

void intro(char *fileName, character *player)
/*Introduction of the game*/
{
    readparagraph(fileName, 1, 5);
    printf("\n");
    readLine(fileName, 10);
    scanf("%s", &player->name);
}

void chap1(char *fileName, character *player, character *zombie, int end)
/*Chapter 1 of the game*/
{
    int key, action, i;

    printf("\n");
    readLine(fileName, 1);
    printf("%s", player->name);
    readparagraph(fileName, 2, 6);
    srand(time(0));
    printf("\n");
    guess_the_number(fileName);
    printf("\n");
    readparagraph(fileName, 21, 26);
    readLine(fileName, 28);
    scanf("%d", &key);
    if (key == 1)
    {
        roll_dice(fileName);
    }
    player->tools = 3;
    printf("\n");
    readparagraph(fileName, 34, 36);
    scanf("%d", &action);
    for (i = 0; i < 2; i++)
    {
        switch (action)
        {
        case 1:
            readLine(fileName, 40);
            scanf("%d", &key);
            if (key == 1)
            {
                printf("\n");
                fight(fileName, player, zombie, end);
            }
            readparagraph(fileName, 48, 54);
            i = 1;
            break;

        case 2:
            readparagraph(fileName, 57, 61);
            player->pv -= 20;
            action = 1;
            break;
        
        default:
            break;
        }
    }
    
    


    if (end == false)
    {
        readLine(fileName, 38);
        end = true;
    }
}

void chap2(char *fileName, character *player, int end)
/*Chapter 2 of the game*/
{

}

int main(int argc, char *argv[])
{
    char language[3], fileName[20], filestats[20];
    int action, i, j;
    bool end;

    /*Initializing Player and Zombie Settings*/
    character player;
    player.pv = 100;
    character zombie;
    zombie.pv = 20;
    end = false;
    

    select_language(language);
    snprintf(fileName, sizeof(fileName), "%s/intro.txt", language);
    intro(fileName, &player);
    print_stats(filestats, language, &player);
    readparagraph(filestats, 1, 4);

    while (end == false)
    {
        snprintf(fileName, sizeof(fileName), "%s/chap1.txt", language);
        chap1(fileName, &player, &zombie, end);
        snprintf(fileName, sizeof(fileName), "%s/chap2.txt", language);
        chap2(fileName, &player, end);
    }
    
    return 0;
}