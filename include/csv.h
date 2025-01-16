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


//create
CSV *csvCreateList();

//IO
CSV *csvReadFile(FILE *f, const char sp);
void csvWriteFile(FILE *f, CSV *root, const char sp);

//get and set
CSV *csvGetElement(CSV *elements, uint32_t row, uint32_t column);
void csvUpdateElement(CSV *root, uint32_t row, uint32_t column, const char *content);
CSV *csvAddElement(CSV *root, uint32_t row, uint32_t column, const char *content);
CSV *csvAppendRowContent(CSV *root, uint32_t row, const char *string);

//find
CSV *csvFindString(CSV *elements, const char *string);
CSV *csvFindAllStrings(CSV *root, const char *string);

//replace
void csvFindAndReplace(CSV *root, const char *toFind, const char *string);
void csvFindAndReplaceAll(CSV *root, const char *toFind, const char *string);

//remove
CSV *csvDeleteColumn(CSV *root, uint32_t column);
CSV *csvDeleteRow(CSV *root, uint32_t row);
CSV *csvRemoveEmptyCells(CSV *root);

//info
uint32_t csvRows(CSV *root);
uint32_t csvColumns(CSV *root, uint32_t row);

//free
void csvFree(CSV *root);

#endif