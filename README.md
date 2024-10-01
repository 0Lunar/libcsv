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

## Available Functions

1. `CSV *readCsvFile(FILE *f, const char sp)`<br>
Reads a CSV file and converts it into a linked list of CSV elements.

- **Parameters**:
    - `f`: file pointer to the CSV file to read.
    - `sp`: separator character (e.g., , or ;).
- **Returns**: a pointer to the linked list of CSV elements.

2. `void writeCsvFile(FILE *f, CSV *root, const char sp)`
<br>Writes a linked list of CSV elements to a file.

- **Parameters**:
    - `f`: file pointer to the CSV file to write to.
    - `root`: pointer to the linked list of CSV elements to write.
    - `sp`: separator character to use in the file.

3. `CSV *csvElement(CSV *elements, uint32_t row, uint32_t column)`<br>
Finds a specific CSV element by row and column.

- **Parameters**:
    - `elements`: pointer to the CSV list.
    - `row`: row number of the element to find.
    - `column`: column number of the element to find.
- **Returns**: pointer to the found CSV element.


4. `void modifyCsvElement(CSV *root, uint32_t row, uint32_t column, const char *content)`<br>
Modifies the content of a specific CSV cell.

- **Parameters**:
    - `root`: pointer to the CSV list.
    - `row`: row number of the element to modify.
    - `column`: column number of the element to modify.
    - `content`: new content for the cell.

5. `void deleteCsvColumn(CSV *root, uint32_t row, uint32_t column)`<br>
Deletes a column from a specific row in the CSV list.

- **Parameters**:
    - `root`: pointer to the CSV list.
    - `row`: row number.
    - `column`: column number to delete.

6. `CSV *findCsvString(CSV *elements, const char *string)`<br>
Searches for the first occurrence of a string in a CSV cell.

- **Parameters**:
    - `elements`: pointer to the CSV list.
    - `string`: string to search for.
- **Returns**: pointer to the cell containing the string, if found.

7. `CSV *addCsvElement(CSV *root, uint32_t row, uint32_t column, const char *content)`<br>
Adds a new element to the CSV list.

- **Parameters**:
    - `root`: pointer to the CSV list.
    - `row`: row number for the new element.
    - `column`: column number for the new element.
    - `content`: content of the new cell.
- **Returns**: updated pointer to the CSV list.

8. `uint32_t csvRows(CSV *root)`<br>
Returns the number of rows in the CSV list.

- **Parameters**:
    - `root`: pointer to the CSV list.
- **Returns**: number of rows.

9. `uint32_t csvColumns(CSV *root, uint32_t row)`<br>
Returns the number of columns in a specific row of the CSV.

- **Parameters**:
    - `root`: pointer to the CSV list.
    - `row`: row number.
- **Returns**: number of columns in the specified row.

10. `void freeCsv(CSV *root)`
Frees the memory used by a CSV list.

- Parameters:
    - `root`: pointer to the CSV list to free.

11. `CSV *deleteCsvRow(CSV *root, uint32_t row)`<br>
Deletes an entire row from the CSV list.

- **Parameters**:
    - `root`: pointer to the CSV list.
    - `row`: row number to delete.
- **Returns**: updated pointer to the CSV list.

12. `CSV *removeEmptyCells(CSV *root)`
Removes all empty cells from the CSV list.

- **Parameters**:
    - `root`: pointer to the CSV list.
- **Returns**: updated pointer to the CSV list without empty cells.

13. `void findAndReplace(CSV *root, const char *string, const char *newString)`<br>
Finds all occurrences of a string and replaces them with a new string.

- **Parameters**:
    - `root`: pointer to the CSV list.
    - `string`: string to search for.
    - `newString`: new string to replace the old one.

14. `CSV *columnElements(CSV *root, uint32_t column)`
Creates a list of all cells in a specific column.

- **Parameters**:
    - `root`: pointer to the CSV list.
    - `column`: column number.
- **Returns**: pointer to the list of cells in the column.

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
gcc -o program main.c csv.c -I include/.
```

## Contributions

Feel free to contribute to this library with new functions, bug fixes, or performance improvements!