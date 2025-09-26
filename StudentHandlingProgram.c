#include <stdio.h>
#include <stdlib.h>
#include "studentfunctions.h"

int main() {
    int studentsNum;
    char choice;



    printf("Enter number of students: ");
    scanf("%d", &studentsNum);

    Student** studentsInput = (Student**) malloc(studentsNum * sizeof(Student*));
    if (studentsInput == NULL) {
        printf("Memory Allocation failed!\n");
        return 1;
    }

    InputStudentInfo(studentsInput, studentsNum);

    printf("Do you want to sort the students in the table in any way? [Y/N]: ");
    scanf(" %c", &choice);
    if (ifYes(choice)) {
        SortingOptions(studentsInput, studentsNum);
    }

    outputStudent(studentsInput, studentsNum);

    for (int i = 0; i < studentsNum; i++) {
        free(studentsInput[i]);
    }
    free(studentsInput);

    return 0;
}

