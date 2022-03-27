/*
Author: Zvonkov Yaroslav Stanislavovich .aka @Gekata
Date: 08.03.2022

Считаем комментарии

    Комментарием в языке Object Pascal является любой текст, находящийся между
    последовательностью символов, начинающих комментарий определённого вида и
    последовательностью символов, заканчивающей комментарий этого вида.

Виды комментариев могут быть следующие:

    1) Начинающиеся с набора символов (* и заканчивающиеся набором символов *).
    2) Начинающиеся с символа { и заканчивающиеся символом }.
    3) Начинающиеся с набора символов // и заканчивающиеся символом новой строки

Еще в языке Object Pascal имеются литеральные строки, начинающиеся
символом одиночной кавычки ' (ASCII код 39) и заканчивающиеся этим же символом.
В корректной программе строки не могут содержать символа перехода на новую строку.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

const uint32_t MAX_STR_LEN = 131272;

enum STATE { 
    END, 
    COMM_ROUND, 
    COMM_FIG, 
    COMM_FSLASH, 
    LIT_STR, 
    BODY, 
};

void count_comms(char *text);

int main() {
    char *text = (char *)calloc(MAX_STR_LEN, sizeof(char));
    fread(text, sizeof(char), MAX_STR_LEN, stdin);

    count_comms(text);
    free(text);

    return 0;
}

void count_comms(char *text) {
    int comm_round_cnt = 0;
    int comm_fig_cnt = 0;
    int comm_fslash_cnt = 0;
    int lit_str_cnt = 0;

    int cur_cond = BODY;

    while (cur_cond != END) {
        switch (cur_cond) {
            case BODY: {
                if (strncmp(text, "(*", 2llu) == 0) {
                    cur_cond = COMM_ROUND;
                    text++;

                } else if (*text == '{') {
                    cur_cond = COMM_FIG;

                } else if (strncmp(text, "//", 2llu) == 0) {
                    cur_cond = COMM_FSLASH;
                    text++;

                } else if (*text == '\'') {
                    cur_cond = LIT_STR;

                } else if (*text == '\0' || *text == EOF) {
                    cur_cond = END;

                }
                break;

            }
            case COMM_ROUND: {
                if (strncmp(text, "*)", 2llu) == 0) {
                    text++;
                    comm_round_cnt++;
                    cur_cond = BODY;

                } else if (*text == '\0' || *text == EOF) {
                    cur_cond = END;

                }
                break;
            }
            case COMM_FIG: {
                if (*text == '}') {
                    comm_fig_cnt++;
                    cur_cond = BODY;

                } else if (*text == '\0' || *text == EOF) {
                    cur_cond = END;

                }
                break;
            }
            case COMM_FSLASH: {
                if (*text == '\n') {
                    comm_fslash_cnt++;
                    cur_cond = BODY;

                } else if (*text == '\0' || *text == EOF) {
                    cur_cond = END;
                }
                break;
            }
            case LIT_STR: {
                if (*text == '\'') {
                    lit_str_cnt++;
                    cur_cond = BODY;

                } else if (*text == '\0' || *text == EOF) {
                    cur_cond = END;

                }
                break;
            }
        }

        text++;
    }

    printf("%d %d %d %d\n", comm_round_cnt, comm_fig_cnt, comm_fslash_cnt, lit_str_cnt);
    return;
}
