#include <stdio.h>
#include <stdlib.h>
struct Node { //Полями структуры могут быть любые объявленные типы, кроме самой структуры этого же типа, но можно хранить указатель на структуру этого типа
    int val; 
    struct Node *left;
    struct Node *right;
};

struct Node * Insert(struct Node * tree, int x); 
struct Node *Minimum(struct Node *tree); 
struct Node *Search(struct Node *tree, int k);
struct Node *parent_search(struct Node *tree, struct Node *Search); 
void Transplant(struct Node *tree, struct Node *current, struct Node *changeTo);
void Erase(struct Node *tree, struct Node *Find);
void InOrder(struct Node *tree);
void tree_destroy(struct Node * tree);

int main() {
    struct Node * tree = NULL;
    int x = 0;
    printf("fill a binary tree\nType 0 to stop : \n");
    scanf("%d", &x);
    while (x != 0) {
        tree = Insert(tree, x);
        scanf("%d", &x);
    }
    InOrder(tree);
    printf("\n");
    printf("Type element you want to erase:");
    int k = 0;
    scanf("%d", &k); // элемент который удаляем
    printf("\n");
    struct Node *Find = Search(tree, k);
    Erase(tree, Find);
    InOrder(tree);
    tree_destroy(tree);
    
    return 0;
}



struct Node * Insert(struct Node * tree, int x) {//рекурсивная реализация функции, которая вставляет элемент
    if(tree == NULL) { //если нет дерева
        struct Node * tree = (struct Node *)malloc(sizeof(struct Node)); //выделяем память под вставляемый элемент
        tree->val = x; //значением корня делаем вставляемый элемент
        tree->left = NULL; 
        tree->right = NULL;
        return tree;
    }
    if(x < tree->val) {
        tree->left = Insert(tree->left, x);
        return tree; 
    }
    if(x > tree->val) {
        tree->right = Insert(tree->right, x);
        return tree;
    }
    return tree;
}

struct Node *Minimum(struct Node *tree) { // рекурсивная функция нахождение минимального - самого левого
    if (tree->left == NULL) {
        return tree;
    }
    return Minimum(tree->left);
}

struct Node* Search(struct Node *tree, int k) { //функция поиска элемента
    if ((tree == NULL) || (k == tree->val)) { //возвращает корень если его нет или значение искомого это значение корня
        return tree;
    } 
    if (k < tree->val) { //если значение меньше значения корня, идем в левое поддерево 
        return Search(tree->left, k);
    }
    else {
        return Search(tree->right, k); //иначе идем в правое поддерево
    }
}
struct Node *parent_search(struct Node *tree, struct Node *Search) {

    if ((tree->right == Search) || ((tree->left) == Search)) {
        return tree; //если возвращаемое значение search это правый или левый потомок корня то возвращаем корень
    }
    else {
        if (tree->val < Search->val) {
            parent_search(tree->right, Search);
        }
        else {
            parent_search(tree->left, Search);
        }
    }
}

void Transplant(struct Node *tree, struct Node *current, struct Node *changeTo) { //является функцией, которая привязывает указатели на след.элемент/родителя
    struct Node *current_parent = parent_search(tree, current); //получаем структуру родителя элемента который надо заменить(current) и на что надо заменить (changeto)
    struct Node *changeto_parent = parent_search(tree, changeTo);

    if ( current == current_parent->left) { //пытаемся понять: current - левый или правый потомок?
        current_parent->left = changeTo;
    }
    else {
        current_parent->right = changeTo;
    }
    if (changeTo != NULL) {//Заменяемый элемент (changeto) вообще существует или это NULL? 
        changeto_parent = current_parent;//Если существует, надо указатель на родителя(changeto_parent) сделать current_parent
    }
}//в результате этой функции, мы как бы вообще избавляемся от этого блока current (на него никто теперь не указывает и он ни на что не указывает)

void Erase(struct Node *tree, struct Node *del) { 
//Функция Erase это как бы Transplant, но рассматривающая разные случаи.
//В отличии от Transplant, который просто меняет на элемент, который ему передадут, Erase должен понять, на что менять
    if (del->left == NULL) {
        Transplant(tree, del, del->right);
    }
    else if (del->right == NULL) {
        Transplant(tree, del, del->left);
    } 
//строки 113 - 118 рассматривают простые случаи, когда один из потомков удаляемого элемента нулевой. Очевидно, в таком случае надо вызывать Transplant от другого.
    else {
        struct Node *y = Minimum(del->right); // y = указатель на наименьший элемент правого поддерева удаляемого элемента
        struct Node *y_parent = parent_search(tree, y);
        struct Node *y_left = parent_search(tree, y->left);
        struct Node *y_right = parent_search(tree, y->right);
        if (y_parent != del) {
            Transplant(tree,y, y->right); //меняем y на правого потомка y
            y->right = del->right;
            y_right = y; 
        }
        Transplant(tree, del, y);
        y->left =del->left;
        y_left = y;
    }
/*строки 120 - 133 - рассматривается более сложный случай, когда потомки оба не нулевые =>
 то есть надо выбрать тот, который либо самый левый (=минимальный) правого поддерева, либо самый правый(= максимальный) левого поддерева*/
}



void InOrder(struct Node *tree) {
    if (tree != NULL) {
        InOrder(tree->left);
        printf("%d ", (int)tree->val);
        InOrder(tree->right);
    }
}

void tree_destroy(struct Node * tree) {
    if(tree != NULL) {
        tree_destroy(tree->left);

        tree_destroy(tree->right);
        free(tree);
    }
}