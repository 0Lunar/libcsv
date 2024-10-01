/*
Copyright (c) 30-09-2024 https://github.com/0lunar

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "csv.h"


/*
reads a CSV file from the file pointer `f` and uses `sp` as the column separator.
It returns a pointer to the CSV structure.
*/

CSV *readCsvFile(FILE *f, const char sp) {
    CSV *root = malloc(sizeof(CSV));
    if (root == NULL) {
        perror("Error allocating memory to root");
        return NULL;
    }

    root->content = malloc(MAX_LINE_LENGTH * sizeof(char));
    if (root->content == NULL) {
        perror("Error allocating memory to content");
        free(root);
        return NULL;
    }

    root->next = NULL;
    root->column = 0;
    root->row = 0;

    CSV *visit = root;

    char ch;
    while ((ch = getc(f)) != EOF) {
        uint32_t cnt = 0;

        while (ch != EOF && ch != sp && cnt < MAX_LINE_LENGTH - 1) {
            if (ch == '\n') {
                break;
            }
            else {
                visit->content[cnt] = ch;
                cnt++;
            }
            ch = getc(f);
        }

        visit->content[cnt] = '\0';

        if (ch == EOF) {
            break;
        }


        if ((cnt > 1 && ch == '\n') || ch == sp){
            visit->next = malloc(sizeof(CSV));
            if (visit->next == NULL) {
                perror("Error allocating memory for next pointer");
                free(visit->content);
                free(root);
                return NULL;
            }

            visit->next->content = malloc(MAX_LINE_LENGTH * sizeof(char));
            if (visit->next->content == NULL) {
                perror("Error allocating memory for next content pointer");
                free(visit->content);
                free(root);
                return NULL;
            }

            if (ch == '\n') {
                visit->next->column = 0;
                visit->next->row = visit->row + 1;
            }

            else {
                visit->next->column = visit->column + 1;
                visit->next->row = visit->row;
            }

            visit = visit->next;
            visit->next = NULL;
        }
    }

    return root;
}


/*
Writes the content of a CSV structure to a file `f`, using `sp` as the column separator.
*/

void writeCsvFile(FILE *f, CSV *root, const char sp) {
    CSV *visitor;
    uint32_t row;

    if (root == NULL) {
        perror("Error, root is empity");
        return;
    }

    row = 0;
    visitor = root;

    while (visitor != NULL) {
        while (visitor->row != row) {
            putc('\n', f);
            row++;
        }

        for (int i = 0; i < strlen(visitor->content); i++) {
            putc(visitor->content[i], f);
        }

        if (visitor->next != NULL) {
            putc(sp, f);
        }

        visitor = visitor->next;
    }
}


/*
Returns a pointer to the element at the specified `row` and `column`.
*/

CSV *csvElement(CSV *elements, uint32_t row, uint32_t column) {
    while (elements != NULL && elements->row != row) {
        elements = elements->next;
    }

    while (elements != NULL && elements->column != column) {
        elements = elements->next;
    }

    return elements;
}


/*
Return a pointer of the first element corrisponding to the `string`.
*/

CSV *findCsvString(CSV *elements, const char *string) {
    while (elements != NULL && strcmp(string, elements->content) != 0) {
        elements = elements->next;
    }

    return elements;
}


/*
Modifies the content of the element at the specified position with the new content provided.
*/

void modifyCsvElement(CSV *root, uint32_t row, uint32_t column, const char *content) {
    
    root = csvElement(root, row, column);

    if (root == NULL) {
        perror("Column/row not found");
        return;
    }

    free(root->content);
    root->content = malloc(MAX_LINE_LENGTH * sizeof(char));

    if (root->content == NULL) {
        perror("Error allocating memory for content");
        return;
    }

    strcpy(root->content, content);
    printf("%s", root->content);
}




void deleteCsvColumn(CSV *root, uint32_t row, uint32_t column) {
    if (column == 0 && row > 0) {
        root = csvElement(root, row-1, column);
    }

    else if (column > 0) {
        root = csvElement(root, row, column-1);
    }

    if (root == NULL || root->next == NULL) {
        perror("Column/row not found");
        return;
    }


    if ((column == 0 && row > 0) || column > 0) {
        root->next = root->next->next;
    }

    else {
        root = root->next;
    }
}




CSV *deleteCsvRow(CSV *root, uint32_t row) {
    CSV *realRoot;
    CSV *back;
    CSV *tmp;

    if (root == NULL) {
        perror("Error, root pointer NULL");
        return NULL;
    }

    realRoot = root;

    //reach the row
    while (root->row != row) {
        back = root;
        root = root->next;
    }

    if (row > 0) {
        while (root != NULL && root->row == row) {
            free(root->content);
            tmp = root->next;
            free(root);
            root = tmp;
        }

        back->next = root;
    }
    else {
        while (root != NULL && root->row == row) {
            root = root->next;
        }

        realRoot = root;
    }

    return root;
}




