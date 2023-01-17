/***
 * Program to measure the size of a variable without using the sizeof() function
 * 
 * Joshua Snyder
*/

#include <stdio.h>
#include <stdint.h>

int main(void)
{
    // Let's measure the size of this variable without the use of the sizeof operator
    int num = 10; 
    
    // Cast the end and base addresses of the variable as (char *) to ensure we measure the size in bytes 
    char *end_addr = (char *)(&num + 1);    // ending byte address
    char *base_addr = (char *)&num;         // base byte address

    printf("Size of num = %i\n", end_addr - base_addr);
    printf("Size of num using sizeof() = %i\n", sizeof(num));

    // This also works with arrays
    int nums[10];

    char *end_arr_addr = (char *)(&nums + 1);
    char *base_arr_addr = (char *)&nums;

    printf("Size of nums = %i\n", end_arr_addr - base_arr_addr);
    printf("Size of nums using sizeof() = %i\n", sizeof(nums));

    return 0;
}