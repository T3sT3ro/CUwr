#include <stdio.h>

/*
 * Program for checking if number is narcissistic.
 * @author Tooster
 */
void narcissistic(long long number) { // whole isn't integer, so why not a negative ?
    if (number == 0) {    //handle zero separately
        printf("TAK\n");
        return;
    }

    long long tmp = number; //universal temporary variable
    unsigned short digits = 0;
    while (tmp != 0) {
        tmp /= 10;
        digits++;
    }

    if (digits % 2 == 0 && number < 0) { //handle negative numbers
        printf("NIE\n");
        return;
    } else if (digits % 2 == 1 && number < 0)
        number *= -1; //if number of digits is odd and number is < 0, make it positive


    long long sum = 0;
    long long current = number; //current will be repeatedly divided by 10;
    for (int i = 0; i < digits; ++i) {
        long long current_digit = current % 10; //separate rightmost digit
        tmp = current_digit;    //tmp will be the current_digit^digits
        for (int j = 0; j < digits - 1; ++j) {  //simple, brute power by repetitive multiplication
            if (tmp > number - sum) { //early exit if we go beyond anticipated number
                printf("NIE\n");
                return;
            }
            tmp *= current_digit;

        }
        sum += tmp;
        current /= 10;    //handle next digit
    }

    if (sum == number) printf("TAK\n");
    else
        printf("NIE\n");
}

int narcissistic_main() {

    //9999998888888777777
    long long number;
    scanf("%lld", &number);
    narcissistic(number);

    return 0;
}