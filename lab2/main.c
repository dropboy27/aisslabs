#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 50
#define MAX_DATA_LEN 100
#define N 8

typedef struct {
    char str[MAX_STR_LEN];
    int num;
    char data[MAX_DATA_LEN];
} Record;

int compare_keys(Record *a, Record *b) {
    int cmp = strcmp(a->str, b->str);
    if (cmp != 0) return cmp;
    if (a->num < b->num) return -1;
    if (a->num > b->num) return 1;
    return 0;
}

void print_record(Record *r, int index) {
    printf("%2d: (\"%s\", %d) -> %s\n", index, r->str, r->num, r->data);
}

void print_table(Record *arr, int n) {
    printf("Table:\n");
    for (int i = 0; i < n; i++) {
        printf("%2d: (\"%s\", %d) -> %s\n", i+1, arr[i].str, arr[i].num, arr[i].data);
    }
}

void counting_sort(Record *arr, int n) {
    if (n <= 1) return;
    int *count = (int*)malloc(n * sizeof(int));
    Record *temp = (Record*)malloc(n * sizeof(Record));
    if (!count || !temp) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) count[i] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int cmp = compare_keys(&arr[j], &arr[i]);
            if (cmp < 0) {
                count[i]++;
            } else if (cmp == 0 && j < i) {
                count[i]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        temp[count[i]] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
    free(count);
    free(temp);
}

int binary_search(Record *arr, int n, char *key_str, int key_num) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(arr[mid].str, key_str);
        if (cmp < 0) {
            left = mid + 1;
        } else if (cmp > 0) {
            right = mid - 1;
        } else {
            if (arr[mid].num < key_num) {
                left = mid + 1;
            } else if (arr[mid].num > key_num) {
                right = mid - 1;
            } else {
                return mid;
            }
        }
    }
    return -1;
}

void copy_table(Record *dest, Record *src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void reverse_table(Record *dest, Record *src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[n - 1 - i];
    }
}

int main() {
    Record table_original[N] = {
            {"alpha", 15, "Data A"},
            {"gamma", 7,  "Data G"},
            {"beta",  22, "Data B"},
            {"alpha", 10, "Data A2"},
            {"delta", 5,  "Data D"},
            {"gamma", 20, "Data G2"},
            {"beta",  10, "Data B2"},
            {"alpha", 30, "Data A3"}
    };

    printf("Initial (unsorted) table\n");
    print_table(table_original, N);

    Record *sorted   = (Record*)malloc(N * sizeof(Record));
    Record *reverse  = (Record*)malloc(N * sizeof(Record));
    Record *unsorted = (Record*)malloc(N * sizeof(Record));
    if (!sorted || !reverse || !unsorted) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    copy_table(sorted, table_original, N);
    counting_sort(sorted, N);
    printf("\nCase 1: table initially sorted in ascending order\n");
    printf("Initial state:\n");
    print_table(sorted, N);
    counting_sort(sorted, N);
    printf("After sorting:\n");
    print_table(sorted, N);

    reverse_table(reverse, sorted, N);
    printf("\nCase 2: table initially sorted in descending order\n");
    printf("Initial state (reverse order):\n");
    print_table(reverse, N);
    counting_sort(reverse, N);
    printf("After sorting:\n");
    print_table(reverse, N);

    copy_table(unsorted, table_original, N);
    printf("\nCase 3: table unsorted (original)\n");
    printf("Initial state:\n");
    print_table(unsorted, N);
    counting_sort(unsorted, N);
    printf("After sorting:\n");
    print_table(unsorted, N);

    printf("\nBinary search automatic check\n");
    printf("Searching for existing and missing keys:\n");

    if (N > 0) {
        int idx = binary_search(unsorted, N, unsorted[0].str, unsorted[0].num);
        printf("Key (\"%s\", %d): ", unsorted[0].str, unsorted[0].num);
        if (idx != -1) {
            print_record(&unsorted[idx], idx+1);
        } else {
            printf("not found\n");
        }

        idx = binary_search(unsorted, N, unsorted[N-1].str, unsorted[N-1].num);
        printf("Key (\"%s\", %d): ", unsorted[N-1].str, unsorted[N-1].num);
        if (idx != -1) {
            print_record(&unsorted[idx], idx+1);
        } else {
            printf("not found\n");
        }

        if (N > 1) {
            int mid = N / 2;
            idx = binary_search(unsorted, N, unsorted[mid].str, unsorted[mid].num);
            printf("Key (\"%s\", %d): ", unsorted[mid].str, unsorted[mid].num);
            if (idx != -1) {
                print_record(&unsorted[idx], idx+1);
            } else {
                printf("not found\n");
            }
        }

        idx = binary_search(unsorted, N, "ZZZ", 999999);
        printf("Key (\"ZZZ\", 999999): ");
        if (idx != -1) {
            print_record(&unsorted[idx], idx+1);
        } else {
            printf("not found\n");
        }
    }

    free(sorted);
    free(reverse);
    free(unsorted);
    return 0;
}