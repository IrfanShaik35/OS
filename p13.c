#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee.dat"

typedef struct {
    int id;
    char name[30];
    int age;
    float salary;
} Employee;
void addEmployee(FILE *file) {
    Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee age: ");
    scanf("%d", &emp.age);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fseek(file, 0, SEEK_END);
    fwrite(&emp, sizeof(Employee), 1, file);
    printf("Employee added successfully.\n");
}
void viewEmployee(FILE *file) {
    Employee emp;
    int id;
    printf("Enter employee ID to view: ");
    scanf("%d", &id);

    fseek(file, 0, SEEK_SET);
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            printf("ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Age: %d\n", emp.age);
            printf("Salary: %.2f\n", emp.salary);
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}
void updateEmployee(FILE *file) {
    Employee emp;
    int id;
    printf("Enter employee ID to update: ");
    scanf("%d", &id);

    fseek(file, 0, SEEK_SET);
    long pos;
    while ((pos = ftell(file)) && fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            printf("Enter new employee name: ");
            scanf("%s", emp.name);
            printf("Enter new employee age: ");
            scanf("%d", &emp.age);
            printf("Enter new employee salary: ");
            scanf("%f", &emp.salary);

            fseek(file, pos - sizeof(Employee), SEEK_SET);
            fwrite(&emp, sizeof(Employee), 1, file);
            printf("Employee updated successfully.\n");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}
void deleteEmployee(FILE *file) {
    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        printf("Unable to open temporary file.\n");
        return;
    }

    Employee emp;
    int id;
    printf("Enter employee ID to delete: ");
    scanf("%d", &id);

    fseek(file, 0, SEEK_SET);
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id != id) {
            fwrite(&emp, sizeof(Employee), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(FILENAME);
    rename("temp.dat", FILENAME);

    file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("Unable to reopen the file.\n");
        return;
    }

    printf("Employee deleted successfully.\n");
}
int main() {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        file = fopen(FILENAME, "wb+");
        if (!file) {
            printf("Unable to open file.\n");
            return 1;
        }
    }

    int choice;
    do {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. View Employee\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                viewEmployee(file);
                break;
            case 3:
                updateEmployee(file);
                break;
            case 4:
                deleteEmployee(file);
                break;
            case 5:
                fclose(file);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}
