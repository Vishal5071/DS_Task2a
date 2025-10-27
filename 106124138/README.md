# CSPC32 - Assignment 2, Task #2a: Social Media Platform

## Project Overview

This is the code for the first part of Assignment 2—building a simple social media platform. The whole goal here was to practice **modularity** and use **linked lists** to manage posts, comments, and replies, just like the task asked.

We've got five main modules: `post`, `comment`, `reply`, `platform`, and the `main` driver. Everything is set up to follow the ADT rules.

## Git Repository Link: *https://github.com/Vishal5071/DS_Task2a*

## How to Build and Run It

Open the terminal in the same folder as *Makefile*.

1. **To Compile:**
   ```bash
   make all
   ```
2. **To Run:**
    ```bash
    make run
    ```
3. **To clean**
    ```bash
    make clean
    ```

(Type help once it starts for a list of commands.)

## Assumptions

* Key Design Choices & Assumptions
List Order: All lists (Posts, Comments, Replies) are maintained with the Most Recent Item at the Head of the singly linked list. This makes adding new items super fast.

* The Big Exception (viewComments): To meet the requirement that comments must be displayed with the latest comment at the last, the viewComments function creates a brand new, reversed copy of the list to return to the user. This avoids permanently messing up the internal comment list, which is needed for correct indexing (e.g., delete reply 2 1).

* Memory Safety: Everything uses deep copy (strdup) for strings. This prevents data from disappearing if the input buffers are overwritten.

* Fatal Errors: Per the assignment's implied rule for critical memory failure, if the system runs out of memory (malloc fails), the program will print an error and use exit(1) after cleaning up any partially allocated memory.

* Bonus: The full reply.h and reply.c modules have been implemented.