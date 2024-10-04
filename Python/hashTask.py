from os import system, name
from time import sleep

# Description: This is a hash table implementation of a task list
class LL:
    def __init__(self, key, value):
        self. key = key
        self.value = value
        self.next = None

class Todo:
    #Constructor
    
    def __init__ (self):
        self.capacity = 40   
        self.num_tasks = 0
        self.table = [None] * self.capacity
        
    def _hash(self, task):
        return hash(task.lower()) % self.capacity
    
    def search(self, task):
        index = self._hash(task)
        curr = self.table[index]
        while curr != None:
            if curr.key.lower() == task.lower():
                return curr
            curr = curr.next
        return None
    
    def doubleCapacity(self):
        oldTable = self.table
        self.capacity = self.capacity * 2
        self.task = [None] * self.capacity

        for head in oldTable:
            curr = head
            while curr is not None:
                self.insert(curr.task, curr.value)
                curr = curr.next

    def insert(self, task, proirity):
        if self.search(task) is not None:
            print(f"\033[1;31;40mTASK: {task.upper()} -- ALREADY EXISTS \033[0m")
            sleep(2)
            return
        
        if self.num_tasks >= self.capacity:
            self.doubleCapacity()

        index = self._hash(task)
        new_task_node = LL(task, proirity)
        
        if self.table[index] is None:
            self.table[index] = new_task_node  # No collision, add the node
            self.num_tasks += 1
            print(f"\033[1;32;40m TASK {task.upper()} -- ADDED SUCCESSFULLY. \033[0m")
            sleep(2)
            

        else:
            # Collision: Add the node to the end of the list
            curr = self.table[index]
            while curr.next is not None:
                curr = curr.next
            curr.next = new_task_node  # Add the new node at the end
            self.num_tasks += 1
            print(f"\033[1;32;40m TASK {curr.key.upper} -- ADDED SUCCESSFULLY. \033[0m")
            sleep(2)
    
    def delete(self, task):
        indx = self._hash(task)
        curr = self.table[indx]
        prev = None
        
        while curr:
            if curr.key.lower() == task.lower():
                if prev:
                    prev.next = curr.next  # Bypass the current node
                else:
                    self.table[indx] = curr.next  # If deleting the head, update the table entry
                print(f"\033[1;32;40m TASK: {curr.key.upper()}-- DELETED SUCCESSFULLY. \033[0m")
                sleep(2)
                return
            prev = curr
            curr = curr.next
    
        print("\033[1;31;40m TASK NOT FOUND. PLEASE TRY AGAIN. \033[0m")
        sleep(2)
    
    def display(self):
        for i in range(self.capacity):
            if self.table[i] is not None:
                curr = self.table[i]
                while curr is not None:
                    print(f"\033[1;32;40m ({curr.key}, Priority: {curr.value})", end=" -> \033[0m")
                    curr = curr.next
                print("\033[1;32;40m None \033[0m")  # To mark the end of the chain

def menu():
    print("1. Add Task")
    print("2. Delete Task")
    print("3. Display Task")
    print("4. Exit")
    print("Enter your choice: ")
    choice = int(input())
    return choice

def priority():
    print("1. Low")
    print("2. Medium")
    print("3. High")
    print("Enter your choice: ")
    choice = int(input())
    return choice

def clear():
    if name == "nt":
        _ = system("cls")
    else:
        _ = system("clear")



if __name__ == "__main__":
    todo = Todo()
    try:
        while True:
            choice = menu()
            if choice == 1:
                task = input("Enter task: ")
                print("Enter priority: ")
                prio = priority()
                while(prio not in [1, 2, 3]):
                    print("Invalid choice")
                    print("Enter priority: ")
                    prio = priority()
                todo.insert(task, prio)
                clear()
            elif choice == 2:
                task = input("Enter task: ")
                todo.delete(task)
                clear()
            elif choice == 3:
                print("Task List:")
                todo.display()
                sleep(10)
                clear()
            elif choice == 4:
                print("\033[1;31;40m CLOSING PROGRAM... \033[0m")
                sleep(3)
                break
            else:
                print("Invalid choice")
        clear()
    except KeyboardInterrupt:
        print("\nExiting...")
        clear()

