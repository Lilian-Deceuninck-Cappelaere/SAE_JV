/*Deceuninck Cappelaere Lilian et Molinaro Antoine*/

#include <stdio.h>     /*Input/output library*/
#include <stdlib.h>    /*For files*/
#include <ctype.h>     /*To pass a string in lowercase*/
#include <string.h>    /*For string*/
#include <time.h>      /*For time*/
#include <stdbool.h>   /*For boolean*/
#include <unistd.h>    /*To stop execution temporary*/

/*The player and zombie statistics*/
typedef struct {
    char name[20];
    int pv;
    int tools;
} character;



bool validInput(char *input) {/*Function used to check if user's input is a number*/
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

char* strlwr(char *str)
/*Pass a string in lowercase*/
{
    char *tmp = str;
    while (*tmp)
    {
        *tmp = tolower((char)*tmp);         /*Convert*/
        tmp++;
    }
    return str;
}

void print_stats(char *filestats, char *language, character *player)
/*Saves and displays player statistics*/
{
    snprintf(filestats, 13, "%s/stats.txt", language);  /*Name of file*/
    FILE *file = fopen(filestats, "w");                 /*Open the file in write tights*/

    if (strcmp(language, "fr") == 0)
    {
        fprintf(file, "**** Vos statistiques ****\n\tNom : %s\n\tPoints de vie : %d\n\tPoints d'attaque outils : %d", player->name, player->pv, player->tools);
    }
    else
    {
        fprintf(file, "**** Your statistics ****\n\tName : %s\n\tHealth points : %d\n\tTools attack  : %d", player->name, player->pv, player->tools);
    }
    fclose(file);
}


void readLine(char *fileName, int lineNumber)
/*Read the line number lineNumber*/
{
    FILE *file = fopen(fileName, "r");  /*Open the file in read rights*/

    char buffer[1000];    /*Containts the caracters of the text*/
    int currentLine = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL) /*While line not find*/
    {
        if (currentLine == lineNumber)
        {
            printf("%s", buffer);   /*Displays the line*/
            fclose(file);           /*Close file*/
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

        if (strcmp(strlwr(language), "fr") == 0) /*Turns the string to lowercase and compares whith "fr"*/
        {
            printf("****Jeux en Français****\n\n");
            ok = 1;
        }

        else if (strcmp (strlwr(language), "en") == 0)/*Turns the string to lowercase and compares whith "en"*/
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
    srand(time(0));     /*For different random number in each game*/
    return rand() % (max - min + 1) + min; /*Generate a random number within a specified range [min, max] */
}

int roll_dice(char *language)
/*Roll of dice up to result*/
{
    int dice, i;
    char fileName_dice[13];

    dice = 0;

    snprintf(fileName_dice, 13, "%s/chap1.txt", language); /*Change the file*/
    FILE *file = fopen(fileName_dice, "r");

    i = 0;

    while ((dice <= 4) && (i < 7))
    {
        if ((dice < 4) && (i <= 5))
        {
            printf("\n");
            readLine(fileName_dice, 30);        /*Read  line 30 in file*/
            dice = Randomnum(1, 6);             /*Generate a random number between 1 and 6*/
            printf("%d", dice);
            i++;
        }

        if (i == 6)
        {
            printf("\n");
            readLine(fileName_dice, 30);
            dice = 5;
            printf("%d", dice);
        }
        

        if (dice >= 4)
        {
            printf("\n");
        }
    }
}




void guess_the_number(char *fileName) {
    int numbertofind, counter, userinputnumber;
    bool numfound, gamewin;
    char userinputnumberchar[10];
    numbertofind = Randomnum(1, 100);
    counter = 10;
    numfound = false;
    printf("%d",numbertofind);
    while ((!numfound) && (counter > 0)) {
        userinputnumberchar[0] = '\0'; /*Initialize the variable to an empty string*/
        readLine(fileName, 9);
        scanf("%s", userinputnumberchar); /*Read input as string*/
        if (!validInput(userinputnumberchar)) {/*Calls validInput function*/
            readLine(fileName, 118);
            continue; /*Skip the rest of the loop if user's input is invalid*/
        }
        userinputnumber = atoi(userinputnumberchar); /*Convert input string to an integer if valid*/
        if (numbertofind == userinputnumber) {
            readLine(fileName, 17);
            numfound = true;
        } else if (userinputnumber < numbertofind) {
            readLine(fileName, 11);
            counter--;
            readLine(fileName, 15);
            printf("%d\n", counter);
        } else {
            readLine(fileName, 13);
            counter--;
            readLine(fileName, 15);
            printf("%d\n", counter);
        }
    }
    if ((counter == 0) && (!numfound)) {
        readLine(fileName, 19);
        guess_the_number(fileName);
    }
}


void fight(char *fileName, character *player, character *zombie) 
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

        player->pv -= zombieAttack;/*substract zombie attack health points to player's health points*/
        zombie->pv -= playerAttack;/*substract player's attack health points to zombie's health points*/

        printf("%s", player->name);
        readLine(fileName, 45);
        printf("%d\n", player->pv);
        readLine(fileName, 46);
        if (zombie->pv < 0)/*If zombies healt points are negative, they are set to 0 because HP can't be negative*/
        {
            zombie->pv = 0;
        }
        
        printf("%d\n", zombie->pv);
        sleep(1.5);
        printf("\n");
    }
}

