#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

int row1, col1, row2, col2;
int i, j, k;
int matrix1[1000][1000];
int matrix2[1000][1000];
int result1[1000][1000];
int result2[1000][1000];

typedef struct parameters {
    int row_x;
    int col_y;
} args;


void *multiply_element(void *para) {

    args p = *((args *) para);
    //args* p =para;
    for (k = 0; k < row2; k++) {

        result1[p.row_x][p.col_y] += matrix1[p.row_x][k] * matrix2[k][p.col_y];
        // result1[p->row_x][p->col_y]+=matrix1[p->row_x][k]*matrix2[k][p->col_y];

    }


    // printf("End Of thread \n");
}


void *multiply_row(void *para) {

    int i = *((int *) para);

    for (j = 0; j < col2; j++) {
        for (k = 0; k < row2; k++) {
            result2[i][j] += matrix1[i][k] * matrix2[k][j];


        }
    }

    // printf("End Of thread \n");
}


int main(int argc, char **argv) {
    clock_t time1, time2;
    //char fname[20];
    //printf("Enter file name .txt  \n");
    //scanf("%s",fname);
    FILE *input;
    if (argv[1] == 0)
        return 0;
    input = fopen(argv[1], "r");
    // input = fopen(fname, "r");
    FILE *output = fopen("output.txt", "w");
    if (input == NULL) {
        printf("file not exist \n");
        exit(1);
    } else if (output == NULL) {
        printf("failed to open and create file \n");
        exit(1);
    } else {

        fscanf(input, "%d", &row1);
        fscanf(input, "%d", &col1);

        for (i = 0; i < row1; i++) {
            for (j = 0; j < col1; j++) {
                fscanf(input, "%d", &matrix1[i][j]);

            }
        }

        fscanf(input, "%d", &row2);
        fscanf(input, "%d", &col2);

        if (col1 != row2) {
            printf("Multiplication of Matrix is not possible... calculation failed \n");
            fprintf(output, "Multiplication of Matrix is not possible... calculations failed !\n");
            printf("You can also see output in file (output.txt) \n");
            exit(1);
        }


        for (i = 0; i < row2; i++) {
            for (j = 0; j < col2; j++) {
                fscanf(input, "%d", &matrix2[i][j]);

            }
        }

        fclose(input);


        args p[row1 * col2];
        time1 = clock();

        pthread_t threads1[row1 * col2];
        int numberOfthread = 0;
        int ST;
        for (int i = 0; i < row1; i++) {
            for (j = 0; j < col2; j++) {
                p[numberOfthread].row_x = i;
                p[numberOfthread].col_y = j;

                ST = pthread_create(&threads1[numberOfthread], NULL, multiply_element, &p[numberOfthread]);


                if (ST != 0) {
                    exit(1);
                }
                numberOfthread++;

            }
        }
        for (i = 0; i < row1 * col2; i++)
            pthread_join(threads1[i], NULL);
        time1 = clock() - time1;
        double t_taken1 = ((double) time1) / CLOCKS_PER_SEC;


        fprintf(output, "By Element \n");
        for (i = 0; i < row1; i++) {
            for (j = 0; j < col2; j++) {
                printf("%d\t", result1[i][j]);
                fprintf(output, "%d\t", result1[i][j]);

            }
            printf("\n");
            fprintf(output, "\n");
        }
        printf("procedure1 takes[%f seconds to execute] \n", t_taken1);
        fprintf(output, "procedure1 takes [%f seconds to execute] \n", t_taken1);
        printf("\n");
        fprintf(output, "\n");



//second PROCEDURE :Multiplication by row ....................


        int ptr[row1];
        pthread_t threads2[row1];
        time2 = clock();


        for (i = 0; i < row1; i++) {
            ptr[i] = i;
            pthread_create(&threads2[i], NULL, multiply_row, &ptr[i]);
        }
        for (i = 0; i < row1; i++) {
            pthread_join(threads2[i], NULL);
        }
        time2 = clock() - time2;
        double t_taken2 = ((double) time2) / CLOCKS_PER_SEC;

        fprintf(output, "By Row\n");
        for (i = 0; i < row1; i++) {
            for (j = 0; j < col2; j++) {
                printf("%d\t", result2[i][j]);
                fprintf(output, "%d\t", result2[i][j]);
            }
            printf("\n");
            fprintf(output, "\n");
        }
        printf("procedure2 takes  [%f seconds to execute] \n", t_taken2);
        fprintf(output, "procedure2 takes [%f seconds to execute] \n", t_taken2);

    }
    printf("You can also see the calculations results in file (output.txt) \n");

    return 0;

}
