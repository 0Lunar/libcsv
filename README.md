# CSV Library - Documentation

This library provides functions for managing CSV files, allowing you to read, write, modify, search, and handle cells in a CSV file organized by rows and columns.

## Data Structure

The library uses a data structure to represent the elements of a CSV file:

```c
struct csvType {
    uint32_t row;
    uint32_t column;
    char *content;
    struct csvType *next;
};
```

Each element (`CSV`) represents a cell in the CSV file with:

- `row`: row number of the cell.
- `column`: column number of the cell.
- `content`: content of the cell (string).
- `next`: pointer to the next cell in the list.


## How to Use the Library

1. **Compilation**: Include the `csv.h` file in your project and link the implementation file (e.g., `csv.c`) to your project.

```c
#include "csv.h"
```

2. **Example of Reading and Writing CSV**:

```c
FILE *f = fopen("input.csv", "r");
CSV *csvData = readCsvFile(f, ',');
fclose(f);

// Modify or manipulate the CSV
// ...

FILE *out = fopen("output.csv", "w");
writeCsvFile(out, csvData, ',');
fclose(out);

freeCsv(csvData);

```

## Compilation

You can compile your program using `gcc` or other C compilers:

```bash
gcc -o program main.c src/csv.c -I include/.
```

## Contributions

Feel free to contribute to this library with new functions, bug fixes, or performance improvements!