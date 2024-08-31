#include "hashTask.hpp"
using namespace std;  
#include <cwchar>  
#include <csignal> 
void resetColor() {
    cout << "\033[0m" << flush;
}

// Signal handler for SIGINT (Ctrl + C)
void signalHandler(int signum) {
    resetColor();
    exit(signum); // Exit the program gracefully
}
void menu()
{
    cout << "================MENU==============" << endl;
    cout << "1. Add a task" << endl;
    cout << "2. Remove a task" << endl;
    cout << "3. Update Task Name" << endl;
    cout << "4. Update Task completion" << endl;
    cout << "5. Update Task Priority" << endl;
    cout << "6. Print By Priority " << endl;
    cout << "7. Print all tasks" << endl;
    cout << "8. Exit" << endl;
}
void PriorityMenu()
{
    cout << "Enter the priority of the task: " << endl;
    cout << "1. Low" << endl;
    cout << "2. Medium" << endl;
    cout << "3. High" << endl;
} 

int main()
{
    atexit(resetColor);
    SetConsoleOutputCP(CP_UTF8);
    signal(SIGINT, signalHandler);

    HashTask todo;
    int choice;
    string taskName;
    char isCompleted;
    int taskPriority;
    string newTaskName;
    do {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter the task name: ";
            getline(cin, taskName);
            PriorityMenu();
            cin >> taskPriority;
            todo.insert(Task(taskName, taskPriority));
            break;
        case 2:
            cout << "Enter the task name to remove: ";
            getline(cin, taskName);
            todo.remove(taskName);
            break;
        case 3:
            cout << "Enter existing task name you want to change: ";
            getline(cin, taskName);
            cout << "Enter new task name: ";
            getline(cin, newTaskName);
            todo.updateTaskName(taskName, newTaskName);
            break;
        case 4:
            cout << "Enter the task name to update completion: ";
            getline(cin, taskName);
            cout << "Completed? (Y/N): ";
            cin >> isCompleted;
            isCompleted = (isCompleted == 'Y' || isCompleted == 'y') ? 1 : 0;
            todo.UpdateCompleted(taskName, isCompleted);
            break;
        case 5:
            cout << "Enter the task name to update completion: ";
            getline(cin, taskName);
            PriorityMenu();
            cin >> taskPriority;
            todo.updatePriorty(taskName, taskPriority);
            break;
        case 6:
            cout << "What Priority are you looking for 1 to 3" << endl;
            cin >> taskPriority;
            todo.printPriority (taskPriority);
            break;
        case 7:
            todo.print();
            break;
        case 8:
            todo.printCompleted();
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 8);
    cout << "\033[0m" << flush;
    return 0;
}