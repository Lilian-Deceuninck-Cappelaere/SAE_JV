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

void guess_the_number(){
    int numbertofind = Randomnum(1,100);
    int userinputnumber;
    int counter;
    bool numfound;
    userinputnumber=0;
    counter=0;
    numfound=false;
    while(numfound=false && counter<=10){
        readLine("chap1_fr.txt", 5);
        scanf("%d",&userinputnumber);
        if(numbertofind==userinputnumber){
            readLine("chap1_fr.txt", 7);
            numfound=true;
        }   
        counter++;
    }
    if(counter>10 && numfound==false){
        readLine("chap1_fr.txt", 9);
    }
}

int main(){
    srand(time(0));
    guess_the_number();
    return(0);
}