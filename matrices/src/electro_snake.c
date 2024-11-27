#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m, int **result_matrix);
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);
void input(int ***matrix, int *n, int *m);
void output(int **matrix, int n, int m);
void free_matrix(int **matrix, int n);

int main() {
    int **matrix = NULL, **result = NULL;
    int n, m;

    input(&matrix, &n, &m);
    if (matrix == NULL || n <= 0 || m <= 0) {
        printf("n/a");
        return 0;
    }

    result = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        result[i] = (int *)malloc(m * sizeof(int));
    }

    sort_vertical(matrix, n, m, result);
    output(result, n, m);
    printf("\n\n");

    sort_horizontal(matrix, n, m, result);
    output(result, n, m);

    free_matrix(matrix, n);
    free_matrix(result, n);

    return 0;
}

void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int *temp = (int *)malloc(n * m * sizeof(int));
    int k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[k++] = matrix[i][j];
        }
    }

    for (int i = 0; i < n * m; i++) {
        for (int j = i + 1; j < n * m; j++) {
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    k = 0;
    for (int j = 0; j < m; j++) {
        if (j % 2 == 0) {
            for (int i = 0; i < n; i++) {
                result_matrix[i][j] = temp[k++];
            }
        } else {
            for (int i = n - 1; i >= 0; i--) {
                result_matrix[i][j] = temp[k++];
            }
        }
    }

    free(temp);
}

void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int *temp = (int *)malloc(n * m * sizeof(int));
    int k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[k++] = matrix[i][j];
        }
    }

    for (int i = 0; i < n * m; i++) {
        for (int j = i + 1; j < n * m; j++) {
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    k = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++) {
                result_matrix[i][j] = temp[k++];
            }
        } else {
            for (int j = m - 1; j >= 0; j--) {
                result_matrix[i][j] = temp[k++];
            }
        }
    }

    free(temp);
}

void input(int ***matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0 || (getchar() != '\n' && getchar() != EOF)) {
        *matrix = NULL;
        return;
    }

    *matrix = (int **)malloc(*n * sizeof(int *));
    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = (int *)malloc(*m * sizeof(int));
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &((*matrix)[i][j])) != 1) {
                *matrix = NULL;
                return;
            }
        }
    }
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }
}

void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
