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
|0x1000|x|10|
|0x1001|*px|0x1000|
|0x1002|||
|0x1003|||


(You can write ```*x``` but using the ```p``` is good notation for indicating pointers)

A good real life example of pointers is: Imagine your house was just robbed by someone you know and instead of going to the cops and telling them who robbed you, you tell them where the robber lives (the address).

### You need pointers when you want:

1) Direct memory access
2) Dynamic memory management
3) Efficient passing of large data to functions
4) Linked or dynamic data structures

## How pointers are used to store the values of the student object in the struct:

In order to store the information the program uses ```malloc()``` which is short for "Memory Allocation". To understand how memory is being allocated you need to know what is a **stack** and a **heap**.

## What is Stack and Heap?

### Stack

- **What it is:** The stack is for static (fixed) allocation.

- **How it works:** When you call a function, the system knows exactly how much space to reserve for its local variables.
That memory is allocated at compile time (or determined at runtime in a fixed way) and automatically released when the function ends.

- **You cannot change the size of stack memory once it’s allocated for a variable.**

- **What goes there:**

    - Local variables (like ```char borger[10] = "big borger";```)

    - Function call information (who called who, return addresses, etc.)

- **Managed by:** The system, automatically.

- **Size:** Limited (usually a few MB).

- **Example:**
```c
void borger() {
    char borger[6] = "borger";  // 'borger' is on the stack
}

```
When ```borger()``` ends, ```borger``` disappears automatically.

### Heap

- The heap is for **dynamic (flexible) allocation.**

- You request memory **at runtime**, when the program is already running, and you can choose the size.

- The memory lives until you **free it manually**.

- Much more flexible than the stack, but slower and requires care.

- **What goes there:**

    - Dynamically allocated memory (malloc, calloc, new in C/C++).

    - Large data structures that you need to keep around.

- **Managed by:** The programmer (in C/C++). If you forget to free it, you get a memory leak.

- **Size:** Much larger than the stack.

Example:
```c
Student** studentsInput = (Student**)malloc(sizeof(Student)); // stored in heap
```
This memory stays until you explicitly free(studentsInput).

####  What is ```malloc()```? What does it do?

```malloc()``` is a function in C that dynamically allocates a specified amount of bytes in memory.
In this program ```malloc()``` allocates each student 112 bytes + padding which is ~120 bytes of memory. The padding comes from the ```sizeof``` function. It gets the size of a variable in bytes.
```c
typedef struct Student {
    char fullName[50]; // 50 bytes
    int age; //4 bytes
    double gpa; // 8 bytes
    char program[50]; //50 bytes
} Student; // Total per student: 112 bytes + 8 (padding from sizeof() function)
```
### What happens normally (without malloc)

If you write:
```
Student studentsInput;
```

The compiler reserves memory for ```s``` at compile time (before the program runs).

That memory is usually on the **stack**, and it disappears when the function ends.

### What happens with malloc?

If you write:
```c
Student** studentsInput = (Student**)malloc(sizeof(Student));
free(studentsInput); // You always have to free the allocated memory manually with this
```
The compiler does not reserve space ahead of time. Instead, while the program is running, it asks the operating system for a block of memory big enough to hold one Student. That memory comes from the **heap** (a large pool of memory managed while your program runs). You get a pointer (s) that tells you where that memory lives.

**This is used in the code to dynamically allocate memory for each student:**

```c
Student** studentsInput = (Student**) malloc(studentsNum * sizeof(Student*));
if (studentsInput == NULL) {
    printf("Memory Allocation failed!\n");
    return 1;
}
free(studentsInput);
```

In human language this means "Give me enough memory for studentsNum slots, where each slot can hold the address of a Student. Let studentsInput point to the first student pointer.".

### Diagram
```c
studentsInput (array of pointers) on heap
     │
     ▼
+--------------------------+--------------------------+--------------------------+
|   student object 0       |   student object 1       |   student object 2       |
|  ──────────────────►     |   (empty)                |   (empty)                |
+--------------------------+--------------------------+--------------------------+
      |
      ▼
+-------------------------------+
|   struct Student (data here)  | // This happens for each student object 
|  name, age, gpa, program...   | // This is the heap holding data of each student object.
|         120 bytes             | // Each student is on the heap but seperately allocated.
+-------------------------------+ 
```

## How to use the Variables of the data struct in Functions

```c
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
```

This is the function to sort the students by age using the **Bubble Sort algorithm**.

***(This guide will not go into explaining algorithms but the next guide will)***

In order to access the contents of the data structure you first have to put ```Students** StudentsInput``` in the parameters of the function.

After that you can use the variables that are inside of the data struct by using ```->``` symbol like this: ```studentsInput[j]->age```

**But this method works only in this scenario.**

If you do void ```sortByAge(Student* studentsInput, int studentsNum, int order)``` (If you pass ```Student*``` instead of ```Student**```) 

To use the variables of the struct you would have to write
```c
studentsInput[j].age
```

- Use ```.``` when you have the struct directly.

- Use ```->``` when you have a pointer to a struct.

- You can pass ```Student*``` or ```Student**``` into functions depending on whether you’re modifying a single student or the entire array of students.

- Struct variables behave like normal variables inside functions — you just need to use the right access operator.
