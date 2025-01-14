#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

/*Random number generator function*/
int Randomnum(int min, int max) {
    return rand() % (max - min + 1) + min;
}


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

void guess_the_number(char *fileName){
    int numbertofind = Randomnum(1, 100), counter, userinputnumber;
    bool numfound;

    userinputnumber=0;
    counter=0;
    numfound=false;

    while((numfound = false) || (counter <= 10)){
        // readLine(fileName, 5);
        printf("?");
        scanf("%d",&userinputnumber);
        if(numbertofind==userinputnumber){
            readLine(fileName, 7);
            numfound=true;
        }
        else if (userinputnumber < numbertofind)
        {
            printf("c'est plus");
        }
        else
        {
            printf("c'est moins");
        }
        printf("%d", counter);

        counter++;
    }
    if(counter>10 && numfound==false){
        readLine(fileName, 9);
    }
}

int main(){
    char fileName[20];
    snprintf(fileName, sizeof(fileName), "intro_fr.txt");

    srand(time(0));
    guess_the_number(fileName);
    return(0);
}
