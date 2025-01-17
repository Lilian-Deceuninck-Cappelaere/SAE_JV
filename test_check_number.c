#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char input[100];
    int isValid;

    while (1) {
        printf("Please enter a number: ");
        fgets(input, sizeof(input), stdin);  // Read the input

        // Check if input contains only digits
        isValid = 1;
        for (int i = 0; i < strlen(input) - 1; i++) {  // Ignore the newline character
            if (!isdigit(input[i])) {
                isValid = 0;
                break;
            }
        }

        if (isValid) {
            printf("You entered: %s\n", input);
            break;
        } else {
            printf("Invalid input. Please enter a valid number.\n");
        }
    }

    return 0;
}
