# TODO List Program

## Background
I created a TODO LIST program in C++ using a hash table, inspired by JIRA. The program allows users to:

- Add tasks
- Change task names
- Add priority to tasks
- Change task priority

When the user closes the program (by pressing 8), it logs the completion percentage for that day in a text file. This allows users to track how productive they were throughout the day, week, or even the year.

### Pre-Req
Must have CMake (3.10) installed on machine in order to run (optional).

## How to Run
1. **Ensure C++ is Installed**  
   Verify C++ is installed on your local machine by typing `gcc` in the Visual Studio Code terminal or Command Prompt (CMD).

2. **Compile the Program**  
  CMake compile:
    ```bash
      cd build
    ```
    - When Using MinGW:
      ``` bash
        1. cmake -G "MinGW Makefiles" ..
        2. mingw32-make 
        3. ./todo
      ```
    - When Using GCC/Clang:
    ``` bash
      1. cmake ..
      2. make
      3. ./todo
    ```
   Normal Compile:

   - To compile without specifying an output name:
     ```bash
     g++ -std=c++17 .\hashTask.cpp
     ```

   - To compile and specify an output name:
     ```bash
     g++ -std=c++17 .\hashTask.cpp -o <give it a name>
     ```

3. **Run the Program**  
   - For the first compile method, run:
     ```bash
     ./a
     ```

   - For the second compile method (where you specify a name), run:
     ```bash
     ./<givename>
     ```

4. **Follow Prompts and Enjoy**  
   Follow the on-screen prompts to use the TODO List program.