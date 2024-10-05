#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100

// Define the structure for an expense
typedef struct {
    float amount;
    char category[50];
    char description[100];
    char date[11]; // Format: YYYY-MM-DD
} Expense;

Expense expenses[MAX_EXPENSES];
int expense_count = 0; // Keep track of the number of expenses

// Function Prototypes
void add_expense();
void view_expenses();
void edit_expense();
void delete_expense();
void generate_report();
void save_expenses_to_file();
void load_expenses_from_file();
void menu();

void add_expense() {
    // Logic to add an expense
    if (expense_count < MAX_EXPENSES) {
        printf("Enter amount: ");
        scanf("%f", &expenses[expense_count].amount);
        printf("Enter category: ");
        scanf("%s", expenses[expense_count].category);
        printf("Enter description: ");
        scanf("%s", expenses[expense_count].description);
        printf("Enter date (YYYY-MM-DD): ");
        scanf("%s", expenses[expense_count].date);
        expense_count++;
        printf("Expense added successfully!\n");
    } else {
        printf("Expense limit reached!\n");
    }
}

void view_expenses() {
    // Logic to view all expenses
    printf("\nExpenses:\n");
    for (int i = 0; i < expense_count; i++) {
        printf("%d. Amount: %.2f | Category: %s | Description: %s | Date: %s\n", 
               i + 1, 
               expenses[i].amount, 
               expenses[i].category, 
               expenses[i].description, 
               expenses[i].date);
    }
}

void edit_expense() {
    int index;
    view_expenses(); // Display expenses to select one for editing
    printf("Enter the number of the expense you want to edit: ");
    scanf("%d", &index);
    
    // Validate index
    if (index < 1 || index > expense_count) {
        printf("Invalid selection!\n");
        return;
    }

    index--; // Convert to 0-based index
    printf("Editing Expense %d:\n", index + 1);
    printf("Current Amount: %.2f\n", expenses[index].amount);
    printf("Enter new amount (or press enter to keep current): ");
    char buffer[50];
    fgets(buffer, sizeof(buffer), stdin); // Clear newline from previous input
    if (strlen(buffer) > 1) { // Only update if new value is provided
        sscanf(buffer, "%f", &expenses[index].amount);
    }
    printf("Current Category: %s\n", expenses[index].category);
    printf("Enter new category (or press enter to keep current): ");
    fgets(expenses[index].category, sizeof(expenses[index].category), stdin);
    expenses[index].category[strcspn(expenses[index].category, "\n")] = 0; // Remove newline

    printf("Current Description: %s\n", expenses[index].description);
    printf("Enter new description (or press enter to keep current): ");
    fgets(expenses[index].description, sizeof(expenses[index].description), stdin);
    expenses[index].description[strcspn(expenses[index].description, "\n")] = 0; // Remove newline

    printf("Current Date: %s\n", expenses[index].date);
    printf("Enter new date (or press enter to keep current): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (strlen(buffer) > 1) {
        sscanf(buffer, "%s", expenses[index].date);
    }

    printf("Expense edited successfully!\n");
}

void delete_expense() {
    int index;
    view_expenses(); // Display expenses to select one for deletion
    printf("Enter the number of the expense you want to delete: ");
    scanf("%d", &index);
    
    // Validate index
    if (index < 1 || index > expense_count) {
        printf("Invalid selection!\n");
        return;
    }

    index--; // Convert to 0-based index
    for (int i = index; i < expense_count - 1; i++) {
        expenses[i] = expenses[i + 1]; // Shift expenses left
    }
    expense_count--; // Reduce count
    printf("Expense deleted successfully!\n");
}

void generate_report() {
    float total_expense = 0.0;
    float category_totals[10] = {0}; // Assume 10 categories max
    const char* categories[10] = {"Food", "Transport", "Entertainment", "Utilities", "Health", "Education", "Miscellaneous"};
    
    for (int i = 0; i < expense_count; i++) {
        total_expense += expenses[i].amount;
        for (int j = 0; j < 10; j++) {
            if (strcmp(expenses[i].category, categories[j]) == 0) {
                category_totals[j] += expenses[i].amount;
                break;
            }
        }
    }

    printf("\nMonthly Expense Report:\n");
    printf("Total Expenses: %.2f\n", total_expense);
    for (int j = 0; j < 10; j++) {
        if (category_totals[j] > 0) {
            printf("Total in %s: %.2f\n", categories[j], category_totals[j]);
        }
    }
}

void save_expenses_to_file() {
    FILE *file = fopen("data/expenses.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    for (int i = 0; i < expense_count; i++) {
        fprintf(file, "%.2f,%s,%s,%s\n", expenses[i].amount, expenses[i].category, expenses[i].description, expenses[i].date);
    }
    fclose(file);
    printf("Expenses saved to file successfully!\n");
}

void load_expenses_from_file() {
    FILE *file = fopen("data/expenses.txt", "r");
    if (file == NULL) {
        printf("No previous expenses found.\n");
        return;
    }
    
    while (fscanf(file, "%f,%49[^,],%99[^,],%10s\n", 
           &expenses[expense_count].amount, 
           expenses[expense_count].category, 
           expenses[expense_count].description, 
           expenses[expense_count].date) != EOF) {
        expense_count++;
    }
    fclose(file);
    printf("Expenses loaded from file successfully!\n");
}

void menu() {
    int choice;
    load_expenses_from_file(); // Load expenses from file on startup
    do {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Edit Expense\n");
        printf("4. Delete Expense\n");
        printf("5. Generate Monthly Report\n");
        printf("6. Save Expenses to File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_expense(); break;
            case 2: view_expenses(); break;
            case 3: edit_expense(); break;
            case 4: delete_expense(); break;
            case 5: generate_report(); break;
            case 6: save_expenses_to_file(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}
