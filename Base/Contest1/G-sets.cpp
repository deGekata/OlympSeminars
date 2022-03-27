/*
Подмножества
Множество задано строкой, состоящей из букв латинского алфавита и цифр. Каждый символ строки есть элемент множества.

Но это множество — не совсем простое. Элементы в нём могут повторяться.

Два подмножества считаются одинаковыми, если все элементы одного множества совпадают с элементами другого. Например, множества, представленные строками abc и cba совпадают. Совпадают также множества abra и raba.

Ваша задача по заданной строке, представляющей исходное множество, вывести все различные его подмножества, каждое на отдельной строке вывода. Выводить можно в произвольном порядке. Выход не должен содержать совпадающие подмножества.

Пустое множество тоже является подмножеством исходного.


*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

void print_dig(int arr[], int offs, char buff[], int buff_offs);

void print_small(int arr[], int offs, char buff[], int buff_offs);

void print_dig(int arr[], int offs, char buff[], int buff_offs) {  
    if (offs >= ('9' - '0')) {
        print_small(arr, offs + 1, buff, buff_offs);
        
        return;
    }

    for (int it = 0; it <= arr[offs]; ++it) {
        for (int jit = 0; jit < it; ++jit) {
            buff[buff_offs++] = '0' + offs;
        }

        print_dig(arr, offs + 1, buff, buff_offs);
        buff_offs -= it;
    }
}

void print_small(int arr[], int offs, char buff[], int buff_offs) {
    if (offs > ('9' - '0' + 'z' - 'a')) {
        buff[buff_offs] = '\n';
        buff[buff_offs + 1] = 0;

        printf("%s", buff);
        return;
    }

    for (int it = 0; it <= arr[offs]; ++it) {
        for (int jit = 0; jit < it; ++jit) {
            buff[buff_offs++] = 'a' - ('9' - '0' + 1) + offs;
        }
        
        print_small(arr, offs + 1, buff, buff_offs);
        buff_offs -= it;
    }
}


int main() {
    int arr[62] = {0};
    char str[100];
    char buff[100];

    scanf("%s", str);
    int N = strlen(str);

    for (int it = 0; it < N; ++it) {
        if (isdigit(str[it]))
            arr[str[it] - '0']++;
        else if (islower(str[it])) 
            arr[str[it] - 'a' + '9' - '0' + 1]++;
    }

    print_dig(arr, 0, buff, 0);

    return 0;
}

/*
Перебор количества каждой буквы
Асимптотика: 2^n
Память: длина входной строки
*/