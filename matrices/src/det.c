#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n, int m);
void input(double ***matrix, int *n, int *m);
void output(double det);
void free_matrix(double **matrix, int n);

int main() {
    double **matrix = NULL;
    int n, m;
    input(&matrix, &n, &m);
    if (n == 0 || m == 0 || matrix == NULL) {
        printf("n/a");
        return 1;
    }
    double determinant = det(matrix, n, m);
    output(determinant);
    free_matrix(matrix, n);  // Освобождение памяти после использования
    return 0;
}

double det(double **matrix, int n, int m) {
    if (n != m) {
        return 0;  // Определитель можно вычислить только для квадратных матриц
    }

    if (n == 1) {
        return matrix[0][0];
    }

    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    double determ = 0;
    for (int x = 0; x < n; x++) {
        double **submatrix = (double **)malloc((n - 1) * sizeof(double *));
        for (int i = 0; i < n - 1; i++) {
            submatrix[i] = (double *)malloc((n - 1) * sizeof(double));
        }

        for (int i = 1; i < n; i++) {
            int subi = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) continue;  // Пропуск столбца x
                submatrix[i - 1][subi] = matrix[i][j];
                subi++;
            }
        }

        double sub_det = det(submatrix, n - 1, n - 1);
        if (x % 2 == 0) {
            determ += matrix[0][x] * sub_det;
        } else {
            determ -= matrix[0][x] * sub_det;
        }

        for (int i = 0; i < n - 1; i++) {
            free(submatrix[i]);
        }
        free(submatrix);
    }

    return determ;
}

void input(double ***matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n != *m || *n <= 0 || (getchar() != '\n' && getchar() != EOF)) {
        *n = *m = 0;
        *matrix = NULL;
        return;
    }
    *matrix = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = (double *)malloc(*m * sizeof(double));
        for (int j = 0; j < *m; j++) {
            if (scanf("%lf", &(*matrix)[i][j]) != 1) {
                *n = *m = 0;
                for (int k = 0; k <= i; k++) {
                    free((*matrix)[k]);
                }
                free(*matrix);
                *matrix = NULL;
                return;
            }
        }
    }
}

void output(double det) {
    if (det == -0.0) {
        det = 0.0;
    }
    printf("%.6f", det);
}

void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
