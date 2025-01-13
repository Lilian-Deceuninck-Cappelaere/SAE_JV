#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>



int main(int argc, char *argv[])
{
    char language[1], filename[20];

    printf("Choisir la langue (fr) / Select language (en) : ");
    scanf("%s", language);

    if (language == "fr")
    {
        printf("Jeux en français\n");
    }

    else if (language == "en")
    {
        printf("Game in EN\n");
    }

    snprintf(filename, sizeof(filename), "intro_%s.txt", language);
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
    exit(EXIT_SUCCESS);

    return 0;
}