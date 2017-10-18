//
// Created by Tooster on 18.10.17.
//

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_YEAR 3000

struct tm tm; //current time;

int isDateOk(int dd, int mm, int yyyy){
    // too small
    if(yyyy < 0 || mm < 0 || dd < 0) return false; // illegal input string
    if(yyyy < tm.tm_year) return false;            // year in the past
    if(yyyy == tm.tm_year && mm < tm.tm_mon) return false;  //month in the past
    if(yyyy == tm.tm_year && mm == tm.tm_mon && dd <= tm.tm_mday) return false; //day in the past
    // too big
    if(yyyy > MAX_YEAR) return false;
    if(dd > 31 || mm > 12) return false; // month too big
    if(mm <= 7 && mm%2==0 && dd >30) return false;  // months Jan-July with 30 days
    if(mm >= 8 && mm%2==1 && dd >30 ) return false; // months Aug-Dec with 30 days
    // irregular
    if(mm == 2 && !((yyyy % 4 == 0 && yyyy % 100 !=0) || yyyy%400 == 0) && dd > 28) return false; //regular year, Feb with 29
    return true;
}

char* getDayOfTheWeek(int dd, int mm, int yyyy){
    char* days[] = {"saturday", "sunday", "monday", "tuesday", "wednesday", "thursday", "friday"};
    //Zeller's congruence - https://en.wikipedia.org/wiki/Zeller%27s_congruence
    int m = mm;
    if(mm < 3){
        mm = 12+m;
        yyyy--;
    }
    int day = (dd + ((13 * (mm + 1)) / 5) + yyyy + (yyyy/4) - (yyyy/100) + (yyyy/400)) % 7;
    return days[day];
}

int main(){
    // initialize current date
    time_t t = time(NULL);
    tm = *localtime(&t);
    tm.tm_year+=1900;
    tm.tm_mon++;
    //
    int dd, mm, yyyy;
    printf("Please, input a future date till 31.12.3000\n");
    printf("in format dd.mm.yyyy\n");
    printf("To stop the program, input -1\n");
    while(true) {
        printf("> ");

        scanf("%d", &dd); // exit
        if(dd == -1) break;

        scanf(".%d.%d",&mm, &yyyy);
        if (isDateOk(dd, mm, yyyy))
            printf("   is %s\n", getDayOfTheWeek(dd, mm, yyyy));
        else
            printf("   ! invalid date !\n");
    }
    return 0;
}

