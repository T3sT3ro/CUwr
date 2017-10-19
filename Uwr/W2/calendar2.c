//
// Created by Tooster on 2017-10-19.
//

// Maksymilian Polarczyk
// Lista 2 zadanie kalendarz

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windef.h>

#define MAX_YEAR 3000
#define LEAP_YEAR(y) (((y) % 4 == 0 && (y) % 100 != 0) || (y) % 400 == 0)

struct tm today; //current time;

/// initialize struct today
void initDate() {
    // initialize current date
    time_t t = time(NULL);
    today = *localtime(&t);
    today.tm_year += 1900;
    today.tm_mon++; // make months start from 1
    // check documentation of tm to see why such initialization
}


int isDateOk(int dd, int mm, int yyyy) {
    // too small
    if (yyyy < 1 || mm < 1 || dd < 1) return false; // illegal input string
    if (yyyy < today.tm_year) return false;            // year in the past
    if (yyyy == today.tm_year && mm < today.tm_mon) return false;  //month in the past
    if (yyyy == today.tm_year && mm == today.tm_mon && dd <= today.tm_mday) return false; //day in the past
    // too big
    if (yyyy > MAX_YEAR) return false;
    if (dd > 31 || mm > 12) return false; // month too big
    if (mm <= 7 && mm % 2 == 0 && dd > 30) return false;  // months Jan-July with 30 days
    if (mm >= 8 && mm % 2 == 1 && dd > 30) return false; // months Aug-Dec with 30 days
    // leap year
    if (mm == 2 && LEAP_YEAR(yyyy) && dd > 29) return false;
    if (mm == 2 && !LEAP_YEAR(yyyy) && dd > 28) return false;
    return true;
}

/// returns number of leap years in range [0,yyyy]
int getLeapYearsBefore(int yyyy) {
    // yyyy/100 are number of years that weren't leap years
    // yyyy/400 are number of years that actually were leap years
    return yyyy / 4 - yyyy / 100 + yyyy / 400;
}

/// returns integer representing date as nth day of the year
int nthDayFromDate(int dd, int mm, int yyyy) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //regular month
    if (LEAP_YEAR(yyyy)) // case: leap year => february = 29 days
        daysInMonth[1] = 29;
    int days = dd;
    for (int i = 0; i < mm - 1; ++i) // cuz months start from 1
        days += daysInMonth[i];
    return days;
}

/// returns day of the month for given date as char*
char *getDayOfTheWeek(int dd, int mm, int yyyy) {
    char *daysNames[] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};

    int days;
    if (yyyy == today.tm_year)   // CASE 1: dates in same year
        days = nthDayFromDate(dd, mm, yyyy) - nthDayFromDate(today.tm_mday, today.tm_mon, today.tm_year);
    else { // CASE 2: dates in different years
        days = 365;
        if (LEAP_YEAR(today.tm_year))
            days++;
        days -= nthDayFromDate(today.tm_mday, today.tm_mon, today.tm_year); // how many to the end of the year
        days += nthDayFromDate(dd, mm, yyyy); // how many from the beginning
    }
    days += max(0, yyyy - today.tm_year - 1) * 365; // add 365*number of years between dates
    days += max(0, getLeapYearsBefore(yyyy - 1) -
                   getLeapYearsBefore(today.tm_year)); // add 1 for each leap year in (today, yyyy)

    int dayOfTheWeek = (today.tm_wday + days) % 7;
    return daysNames[dayOfTheWeek];
}


int main() {
    initDate();
    int dd, mm, yyyy;
    printf("Please, input a future date till 31.12.3000\n");
    printf("in format dd.mm.yyyy\n");
    printf("To stop the program, input -1\n");
    while (true) {
        printf("> ");

        scanf("%d", &dd); // exit
        if (dd == -1) break;

        scanf(".%d.%d", &mm, &yyyy);
        if (isDateOk(dd, mm, yyyy))
            printf("   is %s\n", getDayOfTheWeek(dd, mm, yyyy));
        else
            printf("! invalid date !\n");
    }
    return 0;
}

