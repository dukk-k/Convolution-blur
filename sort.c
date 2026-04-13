#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void bubble_sort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        float temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertion_sort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void print_array(float arr[], int n) {
    for (int i = 0; i < n; i++) printf("%.2f ", arr[i]);
    printf("\n");
}

double hitung_waktu(clock_t mulai, clock_t selesai) {
    return (double)(selesai - mulai) / CLOCKS_PER_SEC;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Penggunaan: %s <ukuran_problem>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    float *original = (float *) malloc(n * sizeof(float));
    float *temp     = (float *) malloc(n * sizeof(float));

    if (!original || !temp) {
        printf("Gagal alokasi memori!\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        original[i] = ((float) rand() / (float)(RAND_MAX)) * 100.0;
    }

    printf("Ukuran array : %d\n", n);
    printf("--------------------------------------\n");

    if (n <= 20) {
        printf("Data awal    : ");
        print_array(original, n);
    }

    clock_t mulai, selesai;

    //bubble sort
    memcpy(temp, original, n * sizeof(float));
    mulai = clock();
    bubble_sort(temp, n);
    selesai = clock();
    double waktu_bubble = hitung_waktu(mulai, selesai);

    if (n <= 20) {
        printf("\nBubble Sort  : ");
        print_array(temp, n);
    }
    printf("Waktu Bubble Sort    : %.6f detik\n", waktu_bubble);

    //selection sort
    memcpy(temp, original, n * sizeof(float));
    mulai = clock();
    selection_sort(temp, n);
    selesai = clock();
    double waktu_selection = hitung_waktu(mulai, selesai);

    if (n <= 20) {
        printf("\nSelection Sort: ");
        print_array(temp, n);
    }
    printf("Waktu Selection Sort : %.6f detik\n", waktu_selection);

    //insertion sort
    memcpy(temp, original, n * sizeof(float));
    mulai = clock();
    insertion_sort(temp, n);
    selesai = clock();
    double waktu_insertion = hitung_waktu(mulai, selesai);

    if (n <= 20) {
        printf("\nInsertion Sort: ");
        print_array(temp, n);
    }
    printf("Waktu Insertion Sort : %.6f detik\n", waktu_insertion);

    printf("--------------------------------------\n");

    free(original);
    free(temp);
    return 0;
}