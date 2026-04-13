#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** alloc_m(int n) {
    int** m = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        m[i] = (int*)malloc(n * sizeof(int));
    return m;
}


void free_m(int** m, int n) {
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}


void init_rand(int** m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = rand() % 10;
}


void add_m(int** A, int** B, int** hasil, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            hasil[i][j] = A[i][j] + B[i][j];
}


void sub_m(int** A, int** B, int** hasil, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            hasil[i][j] = A[i][j] - B[i][j];
}


void print_m(int** m, int n, const char* nama) {
    printf("Matriks %s:\n", nama);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d", m[i][j]);
        printf("\n");
    }
    printf("\n");
}


void strassen(int** A, int** B, int** C, int n) {

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;

    int** A00 = alloc_m(half); int** A01 = alloc_m(half);
    int** A10 = alloc_m(half); int** A11 = alloc_m(half);
    int** B00 = alloc_m(half); int** B01 = alloc_m(half);
    int** B10 = alloc_m(half); int** B11 = alloc_m(half);
    int** m1  = alloc_m(half); int** m2  = alloc_m(half);
    int** m3  = alloc_m(half); int** m4  = alloc_m(half);
    int** m5  = alloc_m(half); int** m6  = alloc_m(half);
    int** m7  = alloc_m(half);
    int** T1  = alloc_m(half); int** T2  = alloc_m(half);

    // DIVIDE: pecah A dan B menjadi sub-matriks
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A00[i][j] = A[i][j];
            A01[i][j] = A[i][j + half];
            A10[i][j] = A[i + half][j];
            A11[i][j] = A[i + half][j + half];

            B00[i][j] = B[i][j];
            B01[i][j] = B[i][j + half];
            B10[i][j] = B[i + half][j];
            B11[i][j] = B[i + half][j + half];
        }
    }

    // REKURSI: hitung m1-m7
    add_m(A00, A11, T1, half); 
    add_m(B00, B11, T2, half);
    strassen(T1, T2, m1, half);                             // m1 = (A00+A11)(B00+B11)

    add_m(A10, A11, T1, half);
    strassen(T1, B00, m2, half);                            // m2 = (A10+A11)(B00)

    sub_m(B01, B11, T2, half);
    strassen(A00, T2, m3, half);                            // m3 = (A00)(B01-B11)

    sub_m(B10, B00, T2, half);
    strassen(A11, T2, m4, half);                            // m4 = (A11)(B10-B00)

    add_m(A00, A01, T1, half);
    strassen(T1, B11, m5, half);                            // m5 = (A00+A01)(B11)

    sub_m(A10, A00, T1, half); 
    add_m(B00, B01, T2, half);
    strassen(T1, T2, m6, half);                             // m6 = (A10-A00)(B00+B01)

    sub_m(A01, A11, T1, half); 
    add_m(B10, B11, T2, half);
    strassen(T1, T2, m7, half);                             // m7 = (A01-A11)(B10+B11)

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j]               = m1[i][j] + m4[i][j] - m5[i][j] + m7[i][j]; // C00
            C[i][j + half]        = m3[i][j] + m5[i][j];                          // C01
            C[i + half][j]        = m2[i][j] + m4[i][j];                          // C10
            C[i + half][j + half] = m1[i][j] - m2[i][j] + m3[i][j] + m6[i][j];  // C11
        }
    }

    free_m(A00, half); free_m(A01, half);
    free_m(A10, half); free_m(A11, half);
    free_m(B00, half); free_m(B01, half);
    free_m(B10, half); free_m(B11, half);
    free_m(m1, half);  free_m(m2, half);
    free_m(m3, half);  free_m(m4, half);
    free_m(m5, half);  free_m(m6, half);
    free_m(m7, half);
    free_m(T1, half);  free_m(T2, half);
}


int main() {
    srand(time(NULL));

    int n = 4; 

    int** A = alloc_m(n);
    int** B = alloc_m(n);
    int** C = alloc_m(n);

    init_rand(A, n);
    init_rand(B, n);

    strassen(A, B, C, n);

    print_m(A, n, "A");
    print_m(B, n, "B");
    print_m(C, n, "C (Hasil Strassen)");

    free_m(A, n);
    free_m(B, n);
    free_m(C, n);

    return 0;
}