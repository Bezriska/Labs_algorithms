# include <stdio.h>
# include <string.h>
# include "tree.h"
# include "read.h"


int main() {
    
    Node* root = read(1);
    if (root == NULL) {
        printf("Дерево пустое или файл не найден\n");
        return 1;
    }

    for (int i = 0; i < 25; ++i) {
        char key[7];
        snprintf(key, sizeof(key), "k%d", i);
        root = avl_insert(key, (i + 1)*1.5, root);
    }

    root = avl_delete(root, "k10");
    root = avl_delete(root, "k11");


    double res = search("k9", root);
    printf("\nРезультат поиска по ключу 'k9': %lf\n", res);

    print_tree(root, NULL);



}