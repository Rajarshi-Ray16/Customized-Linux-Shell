#include "sort.h"

int lineCountFile(char *filename) {

    FILE *fp = fopen(filename, "r");
    int linecount = 0;
    int c;
    if (fp == NULL) {
        fclose(fp);
        return 0;
    }
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            linecount++;
        }
    }
    fclose(fp);
    return linecount;
}

void sortfile(char **array, int linecount) {
    int i, j;
    char t[MAX_LINE];

    for (i = 1; i < linecount; i++) {
        for (j = 1; j < linecount; j++) {
            if (strcmp(array[j-1], array[j]) > 0) {
                strcpy(t, array[j-1]);
                strcpy(array[j-1], array[j]);
                strcpy(array[j], t);
            }
        }
    }
}

void sort_command(char* tokenS, int times, int flag) {

    if (flag == 0) {

        tokenS = strtok(NULL, " ");

        //The two file pointers.
        FILE *fileIN;

        //Storing the current working directory.
        char storeCWDIn[512];

        getcwd(storeCWDIn, 512);
        strcat(storeCWDIn, "/");
        strcat(storeCWDIn, tokenS);

        fileIN = fopen(storeCWDIn, "r");

        if (fileIN == NULL) {
            printf("Error!");   
            exit(1);         
        }

        //Gets the number of lines in the file.
        int linecount = lineCountFile(storeCWDIn);
        linecount += 1;

        //An array to store all the lines in an array.
        char **array = (char**) malloc(linecount * sizeof(char*));
        char singleline[MAX_LINE];

        int i = 0;
        while (fgets(singleline, MAX_LINE, fileIN) != NULL) {
            array[i] = (char*) malloc (MAX_LINE * sizeof(char));
            if (i == (linecount - 1)) {
                singleline[strlen(singleline)] = '\n';
            }
            singleline[MAX_LINE] = '\0';
            strcpy(array[i], singleline);
            i++;
        }

        sortfile(array, linecount);

        for (i = 0; i < linecount; i++) {
            printf("%s", array[i]);
        }

        fclose(fileIN);

    } else if (flag == 1) {

        tokenS = strtok(NULL, " ");
        tokenS = strtok(NULL, " ");

        //The two file pointers.
        FILE *fileIN;

        //Storing the current working directory.
        char storeCWDIn[512];

        getcwd(storeCWDIn, 512);
        strcat(storeCWDIn, "/");
        strcat(storeCWDIn, tokenS);

        fileIN = fopen(storeCWDIn, "r");

        if (fileIN == NULL) {
            printf("Error!");   
            exit(1);         
        }

        //Gets the number of lines in the file.
        int linecount = lineCountFile(storeCWDIn);
        linecount += 1;

        //An array to store all the lines in an array.
        char **array = (char**) malloc(linecount * sizeof(char*));
        char singleline[MAX_LINE];

        int i = 0;
        while (fgets(singleline, MAX_LINE, fileIN) != NULL) {
            array[i] = (char*) malloc (MAX_LINE * sizeof(char));
            if (i == (linecount - 1)) {
                singleline[strlen(singleline)] = '\n';
            }
            singleline[MAX_LINE] = '\0';
            strcpy(array[i], singleline);
            i++;
        }

        sortfile(array, linecount);

        for (i = 0; i < linecount; i++) {
            printf("%s", array[i]);
        }

        fclose(fileIN);

    } else if (flag == 3) {
        
        tokenS = strtok(NULL, " ");
        tokenS = strtok(NULL, " ");

        //The two file pointers.
        FILE *fileIN, *fileOUT;

        //Storing the current working directory.
        char storeCWDIn[512];
        char storeCWDOut[512];

        getcwd(storeCWDIn, 512);
        strcat(storeCWDIn, "/");
        strcat(storeCWDIn, tokenS);
        
        tokenS = strtok(NULL, " ");
        tokenS = strtok(NULL, " ");

        printf("%s\n", storeCWDIn);

        getcwd(storeCWDOut, 512);
        strcat(storeCWDOut, "/");
        strcat(storeCWDOut, tokenS);

        printf("%s\n", storeCWDOut);

        fileIN = fopen(storeCWDIn, "r");

        if (fileIN == NULL) {
            printf("Error!");   
            exit(1);         
        }

        fileOUT = fopen(storeCWDOut, "w");

        if (fileOUT == NULL) {
            printf("Error!");   
            exit(1);         
        }

        //Gets the number of lines in the file.
        int linecount = lineCountFile(storeCWDIn);
        linecount += 1;

        //An array to store all the lines in an array.
        char **array = (char**) malloc(linecount * sizeof(char*));
        char singleline[MAX_LINE];

        int i = 0;
        while (fgets(singleline, MAX_LINE, fileIN) != NULL) {
            array[i] = (char*) malloc (MAX_LINE * sizeof(char));
            if (i == (linecount - 1)) {
                singleline[strlen(singleline)] = '\n';
            }
            singleline[MAX_LINE] = '\0';
            strcpy(array[i], singleline);
            i++;
        }

        sortfile(array, linecount);

        for (i = 0; i < linecount; i++) {
            fprintf(fileOUT, "%s", array[i]);
        }

        fclose(fileIN);
        fclose(fileOUT);

    } else if (flag == 2) {
        
        tokenS = strtok(NULL, " ");

        //The two file pointers.
        FILE *fileIN, *fileOUT;

        //Storing the current working directory.
        char storeCWDIn[512];
        char storeCWDOut[512];

        getcwd(storeCWDIn, 512);
        strcat(storeCWDIn, "/");
        strcat(storeCWDIn, tokenS);
        
        tokenS = strtok(NULL, " ");
        tokenS = strtok(NULL, " ");

        printf("%s\n", storeCWDIn);

        getcwd(storeCWDOut, 512);
        strcat(storeCWDOut, "/");
        strcat(storeCWDOut, tokenS);

        printf("%s\n", storeCWDOut);

        fileIN = fopen(storeCWDIn, "r");

        if (fileIN == NULL) {
            printf("Error!");   
            exit(1);         
        }

        fileOUT = fopen(storeCWDOut, "w");

        if (fileOUT == NULL) {
            printf("Error!");   
            exit(1);         
        }

        //Gets the number of lines in the file.
        int linecount = lineCountFile(storeCWDIn);
        linecount += 1;

        //An array to store all the lines in an array.
        char **array = (char**) malloc(linecount * sizeof(char*));
        char singleline[MAX_LINE];

        int i = 0;
        while (fgets(singleline, MAX_LINE, fileIN) != NULL) {
            array[i] = (char*) malloc (MAX_LINE * sizeof(char));
            if (i == (linecount - 1)) {
                singleline[strlen(singleline)] = '\n';
            }
            singleline[MAX_LINE] = '\0';
            strcpy(array[i], singleline);
            i++;
        }

        sortfile(array, linecount);

        for (i = 0; i < linecount; i++) {
            fprintf(fileOUT, "%s", array[i]);
        }

        fclose(fileIN);
        fclose(fileOUT);

    } else if (flag == 4) {
        
        tokenS = strtok(NULL, " ");

        //The two file pointers.
        FILE *fileIN, *fileOUT;

        //Storing the current working directory.
        char storeCWDIn[512];
        char storeCWDOut[512];

        getcwd(storeCWDIn, 512);
        strcat(storeCWDIn, "/");
        strcat(storeCWDIn, tokenS);
        
        tokenS = strtok(NULL, " ");
        tokenS = strtok(NULL, " ");

        printf("%s\n", storeCWDIn);

        getcwd(storeCWDOut, 512);
        strcat(storeCWDOut, "/");
        strcat(storeCWDOut, tokenS);

        printf("%s\n", storeCWDOut);

        fileIN = fopen(storeCWDIn, "r");

        if (fileIN == NULL) {
            printf("Error!");   
            exit(1);         
        }

        fileOUT = fopen(storeCWDOut, "a");

        if (fileOUT == NULL) {
            printf("Error!");   
            exit(1);         
        }

        //Gets the number of lines in the file.
        int linecount = lineCountFile(storeCWDIn);
        linecount += 1;

        //An array to store all the lines in an array.
        char **array = (char**) malloc(linecount * sizeof(char*));
        char singleline[MAX_LINE];

        int i = 0;
        while (fgets(singleline, MAX_LINE, fileIN) != NULL) {
            array[i] = (char*) malloc (MAX_LINE * sizeof(char));
            if (i == (linecount - 1)) {
                singleline[strlen(singleline)] = '\n';
            }
            singleline[MAX_LINE] = '\0';
            strcpy(array[i], singleline);
            i++;
        }

        sortfile(array, linecount);

        for (i = 0; i < linecount; i++) {
            fprintf(fileOUT, "%s", array[i]);
        }

        fclose(fileIN);
        fclose(fileOUT);

    } else if (flag == 5) {
        
        tokenS = strtok(NULL, " ");
        tokenS = strtok(NULL, " ");

        //The two file pointers.
        FILE *fileIN, *fileOUT;

        //Storing the current working directory.
        char storeCWDIn[512];
        char storeCWDOut[512];

        getcwd(storeCWDIn, 512);
        strcat(storeCWDIn, "/");
        strcat(storeCWDIn, tokenS);
        
        tokenS = strtok(NULL, " ");
        tokenS = strtok(NULL, " ");

        printf("%s\n", storeCWDIn);

        getcwd(storeCWDOut, 512);
        strcat(storeCWDOut, "/");
        strcat(storeCWDOut, tokenS);

        printf("%s\n", storeCWDOut);

        fileIN = fopen(storeCWDIn, "r");

        if (fileIN == NULL) {
            printf("Error!");   
            exit(1);         
        }

        fileOUT = fopen(storeCWDOut, "a");

        if (fileOUT == NULL) {
            printf("Error!");   
            exit(1);         
        }

        //Gets the number of lines in the file.
        int linecount = lineCountFile(storeCWDIn);
        linecount += 1;

        //An array to store all the lines in an array.
        char **array = (char**) malloc(linecount * sizeof(char*));
        char singleline[MAX_LINE];

        int i = 0;
        while (fgets(singleline, MAX_LINE, fileIN) != NULL) {
            array[i] = (char*) malloc (MAX_LINE * sizeof(char));
            if (i == (linecount - 1)) {
                singleline[strlen(singleline)] = '\n';
            }
            singleline[MAX_LINE] = '\0';
            strcpy(array[i], singleline);
            i++;
        }

        sortfile(array, linecount);

        for (i = 0; i < linecount; i++) {
            fprintf(fileOUT, "%s", array[i]);
        }

        fclose(fileIN);
        fclose(fileOUT);

    }
}