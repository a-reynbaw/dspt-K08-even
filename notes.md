## 🔗 Linked Data Representations

#### Key Concepts:
- **Linked Structures**: Lists, stacks, queues, sets, and trees are dynamic and flexible, ideal when data sizes or shapes are unpredictable.

- **Pointers in C**: Core for implementing linked structures.

    - `*` dereferences a pointer.

    - `&` gives the address.

    - `malloc()` allocates memory dynamically.

    - `free()` deallocates memory, cautioning against dangling pointers.

#### Linked Lists:

- **Structure**:
    ```c
    typedef struct NodeTag {
        AirportCode Airport;
        struct NodeTag * Link;
    } NodeType;
    ```

- **Operations**:
    - Insert/delete nodes (e.g., insert in second position or at the end).

    - Traverse/search via `ListSearch`.

    - Print list using pointer traversal.

    - **Visual diagrams** help illustrate node connections and effects of operations.

#### Function Examples:
- swapping with pointers:
    ```c
    void Swap(int * p, int * q) {
        int temp = *p;
        *p = *q;
        *q = temp;
    }
    ```

- insert new node:
    ```c
    N->Link = L->Link;
    L->Link = N;
    ```

- delete last node:
    Requires `NodeType ** L` to modify the head if necessary.

## 🔁 Recursion

#### Introduction:

- Recursion solves problems by breaking them into smaller subproblems.

- Needs:

    - A **base case** to stop recursion.
    - Recursive step(s) to reduce problem size.

#### Examples:

- **Sum of squares (m to n)**:

    - Going up: `return m*m + SumSquares(m+1, n)`;

    - Going down: `return SumSquares(m, n-1) + n*n`;

    - Divide & conquer: splits range into two halves.

- **Factorial**:
    ```c
    int Factorial(int n) {
        return (n == 1) ? 1 : n * Factorial(n - 1);
    }
    ```

- **Reversing a Linked List**:

    - **Iteratively**: uses pointers R (reversed), N (current), L1 (traverse).

    - **Recursively**: splits list into head/tail, reverses tail, then concatenates.

Advanced Example:

- **Towers of Hanoi**: classic recursion puzzle.

    - Moves are computed recursively: `2^n - 1` steps.

    - Recursive function `MoveTowers` calls itself three times.
