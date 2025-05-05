#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <csv.h>

int main() {
    FILE *f = fopen("test.csv", "w");
    if (!f) {
        perror("Error opening test.csv for writing");
        return 1;
    }
    fprintf(f, "Name,Age,City\nAlice,30,Milan\nBob,25,Rome\n");
    fclose(f);

    f = fopen("test.csv", "r");
    if (!f) {
        perror("Error opening test.csv for reading");
        return 1;
    }

    CSV *data = csvReadFile(f, ',');
    fclose(f);

    if (!data) {
        printf("Error reading the CSV file.\n");
        return 1;
    }

    CSV *element = csvGetElement(data, 1, 0);
    if (element) {
        printf("Element [1,0]: %s\n", element->content);
    }

    csvUpdateElement(data, 1, 2, "Florence");

    data = csvAddElement(data, 2, 0, "Charlie");
    data = csvAddElement(data, 2, 1, "40");
    data = csvAddElement(data, 2, 2, "Naples");

    data = csvDeleteRow(data, 0);

    f = fopen("output.csv", "w");
    if (!f) {
        perror("Error opening output.csv");
        return 1;
    }

    csvWriteFile(f, data, ',');
    fclose(f);

    csvFree(data);

    printf("Test completed. Check output.csv.\n");
    return 0;
}

