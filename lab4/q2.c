#include <stdio.h>

int main() {
    char str[100];
    FILE *fp;

    printf("Enter the string: ");
    fgets(str, sizeof(str), stdin);

    fp = fopen("file1.dat", "w+");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "%s", str);
    rewind(fp);

    printf("Contents of file:\n");
    while (fscanf(fp, "%s", str) != EOF) {
        printf("%s\n", str);
    }

    fclose(fp);
    return 0;
}

