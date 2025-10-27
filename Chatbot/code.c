#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 256
#define MAX_LINE 512
#define FAQ_FILE "faq.txt"


void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = (char)tolower(str[i]);
}

void trimNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

int searchFAQ(const char *input) {
    FILE *file = fopen(FAQ_FILE, "r");
    if (!file) {
        printf("FAQ file not found.\n");
        return 0;
    }

    char keyword[MAX_INPUT];
    char answer[MAX_LINE];
    char line[MAX_LINE];
    int foundAnswer = 0;

    while (fgets(keyword, sizeof(keyword), file)) {
        trimNewline(keyword);

        // Read answer line
        if (!fgets(answer, sizeof(answer), file))
            break;
        trimNewline(answer);

        // Skip blank line after block
        fgets(line, sizeof(line), file);

        if (strstr(input, keyword) != NULL) {
            printf("%s\n", answer);
            foundAnswer = 1;
            break;
        }
    }
    fclose(file);
    return foundAnswer;
}

void printSupportedQueries() {
    printf("This bot can answer queries about:\n");
    printf("- variable\n- constant\n- pointer\n- array\n- function\n");
    printf("- loop\n- struct\n- dynamic memory\n- header file\n");
    printf("- compile error\n- runtime error\n- exit\n\n");
}

int main() {
    char input[MAX_INPUT];
    printf("Welcome to the C FAQ Assistant! Type your query or 'exit' to quit.\n\n");
    printSupportedQueries();

    while (1) {
        printf("You: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        trimNewline(input);
        toLowerCase(input);

        if (strstr(input, "exit") != NULL) {
            printf("Goodbye!\n");
            break;
        }

        if (!searchFAQ(input)) {
            printf("Sorry, I don't understand. Please try another query.\n");
            printSupportedQueries();
        }
    }
    return 0;
}

