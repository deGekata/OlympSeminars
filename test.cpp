/* H-coins-Пары монет
 * Рюкзак через полный перебор
 * Можно ли получить заданную сумму (минимизировав еол-во монет)
 * 
 * input:
 *      заданная сумма
 *      кол-во монет
 *      номиналы монет
 * 
 * ouput:
 *      минимальное кол-во монет
 * 
 * @ Платонов Тимофей
*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(LHS, RHS) ((LHS) < (RHS) ? (LHS) : (RHS))
#define INF 40

static int* CalcSubSum(int *buffer, int *money, int sum, int cnt_mon, int n) {
    if (n == 0) {
        buffer[0] = sum;
        buffer[1] = cnt_mon;
        return buffer + 2;
    }

    buffer = CalcSubSum(buffer, money + 1, sum + *money * 2, cnt_mon + 2, n - 1);
    buffer = CalcSubSum(buffer, money + 1, sum + *money    , cnt_mon + 1, n - 1);
    return   CalcSubSum(buffer, money + 1, sum             , cnt_mon    , n - 1);
}

static int IncComp(const void* lhs, const void* rhs) {
    if (*(int*)lhs == *(int*)rhs) 
        return *((int*)lhs + 1) - *((int*)rhs + 1);
    return *(int*)lhs - *(int*)rhs;
}

static int DecComp(const void* lhs, const void* rhs) {
    if (*(int*)lhs == *(int*)rhs) 
        return *((int*)lhs + 1) - *((int*)rhs + 1);
    return *(int*)rhs - *(int*)lhs;
}

static int Solve(int cost, int N, int *money) {
    N += N % 2;

    const int size = pow(3, N / 2);
    int *left_buffer = (int*) malloc(sizeof(int) * size * 2);
    int *right_buffer = (int*) malloc(sizeof(int) * size * 2);

    CalcSubSum(left_buffer, money, 0, 0, N / 2);
    CalcSubSum(right_buffer, money + N / 2, 0, 0, N / 2);
      
    qsort(left_buffer, size, sizeof(int) * 2, IncComp);
    qsort(right_buffer, size, sizeof(int) * 2, DecComp);

    int ans = INF;
    int L = 0, R = 0;

    while (L < size && R < size) {
        int sum = left_buffer[L * 2] + right_buffer[R * 2];
        if (sum == cost) {
            ans = MIN(ans, left_buffer[L * 2 + 1] + right_buffer[R * 2 + 1]);

            if (L < size) ++L;
            else break;

            if (R < size) ++R;
            else break;

        } else if (sum < cost) {
            if (L < size) {
                ++L;
            } else break;
        } else {  // (sum > cost)
            if (R < size) {
                ++R;
            } else break;
        }
    }

    return ans;
}


int mainH() {
    int N = 0, cost = 0;
    scanf("%d %d", &cost, &N);

    int sum = 0;
    int money[16] = {0};
    for (size_t i = 0; i < N; ++i) {
        scanf("%d", money + i);
        sum += money[i];
    }

    if (sum * 2 < cost) {
        printf("Impossible");
        return 0;
    }

    int ans = Solve(cost, N, money);
    if (ans < INF) printf("%d", ans);
    else printf("Change");
    return 0;
}

/*
 * Делим массив на двое, для каждого считаем все возможные суммы (O^(N / 2)), после сортим и пытаемся найти нужную комбинацию (meet in the middle).
*/