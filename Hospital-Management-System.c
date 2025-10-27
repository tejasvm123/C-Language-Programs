#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[100];
    struct Patient *next;
} Patient;

Patient *head = NULL;


Patient* createPatient(int id, char *name, int age, char *gender, char *disease) {
    Patient *new_patient = (Patient *)malloc(sizeof(Patient));
    new_patient->id = id;
    strcpy(new_patient->name, name);
    new_patient->age = age;
    strcpy(new_patient->gender, gender);
    strcpy(new_patient->disease, disease);
    new_patient->next = NULL;
    return new_patient;
}


void addPatient() {
    int id, age;
    char name[50], gender[10], disease[100];

    printf("Enter Patient ID: "); scanf("%d", &id);
    
    Patient *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Patient ID already exists!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Enter Name: "); scanf(" %[^\n]", name);
    printf("Enter Age: "); scanf("%d", &age);
    printf("Enter Gender: "); scanf(" %[^\n]", gender);
    printf("Enter Disease: "); scanf(" %[^\n]", disease);

    Patient *new_patient = createPatient(id, name, age, gender, disease);

    if (head == NULL) {
        head = new_patient;
    } else {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_patient;
    }
    printf("Patient added successfully.\n");
}
void displayPatients() {
    if (head == NULL) {
        printf("No patient records found.\n");
        return;
    }
    printf("\n--- Patient Records ---\n");
    printf("%-5s %-20s %-5s %-10s %-20s\n", "ID", "Name", "Age", "Gender", "Disease");
    Patient *temp = head;
    while (temp != NULL) {
        printf("%-5d %-20s %-5d %-10s %-20s\n", temp->id, temp->name, temp->age, temp->gender, temp->disease);
        temp = temp->next;
    }
}

void searchPatient() {
    if (head == NULL) {
        printf("No patient records found.\n");
        return;
    }
    int id; printf("Enter Patient ID to search: "); scanf("%d", &id);

    Patient *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Patient found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\n",
                   temp->id, temp->name, temp->age, temp->gender, temp->disease);
            return;
        }
        temp = temp->next;
    }
    printf("Patient with ID %d not found.\n", id);
}

void deletePatient() {
    if (head == NULL) {
        printf("No patient records found.\n");
        return;
    }
    int id; printf("Enter Patient ID to delete: "); scanf("%d", &id);

    Patient *temp = head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }
    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Patient record deleted successfully.\n");
}

void menu() {
    int choice;
    while (1) {
        printf("\nHospital Management System Menu:\n");
        printf("1. Add Patient\n");
        printf("2. Display All Patients\n");
        printf("3. Search Patient by ID\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");
        printf("Enter your choice: "); scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    printf("Welcome to the Hospital Management System\n");
    menu();
    return 0;
}