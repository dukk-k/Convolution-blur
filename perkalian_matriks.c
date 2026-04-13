#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);

   
    int **A = (int**) malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        A[i] = (int*) malloc(m * sizeof(int));
    }

    
    int **B = (int**) malloc(m * sizeof(int*));
    for(int i = 0; i < m; i++) {
        B[i] = (int*) malloc(p * sizeof(int));
    }


    int **C = (int**) malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        C[i] = (int*) malloc(p * sizeof(int));
    }


    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &A[i][j]);
        }
    }


    for(int i = 0; i < m; i++) {
        for(int j = 0; j < p; j++) {
            scanf("%d", &B[i][j]);
        }
    }


    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            C[i][j] = 0;
        }
    }

   
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            for(int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

   
    for(int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

   
    for(int i = 0; i < m; i++) {
        free(B[i]);
    }
    free(B);

  
    for(int i = 0; i < n; i++) {
        free(C[i]);
    }
    free(C);

    return 0;
}