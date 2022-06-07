#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum Line_type {
    row,
    column,
};

typedef struct line {
    enum Line_type type;

    int32_t sum;
    uint32_t cnt;
} line;

int32_t lineCmp(const void* elem1, const void* elem2) {
    return ((line*)elem1)->sum > ((line*)elem2)->sum;
}

int main() {
    uint32_t matrix_h = 0;
    uint32_t matrix_w = 0;

    scanf("%u %u", &matrix_h, &matrix_w);

    line* lines = (line*) calloc(sizeof(line), matrix_h + matrix_w);

    int32_t** matrix = (int32_t**) calloc(sizeof(int32_t*), matrix_w);
    for (uint32_t curColumn = 0; curColumn < matrix_w; curColumn++) {
        matrix[curColumn] = (int32_t*) calloc(sizeof(int32_t), matrix_h);
        lines[matrix_h + curColumn].cnt = curColumn;
        lines[matrix_h + curColumn].type = column;
    }

    int32_t tempValue = 0;
    for (uint32_t curRow = 0; curRow < matrix_h; curRow++) {
        lines[curRow].cnt = curRow;
        lines[curRow].type = row;

        for (uint32_t curColumn = 0; curColumn < matrix_w; curColumn++) {
            scanf("%d", &tempValue);

            lines[curRow].sum += tempValue;
            lines[matrix_h + curColumn].sum += tempValue;

            matrix[curColumn][curRow] = tempValue;
        }
    }

    line* mn_e = NULL;
    int32_t mn_sm = INT32_MAX;

    for (uint32_t cur_l = 0; cur_l < matrix_h + matrix_w; cur_l++) {
        if (lines[cur_l].sum < mn_sm) {
            mn_e = lines + cur_l;
            mn_sm = lines[cur_l].sum;
        }
    }

    while (mn_e->sum < 0) {
        mn_e->sum = -mn_e->sum;

        if (mn_e->type == row) {
            printf("l %u\n", mn_e->cnt);
            for (uint32_t curColumn = 0; curColumn < matrix_w; curColumn++) {
                matrix[curColumn][mn_e->cnt] =
                    -matrix[curColumn][mn_e->cnt];
                lines[matrix_h + curColumn].sum +=
                    2 * matrix[curColumn][mn_e->cnt];
            }
        } else {
            printf("c %u\n", mn_e->cnt);

            for (uint32_t curRow = 0; curRow < matrix_h; curRow++) {
                matrix[mn_e->cnt][curRow] =
                    -matrix[mn_e->cnt][curRow];
                lines[curRow].sum += 2 * matrix[mn_e->cnt][curRow];
            }
        }

        mn_sm = INT32_MAX;

        for (uint32_t cur_l = 0; cur_l < matrix_h + matrix_w; cur_l++) {
            if (lines[cur_l].sum < mn_sm) {
                mn_e = lines + cur_l;
                mn_sm = lines[cur_l].sum;
            }
        }
    }

    for (uint32_t curColumn = 0; curColumn < matrix_w; curColumn++) {
        free(matrix[curColumn]);
    }

    free(matrix);
    free(lines);
}