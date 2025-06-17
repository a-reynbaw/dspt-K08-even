# Question4

## Overview

Priority Queue (PQ) implementation, along with a main program and test module. These are all the files contained in the solution direstory:

- **`PQImplementation.c`** contains the source code for the PQ functions
- **`PQInterface.h`** defines the PQ structure and the functions in `PQImplementation.c`
- **`PQTypes.c`** defines the `Item` type
- **`main.c`** creates an interface to use the PQ and its functions
- **`test_module.c`** contains unit tests for each function
- **`Makefile`** used to compile all source files and create the executable files

## Build and Dependencies
- ### Dependencies

    - **`PQImplementation.c`**
    - **`PQInterface.h`**
    - **`PQTypes.c`**
    - **`acutest.h`** (contained inside /acutest dir)

- ### Build

    Use either of these commands to build the main program executable("q4"):
    ```-bash
    $ make
    $ make q4
    ```

    Use strictly this command to build the test executable("test"):
    ```-bash
    $ make test
    ```

## Usage

- `q4`

    To use the main program "q4", type this command:
    ```-bash
    $ ./q4 <num>
    ```

    Where `num` refers to the size of the PQ the user wants to create. `num` should be a natural number.

    After that, a menu will pop, providing three choices:
    1. `Insert` : Adds a new Item to the PQ and prints the updated PQ
    2. `Remove` : Removes the Item with the highest priority from PQ and prints the updated PQ
    3. `Exit` : Closes the menu and terminates the program

- `test`

    To use the program "test", type this command:
    ```-bash
    $ ./test
    ```

If you want to check if the programs have memory leaks or\and errors, do the same as above, but with the command `valgrind` in front, as such:

```-bash
$ valgrind ./q4 <num>
$ valgrind ./test
```

## Function

1. `PQImplementation.c`

    - `QUEUEinit`
        This function initiates a PQ by:
            - allocating memory for the structure and saving it's address to a `PQPointer`,

            - starts the counter (`PQ->Count`) at 0, indicating it is an empty PQ,

            - allocating memory for the array (`PQ->ItemArray`) that implements the actual queue structure which will contain the `Item`s.

    - `QUEUEempty`
        Checks if a PQ is empty and returns an int value accordingly: 1 if empty, 0 zero if not

    - `QUEUEput`
        This function will add a new `Item` to a PQ. The way this works is that:
            - The function will first add the new element at the end of `PQ->ItemArray` and icreases the `PQ->Count`.

            - Then, `postion`, which tracks the new `Item`'s location, is iniated at the end (`PQ->Count`).

            - In order to place the new element in the right position on the `ItemArray`(Heap-based), and up-heap (bubble-up) operation is preformed. This means that, while the root hasn't been reached and the element still has hogher priority than its parent, move the parent to become the new child (current position) and update the new element's current position to the parent's old one (move up);

            - In the end, the new `Item` will be placed in the currect position based on its priority.

    - `QUEUEget`
        Removes the `Item` with the highest priority from the PQ. This is done by first decreasing the counter `PQ->Count` and then returning the last `Item` from `PQ->ItemArray` (`PQ->ItemArray[PQ->Count]`).

    I added two more functions in order to make usage and testing easier

    - `QUEUEprint`
        Prints all the PQ elements. The itteration for printing starts from index 1 instead of 0 since this implementation is a 1-indexed heap. (first `Item` in the first position and so on).

    - `QUEUEfree`
        This function frees the `PQ->ItemArray` and the `PQPointer`, which refers to a PQ stucture.


2. `PQInterface.h`
    This is a header file given to us to base off of it the PQImplemetation.c file.


3. `PQType.h` header file to define the `Item` type.


4. `main.c`
    This program contains 2 functions: `main()` and `menu()`

    1. `main()`:
        - will take an argument from the commandline, which will refer to the maximum capacity of the PQ used in program. 

        - If the arguments given do not correspond to the program's standards, an error message will be printed and the program will terminate.

        - After that, the PQ will be created by using `QUEUEinit(maxN)`, where `maxN` is the number given by the user via commandline.

        - `main()` will then call `menu()` and after the returning, PQ is free with `QUEUEfree(PQ)`.

    2. `menu()`:
        - Displays three choices to the user: 
            1) Insert: checks if the PQ is at maximum capacity and if not, asks the user to provide the new element. After that, it will call `QUEUEput(PQ, num)` and after returning, it prints the updated PQ. 

            2) Remove: Displays to user the element with the highest priority. At the same time it removes it from the PQ by using `QUEUEget(PQ)` and after returning, it prints the updated PQ. 

            3) Exit: returns from `menu()` to `main()`.


5. `test_module.c`
    Tests the functions in `PQImplementation.c` using the `acutest` library for unit tests.

6. `Makefile` 
    Creates the two executable files: `q4` and `test`.

## Demo 
`q4`:
```-bash
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question4$ make
gcc -Wall -Werror -Wextra -pedantic -c main.c -o main.o
gcc -Wall -Werror -Wextra -pedantic main.o PQImplementation.o -o q4
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question4$ ./q4
Usage: ./q4 <num>
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question4$ ./q4 -2
Invalid Priority Queue size. Terminating.
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question4$ ./q4 0
Invalid Priority Queue size. Terminating.
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question4$ ./q4 5
------------------------------
1. Insert
2. Remove
3. Exit
-> 7
Wrong input, please choose again.
-> -1
Wrong input, please choose again.
------------------------------
1. Insert
2. Remove
3. Exit
-> 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Give number to insert:
-> 4
> Updated queue:
4
------------------------------
1. Insert
2. Remove
3. Exit
-> 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Give number to insert:
-> 7
> Updated queue:
7, 4
------------------------------
1. Insert
2. Remove
3. Exit
-> 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Give number to insert:
-> 3
> Updated queue:
7, 4, 3
------------------------------
1. Insert
2. Remove
3. Exit
-> 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Give number to insert:
-> 8
> Updated queue:
8, 7, 4, 3
------------------------------
1. Insert
2. Remove
3. Exit
-> 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Give number to insert:
-> 34
> Updated queue:
34, 8, 7, 4, 3
------------------------------
1. Insert
2. Remove
3. Exit
-> 1
!!! Maximuim capacity for this Priority Queue has been reached. Remove an item before inserting a new one. !!!
------------------------------
1. Insert
2. Remove
3. Exit
-> 2
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Removed Item: 34
> Updated queue:
8, 7, 4, 3
------------------------------
1. Insert
2. Remove
3. Exit
-> 2
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Removed Item: 8
> Updated queue:
7, 4, 3
------------------------------
1. Insert
2. Remove
3. Exit
-> 2
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Removed Item: 7
> Updated queue:
4, 3
------------------------------
1. Insert
2. Remove
3. Exit
-> 2
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Removed Item: 4
> Updated queue:
3
------------------------------
1. Insert
2. Remove
3. Exit
-> 2
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Removed Item: 3
> Updated queue:
0
------------------------------
1. Insert
2. Remove
3. Exit
-> 2
!!! Priority Queue is empty. Insert items before removing. !!!
------------------------------
1. Insert
2. Remove
3. Exit
-> 3
```
`test`:
```-bash
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question4$ ./test
Test test_QUEUEinit...                          [ OK ]
Test test_QUEUEempty...                         [ OK ]
Test test_QUEUEput...                           [ OK ]
Test test_QUEUEget...                           [ OK ]
SUCCESS: All unit tests have passed.
```