# include <stdio.h>
# include <string.h>
# include <math.h>
# include "tree.h"
# include "read.h"


static void print_menu() {
    printf("АВЛ-дерево — меню\n");
    printf("1 — Вставить элемент\n");
    printf("2 — Удалить элемент\n");
    printf("3 — Печать дерева\n");
    printf("4 — Поиск по ключу\n");
    printf("0 — Выход\n");
    printf("Команда: ");
}


int main() {
    // Обрабатываем файл команд
    read(1);

    // Начинаем с пустого дерева для cli
    Node* root = NULL;

    int cmd;
    while (1) {
        print_menu();

        if (scanf("%d", &cmd) != 1) {
            // Сбрасываем буфер при некорректном вводе
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Ошибка: введите число от 0 до 4\n");
            continue;
        }
        // Сбрасываем '\n' после успешного чтения
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (cmd == 0) {
            printf("Выход\n");
            break;
        }

        if (validate_cmd(cmd) != 0) {
            printf("Ошибка: неизвестная команда '%d'\n", cmd);
            continue;
        }

        // Вставка
        if (cmd == 1) {
            char key[7];
            char val_str[16];
            printf("Ключ (латиница, до 6 символов): ");
            scanf("%6s", key);
            int klen = (int)strlen(key);
            int kerr = validate_key(key, klen);
            if (kerr == 1) {printf("Ошибка: пустой ключ\n"); continue;}
            if (kerr == 2) {printf("Ошибка: ключ длиннее 6 символов\n"); continue;}
            if (kerr == 3) {printf("Ошибка: недопустимые символы в ключе\n"); continue;}

            printf("Значение (число): ");
            scanf("%15s", val_str);
            int vlen = (int)strlen(val_str);
            int verr = validate_value(val_str, vlen);
            if (verr == 1) {printf("Ошибка: пустое значение\n"); continue;}
            if (verr == 2) {printf("Ошибка: недопустимый формат числа\n"); continue;}

            double value = strtod(val_str, NULL);
            root = avl_insert(key, value, root);
            printf("Вставлен: %s = %g\n", key, value);
            printf("\n");
        }

        // Удаление
        if (cmd == 2) {
            char key[7];
            printf("Ключ для удаления: ");
            scanf("%6s", key);
            int klen = (int)strlen(key);
            int kerr = validate_key(key, klen);
            if (kerr == 1) {printf("Ошибка: пустой ключ\n"); continue;}
            if (kerr == 2) {printf("Ошибка: ключ длиннее 6 символов\n"); continue;}
            if (kerr == 3) {printf("Ошибка: недопустимые символы в ключе\n"); continue;}

            if (isnan(search(key, root))) {
                printf("Ошибка: элемент с ключом '%s' не найден\n", key);
                continue;
            }
            root = avl_delete(root, key);
            printf("Удалён: %s\n", key);
            printf("\n");
        }

        // Печать дерева
        if (cmd == 3) {
            if (root == NULL) {
                printf("Дерево пустое\n");
            } else {
                print_tree(root, NULL);
            }
        }

        // Поиск
        if (cmd == 4) {
            char key[7];
            printf("Ключ для поиска: ");
            scanf("%6s", key);
            int klen = (int)strlen(key);
            int kerr = validate_key(key, klen);
            if (kerr == 1) {printf("Ошибка: пустой ключ\n"); continue;}
            if (kerr == 2) {printf("Ошибка: ключ длиннее 6 символов\n"); continue;}
            if (kerr == 3) {printf("Ошибка: недопустимые символы в ключе\n"); continue;}

            double data = search(key, root);
            if (isnan(data)) {
                printf("Элемент с ключом '%s' не найден\n", key);
            } else {
                printf("Найден: %s = %g\n", key, data);
            }
            printf("\n");
        }
    }

    return 0;
}
