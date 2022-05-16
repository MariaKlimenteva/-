#include <stdio.h>
#include <stdlib.h>

struct Elem {
    int val;            // данные в узле
    struct Elem * left;  // левый потомок
    struct Elem * right; // правый потомок
};
struct Elem * find(struct Elem * tree, int x){
    if(x == tree->val){
        return tree;
    }
    else if(x > tree->val){
        find(tree->right, x);
    }
    else{
        find(tree->left, x);
    }
}
struct Elem * tree_add (struct Elem * tree, int x){ //рекурсивная функция добавления узла в дерево - из контеста Древо жизни
        
        if(tree == NULL){ //если дерева нет
            tree = (struct Elem *) malloc(sizeof(struct Elem)); //создаем память для нового эл-та
            tree->left = NULL;      
            tree->right = NULL;
            tree->val = x; //заполняем его поля, добавляем его как лист
            
        }
        if(x > tree->val ){ //сравниваем значение нового эл-та с корнем, если больше 
            if(tree->right == NULL){ // и если нет правого потомка у корня то эл-т становится им

                struct Elem * p = (struct Elem *) malloc(sizeof(struct Elem) + 4);
                tree->right = p; // новый эл-т стал правым потомком
                p->left = NULL;
                p->right = NULL;
                p->val = x;

            }
            else{
                tree_add((tree->right), x); //если же у корня был правый потомок то вызываем опять функцию, только уже относительно этого потомка(в этом проявляется рекурсия)
            }
        }
        else if(x < tree->val){
            if(tree->left == NULL){

                struct Elem * p = (struct Elem *) malloc(sizeof(struct Elem));
                tree->left = p;
                p->left = NULL;
                p->right = NULL;
                p->val = x;
            }
            else{
                tree_add(tree->left, x); 
            }
    }
    return tree;
}

void print (struct Elem * tree){ //функция печати дерева - из контеста
    if (tree == NULL){
        return;
    }  
    if(tree->left != NULL){
        print(tree->left);//вызываем функцию печати левого поддерева
    }
    printf("%d ", tree->val);//печать зн-я в узле
    if(tree->right != NULL){
        print(tree->right);//ф-я печати прав поддерева
    } 
}



struct Elem * most_right(struct Elem * tree, int x){ // самый правый элемент подставляем вместо удаляемого
    if(tree->right == NULL){
        return tree;
    }
    while((tree->right)->right != NULL){
        return most_right(tree->right, x);
    }
    return tree;
}

void del_el(struct Elem * tree, int x){ //функция удаления элемента
    struct Elem * del = find(tree, x);
    struct Elem * right_el = most_right(del->left, x);
    struct Elem * max = right_el->right;
    del->val = max->val;
    right_el->right = max->left;
    free(max);
}

int main()
{
    struct Elem * tree = NULL;
    tree = tree_add(tree, 7);
    tree = tree_add(tree, 3);
    tree = tree_add(tree, 2);
    tree = tree_add(tree, 1);
    tree = tree_add(tree, 9);
    tree = tree_add(tree, 5);
    tree = tree_add(tree, 4);
    tree = tree_add(tree, 6);
    tree = tree_add(tree, 8);
    del_el(tree, 5);
    print(tree);
    return 0;
}