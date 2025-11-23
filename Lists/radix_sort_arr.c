#include <stdio.h>
#include <math.h>

int digit_count(int num) {
    int count = 0;

    if (num == 0) return 1;

    while (num != 0) {
        num /= 10;
        count++;
    }
    
    return count;
}

int get_max_digit_count(int arr[], int size) {
    int max_d_count = 0;

    for (int i = 0; i < size; i++) {
        int digits = digit_count(arr[i]);

        if (digits > max_d_count) {
            max_d_count = digits;
        }
    }

    return max_d_count;
}

int get_digit(int num, int pos) {
    int pow_10 = (int)pow(10, pos);
    return (num / pow_10) % 10;
}

void counting_sort(int arr[], int n, int pos) {
    int count_arr[10] = { 0,0,0,0,0,0,0,0,0,0 };
    int output_arr[n];

    // building the counting array
    for (int i = 0; i < n; i++) {
        int num = get_digit(arr[i], pos);
        count_arr[num]++;
    }

    // changing the count_arr to the prefix sum cumulative array for the last index position of every digit
    for (int i = 1; i < 10; i++) {
        count_arr[i] = count_arr[i] + count_arr[i - 1];
    }

    // traversating output array from right to left and setting the output array(right to left for stability in order)
    for (int i = n - 1; i >= 0; i--) {
        int digit = get_digit(arr[i], pos);
        output_arr[count_arr[digit] - 1] = arr[i];
        count_arr[digit]--;
    }

    // copy and replace by the index i the sorted elements from output array to the input array
    for (int i = 0; i < n; i++) {
        arr[i] = output_arr[i];
    }

}

void radix_sort(int arr[], int size) {
    int d = get_max_digit_count(arr, size);

    for (int i = 0; i < d; i++) {
        counting_sort(arr, size, i);
    }
    
}

int main(void) {
    int arr[] = { 802, -2, 24, -45, 66, -170, 75, 90 };
    int size = sizeof(arr) / sizeof(arr[0]);
    
    // Count negative and positive numbers
    int neg[size], pos[size];
    int negCount = 0, posCount = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            neg[negCount++] = -arr[i]; // convert to positive
        } else {
            pos[posCount++] = arr[i];
        }
    }

    // Sort negatives and positives separately(both positives while sorting)
    radix_sort(neg, negCount);
    radix_sort(pos, posCount);

    // Rebuild arr[] but negatives reserved first
    int index = 0; // for insertion order

    // first do negetive(in reversed order)
    for (int i = negCount - 1; i >= 0; i--) {
        arr[index++] = -neg[i]; // convert to negative
    }

    // Then positives
    for (int i = 0; i < posCount; i++) {
        arr[index++] = pos[i];
    }

    // now print the sorted array
    printf("Printing the sorted array after radix sort:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}