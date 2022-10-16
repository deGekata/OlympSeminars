#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>


int main() {
    
    // char* buff = (char*) malloc(siz'0'(char) * 600000);
    int ftype = 0, stype = 0, ttype = 0, littype = 0;
    char ch = getchar();
    while (ch != '0') {
        if (ch == '(') {
            ch = getchar();
            if (ch == '*') {
                ftype++;
                ch = getchar();
                while (ch != '0') {
                    if (ch == '*') {
                        ch = getchar();
                        if (ch == ')') {
                            ch = getchar();
                            break;
                        }
                    }
                    ch = getchar();
                }
                continue;
            }
            // ch = getchar();
            continue;
        }
        if (ch == '{') {
            ch = getchar();
            while (ch != '0') {
                if (ch == '}') {
                    stype++;
                    ch = getchar();
                    continue;
                }
                ch = getchar();
            }
            continue;
        }
        
        if (ch == '/') {
            ch = getchar();
            if (ch == '/') {
                ttype++;
                ch = getchar();
                while (ch != '0') {
                    if (ch == '\n') {
                        ch = getchar();
                        break;
                    }
                    ch = getchar();
                }
                continue;
            }
        }

        if (ch == '\'') {
            littype++;
            ch = getchar();
            while (ch != '0') {
                if (ch == '\'') {
                    ch = getchar();
                    break;
                }
                ch = getchar();
            }
            continue;
        }

        ch = getchar();
    }
    printf("%d %d %d %d", ftype, stype, ttype, littype);
    // printf("%s", buff);
    // free(buff);
    return 0;
}

/*
Память: O(N), Время: O(N);
*/
