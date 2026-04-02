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
        int mid = left + right / 2;
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
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Ошибка: неверное количество записей\n");
        return 1;
    }

    Record *original = (Record*)malloc(n * sizeof(Record));
    if (!original) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%s %d %s", original[i].str, &original[i].num, original[i].data) != 3) {
            fprintf(stderr, "Ошибка ввода данных для записи %d\n", i+1);
            free(original);
            return 1;
        }
    }

    Record *sorted_case   = (Record*)malloc(n * sizeof(Record));
    Record *reverse_case  = (Record*)malloc(n * sizeof(Record));
    Record *unsorted_case = (Record*)malloc(n * sizeof(Record));
    if (!sorted_case || !reverse_case || !unsorted_case) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        free(original);
        return 1;
    }

    /*Таблица изначально упорядочен*/
    copy_table(sorted_case, original, n);
    counting_sort(sorted_case, n); 
    printf("\nТаблица изначально упорядочена \n");
    print_table(sorted_case, n);
    printf("==================");
    counting_sort(sorted_case, n);   
    print_table(sorted_case, n);

    /*Таблица в обратном порядке*/
    reverse_table(reverse_case, sorted_case, n);
    printf("\nТаблица в обратном порядке\n");
    print_table(reverse_case, n);
    printf("==================");
    counting_sort(reverse_case, n);
    print_table(reverse_case, n);

    /*Неупорядоченная таблица */
    copy_table(unsorted_case, original, n);
    printf("\nНеупорядоченная таблица\n");
    print_table(unsorted_case, n);
    printf("==================");
    counting_sort(unsorted_case, n);
    print_table(unsorted_case, n);


    printf("\nДвоичный поиск\n");
    printf("Ввод ключей (строка число):\n");
    char key_str[MAX_STR_LEN];
    int key_num;
    int key_count = 0;
    while (scanf("%s %d", key_str, &key_num) == 2) {
        key_count++;
        int idx = binary_search(unsorted_case, n, key_str, key_num);
        if (idx != -1) {
            printf("Ключ %d: (\"%s\", %d) найден -> ", key_count, key_str, key_num);
            print_record(&unsorted_case[idx], idx+1);
        } else {
            printf("Ключ %d: (\"%s\", %d) не найден\n", key_count, key_str, key_num);
        }
    }

    if (key_count == 0) {
        printf("Не было введено ни одного ключа для поиска.\n");
    }

    free(original);
    free(sorted_case);
    free(reverse_case);
    free(unsorted_case);
    return 0;
}