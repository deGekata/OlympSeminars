#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

uint32_t get_byte(size_t num, int ord_num, int bytes_to_take){
    return ((unsigned long long)num << ((sizeof (num) - bytes_to_take - ord_num * bytes_to_take) * 8)) >> (sizeof (num) * 8 - 8 * bytes_to_take);
}

void Radix_sort(uint32_t Temp[], int length, int bytes_to_take) {
     int cnt_bytes = sizeof (Temp[0]) / bytes_to_take;
     //std::cout << " bytes " << cnt_bytes << "\n";
     int cnt = 1 << (bytes_to_take * 8);
     uint32_t* Temp2 = (uint32_t*) calloc(length, sizeof(*Temp2));
     uint32_t* byte_var = (uint32_t*) malloc(cnt * sizeof(*byte_var));
     for (int byte = 0; byte < cnt_bytes; ++byte) {
         for (size_t it = 0; it < cnt; ++it) byte_var[it] = 0;
         //std::cout << "byte_num: " << byte << "\n";
         for (int iter = 0; iter < length; ++iter) {
             byte_var[get_byte(Temp[iter], byte, bytes_to_take)]++;
             //std::cout << get_byte(Temp[iter], byte, bytes_to_take) << " " << Temp[iter] << "\n";
         }

         int count = 0;
         int temp;
         for (int iter = 0; iter < cnt; ++iter) {
             temp = byte_var[ iter ];
             byte_var[ iter ] = count;
             count += temp;
         }
         //std::cout<<"swaped\n";
         for (int iter = 0; iter < length; ++iter) {
             temp = get_byte(Temp[ iter ], byte, bytes_to_take);
             Temp2[byte_var[temp]] = Temp[ iter ];
             byte_var[ temp ]++;
         }
         uint32_t* tmp = Temp;
         Temp = Temp2;
         Temp2 = tmp;
        //  std::swap(Temp, Temp2);
         //std::cout<<"swaped\n";
     }
     free(Temp2);
    free(byte_var);
     return;
}
//###################################################################################################################################################

void fast_sort(unsigned *begin, unsigned *end) {
    Radix_sort(begin, end - begin, 1);
}


// void fast_sort(unsigned *begin, unsigned *end) {
//     size_t len = end - begin;
//     uint32_t mn = -1, mx = 0;
//     for (unsigned* cur = begin; cur < end; ++cur) {
//         if (mn > *cur) mn = *cur;
//         if (mx < *cur) mx = *cur;
//     }
//     // printf("len = %lu\n", len);

//     uint32_t* tmp_data = (uint32_t*) calloc(mx - mn + 1, sizeof(uint32_t));
//     tmp_data = tmp_data - mn;
//     for (size_t it = 0; it < len; ++it) {
//         tmp_data[begin[it]]++;
//     }
//     // for (uint32_t cur = mn; cur <= mx; ++cur) {
//     //     printf("%u val %u num\n", tmp_data[cur], cur);
                
//     // }
//     for (uint32_t cur = mn + 1; cur <= mx; ++cur) {
//         tmp_data[cur] = tmp_data[cur] + tmp_data[cur - 1];
//     }
//     // printf("----------\n");
//     // for (uint32_t cur = mn; cur <= mx; ++cur) {
//     //     printf("%u val %u num\n", tmp_data[cur], cur);
                
//     // }
//     uint32_t* data = (uint32_t*) calloc(len, sizeof(uint32_t));

//     for (size_t cur = 0; cur < len; ++cur) {
//         data[--tmp_data[begin[cur]]] = begin[cur];
//     }
//     for (size_t cur = 0; cur < len; ++cur) {
//         begin[cur] = data[cur];
//     }
//     free(data);
//     tmp_data = tmp_data + mn;
//     free(tmp_data);
//     return;
// }


int main() {
    unsigned* array = (unsigned*) calloc(8, 4);
    array[0] = 3;
    array[1] = 1;
    array[2] = 4;
    array[3] = 1;
    array[4] = 5;
    array[5] = 9;
    array[6] = 2;
    array[7] = 6;
    // {3,1,4,1,5,9,2,6};
    fast_sort(array, array+8);
    // Radix_sort(array, 8, 1);
    for (size_t it = 0; it < 8; ++it) {
        printf("%d ", array[it]);
    }
    free(array);
    // Now array = {1,1,2,3,4,5,6,9}
}
     