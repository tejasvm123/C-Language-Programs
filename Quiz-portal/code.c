#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 50
#define MAX_CHOICES 4
#define MAX_LINE_LENGTH 256
#define QUESTION_FILE "questions.txt"
#define SCORE_FILE "scores.txt"

typedef struct {
    char question[MAX_LINE_LENGTH];
    char choices[MAX_CHOICES][MAX_LINE_LENGTH];
    int correct_choice;
} Question;

typedef struct {
    char name[50];
    int score;
} Score;


int readQuestions(Question *questions) {
    FILE *file = fopen(QUESTION_FILE, "r");
    if (!file) {
        printf("Error: Could not open %s\n", QUESTION_FILE);
        return 0;
    }
    int count = 0;
    char temp[MAX_LINE_LENGTH];
    while (fgets(temp, MAX_LINE_LENGTH, file) && count < MAX_QUESTIONS) {
        
        strcpy(questions[count].question, temp);
        for (int i = 0; i < MAX_CHOICES; i++) {
            if (fgets(questions[count].choices[i], MAX_LINE_LENGTH, file) == NULL) {
                fclose(file);
                return count;
            }
            questions[count].choices[i][strcspn(questions[count].choices[i], "\n")] = 0; // Remove \n
        }
        
        if (fgets(temp, MAX_LINE_LENGTH, file) == NULL) {
            fclose(file);
            return count;
        }
        questions[count].correct_choice = atoi(temp);
        count++;
        fgets(temp, MAX_LINE_LENGTH, file);
    }
    fclose(file);
    return count;
}

void saveScore(const char* name, int score) {
    FILE *file = fopen(SCORE_FILE, "a");
    if (file) {
        fprintf(file, "%s %d\n", name, score);
        fclose(file);
    }
}

void displayHighScores() {
    FILE *file = fopen(SCORE_FILE, "r");
    if (!file) {
        printf("No scores available.\n");
        return;
    }
    printf("\n---- High Scores ----\n");
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    printf("---------------------\n");
    fclose(file);
}

void shuffle(int *array, int n) {
    srand(time(NULL));
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main() {
    Question questions[MAX_QUESTIONS];
    int question_count = readQuestions(questions);
    if (question_count == 0) {
        printf("No questions loaded.\n");
        return 1;
    }

    char user[50];
    printf("Enter your name: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;

    int indices[MAX_QUESTIONS];
    for (int i = 0; i < question_count; i++) {
        indices[i] = i;
    }
    shuffle(indices, question_count);

    int score = 0;
    for (int i = 0; i < question_count; i++) {
        int qidx = indices[i];
        printf("\nQ%d: %s", i+1, questions[qidx].question);
        for (int c = 0; c < MAX_CHOICES; c++) {
            printf("%c) %s\n", 'A' + c, questions[qidx].choices[c]);
        }
        printf("Your answer (A-D): ");
        char ans;
        scanf(" %c", &ans);
        int user_choice = ans - 'A' + 1;
        if (user_choice == questions[qidx].correct_choice) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong! Correct answer is %c\n", 'A' + questions[qidx].correct_choice - 1);
        }
    }
    printf("\nQuiz complete! Your score: %d/%d\n", score, question_count);

    saveScore(user, score);
    displayHighScores();

    return 0;
}