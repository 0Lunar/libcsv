#ifndef CSV_LIB_H
#define CSV_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024


struct csvType {
    uint32_t row;
    uint32_t column;
    char *content;
    struct csvType *next;
};


typedef struct csvType CSV;


CSV *readCsvFile(FILE *f, const char sp);
void writeCsvFile(FILE *f, CSV *root, const char sp);
CSV *csvElement(CSV *elements, uint32_t row, uint32_t column);
void modifyCsvElement(CSV *root, uint32_t row, uint32_t column, const char *content);
void deleteCsvColumn(CSV *root, uint32_t row, uint32_t column);
CSV *findCsvString(CSV *elements, const char *string);
CSV *addCsvElement(CSV *root, uint32_t row, uint32_t column, const char *content);
uint32_t csvRows(CSV *root);
uint32_t csvColumns(CSV *root, uint32_t row);
void freeCsv(CSV *root);
CSV *deleteCsvRow(CSV *root, uint32_t row);
CSV *removeEmpityCells(CSV *root);
void findAndReplace(CSV *root, const char *string, const char *newString);
CSV *columnElements(CSV *root, uint32_t column);

#endif