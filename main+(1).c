#include "event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define RESET  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
int main() {

  Year *Patitin = createYear(-1);
  Stack *outdate = createStack(100);
  char buffer[10];
  int cmd;

  int year = -1, month = -1, day = -1, favorite = -1;
  char start[12], end[12], event[3000];

  // DailyNotification
  displayCurrentDateTask(Patitin);
  readTextFile(Patitin);

  while (1) {

    // Clear Outdated
    cleanOutdatedData(Patitin, outdate);

    // Main function
    printf("-----------------------\n");
    printf(CYN"1  - Create task\n");
    printf("2  - Display all task\n");
    printf("3  - Display Outdated\n");
    printf("4  - Display Favorited\n");
    printf("5  - Delete task\n");
    printf("6  - Search\n");
    printf("7  - Edit\n");
    printf("99 - Exit\n"RESET);
    printf("Insert command :");
    
    fgets(buffer, 10, stdin);
    enterRemover(buffer);
    while (sscanf(buffer, "%d", &cmd) != 1) {
      printf("wrong command format please try again\n");
      printf("Inset command :");
      fgets(buffer, 10, stdin);
      enterRemover(buffer);
    }

    if (cmd == 1) {
      userInput(&year, &month, &day, start, end, event, &favorite, 1);
      insert(Patitin, year, month, day, start, end, event, favorite);
    }

    else if (cmd == 2) {
      int allTask = 0;
      displayAll(Patitin, 2, &allTask);
    }

    else if (cmd == 3) {
      displayOutdated(outdate);
    }

    else if (cmd == 4) {
      displayFavorite(Patitin);
    }

    else if (cmd == 5) {
      printf("Please input date to show all Lists in that day\n");
      userInput(&year, &month, &day, start, end, event, &favorite, 2);
      deleteEvent(Patitin, outdate, year, month, day);
    }

    else if (cmd == 6) {
      printf(YEL"Please insert date and name to search\n");
      printf("(leave \"--\" if don't want to search in that fields)\n");
      printf("*** for now you can only search by only one fields at the time "
             "***\n"RESET);
      userInput(&year, &month, &day, start, end, event, &favorite, 3);

      // searchByDate
      if (day != -1 && month != -1 && year != -1 && !strcmp(event, "--")) {
        displayByDate(Patitin, year, month, day);
      }
      // searchByDay
      else if (day != -1 && month == -1 && year == -1 && !strcmp(event, "--")) {
        displayByDay(Patitin, day);
      }
      // searchByMonth
      else if (day == -1 && month != -1 && year == -1 && !strcmp(event, "--")) {
        displayByMonth(Patitin, month);
      }
      // searchByYear
      else if (day == -1 && month == -1 && year != -1 && !strcmp(event, "--")) {
        displayByYear(Patitin, year);
      }
      // searchByName
      else if (day == -1 && month == -1 && year == -1 && strcmp(event, "--")) {
        displayByEvent(Patitin, event);
      }
    }

    else if (cmd == 7) {
      printf(YEL"Please input date to show all Lists in that day\n"RESET);
      userInput(&year, &month, &day, start, end, event, &favorite, 2);
      edit(Patitin, year, month, day);
    }

    else if (cmd == 99)
      return 0;
    saveToText(Patitin);
    saveToOutdated(outdate);
  }

  return 0;
}
