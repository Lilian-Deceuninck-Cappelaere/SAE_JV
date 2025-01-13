#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void readLine(const char *fileName, int lineNumber)
{
    FILE *file = fopen(fileName, "r");

    char buffer[1000];
    int currentLine = 1;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (currentLine == lineNumber)
        {
            printf("Line %d: %s", lineNumber, buffer);
            fclose(file);
            return;
        }
        currentLine++;
    }

    printf("Line %d not found in the file.\n", lineNumber);
    fclose(file);
}



char select_language(char *language)
{
    printf("Choisir la langue (fr) / Select language (en) : ");
    scanf("%s", language);

    if (strcmp(language, "fr") == 0)
    {
        printf("Jeux en français\n");
    }

    else if (strcmp(language, "en") == 0)
    {
        printf("Game in EN\n");
    }

    return *language;
}

char intro(char *fileName)
{
    readLine(fileName, 1);
}

int main(int argc, char *argv[])
{
    char language[3], fileName[20];

    select_language(language);

    snprintf(fileName, sizeof(fileName), "intro_%s.txt", language);

    intro(fileName);

    return 0;
}