void paper_scissors_stone(char *fileName)
/*Mini game : paper, scissors, stone*/
{
    int choice, winp, winl, looter;

    winp = 0;
    winl = 0;
    
    printf("\n");

    do
    {
        readparagraph(fileName, 53, 56);
        scanf("%d", &choice);
        looter = Randomnum(1, 3);

        if (choice == looter)
        {
            readLine(fileName, 58);
        }

        else if ((((choice == 1) && (looter == 3)) || ((choice == 2) && (looter == 1)) || ((choice == 3) && (looter == 2))))
        {
            readLine(fileName, 60);
            winp++;
        }

        else
        {
            readLine(fileName, 62);
            winl++;
        }

    } while ((winp != 3) && (winl != 3));
    
    if (winp == 3)
    {
        readLine(fileName, 64);
    }

    else
    {
        readLine(fileName, 66);
    }
}

void enigma(char *fileName)
/*A riddle*/
{
    char word[50];
    int i;
    bool find;
    i = 0;
    find = false;
    do
    {
        readLine(fileName, 73);
        scanf("%s", word);
        printf("\n");

        if ((strcmp(strlwr(word), "silence") == 0) || (strcmp(strlwr(word), "quiet") == 0))
        {
            readLine(fileName, 75);
            printf("\n");
            find = true;
        }
        else
        {
            readLine(fileName, 77);
            i++;
        }
    } while (!find && i < 2);
    if(find=false){
        readLine(fileName,78);
    }
}


void intro(char *fileName, character *player)
/*Introduction of the game*/
{
    readparagraph(fileName, 1, 5);
    printf("\n");
    readLine(fileName, 10);
    scanf("%s", &player->name);
}

void chap1(char *fileName, char *filestats, char *language, character *player, character *zombie)
/*Chapter 1 of the game*/
{
    int key, action, i, room, code;
    bool computer, td, tp, mrSynaveoffice, library, password, inpOk;
    char roomchar[10], codechar[4];

    printf("\n");
    print_stats(filestats, language, player);
    readparagraph(filestats, 1, 4);
    printf("\n");
    readLine(fileName, 1);
    printf("%s", player->name);
    readparagraph(fileName, 2, 6);
    printf("\n");
    guess_the_number(fileName);
    printf("\n");
    readparagraph(fileName, 21, 26);
    readLine(fileName, 28);
    scanf("%d", &key);
    
    if (key == 1)
    {
        roll_dice(language);
    }

    readLine(fileName, 32);
    printf("\n");
    player->tools = 3;
    print_stats(filestats, language, player);
    readparagraph(filestats, 1, 4);
    printf("\n\n");
    readparagraph(fileName, 34, 36);
    scanf("%d", &action);
    for (i = 0; i < 2; i++)/*User choices between two possibilities*/
    {
        switch (action)
        {
        case 1:
            readparagraph(fileName, 57, 61);
            player->pv -= 20;
            action = 2;
            break;

        case 2:
            readLine(fileName, 40);
            scanf("%d", &key);
            if (key == 1)
            {
                printf("\n");
                print_stats(filestats, language, player);
                readparagraph(filestats, 1, 4);
                printf("\n");
                fight(fileName, player, zombie);
            }
            readparagraph(fileName, 48, 54);
            i = 1;
            break;

        default:
            break;
        }
    }
    /*room visited status. False if user haven't visited the room yet*/
    computer = false;
    td = false;
    tp = false;
    mrSynaveoffice = false; 
    library = false;

    
    while ((!computer) || (!td) || (!tp) || (!mrSynaveoffice) || (!library))/*Loop: stops if user visited all rooms*/
    {
        printf("\n");
        roomchar[0] = '\0'; /*Initialize the variable to an empty string*/
        readparagraph(fileName, 64, 70);
        scanf("%s", roomchar); /*Read input as string*/
        if (!validInput(roomchar)) {/*Calls validInput function*/
            readLine(fileName, 118);
            continue; /*Skip the rest of the loop if user's input is invalid*/
        }
        room = atoi(roomchar); /*Convert input string to an integer if valid*/
        switch (room)
        {
        case 1:
            if(computer==true){/*test if the room has already been visited*/
                readLine(fileName,115);
            }
            else{/*If the room has never been visited by the player*/
            readparagraph(fileName, 74, 78);
            computer = true;
            }
            break;
        case 2:
            if(tp==true){
                readLine(fileName,115);
            }
            else
            {
            readparagraph(fileName, 81, 87);
            player->pv -= 5;
            printf("\n");
            print_stats(filestats, language, player);
            readparagraph(filestats, 1, 4);
            printf("\n");
            tp = true;
            }
            break;

        case 3:
            if(td==true){
                readLine(fileName,115);
            }
            else
            {
            readparagraph(fileName, 90, 92);
            zombie->pv = 20;
            fight(fileName, player, zombie);
            readLine(fileName, 93);
            td = true;
            }
            break;

        case 4:
            readLine(fileName, 96);
            mrSynaveoffice = true;
            break;

        case 5:
            if(library==true){
                readLine(fileName,115);
            }
            else
            {
            readparagraph(fileName, 99, 101);
            library = true;
            }
            break;

        default:
            break;
        }
    }

    printf("\n");
    readLine(fileName, 104);
    password = false;
    while (!password)
    {
        codechar[0] = '\0'; /*Initialize the variable to an empty string*/
        readLine(fileName, 106);
        scanf("%s", codechar); /*Read input as string*/
        if (!validInput(codechar)) {/*Calls validInput function*/
            readLine(fileName, 118);
            continue; /*Skip the rest of the loop if user's input is invalid*/
        }
        code = atoi(codechar); /*Convert input string to an integer if valid*/

        if (code == 371)
        {
            printf("\n");
            readparagraph(fileName, 109, 111);
            password = true;
            printf("\n");
        }

        else
        {
            readLine(fileName, 108);
        }
    }
}

