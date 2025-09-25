# Beginner-Friendly Student Management Program Written in C
This is a project in C meant for beginners. It will include a beginner-friendly guide and description for data structure, memory allocation, pointers and etc.

## What does this program do?

The program takes information of students and outputs the information of the students is the for of the table.

#### Example inputs:

```
Enter number of students: 3

Enter students info:

Student 1:
Full name: Amogus Michael
Age: 18
GPA: 0.34
Program: CPA

Student 2:
Full name: John Pork
Age: 20
GPA: 3.8
Program: CPP

Student 3:
Full name: Ivan Dorm
Age: 17
GPA: 2.67
Program: ART
Do you want to sort the students in the table in any way? [Y/N]: Y
How do you want to sort the Table?
 1. Age
 2. GPA
 3. Name Alphabetically
Enter choice: 2
Choose sorting order (1 = ascending, 2 = descending): 2

Students sorted by GPA.

Data successfully written to output.txt
```
#### Example output:

```
--------------Student Info--------------
Full Name      AGE PROGRAM GPA 
-------------- --- ------- ----
John Pork      20  CPP     3.80
Ivan Dorm      17  ART     2.67
Amogus Michael 18  CPA     0.34
```

## How does this program work?

The program has a data structure that contains the Student objects that hold information of the student like Full name, Age, GPA and Program.

```c
typedef struct Student {
    char fullName[50];
    int age;
    double gpa;
    char program[50];  
} Student;
```
A struct is a way of grouping related variables to each other. Unlike an array also known as list a struct can hold data of different data types like int, char, double, float and it can even hold other structs.

To understand how this data structure is used in this program you need to know what a pointer is.

## What is a pointer?

The syntax for a pointer is the ```*``` sign. A simple example of a pointer would be:  

```c
int x = 10;
int *px = &x;
```
```ìnt x = 10``` means that the variable ```x``` is equal to 10.
```ìnt *px = &x``` means that the pointer ```*px``` is equal to the memory address of ```x```. You can use a table to visualise this.

| Memory Address | Variable | Value|
|----------------|-------|---------|
|0x1000|x|10
|0x1001|*px|0x1000
|0x1002|
|0x1003|


(You can write ```*x``` but using the ```p``` is good notation for indicating pointers)

A good real life example of pointers is: Imagine your house was just robbed by someone you know and instead of going to the cops and telling them who robbed you, you tell them where the robber lives (the address).

### You need pointers when you want:

1) Direct memory access
2) Dynamic memory management
3) Efficient passing of large data to functions
4) Linked or dynamic data structures

## How pointers are used to store the values of the student object in the struct:

In order to store the information the program uses ```malloc().``` which is short for "Memory Allocation".

```c
Student** studentsInput = (Student**) malloc(studentsNum * sizeof(Student*));
if (studentsInput == NULL) {
    printf("Memory Allocation failed!\n");
    return 1;
}
free(studentsInput);
```
What is ```malloc().```? What does it do?

The first line basically means "Give me enough memory for studentsNum Student structs, and let studentsInput point to the first one."

1) ``` Student** studentsInput ``` - this is a pointer to a pointer.


