/*1) создать массив на n элементов,
 (m, n - вводит пользователь), заполнить его; 
 и в регистр rdx положить значение элемента c номером m*/
 
 #include <stdio.h>
 int main(){
     int n;
     long long res = 0;
     printf("Введите число элементов массива\n");
     scanf ("%d", &n);
     int arr[n];
     printf("Вводите элементы массива из %d элементов\n", n);
     for (int i = 0; i < n - 1; ++i){
         scanf("%d", &arr[i]);
     }
     int m;
     printf("Введите m - номер элемента массива\n m = \n");
     scanf("%d",&m);
     int *p_arr = arr;//в p_arr лежит адрес на начало массива arr

     asm volatile(
    ".intel_syntax noprefix\n"
        
    "xor rdx, rdx;\n"
    "L2:;\n"
    "cmp rbx, (rcx-1)*4;\n"
    "je L1;\n"
    "jne L2;\n"
    "L1: mov rdx, [(rcx-1)*4];\n"

    ".att_syntax noprefix"
    : "=d" (res)//кладем в регистр d значение переменной res
    /* Пусть res - это значение элемента массива с номером m */
    : "a" (p_arr), "c" (n), "b" (m)
        );
    printf("After asm:\nres = %lld\narr = %p", res, p_arr);

 return 0;
 
 }
