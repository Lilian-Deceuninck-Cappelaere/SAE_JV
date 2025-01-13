#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void readLine(const char *fileName, int lineNumber)
{
    FILE *file = fopen(fileName, "r");

    char buffer[256];
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

int main(int argc, char *argv[])
{
    char language[3], fileName[20];

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

    snprintf(fileName, sizeof(fileName), "intro_%s.txt", language);

    int lineNumber = 2; // The line number you want to read

    readLine(fileName, lineNumber);


    return 0;
}