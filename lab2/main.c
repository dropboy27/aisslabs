#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 50
#define MAX_DATA_LEN 100

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
    printf("Таблица:\n");
    for (int i = 0; i < n; i++) {
        printf("%2d: (\"%s\", %d) -> %s\n", i+1, arr[i].str, arr[i].num, arr[i].data);
    }
}
void counting_sort(Record *arr, int n) {
    if (n <= 1) return;
    int *count = (int*)malloc(n * sizeof(int));
    Record *temp = (Record*)malloc(n * sizeof(Record));
    if (!count || !temp) {
        fprintf(stderr, "Ошибка выделения памяти\n");
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

int main() {
    int n;
    printf("Введите количество записей: ");
    scanf("%d", &n);
    getchar();

    Record *table = (Record*)malloc(n * sizeof(Record));
    if (!table) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    printf("Введите %d записей в формате: строка_ключа целое_число данные\n", n);
    for (int i = 0; i < n; i++) {
        char line[256];
        if (!fgets(line, sizeof(line), stdin)) {
            fprintf(stderr, "Ошибка ввода записи %d\n", i+1);
            free(table);
            return 1;
        }
        char str_part[MAX_STR_LEN];
        int num_part;
        char data_part[MAX_DATA_LEN];
        int items = sscanf(line, "%s %d %[^\n]", str_part, &num_part, data_part);
        if (items < 2) {
            fprintf(stderr, "Ошибка: в записи %d нет строки и числа\n", i+1);
            free(table);
            return 1;
        }
        strcpy(table[i].str, str_part);
        table[i].num = num_part;
        if (items == 2) {
            table[i].data[0] = '\0';
        } else {
            strcpy(table[i].data, data_part);
        }
    }
    printf("\nИсходная таблица\n");
    print_table(table, n);

    counting_sort(table, n);
    printf("\nОтсортированная таблица \n");
    print_table(table, n);

    printf("\nПоиск по ключу\n");
    printf("Введите ключи для поиска (строка и число, для выхода введите пустую строку):\n");
    getchar();
    while (1) {
        char search_str[MAX_STR_LEN];
        int search_num;
        char line[256];

        printf("Ключ (строка число): ");
        if (!fgets(line, sizeof(line), stdin)) break;

        if (line[0] == '\n') break;


        if (sscanf(line, "%s %d", search_str, &search_num) != 2) {
            printf("Ошибка формата ключа. Попробуйте ещё раз.\n");
            continue;
        }

        int idx = binary_search(table, n, search_str, search_num);
        if (idx != -1) {
            printf("Найдено: ");
            print_record(&table[idx], idx+1);
        } else {
            printf("Запись с ключом \"%s %d\" не найдена.\n", search_str, search_num);
        }
    }

    free(table);
    return 0;
}
