#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Windows-friendly ANSI colors
#define RESET   "\x1b[0m"
#define RED     "\x1b[1;31m"
#define GREEN   "\x1b[1;32m"
#define YELLOW  "\x1b[1;33m"
#define BLUE    "\x1b[1;34m"
#define MAGENTA "\x1b[1;35m"
#define CYAN    "\x1b[1;36m"
#define BOLD    "\x1b[1m"

typedef struct {
    int id;
    char name[50];
    char role[50];
    float salary;
    int attendance;
} Employee;

Employee employees[MAX];
int count = 0;
const char *filename = "employees.dat";

// *************** FILE HANDLING ****************
void saveData() {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf(RED "Error saving data!\n" RESET);
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(employees, sizeof(Employee), count, fp);
    fclose(fp);
}

void loadData() {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        count = 0;
        return;
    }
    fread(&count, sizeof(int), 1, fp);
    fread(employees, sizeof(Employee), count, fp);
    fclose(fp);
}

// *************** ADD EMPLOYEE ****************
void addEmployee() {
    printf(CYAN "\n--- Add Employee ---\n" RESET);

    printf(YELLOW "Enter Employee ID: " RESET);
    scanf("%d", &employees[count].id);

    printf(YELLOW "Enter Name: " RESET);
    scanf(" %[^\n]", employees[count].name);

    printf(YELLOW "Enter Role: " RESET);
    scanf(" %[^\n]", employees[count].role);

    printf(YELLOW "Enter Salary/Day: " RESET);
    scanf("%f", &employees[count].salary);

    employees[count].attendance = 0;
    count++;

    saveData(); // save after adding
    printf(GREEN "Employee Added Successfully!\n" RESET);
}

// *************** VIEW EMPLOYEES ****************
void viewEmployees() {
    printf(CYAN "\n--- Employee List ---\n" RESET);

    if (count == 0) {
        printf(RED "No employee found.\n" RESET);
        return;
    }

    for (int i = 0; i < count; i++) {
        printf(BLUE "ID: %d " RESET, employees[i].id);
        printf(MAGENTA "| Name: %s " RESET, employees[i].name);
        printf(CYAN "| Role: %s " RESET, employees[i].role);
        printf(YELLOW "| Salary: %.2f " RESET, employees[i].salary);
        printf(GREEN "| Attendance: %d" RESET, employees[i].attendance);
        printf("\n");
    }
}

// *************** UPDATE EMPLOYEE ****************
void updateEmployee() {
    int id, found = 0;
    printf(CYAN "\n--- Update Employee ---\n" RESET);
    printf(CYAN "Enter Employee ID to update: " RESET);
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            found = 1;

            printf(YELLOW "Enter new Name: " RESET);
            scanf(" %[^\n]", employees[i].name);

            printf(YELLOW "Enter new Salary: " RESET);
            scanf("%f", &employees[i].salary);

            printf(YELLOW "Enter new Role: " RESET);
            scanf(" %[^\n]", employees[i].role);

            saveData(); // save after updating
            printf(GREEN "Updated Successfully!\n" RESET);
            return;
        }
    }

    if (!found)
        printf(RED "Employee not found.\n" RESET);
}

// *************** DELETE EMPLOYEE ****************
void deleteEmployee() {
    int id, found = 0;

    printf(CYAN "Enter Employee ID to delete: " RESET);
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            found = 1;

            for (int j = i; j < count - 1; j++)
                employees[j] = employees[j + 1];

            count--;
            saveData(); // save after deletion
            printf(GREEN "Employee Deleted Successfully!\n" RESET);
            return;
        }
    }

    if (!found)
        printf(RED "Employee not found.\n" RESET);
}

// *************** MARK ATTENDANCE ****************
void markAttendance() {
    int id;

    printf(CYAN "Enter Employee ID to mark attendance: " RESET);
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            employees[i].attendance++;
            saveData(); // save after marking attendance
            printf(GREEN "Attendance Marked!\n" RESET);
            return;
        }
    }

    printf(RED "Employee not found.\n" RESET);
}

// *************** VIEW ATTENDANCE ****************
void viewAttendance() {
    printf(CYAN "\n--- Attendance Records ---\n" RESET);

    if (count == 0) {
        printf(RED "No employees found.\n" RESET);
        return;
    }

    for (int i = 0; i < count; i++) {
        printf(BLUE "ID: %d " RESET, employees[i].id);
        printf(MAGENTA "| Name: %s " RESET, employees[i].name);
        printf(GREEN "| Attendance: %d" RESET, employees[i].attendance);
        printf("\n");
    }
}

// *************** PAYROLL ****************
void calculatePayroll() {
    printf(CYAN "\n--- Payroll ---\n" RESET);

    for (int i = 0; i < count; i++) {
        float total = employees[i].salary * employees[i].attendance;

        printf(BLUE "ID: %d " RESET, employees[i].id);
        printf(MAGENTA "| Name: %s " RESET, employees[i].name);
        printf(GREEN "| Total Pay: %.2f" RESET, total);
        printf("\n");
    }
}

// *************** MENU ****************
void showMenu() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf(BOLD CYAN "======================================================\n" RESET);
    printf(BOLD YELLOW "                 EMPLOYEE MANAGER\n" RESET);
    printf(BOLD CYAN "======================================================\n\n" RESET);

    printf(CYAN   " [1] Add New Employee      " RESET CYAN "[2] View All Employees\n" RESET);
    printf(MAGENTA "------------------------------------------------------\n" RESET);

    printf(CYAN   " [3] Update Employee       " RESET CYAN "[4] Delete Employee\n" RESET);
    printf(MAGENTA "------------------------------------------------------\n" RESET);

    printf(CYAN   " [5] Mark Attendance       " RESET CYAN "[6] View Attendance\n" RESET);
    printf(MAGENTA "------------------------------------------------------\n" RESET);

    printf(CYAN   " [7] Calculate Payroll     " RESET CYAN "[8] Save & Exit\n" RESET);
    printf(BOLD CYAN "======================================================\n" RESET);

    printf(YELLOW "Enter your choice: " RESET);
}

// *************** MAIN ****************
int main() {
    loadData(); // Load data at startup

    int ch;
    while (1) {
        showMenu();
        scanf("%d", &ch);

        switch (ch) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: updateEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: markAttendance(); break;
            case 6: viewAttendance(); break;
            case 7: calculatePayroll(); break;
            case 8:
                printf(GREEN "Exiting Program...\n" RESET);
                exit(0);

            default:
                printf(RED "Invalid choice. Try again.\n" RESET);
        }

        printf(YELLOW "\nPress Enter to continue..." RESET);
        getchar();
        getchar();
    }

    return 0;
}