CSV *addCsvElement(CSV *root, uint32_t row, uint32_t column, const char *content) {
    CSV *realRoot = root;
    CSV *newElement = malloc(sizeof(CSV));
    CSV *tmp = root;
    
    if (newElement == NULL) {
        perror("Error allocating memory to new element");
        return NULL;
    }

    newElement->row = row;
    newElement->column = column;
    newElement->content = malloc(MAX_LINE_LENGTH * sizeof(char));

    if (newElement->content == NULL) {
        perror("Error allocating memory for content");
        free(newElement);
        return NULL;
    }

    strcpy(newElement->content, content);
    newElement->next = NULL;

    if (root == NULL) {
        return newElement;
    }

    if (column == 0 && row == 0) {
        newElement->next = root;
        return newElement;
    }

    CSV *prev = NULL;
    while (tmp != NULL && (tmp->row < row || (tmp->row == row && tmp->column < column))) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (prev == NULL) {
        newElement->next = root;
        realRoot = newElement;  
    } else {
        newElement->next = prev->next;
        prev->next = newElement;
    }

    while (tmp != NULL && tmp->row == row) {
        tmp->column++;
        tmp = tmp->next;
    }

    return realRoot;
}




uint32_t csvRows(CSV *root) {
    uint32_t rows;
    uint32_t row;

    if (root == NULL) {
        return 0;
    }

    row = 0;
    rows = 0;
    while (root != NULL) {
        if (root->row > rows) {
            rows = root->row;
            row++;
        }

        root = root->next;
    }

    return row + 1;
}




uint32_t csvColumns(CSV *root, uint32_t row) {
    uint32_t columns;

    if (root == NULL) {
        return 0;
    }


    // reach the row
    while (root != NULL && root->row != row) {
        root = root->next;
    }

    if (root->row != row && root == NULL) {
        return 0;
    }

    columns = 0;

    while (root != NULL && root->row == row) {
        columns++;
        root = root->next;
    }

    return columns;
}




void freeCsv(CSV *root) {
    CSV *tmp;
    CSV *toFree;

    tmp = root;
    toFree = tmp;

    while (toFree != NULL) {
        tmp = toFree->next;
        free(toFree->content);
        free(toFree);
        toFree = tmp;
    }
}




CSV *removeEmpityCells(CSV *root) {
    CSV *realRoot;
    CSV *back;
    
    realRoot = root;
    back = root;

    while (root != NULL) {
        if (strlen(root->content) == 0) {
            if (root->column == 0 && root->row == 0) {
                realRoot = realRoot->next;
            }
            else {
                back->next = root->next;
            }
        }

        back = root;
        root = root->next;
    }

    return realRoot;
}


void findAndReplace(CSV *root, const char *string, const char *newString) {
    if (root == NULL || string == NULL || newString == NULL) {
        perror("Invalid argument(s) provided.");
        return;
    }

    while (root != NULL) {
        if (strcmp(root->content, string) == 0) {
            free(root->content);
            root->content = malloc((strlen(newString) + 1) * sizeof(char));

            if (root->content == NULL) {
                perror("Error allocating memory to pointer content");
                return;
            }

            strcpy(root->content, newString);
        }

        root = root->next;
    }
}


CSV *findAllCsvStrings(CSV *root, const char *string) {
    CSV *newCsvRoot;
    CSV *newCsv;

    newCsv = NULL;
    newCsvRoot = NULL;

    while (root != NULL) {
        if (strcmp(root->content, string) == 0) {
            if (newCsv == NULL) {
                newCsv = malloc(sizeof(CSV));

                if (newCsv == NULL) {
                    perror("Error allocating memory to newCsv");
                    return NULL;
                }

                newCsvRoot = newCsv;
            }
            else {
                newCsv->next = malloc(sizeof(CSV));

                if (newCsv->next == NULL) {
                    perror("Error allocating memory to newCsv");
                    return NULL;
                }

                newCsv = newCsv->next;
            }

            newCsv->content = malloc((strlen(root->content) + 1) * sizeof(char));

            if (newCsv->content == NULL) {
                perror("Error allocating memory to newCsv content");
                return NULL;
            }

            newCsv->column = root->column;
            newCsv->row = root->row;
            strcpy(newCsv->content, root->content);
            newCsv->next = NULL;
        }

        root = root->next;
    }

    return newCsvRoot;
}


CSV *columnElements(CSV *root, uint32_t column) {
    CSV *newCsv;
    CSV *newCsvRoot;

    newCsv = NULL;
    newCsvRoot = NULL;

    while (root != NULL) {
        if (root->column == column) {
            if (newCsv == NULL) {
                newCsv = malloc(sizeof(CSV));

                if (newCsv == NULL) {
                    perror("Error allocating memory to newCsv");
                    return NULL;
                }

                newCsvRoot = newCsv;
            }
            else {
                newCsv->next = malloc(sizeof(CSV));
                
                if (newCsv->next == NULL) {
                    perror("Error allocating memory to next newCsv");
                    return NULL;
                }

                newCsv = newCsv->next;
            }

            newCsv->content = malloc((strlen(root->content) + 1) * sizeof(char));

            if (newCsv->content == NULL) {
                perror("Error allocating memory to newCsv content");
                return NULL;
            }

            strcpy(newCsv->content, root->content);
            newCsv->row = root->row;
            newCsv->column = root->column;
            newCsv->next = NULL;
        }

        root = root->next;
    }

    return newCsvRoot;
}