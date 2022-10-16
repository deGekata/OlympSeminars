#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>


int main() {
    char* buff = (char*) malloc(sizeof(char) * 600000);
    char ch;
    char hasSl = 0, is_many = 0, is_single = 0, has_star = 0, is_double = 0, is_singquot = 0;
    int pos = 0;
    ch = getchar();
    while (ch != EOF) {
        if (is_many) {
            if (ch == '*') {
                has_star = 1;
            } else if (has_star && ch == '/') {
                buff[pos++] = ' ';
                is_many = 0;
                has_star = 0;
            } else {
                has_star = 0;
            }
            ch = getchar();
            continue;
        }
        if (is_single) {
            if (ch == '\n') {
                is_single = 0;
                buff[pos++] = '\n';
                ch = getchar();
                continue;
            }
            ch = getchar();
            continue;
        }
        if (is_double) {
            if (ch == '"') {
                is_double = 0;
            }
            buff[pos++] = ch;
            ch = getchar();
            continue;
        }

        if (is_singquot) {
            
            if (ch == '\'') {
                is_singquot = 0;
            }
            buff[pos++] = ch;
            ch = getchar();
            continue;
        }
        
        if (hasSl) {
            if (ch == '*') {
                is_many = 1;
                hasSl = 0;
                ch = getchar();
                continue;
            }
            if (ch == '/') {
                is_single = 1;
                hasSl = 0;
                ch = getchar();
                continue;
            }
            hasSl = 0;
            buff[pos++] = '/';
            buff[pos++] = ch;
            ch = getchar();
            continue;
        }
        if (ch == '\'') {
            is_singquot = 1;
            buff[pos++] = '\'';
            ch = getchar();
            continue;
        }
        if (ch == '"') {
            is_double = 1;
            buff[pos++] = '"';
            ch = getchar();
            continue;
        }
        if (ch == '/') {
            hasSl = 1;
            ch = getchar();
            continue;
        }
        buff[pos++] = ch;
        ch = getchar();
        

    }

    buff[pos] = 0;

    printf("%s", buff);
    free(buff);
    return 0;
}

/*
Память: O(N), Время: O(N);
*/
