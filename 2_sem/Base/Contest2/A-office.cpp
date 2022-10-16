#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b));

typedef struct my_time {
    uint64_t event_time;
    int8_t in_out_flag;
} my_time;

int timeCmp(const void* first, const void* second) {
    my_time* first_time = (my_time*) first;
    my_time* second_time = (my_time*) second;
    if (first_time->event_time > second_time->event_time) {
        return 1;
    }
    
    if (first_time->event_time == second_time->event_time) {
        return first_time->in_out_flag < second_time->in_out_flag;
    }
    
    return -1;
}

int main() {
    uint32_t cnt = 0;
    scanf("%u", &cnt);

    my_time* times_arr = (my_time*) calloc(sizeof(my_time), cnt * 2);
    
    uint32_t hour = 0;
    uint32_t minutes  = 0;
    uint32_t seconds  = 0;

    for (uint32_t cur_event_it = 0; cur_event_it < cnt * 2; cur_event_it += 2) {
        scanf("%u:%u:%u", &hour, &minutes, &seconds);
        times_arr[cur_event_it].event_time = 3600 * hour + 60 * minutes + seconds;
        times_arr[cur_event_it].in_out_flag    = 1;

        scanf("%u:%u:%u", &hour, &minutes, &seconds);
        times_arr[cur_event_it + 1].event_time = 3600 * hour + 60 * minutes + seconds;
        times_arr[cur_event_it + 1].in_out_flag    = -1;
    }
    qsort(times_arr, cnt * 2, sizeof(my_time), timeCmp);

    int32_t cur = 0, mx = 0;

    for (uint32_t cur_event_it = 0; cur_event_it < 2 * cnt; cur_event_it++) {
        cur += times_arr[cur_event_it].in_out_flag;
        mx = cur > mx ? cur : mx;
    }
    printf("%u", mx);

    free(times_arr);
    return 0;
}