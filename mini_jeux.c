#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/*Random number generator function*/
int Randomnum(int min, int max) {
    return rand() % (max - min + 1) + min;
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
        printf("Texte entrez votre nombre");
        scanf("%d",&userinputnumber);
        if(numbertofind==userinputnumber){
            printf("texte vous avez gagner");
            numfound=true;
        }   
        counter++;
    }
    if(counter>10 && numfound==false){
        printf("Texte : vous avez perdu");
    }
}

int main(){
    srand(time(0));
    guess_the_number();
    return(0);
}