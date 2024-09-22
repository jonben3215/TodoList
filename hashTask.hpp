#ifndef HASH_TASK_HPP
#define HASH_TASK_HPP

#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include <fstream>
#include <thread>
#include <windows.h>
#include <ctime>
#include <unistd.h>  // Include the unistd.h header for the sleep function
using namespace std; // Use the std namespace

#define HT 40

struct Task
{
    string name;
    bool completed;
    int priority; // The higher the number, the higher the priority

    Task(string taskName = "", bool isCompleted = false, int taskPriority = 1)
        : name(taskName), completed(isCompleted), priority(taskPriority) {}

    bool isEmpty() const
    {
        return name.empty();
    }
};

class HashTask
{
public:
    HashTask() : tableSize(HT), numberOfItems(0), numcompleted(0) // Initialize members
    {
        table.resize(tableSize);
    }

    vector<list<Task>> &doubleSpace(vector<list<Task>>& table)
    {
        if(tableSize == HT)
        {   
            tableSize *= 2;
            table.resize(tableSize);
        }
        
        return table;
    }

    int hashFunction(const string &name) const
    {
        int sum = 0;
        for (char ch : name)
            sum += ch;

        return sum % tableSize;
    }
    string toLower(string name)
    {
        string lowerName = "";
        for (int i = 0; i < name.length(); i++)
            lowerName += tolower(name[i]);

        return lowerName;
    }
    
    Task*search(string name)
    {
        string looking = toLower(name);
        for(int i =0; i < tableSize; i++)
        {
            for(auto &it : table[i])
            {
                string inside = toLower(it.name);

                if(inside  == looking)
                    return &it;
            }
        }
        return NULL;
    }

    void insert(const Task &t) 
    {
        int index = hashFunction(t.name);
        if(tableSize == HT)
        {
            cout << "Resizing..." << endl;
            doubleSpace(table);
            sleep(5);
            cout << "SUCCESSFULLY RESIZED TODO LIST TO: " << tableSize << endl;
        }
        for (const auto &task : table[index])
        {
            if (task.name == t.name)
            {
                cout << "\u26A0 " << " \033[31mTask Already Exist.\033[0m" << endl;
                return;
            }
        }
        table[index].push_back(t);
        cout << "\033[32m TASK: " << t.name << " ADDED SUCCESSFULLY.\033[0m" << endl;
        numberOfItems++;
    }

    //Re-factored
    void UpdateCompleted(string name, bool completed = true)
    {
        Task *foundTask = search(name); // Use search to find the task
        if (foundTask == NULL) {
            cout << "\u26D4 \033[31mTASK NOT FOUND.\033[0m" << endl;
            return;
        }   
        else{
            foundTask->completed = completed;
            cout << "\033[32mTASK: " << foundTask->name << " COMPLETED SUCCESSFULLY.\033[0m" << endl;
        }
    }

    void updatePriorty(string name, int priority)
    {
       Task * foundTask = search(name);
       if(foundTask == NULL)
       {
            cout << "\u26D4 \033[31mTASK NOT FOUND.\033[0m" << endl;
            return;
       }
       
       foundTask -> priority = priority;
       cout << "\033[32mTASK: " << foundTask->name << " PRIORITY CHANGED TO " << foundTask -> priority << "\033[0m" << endl;
    }

    void remove(const string &name)
    {
        int index = hashFunction(name);
        auto &items = table[index];
        bool found = false;
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if (it->name == name)
            {
                items.erase(it);
                found = true;
                numberOfItems--;
                cout << "\033[31mTASK" << it->name << " REMOVED SUCCESSFULLY!\033[0m" <<endl;
                return; 
            }
        }

        if (!found)
            cout << "\u26D4" << "\033[31mTASK NOT FOUND.\033[0m" << endl;
    }
    void updateTaskName(string taskName, string changeName)
    {
        Task * foundTask = search(taskName);
        if(foundTask == NULL)
        {
            cout << "\u26D4 \033[31mTASK NOT FOUND.\033[0m" << endl;
            return;
        }
        foundTask -> name = changeName;
        cout << "\033[32mTASK: " << taskName << " HAS BEEN CHANGED TO " << changeName << "\033[0m" << endl;
    }

    void print()
    {
        for (int i = 0; i < tableSize; i++)
        {
            for (const auto &t : table[i])
            {
                if (t.name != "" && t.completed == false)
                {
                    cout << "\033[31m" << t.name << " (PR:" << t.priority << ")" << "\033[0m" << endl;
                }
                else if (t.name != "" && t.completed == true)
                {
                    cout << "\033[32m" << t.name << " (PR:" << t.priority << ")" << "\033[0m" << endl;
                }
            }
        }
    }

    void printPriority(int priority)
    {
        if (numberOfItems == 0)
            cout << "\u26D4 \033[31m TODO LIST IS EMPTY \033[0m" << endl;

        bool found = false;
        cout << "\033[32mLIST OF TASK WITH LEVEL " << priority << " PRIORITY:\033[0m" << endl;
        for (int i = 0; i < tableSize; i++)
        {

            for (const auto &t : table[i])
            {
                found = false;
                if (t.priority == priority)
                {

                    cout << "\033[32m" << t.name << "\033[0m" << endl;
                    found = true;
                }
            }
        }

        if (!found)
            cout << "\u26D4 \033[31m TASK(S) WITH PRIORITY " << priority << " NOT FOUND\033[0m" << endl;
    }

    void printCompleted()
    {
        ofstream file("TodoListCompletion.txt", ios::app);
        numcompleted = 0; // Reset the completed count before calculation
        for (int i = 0; i < tableSize; i++)
            for (const auto &t : table[i])
                if (t.completed)
                    numcompleted++;

        if (numberOfItems == 0)
        {
            cout << "Number of completed tasks: " << 0 << endl;
            cout << "Number of uncompleted tasks: " << 0 << endl;
            cout << "Completion rate: 0%" << endl;
            return;
        }
        auto percentage = (static_cast<double>(numcompleted) / numberOfItems) * 100;
        cout << "Number of completed tasks: " << numcompleted << endl;
        cout << "Number of uncompleted tasks: " << numberOfItems - numcompleted << endl;
        cout << "Completion rate: " << percentage << "%" << endl;

        cout << "Writing to file..." << endl;

        time_t now = time(nullptr);
        tm *ltm = localtime(&now);

        file << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday << "/"
             << (ltm->tm_mon + 1 < 10 ? "0" : "") << ltm->tm_mon + 1 << "/"
             << 1900 + ltm->tm_year << " - "
             << "Completion rate: " << percentage << "%" << endl;
    }

private:
    vector<list<Task>> table; // Use list to handle chaining (collisions)
    int tableSize;
    int numberOfItems;
    int numcompleted;
};

#endif // HASH_TASK_HPP
