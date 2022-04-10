#include <stdio.h>
#include <stdlib.h>
#define n 4

char instruct[n];
char reg[n];
char num[n];
int smth;
int out[n] = {0, 0, 0, 0};

int counter(char *reg){
    int i = 0;
    switch(reg[0]){
        case 'a': i = 0; break;
        case 'b': i = 1; break;
        case 'c': i = 2; break;
        case 'd': i = 3; break;
        default: printf("Неверный ввод"); break;
    }
    return i;
}

void mov (int *out, char *reg, int smth){ //функция, которая ставит третье введенное число или регистр на место out[i], в зависимости от того, какой регистр был введен
    int i = counter(reg);
    out[i] = smth;
    for (int k = 0; k < n; k++) printf("%d", out[k]);
    return;
}

void add (int *out, char *reg, int smth){
    int i = counter(reg);
    out[i] = out[i] + smth;
    for (int k = 0; k < n; k++) printf("%d", out[k]);
    return;
}

void sub (int *out, char *reg, int smth){
    int i = counter(reg);
    out[i] = out[i] - smth;
    for (int k = 0; k < n; k++) printf("%d", out[k]); 
    return;   
}


int command(char *instruct){    
        switch(instruct[0]){
            case 'm': mov(out, reg, smth); break;
            case 'a': add(out, reg, smth); break;
            case 's': sub(out, reg, smth); break;
            case 'r': return 0;
            break;
            default: printf("Неверный ввод"); break;
        }
}
int main(){

    printf(" Обозначайте регистры как a, b, c, d \n");

    while (1){
        scanf("%s %s %s", instruct, reg, num);

        if ((num[0] - 48 > 9)||(num[0] - 48 < 0)){
            smth = out[counter(num)];
        }
        
        else{
            smth = num[0] - 48;
        }          
        command(instruct);
    }
    return 0;
}

