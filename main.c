#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t ns[] = { 10, /* TODO: fill in "n" i.e. instance sizes */ };

void fill_increasing(int *t, size_t n) {
    // TODO: implement
}

void fill_decreasing(int *t, size_t n) {
    // TODO: implement
}

void fill_vshape(int *t, size_t n) {
    // TODO: implement
}

void selection_sort(int *t, size_t n) {
    // TODO: implement
}

void insertion_sort(int *t, size_t n) {
    // TODO: implement
}

void quick_sort(int *t, size_t n) {
    // TODO: implement
}

void heap_sort(int *t, size_t n) {
    // TODO
}

void fill_random(int *t, size_t n) {
    for (size_t i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, size_t n) {
    return;
}

void is_increasing(int *t, size_t n) {
    for (size_t i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, size_t n) {
    for (size_t i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, size_t n) {
    if (n % 2 == 0) {
        // n is even
        for (size_t i = 1; i < (n / 2); i++) {
            assert(t[i] < t[i - 1]);
        }
        for (size_t i = (n / 2) + 1; i < n; i++) {
            assert(t[i] > t[i - 1]);
        }
    } else {
        // n is odd
        for (size_t i = 1; i <= (n / 2); i++) {
            assert(t[i] < t[i - 1]);
        }
        for (size_t i = (n / 2) + 2; i < n; i++) {
            assert(t[i] > t[i - 1]);
        }
    }
}

void is_sorted(int *t, size_t n) {
    for (size_t i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, size_t) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, size_t) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, size_t) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "Selection Sort", "Insertion Sort", "Quick Sort", "Heap Sort" };

int main() {
    for (int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, size_t) = sort_functions[i];
        double times[sizeof(fill_functions) / sizeof(*fill_functions)];

        for (int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, size_t) = fill_functions[j];
            void (*check)(int *, size_t) = check_functions[j];

            for (size_t k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                size_t n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fprintf(stderr, "Filling data using generator: %s\n", fill_names[j]);
                fill(t, n);
                check(t, n);

                fprintf(stderr, "Sorting with: %s\n", sort_names[i]);
                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                times[j] = (double)(end - begin) / (double) CLOCKS_PER_SEC;
                free(t);
            }
        }
    }
    return 0;
}