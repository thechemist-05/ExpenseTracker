#ifndef EXPENSE_TRACKER_H
#define EXPENSE_TRACKER_H

#define MAX_EXPENSES 100

typedef struct {
    float amount;
    char category[50];
    char description[100];
    char date[11]; // Format: YYYY-MM-DD
} Expense;

// Function Prototypes
void add_expense();
void view_expenses();
void edit_expense();
void delete_expense();
void generate_report();
void save_expenses_to_file();
void load_expenses_from_file();

#endif // EXPENSE_TRACKER_H
