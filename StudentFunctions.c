#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "studentfunctions.h"

int maxNameLen = 0;

bool ifYes(char c) {
    return (c == 'Y' || c == 'y');
}

void SortingOptions(Student** studentsInput, int studentsNum) {
    int done = 0;
    int assOrDes;
    int sortingChoice;

    while (!done) {
        printf("How do you want to sort the Table?\n");
        printf(" 1. Age\n 2. GPA\n 3. Name Alphabetically\n");
        printf("Enter choice: ");
        scanf("%d", &sortingChoice);

        if (sortingChoice == 1) {
            printf("Choose sorting order (1 = ascending, 2 = descending): ");
            scanf("%d", &assOrDes);
            sortByAge(studentsInput, studentsNum, assOrDes);
            printf("\nStudents sorted by Age.\n");
            done = 1;
        }
        else if (sortingChoice == 2) {
            printf("Choose sorting order (1 = ascending, 2 = descending): ");
            scanf("%d", &assOrDes);
            sortByGpa(studentsInput, studentsNum, assOrDes);
            printf("\nStudents sorted by GPA.\n");
            done = 1;
        }
        else if (sortingChoice == 3) {
            printf("Choose sorting order (1 = A to Z, 2 = Z to A): ");
            scanf("%d", &assOrDes);
            AlphabeticalSorting(studentsInput, studentsNum, assOrDes);
            printf("\nStudents sorted Alphabetically.\n");
            done = 1;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }
}

void InputStudentInfo(Student** studentsInput, int studentsNum) {
    printf("\nEnter students info:\n");

    for (int i = 0; i < studentsNum; i++) {
        studentsInput[i] = (Student*) malloc(sizeof(Student));
        if (studentsInput[i] == NULL) {
            printf("Memory allocation failed for student %d!\n", i + 1);
            exit(1);
        }

        printf("\nStudent %d:\n", i + 1);
        printf("Full name: ");
        fscanf(stdin, " %[^\n]", studentsInput[i]->fullName);

        int nameLen = GetStrLen(studentsInput[i]->fullName);
        if (nameLen > maxNameLen) {
            maxNameLen = nameLen;
        }

        printf("Age: ");
        scanf("%d", &studentsInput[i]->age);
        getchar(); 

        printf("GPA: ");
        scanf("%lf", &studentsInput[i]->gpa);
        getchar();

        printf("Program: ");
        fscanf(stdin, " %[^\n]", studentsInput[i]->program);
    }
}

int GetStrLen(char *str) {
    int length = 0;
    while (str[length] != '\0') { 
        length++;
    }
    return length;
}

void outputStudent(Student** studentsInput, int studentsNum) {
    FILE *pFile = fopen("output.txt", "w");
    if (pFile == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    fprintf(pFile, "--------------Student Info--------------\n");
    fprintf(pFile, "%-*s %-3s %-7s %-4s\n", maxNameLen, "Full Name", "AGE", "PROGRAM", "GPA");

    for (int i = 0; i < maxNameLen; i++) fprintf(pFile, "-");
    fprintf(pFile, " --- ------- ----\n");

    for (int i = 0; i < studentsNum; i++) {
        fprintf(pFile, "%-*s %-3d %-7s %.2lf\n",
                maxNameLen,
                studentsInput[i]->fullName,
                studentsInput[i]->age,
                studentsInput[i]->program,
                studentsInput[i]->gpa);
    }

    fclose(pFile);
    printf("\nData successfully written to output.txt\n");
}

void sortByGpa(Student** studentsInput, int studentsNum, int order) {
    int i, j;
    bool swapped;

    for (i = 0; i < studentsNum; i++) {
        swapped = false;
        for (j = 0; j < studentsNum - i - 1; j++) {
            if ((order == 1 && studentsInput[j]->gpa > studentsInput[j + 1]->gpa) ||
                (order == 2 && studentsInput[j]->gpa < studentsInput[j + 1]->gpa)) {
                Student* temp = studentsInput[j];
                studentsInput[j] = studentsInput[j + 1];
                studentsInput[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void sortByAge(Student** studentsInput, int studentsNum, int order) {
    int i, j;
    bool swapped;

    for (i = 0; i < studentsNum; i++) {
        swapped = false;
        for (j = 0; j < studentsNum - i - 1; j++) {
            if ((order == 1 && studentsInput[j]->age > studentsInput[j + 1]->age) ||
                (order == 2 && studentsInput[j]->age < studentsInput[j + 1]->age)) {
                Student* temp = studentsInput[j];
                studentsInput[j] = studentsInput[j + 1];
                studentsInput[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void AlphabeticalSorting(Student** studentsInput, int studentsNum, int order) {
    int i, j;
    bool swapped;

    for (i = 0; i < studentsNum; i++) {
        swapped = false;
        for (j = 0; j < studentsNum - i - 1; j++) {
            if ((order == 1 && StrCmp(studentsInput[j]->fullName, studentsInput[j + 1]->fullName) > 0) ||
                (order == 2 && StrCmp(studentsInput[j]->fullName, studentsInput[j + 1]->fullName) < 0)) {
                Student* temp = studentsInput[j];
                studentsInput[j] = studentsInput[j + 1];
                studentsInput[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int StrCmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return *(unsigned char*)a - *(unsigned char*)b;
}

void StrCpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}
