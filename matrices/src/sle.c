#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-6

void input(double ***matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *m != *n + 1 || (getchar() != '\n' && getchar() != EOF)) {
        printf("n/a");
        return;
    }

    *matrix = (double **)malloc(*n * sizeof(double *));
    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = (double *)malloc(*m * sizeof(double));
        for (int j = 0; j < *m; j++) {
            if (scanf("%lf", &(*matrix)[i][j]) != 1) {
                printf("n/a");
                return;
            }
        }
    }
}

void output_roots(double *roots, int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%.6f", roots[i]);
    }
    printf("\n");
}

int solve_gauss(double **matrix, int n, double *roots) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        int max_row = i;
        for (k = i + 1; k < n; k++) {
            if (fabs(matrix[k][i]) > fabs(matrix[max_row][i])) {
                max_row = k;
            }
        }
        if (fabs(matrix[max_row][i]) < EPS) {
            return 0;
        }
        if (max_row != i) {
            double *temp = matrix[i];
            matrix[i] = matrix[max_row];
            matrix[max_row] = temp;
        }

        for (j = i + 1; j < n; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (k = i; k < n + 1; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    for (i = n - 1; i >= 0; i--) {
        roots[i] = matrix[i][n] / matrix[i][i];
        for (j = i - 1; j >= 0; j--) {
            matrix[j][n] -= matrix[j][i] * roots[i];
        }
    }

    return 1;
}

void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    double **matrix;
    int n, m;
    double *roots;

    input(&matrix, &n, &m);
    roots = (double *)malloc(n * sizeof(double));

    if (solve_gauss(matrix, n, roots)) {
        output_roots(roots, n);
    } else {
        printf("n/a");
    }

    free(roots);
    free_matrix(matrix, n);

    return 0;
}
