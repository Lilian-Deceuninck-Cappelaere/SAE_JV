#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const char *filename = "intro_%c.txt";

int main(int argc, char *argv[])
{
    char language[2];
    printf("Choisir la langue (fr) / Select language (gb) : ");
    scanf("%s", language);

    if ((strcmp(language, "fr") == 0) || (strcmp(language, "FR") == 0) || (strcmp(language, "Fr") == 0) || (strcmp(language, "fR") == 0))
    {
        printf("Jeux en français %s", language);
    }

    else if ((strcmp(language, "gb") == 0) || (strcmp(language, "GB") == 0) || (strcmp(language, "Gb") == 0) || (strcmp(language, "gB") == 0))
    {
        printf("Game in GB");

        // open the file
        FILE *in_file = fopen(filename, "r");

        // read the file size
        struct stat sb;
        stat(filename, &sb);

        // allocation of the character array
        char *file_contents = malloc(sb.st_size);

        // display line by line
        while (fscanf(in_file, " %[^\n] ", file_contents) != EOF)
        {
            printf("> %s\n", file_contents);
        }

        // close the file
        fclose(in_file);
        free(file_contents);
        exit(EXIT_SUCCESS);
    }

    return 0;
}