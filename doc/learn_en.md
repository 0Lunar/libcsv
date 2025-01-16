# Beginner's Guide

## Index

- [Introduction](#introduction)
- [The CSV Type](#the-csv-type)
- [Reading a CSV file](#reading-a-csv-file)
- [Writing on the CSV file](#writing-on-the-csv-file)
- [Manipulating CSV objects](#manipulating-csv-objects)
    - [Get an item](#get-an-item)
    - [Update the content](#update-the-content)
    - [Add a new node](#add-a-new-node)
    - [Find a string](#find-a-string)
    - [Find a string in all nodes](#find-a-string-in-all-nodes)
    - [Find and replace](#find-and-replace)
    - [Find and replace all](#find-and-replace-all)
    - [Delete a column](#delete-a-column)
    - [Delete a row](#delete-a-row)
    - [Remove empity cells](#remove-empity-cells)
    - [Get the number of rows](#get-the-number-of-rows)
    - [Get the number of columns](#get-the-number-of-columns)
    - [Free a CSV list](#free-the-list)


## Introduction

In this markdown file we will explain the functions of the `libcsv` library and how to use them.

This guide is intended for those who want to learn how to manipulate csv files with the `C programming language`.
The library can also be used on `C++`.

## The CSV Type

The `CSV list` consists of a struct that contains the row, column and content in the csv file.

```C
struct csvType {
    uint32_t row;
    uint32_t column;
    char *content;
    struct csvType *next;
};
```

The last parameter will be the pointer to the next element of the list.

**WARNING**: The list **must be sorted by row and column**, if this rule is not respected the writing of the csv file will give rise to problems.


## Reading a CSV file

To read a csv file with libcsv there is the function `csvReadFile` which requires 2 parameters:
 - The `FILE pointer` that points to the input file `(FILE *)`
 - The `separator` which must be a single character `(const char sp)`


The file must be opened in `read` and `text` mode.

```C
CSV *csvReadFile(FILE *f, const char sp)
```

The function will return a `pointer` with a `CSV type list` sorted, that will contain `row`, `column` and `content`.


## Writing on the CSV file

To write to a csv file with libcsv there is the function `csvWriteFile` which requires 2 parameters:
 - `FILE pointer` pointing to the output file `(FILE *f)`
 - The `separator` which must be a single character `(const char sp)`

the file must be opened in `write` and `text` mode.

```C
void csvWriteFile(FILE *f, CSV *root, const char sp)
```

## Manipulating CSV objects

To manipulate `csv objects` in the list there are many functions that allow you to do everything and in this section we will list them all.

### Get an item

To get a CSV element based on row and column you can use the `csvGetElement` function which requires 3 parameters:
 - The **main pointer of the list** (i.e. the one that points to the first element) `(CSV *)`
 - The row `(unsigned int)`
 - The column `(unsigned int)`

```C
CSV *csvGetElement(CSV *elements, uint32_t row, uint32_t column)
```

The function will return the `pointer` of the desired element.

---

### Update the content

To update the content of an element in the list there is the function `csvUpdateElement` which requires 4 parameters:
 - The **main pointer of the list** `(CSV *)`
 - The row  `(unsigned int)`
 - The column `(unsigned int)`
 - The `content` that will **replace the original** `(const char *)`

```C
void csvUpdateElement(CSV *root, uint32_t row, uint32_t column, const char *content)
```

---

### Add a new node

To add a new node to the list there is the function `csvAddElement` which requires 4 parameters:
 - The **main pointer of the list** `(CSV *)`
 - The row  `(unsigned int)`
 - The column `(unsigned int)`
 - The content `(cont char *)`

```C
CSV *csvAddElement(CSV *root, uint32_t row, uint32_t column, const char *content)
```

The function will create a **new node** which will be added in order by position to the list and will **return the updated pointer**.

---

### Find a string

To find a string in a csv list there is the `csvFindString` function which requires 2 parameters:
 - The **main pointer of the list** `(CSV *)`
 - The string to find `(const char *)`

```C
CSV *csvFindString(CSV *elements, const char *string)
```

The function will **return the pointer** of the **first element** that contains the string to search for, if the function does not find any results it **returns the NULL pointer**.

---

### Find a string in all nodes

To find all nodes that contain a given string there is the function `csvFindAllStrings` that will require two parameters:
 - The **main pointer of the list** `(CSV *)`
 - The string to find `(const char *)`

```C
CSV *csvFindAllStrings(CSV *root, const char *string)
```

The function will return a `list` with all elements that contain the provided string.

---

### Find and replace

To search for a string and replace it there is the function `csvFindAndReplace` which requires 3 parameters:
 - The **main pointer of the list** `(CSV *)`
 - The string to replace `(const char *)`
 - The new string `(const char *)`

```C
void csvFindAndReplace(CSV *root, const char *toFind, const char *string)
```

**WARNING**: This function will replace **only the first element** that contains the string to be replaced.

---

### Find and replace all

To replace **all** elements containing a string there is the function `csvFindAndReplaceAll` which requires 3 parameters:
 - The **main pointer of the list** `(CSV *)`
 - The string to replace `(const char *)`
 - The new string `(const char *)`

```C
void csvFindAndReplaceAll(CSV *root, const char *toFind, const char *string)
```

---

### Delete a column

To delete a column in the list there is the function `csv Delete Column` which requires 2 parameters:
 - The **main pointer of the list** `(CSV *)`
 - The column `(unsigned int)`

```C
CSV *csvDeleteColumn(CSV *root, uint32_t column)
```

The function will return the list pointer with the updated values.

---

### Delete a row

To delete a row in the list there is the function `csvDeleteRow` which requires 2 parameters:
 - The **main pointer of the list** `(CSV *)`
 - The row `(unsigned int)`

```C
CSV *csvDeleteRow(CSV *root, uint32_t row);
```

The function will return the list pointer with the updated values.

---

### Remove empity cells

To remove all empty elements in the list there is the function `csvRemoveEmptyCells` which requires 1 parameter:
 - The **main pointer of the list** `(CSV *)`

```C
CSV *csvRemoveEmptyCells(CSV *root)
```

The function will return the list pointer with the updated values.

---

### Get the number of rows

To get the number of rows in the list there is the function `csvRows` which requires 1 parameter:
 - The **main pointer of the list** `(CSV *)`


```C
uint32_t csvRows(CSV *root)
```

---

### Get the number of columns

To get the number of columns in a row there is the function `csvColumns` which requires 2 parameters:
 - The **main pointer of the list** `(CSV *)`
 - The row `(unsigned int)`

```C
uint32_t csvColumns(CSV *root, uint32_t row)
```

---

### Free the list

To free a list and all its contents there is the function `csvFree` which requires 1 parameter:
 - The **main pointer of the list** `(CSV *)`


```C
void csvFree(CSV *root)
```