void chap2(char *fileName, char *filestats, char *language, character *player, character *zombie)
/*Chapter 2 of the game*/
{
    int key;
    bool keyOK;
    char keyChar[2];

    printf("\n");
    readparagraph(fileName, 1, 13);
    sleep(2);
    keyOK=false;
    
    while(!keyOK){
        keyChar[0] = '\0';/*Initialize the variable to an empty string*/ 
        scanf("%s", keyChar);/*Read input as string*/
        if(!validInput(keyChar)){
            readLine(fileName, 96);
            printf("\n");
            continue;/*Skip the rest of the loop if user's input is invalid*/
        }
        else
        {
            keyOK = true;
        }
    }
    key = atoi(keyChar);/*Convert input string to an integer if valid*/
    
    printf("\n\n");
    

    readparagraph(fileName, 15, 31);
    player->pv -= 2;
    sleep(2);
    
    keyOK = false;
    
    while(!keyOK){
        keyChar[0] = '\0';/*Initialize the variable to an empty string*/ 
        scanf("%s", keyChar);/*Read input as string*/
        if(!validInput(keyChar)){
            readLine(fileName, 96);
            printf("\n");
            continue;/*Skip the rest of the loop if user's input is invalid*/
        }
        else
        {
            keyOK = true;
        }
    }
    key = atoi(keyChar);/*Convert input string to an integer if valid*/
    
    printf("\n\n");

    readparagraph(fileName, 39, 43);
    roll_dice(language);
    readLine(fileName, 46);
    printf("\n");

    readLine(fileName, 47);
    printf("\n");
    readparagraph(fileName, 48, 51);
    paper_scissors_stone(fileName);

    sleep(1);
    readparagraph(fileName, 69, 72);
    enigma(fileName);
    sleep(2.5);
    readparagraph(fileName, 79, 93);
}

void chap3(char *fileName, char *language, character player)
{
    int key;
    bool keyOK;
    char keyChar[2];

    printf("\n%s", player.name);
    readparagraph(fileName, 1, 4);

    while (!keyOK)
    {
        keyChar[0] = '\0';    /*Initialize the variable to an empty string*/
        scanf("%s", keyChar); /*Read input as string*/
        if (!validInput(keyChar))
        {
            readLine(fileName, 6);
            printf("\n");
            continue; /*Skip the rest of the loop if user's input is invalid*/
        }
        else
        {
            keyOK = true;
        }
    }
    key = atoi(keyChar); /*Convert input string to an integer if valid*/
}

int main(int argc, char *argv[])
{
    char language[3], fileName[13], filestats[13];
    int action, i, j;

    character player;
    character zombie;

    select_language(language);
    snprintf(fileName, 13, "%s/intro.txt", language);
    intro(fileName, &player);
    

    /*Initializing Player and Zombie Settings*/
    player.pv = 100;
    player.tools = 0;
    zombie.pv = 20;

    snprintf(fileName, 13, "%s/chap1.txt", language);
    chap1(fileName, filestats, language, &player, &zombie);

    snprintf(fileName, 13, "%s/chap2.txt", language);
    chap2(fileName, filestats, language, &player, &zombie);

    snprintf(fileName, 13, "%s/chap3.txt", language);
    chap3(fileName, language, player);

    return 0;
}