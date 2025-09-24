#ifndef STUDENTFUNCTIONS_H
#define STUDENTFUNCTIONS_H

#include <stdbool.h>

typedef struct Student {
    char fullName[50];
    int age;
    double gpa;
    char program[50];  
} Student;

extern int maxNameLen;

void InputStudentInfo(Student **studentsInput, int studentsNum);
void outputStudent(Student **studentsInput, int studentsNum);
void sortByGpa(Student **studentsInput, int studentsNum, int order);
void sortByAge(Student **studentsInput, int studentsNum, int order);
void SortingOptions(Student **studentsInput, int studentsNum);
int GetStrLen(char *str);
bool ifYes(char c);
void AlphabeticalSorting(Student **studentsInput, int studentsNum, int order);
void StrCpy(char *dest, const char *src);
int StrCmp(const char *a, const char *b);

#endif
