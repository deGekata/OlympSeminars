#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

uint8_t get_byte(int num, int ord_num);


void Radix_sort(uint8_t Temp[], int length, int bytes_to_take);

int back_track(int* weight, int h_sum, int cur_sum, int* mx_weight) {
    // if (cur_sum >= h_sum) { printf("cur_weight =%d, cur_sum = %d g\n", *weight, cur_sum); return abs(h_sum - cur_sum);}
    if (cur_sum >= h_sum) return cur_sum;

    // if (weight == mx_weight) { printf("cur_weight =%d, cur_sum = %d, d = %d end\n", *weight, cur_sum, abs(h_sum - cur_sum)); return abs(h_sum - cur_sum);}
    if (weight == mx_weight) return cur_sum;

    // printf("cur_weight =%d, cur_sum = %d\n", *weight, cur_sum);
    int mn = back_track(weight + 1, h_sum, cur_sum + *weight, mx_weight);
    int en = back_track(weight + 1, h_sum, cur_sum,           mx_weight);
    // printf("(mn) %d ? %d (en) \n", mn, en);
    return abs(mn - h_sum) < abs(en - h_sum) ? mn: en;
}
// 8   9   6  9  8     =
// 8 + 9 + 6  _  _     = 23 -> dif = 6
// 8 + 9 + _  9  _     = 26 -> dif = 12
// 8   9   _  _  8     = 25 -> dif = 10
// 8   9   _  _  _     = 17 -> dif = 6
// 8   _   6  9  _     = 23 -> dif = 6
// 8   _   6  _  8     = 22 -> dif = 4

int main() {
    
    int N;
    scanf("%d", &N);

    int mas[50];
    int alsum = 0;
    for (int it = 0; it < N; ++it) {
        scanf("%d", mas + it);
        alsum += mas[it];
    }
    // printf("alsum     = %d\n", alsum);
    // printf("alsum / 2 = %d\n", alsum / 2);
    int res = back_track(mas, alsum / 2, 0, mas + N);

    printf("%d", abs(alsum - res  * 2));
    

    return 0;
}




// uint8_t get_byte(int num, int ord_num) {
//     return ((unsigned int)num << ((sizeof (num) - ord_num) * 8)) >> (sizeof (num) * 8 - 8);
// }

// void Radix_sort(uint64_t Temp[], int length, int bytes_to_take) {
//      int cnt_bytes = sizeof (Temp[0]) / bytes_to_take;
//      //std::cout << " bytes " << cnt_bytes << "\n";
//      int cnt = pow(2, bytes_to_take * 8);
//      uint64_t* Temp2 = new uint64_t[length];
//      for (int byte = 0; byte < cnt_bytes; ++byte) {
//          std::vector<int> byte_var(cnt,0);
//          //std::cout << "byte_num: " << byte << "\n";
//          for (int iter = 0; iter < length; ++iter) {
//              byte_var[get_byte(Temp[iter], byte, bytes_to_take)]++;
//              //std::cout << get_byte(Temp[iter], byte, bytes_to_take) << " " << Temp[iter] << "\n";
//          }

//          int count = 0;
//          int temp;
//          for (int iter = 0; iter < cnt; ++iter) {
//              temp = byte_var[ iter ];
//              byte_var[ iter ] = count;
//              count += temp;
//          }
//          //std::cout<<"swaped\n";
//          for (int iter = 0; iter < length; ++iter) {
//              temp = get_byte(Temp[ iter ], byte, bytes_to_take);
//              Temp2[byte_var[temp]] = Temp[ iter ];
//              byte_var[ temp ]++;
//          }
//          std::swap(Temp, Temp2);
//          //std::cout<<"swaped\n";
//      }
//      return;
// }