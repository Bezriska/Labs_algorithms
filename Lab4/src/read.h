#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tree.h"


// Проверка команды: допустимы только 1, 2, 3, 4
int validate_cmd(int cmd) {
    return (cmd >= 1 && cmd <= 4) ? 0 : 1;
}

// Проверка строки со значением
int validate_value(char* val, int val_len) {
    if (val_len == 0) return 1;
    int dot_count = 0;
    for (int i = 0; i < val_len; ++i) {
        if (i == 0 && val[i] == '-') continue; // допустимый минус
        if (val[i] == '.') { ++dot_count; continue; } // десятичная точка
        if (!isdigit((unsigned char)val[i])) return 2;
    }
    if (dot_count > 1) return 2; // больше одной точки
    return 0;
}

// Возвращает 0 если ключ валиден, иначе код ошибки
int validate_key(char* key, int key_len) {
    if (key_len == 0)  return 1;
    if (key_len >= 7)  return 2;
    for (int i = 0; i < key_len; ++i)
        if (!isalpha((unsigned char)key[i])) return 3;
    return 0;
}


char* zip_str(char* s) {
    size_t len;
    len = strlen(s);
    int count = 0;
    for (int i = 0; i < len; ++i) {
        if (s[i] != '\0') ++count;
    }

    char* out = (char*)malloc(sizeof(char) * (count + 1));
    strcpy(out, s);
    return out;
}


