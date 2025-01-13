/*
MIT License

Copyright (c) 2025 Nicolò Rinaldi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "csv.h"


/*
reads a CSV file from the file pointer `f` and uses `sp` as the column separator.
It returns a pointer to the CSV structure.
*/

CSV *readCsvFile(FILE *f, const char sp) {
    CSV *root = malloc(sizeof(CSV));
    if (!root) return NULL;

    root->content = malloc(MAX_LINE_LENGTH * sizeof(char));
    if (!root->content) {
        free(root);
        return NULL;
    }

    root->next = NULL;
    root->column = 0;
    root->row = 0;

    CSV *visit = root;

    char ch = 0;
    while ((ch = getc(f)) != EOF) {
        uint32_t cnt = 0;

        while (ch != EOF && ch != sp && cnt < MAX_LINE_LENGTH && ch != '\n') {
            visit->content[cnt] = ch;
            cnt++;
            ch = getc(f);
        }

        visit->content[cnt] = '\0';

        if (ch == EOF) break;


        if ((cnt > 1 && ch == '\n') || ch == sp){
            visit->next = malloc(sizeof(CSV));
            if (visit->next == NULL) {
                free(visit->content);
                free(root);
                return NULL;
            }

            visit->next->content = malloc(MAX_LINE_LENGTH * sizeof(char));
            if (visit->next->content == NULL) {
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
    uint32_t column = 0;

    if (root == NULL) return;

    row = 0;
    visitor = root;

    while (visitor != NULL) {
        while (visitor->row != row) {
            putc('\n', f);
            row++;
            column = 0;
        }

        if (visitor->column == column) {
            for (int i = 0; i < strlen(visitor->content) && visitor->content[i] != '\r'; i++)
                putc(visitor->content[i], f);

            if (visitor->next != NULL && visitor->next->row == row)
                putc(',', f);
            
            column++;
        }
            
        else {
            while (visitor->column != column) {
                putc(',', f);
                column++;
            }

            for (int i = 0; i < strlen(visitor->content) && visitor->content[i] != '\r'; i++)
                putc(visitor->content[i], f);
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
        return;
    }

    if (root->content)
        free(root->content);

    root->content = malloc(MAX_LINE_LENGTH * sizeof(char));

    if (root->content == NULL) {
        return;
    }

    strcpy(root->content, content);
}




CSV *deleteCsvColumn(CSV *root, uint32_t column) {
    if (!root) return NULL;

    if (root->column == column) {
        root = root->next;

        while (root->column == column)
            root->column--;
    }

    CSV *tmp = root;

    while (tmp != NULL && tmp->next != NULL) {
        if (tmp->next->column == column) {
            tmp->next = tmp->next->next;
        }
        tmp = tmp->next;
    }

    return root;
}




CSV *deleteCsvRow(CSV *root, uint32_t row) {
    if (!root) return NULL;

    if (root->row == row) {
        while(root->row == row)
            root = root->next;
        
        return root;
    }

    CSV *tmp = root;
    CSV *Root = root;

    while (Root != NULL && Root->next != NULL && Root->next->row != row)
        Root = Root->next;

    tmp = Root->next;

    while (tmp != NULL && tmp->row == row)
        tmp = tmp->next;

    Root->next = tmp;

    while (tmp != NULL) {
        tmp->row--;
        tmp = tmp->next;
    }

    return root;
}




CSV *addCsvElement(CSV *root, uint32_t row, uint32_t column, const char *content) {
    if (!root) return NULL;

    CSV *newElement;
    CSV *tmproot = root;
    uint32_t columnT, rowT;

    newElement = malloc(sizeof(CSV));
    newElement->content = malloc(strlen(content) * sizeof(char));
    strcpy(newElement->content, content);
    newElement->next = NULL;
    newElement->column = column;
    newElement->row = row;
    
    while (tmproot->next != NULL && tmproot->row < row)
        tmproot = tmproot->next;

    rowT = tmproot->row;

    while (tmproot->next != NULL && tmproot->column < column && tmproot->next->row == rowT)
        tmproot = tmproot->next;
    
    if (!tmproot->next) {
        tmproot->next = newElement;
        return tmproot;
    }

    newElement->next = tmproot->next;
    tmproot->next = newElement;

    columnT = newElement->column;
    tmproot = newElement->next;

    while (tmproot != NULL && tmproot->column == columnT) {
        tmproot->column += 1;
        tmproot = tmproot->next;
    }

    return root;
}




uint32_t csvRows(CSV *root) {
    uint32_t rows = 1;
    uint32_t row;

    if (!root) {
        return 0;
    }

    row = root->row;

    while (root != NULL) {
        if (root->row != row) {
            rows++;
            row = root->row;
        }

        root = root->next;
    }

    return row;
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
        return;
    }

    while (root != NULL) {
        if (strcmp(root->content, string) == 0) {
            free(root->content);
            root->content = malloc((strlen(newString) + 1) * sizeof(char));

            if (root->content == NULL) {
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
                    return NULL;
                }

                newCsvRoot = newCsv;
            }
            else {
                newCsv->next = malloc(sizeof(CSV));

                if (newCsv->next == NULL) {
                    return NULL;
                }

                newCsv = newCsv->next;
            }

            newCsv->content = malloc((strlen(root->content) + 1) * sizeof(char));

            if (newCsv->content == NULL) {
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