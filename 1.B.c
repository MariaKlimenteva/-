#include <stdio.h>
#include <stdlib.h>
struct Elem * root; // глобальная переменная, хранящая указатель на начало дерева
struct Info { //отдельная структура для сбора нужной информации
    struct Elem ** p_field; //указатель на поле внутри родительской структуры, хранящее указатель на удаляемый элемент
    struct Elem * del_el;//удаляемый элемент
    struct Elem * most_right;//максимальный эл-т левого поддерева
    struct Elem * parent_most_right;
}
struct Elem {
	int val; // значение, которое хранится в элементе ((!) может быть указателем на строку, например)
	struct Elem * lv, * pr; // указатели на левого и правого потомков
};
struct Elem * find_elem(int x){ // проход по дереву в этом случае аналогичен add_elem

	if (root == NULL){
		printf("Empty tree");
		return NULL;
	}
	
	struct Elem * p = root; // p - будет указателем на текущий элемент на каждой итерации
	while(1){
		if(x == p->val) // если значение совпало - мы нашли нужный элемент
			return p;
		if(x < p->val){ // если x меньше, идем искать в левом поддереве
			if(p->lv != NULL)
				p = p->lv; // если левое поддерево есть - переходим левого потомка
			else
				return NULL; // если левого поддерева нет - значит не нашли нужный элемент
		}
		if(x > p->val){ // если x больше, идем искать в правом поддереве
			if(p->pr != NULL)
				p = p->pr;
			else
				return NULL;
		}
	}
	
	return NULL;
}

void add_elem(int x){ // это нерекурсивная реализация, но можете и рекурсивную сделать тоже, по аналогии с print_tree_dfs
	struct Elem * p = (struct Elem *)malloc(sizeof(struct Elem)); // выделить под элемент память
	p->val = x; // заполнить его поля
	p->lv = NULL;
	p->pr = NULL;
	
	// ищем для него подходящее место в дереве
	// если дерево пусто
	if (root == NULL){
		root = p;
		return;
	}
	
	// если дерево не пусто, ищем для него родительский элемент (вставляем только как лист)
	struct Elem * q = root;
	while(1){
		if (x < q->val){ // если x меньше, чем значение текущего элемента, то вставляем в левое поддерево
			if (q->lv != NULL){
				q = q->lv; // переходим в левого потомка текущего элемента
			}
			else{
				q->lv = p; // вставляем новый элемент, если левого потомка не было
				break;
			}
		}
		else{ // если x больше или равно, то - в правое поддерево
			if (q->pr != NULL){
				q = q->pr; // переход в правого потомка
			}
			else{
				q->pr = p; // вставка в качестве правого потомка
				break;
			}
		}
	}

	return;
}
// Функция нахождения самого правого элемента (сделала самостоятельно, не из примера)
struct Elem * find_most_right (int x){//рассматриваем левое поддерево удаляемого элемента

    struct Elem * p == x -> lv; // p - указатель на текущий элемент на каждой итерации
    while(1){
        if (p -> pr != NULL){
            p = p -> pr;
        }
        else{
            most_right == p;
            return p;
        }
    }
}

void print_tree_dfs(struct Elem * p){ // рекурсивный обход дерева в глубину
	if (p == NULL){
		return;
	}
	
	print_tree_dfs(p->lv); // распечатать левое поддерево все целиком
	printf("%d ", p->val); // распечатать значение текущего элемента
	print_tree_dfs(p->pr); // распечатать правое поддерево все целиком
	
	return;
}

//Функция нахождения родителя удаляемого элемента (сделана самостоятельно, не из примера)
struct Elem * find_parent (int x){ 

    struct Elem * p == root; //p - указатель на текущий элемент на каждой итерации
    if (x == p){ 
     return NULL;
    }
    if (p -> lv == NULL) && (p -> pr == NULL){
        return NULL;
    }
    else{
        while (1){
            if (p -> pr == x) || (p -> lv == x){
                return p;
            }
            else{
                if (x > p -> val){
                    if (p -> pr != NULL){
                        p = p -> pr;
                    }
                    else{
                        return NULL;
                    }
                else{
                    if (p -> lv != NULL){
                        p = p -> lv;
                    }
                    else{
                        return NULL;
                    }
                }
                }
            }
        }   
    }
}   


int main (){
    root = NULL;
	add_elem(7); // вставим в корневой элемент
	add_elem(5); // пойдет как левый потомок 7
	add_elem(8); // пойдет как правый потомок 7
	add_elem(6); // пойдет как правый потомок 5
	add_elem(3); // пойдет как левый потомок 5
	add_elem(1); // пойдет как левый потомок 3
	add_elem(4); // пойдет как правый потомок 3
	add_elem(9); // пойдет как правый потомок 8
    printf("Дерево:\n"); 
	print_tree_dfs(root); 
	printf("\n");
    return 0;
}

////////// еще не доделала, проблема в сборе информации для структуры, хотя почитала как работать со структурами
void del_elem(struct Info * del_el) { //функция удаления элемента (подаем в функцию значение удаляемого эл-та)
if ((del_el -> lv) == NULL) {//нет левого потомка удаляемого эл-та

    if ((del_el -> pr) == NULL) { //если и правого потомка нет
       
        del_el -> val == NULL;
        * p_field == NULL;//?? так ли мы обNULLяем то, что в род эл-те про уд эл-т 

    }
    else{ //нет левого, но есть правый потомок
        * p_field == del_el -> pr;           
    }    
}
else{
    if (find_parent(most_right) == )
}   

}