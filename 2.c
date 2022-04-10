#include <stdio.h>
#include <stdlib.h>
#define n 4
int i = 0;
char instruct[n];
char reg[n];
char num[n];
int smth;
int out[n] = {0, 0, 0, 0};

int main(){ 
    
    printf(" Обозначайте регистры как a, b, c, d \n");

    while (1){
        scanf("%s %s %c", instruct, reg, num);//считываем то что ввели

        if (num[0] - 48 >= 9)//то это регистр введен третьим
            smth = out[counter(num)];
        
        else{//это число
            for (int l = 0, l < 4, l++) smth = smth + num[1] - 48;    
        }
        command(instruct);
    }
    return 0;
}

int counter(char *reg[n]){//обязательно ли *?
    switch(reg[0]){
        case 'a': i = 1;
        case 'b': i = 2;
        case 'c': i = 3;
        case 'd': i = 4;
        default: printf ("Введен несуществующий регистр")
    }
    return i;
}

int command(char *instruct[n]){
    switch(instruct[0]){
        case 'm': mov(out, *reg, smth)
        case 'a': add(out, *reg, smth)
        case 's': sub(out, *reg, smth)
        case '0': printf("Выход"); return 0;
        case 'r': printf("Выход"); return 0;
    }
}
void mov (int out, char *reg, int smth){ //функция, которая ставит третье введенное число или регистр на место out[i], в зависимости от того, какой регистр был введен
    int i = counter(reg);
    out[i] = smth;
    for (int k = 0, k < n, k++) printf("%d", out[k]);
    return;
}

void add (int out, char *reg, int smth){
    int i = counter(reg);
    out[i] = out[i] + smth;
    for (int k = 0, k < n, k++) printf("%d", out[k]);
    return;
}

void sub (int out, char *reg, int smth){
    int i = counter(reg);
    out[i] = out[i] - smth;
    for (int k = 0, k < n, k++) printf("%d", out[k]); 
    return;   
}