Node* read(int output) {
    if (!(output == 1 || output == 0)) {
        printf("Значение output должно быть 1 или 0");
        return NULL;
    }
    
    
    FILE* fp = fopen("../DATA/test.txt", "r");
    if (!fp) {
        printf("Невозможно открыть файл с командами\n");
        return NULL;
    }

    FILE* fp1 = NULL;
    if (output) {
        fp1 = fopen("../DATA/test_out.txt", "a");
        fprintf(fp1, "\n\n=== Вызов функции read ===\n\n");
        if (!fp1) {
            printf("Невозможно открыть файл для вывода\n");
            fclose(fp);
            return NULL;
        }
    }


    char* line = NULL;
    size_t len = 0;
    Node* root = NULL;
    while (getline(&line, &len, fp) != -1) {
        int cmd = line[0] - '0';

        if (validate_cmd(cmd) != 0) {
            printf("Ошибка: неизвестная команда '%c'\n", line[0]);
            if (output) {
                fprintf(fp1, "Команда: %s", line);
                fprintf(fp1, "Ошибка: неизвестная команда '%c'\n\n", line[0]);
            }
            continue;
        }
        
        // Добавляем элемент в дерево
        if (cmd == 1) {
            // Пропускаем пробел
            int start = 2;
            int i = 0;
            char key_temp[7] = {'\0'};
            while (line[start] != ' ') {
                key_temp[i] = line[start];
                ++start;
                ++i;
            }

            
            int err = validate_key(key_temp, i);
            if (err == 1) { printf("Ошибка вставки: пустой ключ\n"); if (output) { fprintf(fp1, "Команда: %s", line); fprintf(fp1, "Ошибка вставки: пустой ключ\n\n"); } continue; }
            if (err == 2) { printf("Ошибка вставки: ключ длиннее 6 символов\n"); if (output) { fprintf(fp1, "Команда: %s", line); fprintf(fp1, "Ошибка вставки: ключ длиннее 6 символов\n\n"); } continue; }
            if (err == 3) { printf("Ошибка вставки: недопустимые символы в ключе\n"); if (output) { fprintf(fp1, "Команда: %s", line); fprintf(fp1, "Ошибка вставки: недопустимые символы в ключе\n\n"); } continue; }

            char* key = zip_str(key_temp);

            // Пропускаем пробел
            ++start;
            i = 0;
            char value_temp[8] = {0};
            while(line[start] != '\n' && line[start] != '\0') {
                value_temp[i] = line[start];
                ++start;
                ++i;
            }

            int verr = validate_value(value_temp, i);
            if (verr == 1) { printf("Ошибка вставки: пустое значение\n"); if (output) { fprintf(fp1, "Команда: %s", line); fprintf(fp1, "Ошибка вставки: пустое значение\n\n"); } free(key); continue; }
            if (verr == 2) { printf("Ошибка вставки: недопустимый формат значения\n"); if (output) { fprintf(fp1, "Команда: %s", line); fprintf(fp1, "Ошибка вставки: недопустимый формат значения\n\n"); } free(key); continue; }

            double value = strtod(value_temp, NULL);

            root = avl_insert(key, value, root);
            if (output) {
                fprintf(fp1, "Команда: %s", line);
                fprintf(fp1, "Выполнена вставка элемента с ключом: %s и значением: %lf\n\n", key, value);
            }
            free(key);
        }
        
        // Удаляем элемент из дерева
        if (cmd == 2) {
            int start = 2;
            int i = 0;
            char key_temp[7] = {'\0'};
            while (line[start] != ' ' && line[start] != '\n' && line[start] != '\0') {
                key_temp[i] = line[start];
                ++start;
                ++i;
            }

            int err = validate_key(key_temp, i);
            if (err == 1) { printf("Ошибка удаления: пустой ключ\n"); if (output) { fprintf(fp1, "Команда: %s", line); fprintf(fp1, "Ошибка удаления: пустой ключ\n\n"); } continue; }
            if (err == 2) { printf("Ошибка удаления: ключ длиннее 6 символов\n"); if (output) { fprintf(fp1, "Команда: %s", line); fprintf(fp1, "Ошибка удаления: ключ длиннее 6 символов\n\n"); } continue; }
            if (err == 3) { printf("Ошибка удаления: недопустимые символы в ключе\n"); if (output) { fprintf(fp1, "Команда: %s", line); fprintf(fp1, "Ошибка удаления: недопустимые символы в ключе\n\n"); } continue; }

            char* key = zip_str(key_temp);

            if (isnan(search(key, root))) {
                printf("Ошибка удаления: элемент с ключом '%s' не найден\n", key);
                if (output) {
                    fprintf(fp1, "Команда: %s", line);
                    fprintf(fp1, "Ошибка удаления: элемент с ключом '%s' не найден\n\n", key);
                }
                free(key);
                continue;
            }

            root = avl_delete(root, key);
            printf("Удален элемент по ключу: %s\n", key);

            if (output) {
                fprintf(fp1, "Команда: %s", line);
                fprintf(fp1, "Выполнено удаление элемента с ключом: %s\n\n", key);
            }
            free(key);
        }

        // Поиск элемента по ключу
        if (cmd == 3) {
            int start = 2;
            int i = 0;
            char key_temp[7] = {'\0'};
            while (line[start] != ' ' && line[start] != '\n' && line[start] != '\0') {
                key_temp[i] = line[start];
                ++start;
                ++i;
            }

            int err = validate_key(key_temp, i);
            if (err == 1) { printf("Ошибка поиска: пустой ключ\n"); if (output) { fprintf(fp1, "Команда: %s\n", line); fprintf(fp1, "Ошибка поиска: пустой ключ\n\n"); } continue; }
            if (err == 2) { printf("Ошибка поиска: ключ длиннее 6 символов\n"); if (output) { fprintf(fp1, "Команда: %s\n", line); fprintf(fp1, "Ошибка поиска: ключ длиннее 6 символов\n\n"); } continue; }
            if (err == 3) { printf("Ошибка поиска: недопустимые символы в ключе\n"); if (output) { fprintf(fp1, "Команда: %s\n", line); fprintf(fp1, "Ошибка поиска: недопустимые символы в ключе\n\n"); } continue; }

            char* key = zip_str(key_temp);
            double data = search(key, root);

            if (isnan(data)) {
                printf("Элемент не найден или нет ключа\n");
                if (output) {
                    fprintf(fp1, "Команда: %s\n", line);
                    fprintf(fp1, "Элемент не найден или нет ключа\n\n");
                }
                continue;
            }
            printf("Найден элемент, ключ: %s, значение: %lf\n", key, data);

            if (output) {
                fprintf(fp1, "Команда: %s", line);
                fprintf(fp1, "Выполнен поиск элемента по ключу: %s, получено значение: %lf\n\n", key, data);
            }
            free(key);
        }

        // Печать дерева
        if (cmd == 4) {
            if (output) {
                fprintf(fp1, "Команда: %s\n", line);
                fprintf(fp1, "Вывод дерева:\n");
            }
            print_tree(root, fp1);
        }
    }
    free(line);
    fclose(fp);
    if (fp1) fclose(fp1);
    return root;


}




































#endif