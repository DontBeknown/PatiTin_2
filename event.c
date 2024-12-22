#include "event.h"
#include <ctype.h>>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//initialize stack
Stack *createStack(int size) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->top = -1;
  stack->size = size;
  return stack;
}
//append data at top of stack
void push(Stack *stack, Year *curYear) {
  if (stack->top == stack->size - 1) {
    printf("Error: Stack is full!\nYou must delete some outdated data\n");
    return;
  }
  stack->arr[++stack->top] = curYear;
}
//iterate to second top of stack
void pop(Stack *stack) {
  if (stack->top == -1) {
    printf("Error: Something went wrong.!\n");
    return;
  }
  stack->top--;
}
//return top data of stack
Year *peek(Stack *stack) {
  if (stack->top == -1) {
    printf("No outdated event yet\n");
    return NULL;
  }
  return stack->arr[stack->top];
}
//Clear whitespace at begin and tail of the text
void trim(char *str) {
  int len = strlen(str);
  int st = 0, en = len - 1;
  //create two pointer
  //isspace-> (if(str[i]==' ')) include from ctype.h
  while (isspace(str[st])) {
    st++;
  }
  while (en > st && isspace(str[en])) {
    en--;
  }
  //mark the end of string as NULL then use memmove to copy a block of memory from a location to another
  str[en + 1] = '\0';
  memmove(str, str + st, en - st + 2);
}
//remove enter at the last of string
void enterRemover(char *str) {
  if (str[strlen(str) - 1] == '\n') {
    str[strlen(str) - 1] = '\0';
  }
}
//check if event outdated or not
int isOutdatedData(int year, int month, int day, char *eventTime) {
  int yearTime, monthTime, dayTime;
  char nowTime[12];
  time_t current_time;
  struct tm *time_info;
  char date_string[20];

  // Get the current time
  current_time = time(NULL);

  // Convert the current time to local time
  time_info = localtime(&current_time);

  // Format the date string
  strftime(date_string, sizeof(date_string), "%d/%m/%y", time_info);
  strftime(nowTime, sizeof(nowTime), "%H:%M", time_info);

  sscanf(date_string, "%d/%d/%d", &dayTime, &monthTime, &yearTime);

  unsigned int status = 0;
  if ((year < yearTime)) {
    status = 1;
  } else if ((year == yearTime) && (month < monthTime)) {
    status = 1;
  } else if ((year == yearTime) && (month == monthTime) && (day < dayTime)) {
    status = 1;
  } else if ((year == yearTime) && (month == monthTime) && (day == dayTime) &&
             (strcmp(eventTime, nowTime) == -1)) {
    status = 1;
  }
  return status;
}
//check that user fill -- or not when input in date field
int findDateBlank(char *date, int *day, int *month, int *year) {

  int ch1 = 0, ch2 = 0, ch3 = 0;
  char *dayStr = strtok(date, "/");
  char *monthStr = strtok(NULL, "/");
  char *yearStr = strtok(NULL, "\n");
  
  if (dayStr == NULL || monthStr == NULL || yearStr == NULL)
    return 0;
  
  if (strcmp(dayStr, "--") == 0) {
    *day = -1;
    ch1 = 1;
  } else {
    if (sscanf(dayStr, "%d", day) == 1)
      ch1 = 1;
  }

  if (strcmp(monthStr, "--") == 0) {
    *month = -1;
    ch2 = 1;
  } else {
    if (sscanf(monthStr, "%d", month) == 1)
      ch2 = 1;
  }

  if (strcmp(yearStr, "--") == 0) {
    *year = -1;
    ch3 = 1;
  } else {
    if (sscanf(yearStr, "%d", year) == 1)
      ch3 = 1;
  }

  if (ch1 && ch2 && ch3)
    return 1;
  else
    return 0;
}

//check that user fill -- or not when input in time field
int findTimeBlank(char *time) {

  int hour, minute;

  if (!strcmp(time, "--"))
    return 1;

  if (sscanf(time, "%d:%d", &hour, &minute) != 2) {

    return 0;
  }
  // validate hour and minute
  if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {

    return 0;
  }

  return 1;
}

//check that user fill -- or not when input in favorite field 
int findFavBlank(char *buffer, int *fav) {

  if (strcmp(buffer, "--") == 0) {
    *fav = -2;
    return 1;
  } else {
    if (sscanf(buffer, "%d", fav) == 1) {
      if (*fav < -1) {
        return 0;
      } else {
        return 1;
      }
    }
  }
  return 0;
}

//validate the date input from user by passing string
int validateDate(char *date) {
  int day, month, year;
  // check does user input in the right format
  if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
    return 0;
  }

  // validate day month year
  if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
    return 0;

  // check for leap year
  if (month == 2) {
    int maxFebDay = 28;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
      maxFebDay = 29;
    }
    if (day < 1 || day > maxFebDay) {
      return 0;
    }
  }

  // check day in month that have 30 day
  if (month == 4 || month == 6 || month == 9 || month == 11) {
    if (day < 1 || day > 30) {
      return 0;
    }
  }
  
  return 1;
}
//validate the date input from user by passing integer
int validateDateNum(int year, int month, int day) {

  // validate day month year
  if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
    return 0;
    
  // check for leap year
  if (month == 2) {
    int maxFebDay = 28;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
      maxFebDay = 29;
    }
    if (day < 1 || day > maxFebDay) {
      return 0;
    }
  }

  // check day in month that have 30 day
  if (month == 4 || month == 6 || month == 9 || month == 11) {
    if (day < 1 || day > 30) {
      return 0;
    }
  }

  return 1;
}
//validate the time input from user
int validateTime(char *time) {

  int hour, minute;
  // check does user input in the right format
  if (sscanf(time, "%d:%d", &hour, &minute) != 2) {
    return 0;
  }
  // validate hour and minute
  if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
    return 0;

  return 1;
}
    
//initialize Event node
Event *createEvent(char *str, char start[], char end[], int favorite) {
  Event *tmp = (Event *)malloc(sizeof(Event));
  tmp->event = (char *)malloc((sizeof(char) * strlen(str)) + 1);
  strcpy(tmp->event, str);
  strcpy(tmp->startTime, start);
  strcpy(tmp->endTime, end);
  tmp->favorite = favorite;
  tmp->next = NULL;
  return tmp;
}

//initialize Day node
Day *createDay(int day) {
  Day *tmp = (Day *)malloc(sizeof(Day));
  tmp->day = day;
  tmp->event = NULL;
  tmp->next = NULL;
  return tmp;
}
    
//initialize Month node
Month *createMonth(int month) {
  Month *tmp = (Month *)malloc(sizeof(Month));
  tmp->month = month;
  tmp->day = NULL;
  tmp->next = NULL;
  return tmp;
}

//initialize Year node
Year *createYear(int year) {
  Year *tmp = (Year *)malloc(sizeof(Year));
  tmp->year = year;
  tmp->month = NULL;
  tmp->next = NULL;
  return tmp;
}

//search specific year
Year *searchByYear(Year *curYear, Year **prev, int year) {
  Year *current = curYear;
  while (current != NULL) {
    if (current->year == year) {
      return current;
    }
    //Keep track previousNode by prev
    *prev = current;
    current = current->next;
  }
  // Don't have any tasks on that year return NULL
  *prev = NULL;
  return current;
}

//search year in the stack if that year is already outdated
Year *searchByYearFromOutdated(Stack *outdated, int year) {
  int prevTop = outdated->top;
  //iterate over stack
  while (outdated->top != -1) {
    Year *headYear = peek(outdated);
    Year *current = headYear->next;
    if (current->year == year) {
      outdated->top = prevTop;
      //find that year and return current node
      return current;
    }
    pop(outdated);
  }
  outdated->top = prevTop;
  // Don't have any tasks on that Date return NULL
  return NULL;
}

//search specific month
Month *searchByMonth(Month *curMonth, Month **prev, int month) {
  Month *current = curMonth;
  while (current != NULL) {
    if (current->month == month) {
      return current;
    }
    *prev = current;
    current = current->next;
  }
  // Don't have any tasks on that month return NULL
  *prev = NULL;
  return current;
}

//search specific day
Day *searchByDay(Day *curDay, Day **prev, int day) {
  Day *current = curDay;
  while (current != NULL) {
    if (current->day == day) {
      return current;
    }
    *prev = current;
    current = current->next;
  }
  // Don't have any tasks on that day return NULL
  *prev = NULL;
  return current;
}

//search specific date
Day *searchByDate(Year *headYear, int year, int month, int day) {
  Year *prevYear = headYear;
  Year *tmpYear = searchByYear(headYear->next, &prevYear, year);
  //That year have some tasks
  if (tmpYear != NULL) {
    Month *prevMonth = tmpYear->month;
    Month *tmpMonth = searchByMonth(tmpYear->month->next, &prevMonth, month);
    //That month have some tasks
    if (tmpMonth != NULL) {
      Day *prevDay = tmpMonth->day;
      Day *tmpDay = searchByDay(tmpMonth->day, &prevDay, day);
      //That day have some tasks and return pointer of day's node
      if (tmpDay != NULL) {
        return tmpDay;
      }
    }
  }
  // Don't have any tasks on that Date.
  return NULL;
}

//search specific date in stack
Day *searchByDateFromOutdated(Stack *outdated, int year, int month, int day) {
  int prevTop = outdated->top;
  //iterate data over stack
  while (outdated->top != -1) {
    Year *headYear = peek(outdated);
    Year *prevYear = headYear;
    Year *tmpYear = searchByYear(headYear->next, &prevYear, year);
    //That year have some tasks
    if (tmpYear != NULL) {
      Month *prevMonth = tmpYear->month;
      Month *tmpMonth = searchByMonth(tmpYear->month->next, &prevMonth, month);
      //That month have some tasks
      if (tmpMonth != NULL) {
        Day *prevDay = tmpMonth->day;
        Day *tmpDay = searchByDay(tmpMonth->day, &prevDay, day);
        //That day have some tasks and return pointer of day's node
        if (tmpDay != NULL) {
          outdated->top = prevTop;
          return tmpDay;
        }
      }
    }
    pop(outdated);
  }
  outdated->top = prevTop;
  // Don't have any tasks on that Date.
  return NULL;
}

//show local time
void displayCurrentTime() {
  int yearTime, monthTime, dayTime;
  char nowTime[12];
  time_t current_time;
  struct tm *time_info;
  char date_string[20];

  // Get the current time
  current_time = time(NULL);

  // Convert the current time to local time
  time_info = localtime(&current_time);

  // Format the date string
  strftime(date_string, sizeof(date_string), "%d/%m/%y", time_info);
  strftime(nowTime, sizeof(nowTime), "%H:%M", time_info);
  // Print the current date and local time
  sscanf(date_string, "%d/%d/%d", &dayTime, &monthTime, &yearTime);
  printf("-----------------------\n");
  printf("Date : %d/%d/%d\n", dayTime, monthTime, yearTime);
  printf("Time : %s\n", nowTime);
}

//show task that user mark favorite when create task or edit favourite on that task 
void displayFavorite(Year *headYear) {
  Year *curYear = headYear->next;
  if (curYear == NULL) {
    printf("No task\n");
  } else {
    while (curYear) {
      Month *curMonth = curYear->month->next;
      while (curMonth) {
        Day *curDay = curMonth->day->next;
        while (curDay) {
          Event *curEvent = curDay->event->next;
          while (curEvent) {
            if (curEvent->favorite != -1) {
              printf("Year: %d Month: %d  Day: %d Task: %s Time: %s - %s "
                     "Favorite: %d\n",
                     curYear->year, curMonth->month, curDay->day,
                     curEvent->event, curEvent->startTime, curEvent->endTime,
                     curEvent->favorite);
            }
            curEvent = curEvent->next;
          }
          curDay = curDay->next;
        }
        curMonth = curMonth->next;
      }
      curYear = curYear->next;
    }
  }
}



//Show all no-outdated event that have same task with user input
void displayByEvent(Year *headYear, char eventName[]) {
  printf("-----------------------\n");
  Year *curYear = headYear->next;
  if (curYear == NULL) {
    printf("No task\n");
  } else {
    while (curYear) {
      Month *curMonth = curYear->month->next;
      while (curMonth) {
        Day *curDay = curMonth->day->next;
        while (curDay) {
          Event *curEvent = curDay->event->next;
          int id = 1;
          while (curEvent) {
            //Check that task have the same name with user input or not
            if (!strcmp(eventName, curEvent->event)) {
              printf("Year: %d Month: %d  Day: %d\n", curYear->year,
                     curMonth->month, curDay->day);
              printf("   Task#%d %s - %s: %s\n", id, curEvent->startTime,
                     curEvent->endTime, curEvent->event);
            }
            curEvent = curEvent->next;
            id++;
          }
          curDay = curDay->next;
        }
        curMonth = curMonth->next;
      }
      curYear = curYear->next;
    }
  }

  printf("\n");
}

//display all tasks that exist on day node 
void displayDayTask(Day *curDay) {
  Event *curEvent = curDay->event->next;
  int id = 1;
  while (curEvent) {
    printf("   Task#%d %s - %s: %s\n", id, curEvent->startTime,
           curEvent->endTime, curEvent->event);
    curEvent = curEvent->next;
    id++;
  }
}

//display all task that exist on the specific date
void displayByDate(Year *headYear, int year, int month, int day) {
  Day *current = searchByDate(headYear, year, month, day);
  if (current) {
    printf("Year: %d Month: %d Day: %d\n", year, month, day);
    displayDayTask(current);
  } else {
    printf("No task\n");
  }
}

//display all task that exist on the specific day
void displayByDay(Year *headYear, int day) {
  Year *curYear = headYear->next;
  while (curYear) {
    Month *headMonth = curYear->month;
    Month *curMonth = headMonth->next;
    while (curMonth) {
      Day *headDay = curMonth->day;
      Day *prevDay = headDay;
      Day *curDay = searchByDay(headDay->next, &prevDay, day);
      if (curDay) {
        printf("Year: %d Month: %d Day: %d\n", curYear->year, curMonth->month,
               curDay->day);
        displayDayTask(curDay);
      }
      curMonth = curMonth->next;
    }

    curYear = curYear->next;
  }
}

//display all task in the current day
void displayCurrentDateTask(Year *headYear) {
  // Get RealTimeDate
  int yearTime, monthTime, dayTime;
  char nowTime[12];
  time_t current_time;
  struct tm *time_info;
  char date_string[20];

  // Get the current time
  current_time = time(NULL);

  // Convert the current time to local time
  time_info = localtime(&current_time);

  // Format the date string
  strftime(date_string, sizeof(date_string), "%d/%m/%y", time_info);
  strftime(nowTime, sizeof(nowTime), "%H:%M", time_info);
  // Print the current date and local time
  sscanf(date_string, "%d/%d/%d", &dayTime, &monthTime, &yearTime);

  // Daily notification
  printf("Today tasks: \n");
  displayByDate(headYear, yearTime, monthTime, dayTime);
}

//display all task that exist on the specific month
void displayByMonth(Year *headYear, int month) {
  Year *curYear = headYear->next;
  while (curYear) {
    Month *headMonth = curYear->month;
    Month *prevMonth = headMonth;
    Month *curMonth = searchByMonth(headMonth->next, &prevMonth, month);
    if (curMonth) {
      Day *headDay = curMonth->day;
      Day *curDay = headDay->next;
      while (curDay) {
        printf("Year: %d Month: %d Day: %d\n", curYear->year, month,
               curDay->day);
        displayDayTask(curDay);
        curDay = curDay->next;
      }
    } else {
      printf("Year: %d - Don't have any tasks in that year\n", curYear->year);
    }
    curYear = curYear->next;
  }
}

//display all task that exist on the specific year
void displayByYear(Year *headYear, int year) {
  Year *prevYear = headYear;
  Year *curYear = searchByYear(headYear, &prevYear, year);

  //Check if we have any tasks on that year
  if (curYear) {
    printf("Year: %d", year);
    Month *headMonth = curYear->month;
    Month *curMonth = headMonth->next;
    while (curMonth) {
      printf("\nMonth %d\n", curMonth->month);
      Day *headDay = curMonth->day;
      Day *curDay = headDay->next;
      while (curDay) {
        printf("Day %d:\n", curDay->day);
        displayDayTask(curDay);
        curDay = curDay->next;
      }
      curMonth = curMonth->next;
    }
  } else {
    printf("Don't have any tasks in that year\n");
  }
}

//display the outdated task (Order by the nearest current time)
void displayOutdated(Stack *outdated) {
  int prevTop = outdated->top;
  // iterate over stack
  while (outdated->top != -1) {
    Year *outdatedHeadYear = peek(outdated);
    // display all outdated task in that year
    displayByYear(outdatedHeadYear, outdatedHeadYear->next->year);
    pop(outdated);
  }
  outdated->top = prevTop;
}

//display all tasks
void displayAll(Year *headYear, int opr, int *allTask) {
  printf("-----------------------\n");
  Year *curYear = headYear->next;
  int id = 1;
  if (curYear == NULL) {
    printf("No task\n");
  } else {
    // Use to edit event
    if (opr == 1) {
      id = 1;
    }
    while (curYear) {
      printf("Year: %d\n", curYear->year);
      Month *curMonth = curYear->month->next;
      while (curMonth) {
        printf("  Month: %d\n", curMonth->month);
        Day *curDay = curMonth->day->next;
        while (curDay) {
          printf("     Day: %d\n", curDay->day);
          Event *curEvent = curDay->event->next;
          // Display normally
          if (opr == 2) {
            id = 1;
          }
          while (curEvent) {
            printf("       Task#%d %s - %s: %s\n", id, curEvent->startTime,
                   curEvent->endTime, curEvent->event);
            curEvent = curEvent->next;
            id++;
            *allTask++;
          }
          curDay = curDay->next;
        }
        
        curMonth = curMonth->next;
      }
      
      curYear = curYear->next;
    }
  }

  printf("\n");
}

//delete first event (like dequeue on queue)
void deleteFirstEvent(Year* headYear, int number, int year, int month, int day, int* status){

    Day* curDay = searchByDate(headYear,year,month,day);
    //Of course, curDay won't be null

    while(number--){
        Event* headEvent = curDay->event;
        Event* prevEvent = headEvent;
        Event* curEvent  = headEvent->next;
        prevEvent->next  = curEvent->next;
        free(curEvent);

        //If don't have any task left then free that day
        if(headEvent->next == NULL){
            //free head of event in that day
            free(headEvent);

            //prev will keep track on node to delete that node;
            Year* prevYear = headYear;
            Year* tmpYear = searchByYear(headYear->next,&prevYear,year);

            Month* headMonth = tmpYear->month;
            Month* prevMonth = headMonth;
            Month* tmpMonth = searchByMonth(tmpYear->month->next,&prevMonth,month);

            Day* headDay = tmpMonth->day;
            Day* prevDay = headDay;
            Day* tmpDay = searchByDay(tmpMonth->day->next,&prevDay,day);


            prevDay->next = tmpDay->next;
            free(tmpDay);
            //If don't have any task left on any days in that month then free that month
            if(headDay->next == NULL){
                free(headDay);

                prevMonth->next = tmpMonth->next;
                free(tmpMonth);

                //If don't have any task left on any months in that year then free that year
                if(headMonth->next == NULL){
                    free(headMonth);

                    prevYear->next = tmpYear->next;
                    free(tmpYear);
                    //free year already and turn status to 1
                    *status = 1;

                }
            }

        }
    }


}

// delete the task that on the selected date
void deleteEvent(Year *headYear, Stack *outdated, int year, int month,
                 int day) {
  char buffer[120];

  Day *curDay = searchByDate(headYear, year, month, day);
  Day *curOutdatedDay = searchByDateFromOutdated(outdated, year, month, day);
  int id = 1;
  // display the task that doesn't outdated on that day
  if (curDay) {
    printf("Year: %d Month: %d Day: %d\n", year, month, day);
    Event *curEvent = curDay->event->next;
    while (curEvent) {
      printf("   Task#%d %s - %s: %s\n", id, curEvent->startTime,
             curEvent->endTime, curEvent->event);
      curEvent = curEvent->next;
      id++;
    }
  }
  // display the task that already outdated on that day
  if (curOutdatedDay) {
    printf("--------------OUTDATED!!!--------------\n");
    printf("Year: %d Month: %d Day: %d\n", year, month, day);
    Event *curEvent = curOutdatedDay->event->next;
    while (curEvent) {
      printf("   Task#%d %s - %s: %s\n", id, curEvent->startTime,
             curEvent->endTime, curEvent->event);
      curEvent = curEvent->next;
      id++;
    }
  }
  //No task on that day
  if (!curDay && !curOutdatedDay) {
    printf("Sorry you don't have any task in that date\n");
    return;
  }
    
  // let the user select task to delete
  int task = 0;
  printf("Select Task that you want to delete by number: ");
  fgets(buffer, 120, stdin);
  enterRemover(buffer);
  sscanf(buffer, "%d", &task);
  while (task < 1 || task > id) {
    printf("Please select in the range (1-%d): \n", id);
    fgets(buffer, 120, stdin);
    enterRemover(buffer);
    sscanf(buffer, "%d", &task);
  }
  id = 1;
  //Delete part
  if (curDay) {
    Event *curEvent = curDay->event->next;
    Event *prevEvent = curDay->event;
    while (curEvent) {
      if (id == task) {
        printf("Remember delete can't be undo\n");
        int choice = 0;
        while (choice != 1 && choice != 2) {
          printf("Choice 1: Yes (Delete it)\n");
          printf("Choice 2: No (Cancel it)\n");
          printf("Select choice : ");
          fgets(buffer, 120, stdin);
          enterRemover(buffer);
          sscanf(buffer, "%d", &choice);
        }
        if (choice == 1) {

          Event *headEvent = curDay->event;
          prevEvent->next = curEvent->next;
          free(curEvent);

          // If don't have any task left then free that day
          if (headEvent->next == NULL) {
            // free head of event in that day
            free(headEvent);

            // prev will keep track on node to delete that node;

            Year *prevYear = headYear;
            Year *tmpYear = searchByYear(headYear->next, &prevYear, year);

            Month *headMonth = tmpYear->month;
            Month *prevMonth = headMonth;
            Month *tmpMonth =
                searchByMonth(tmpYear->month->next, &prevMonth, month);

            Day *headDay = tmpMonth->day;
            Day *prevDay = headDay;
            Day *tmpDay = searchByDay(tmpMonth->day->next, &prevDay, day);

            prevDay->next = tmpDay->next;
            free(tmpDay);
            // If don't have any task left on any days in that month then free
            // that month;
            if (headDay->next == NULL) {
              free(headDay);

              prevMonth->next = tmpMonth->next;
              free(tmpMonth);

              // If don't have any task left on any months in that year then
              // free that year;
              if (headMonth->next == NULL) {
                free(headMonth);

                prevYear->next = tmpYear->next;
                free(tmpYear);
              }
            }
          }
          printf("Deletion Success!!!\n");
          return;
        } else {
          printf("Cancel Success!!!\n");
          return;
        }
      }
      id++;
      prevEvent = curEvent;
      curEvent = curEvent->next;
    }
  }
  // printf("******Outdatd Par******\n");
  //  all event in outdatedData
  if (curOutdatedDay) {
    Event *curEvent = curOutdatedDay->event->next;
    Event *prevEvent = curOutdatedDay->event;
    while (curEvent) {
      printf("Here %d %d\n", id, task);
      if (id == task) {
        printf("Remember delete can't be undo\n");
        int choice = 0;
        while (choice != 1 && choice != 2) {
          printf("Choice 1: Yes (Delete it)\n");
          printf("Choice 2: No (Cancel it)\n");
          printf("Select choice : ");
          fgets(buffer, 120, stdin);
          enterRemover(buffer);
          sscanf(buffer, "%d", &choice);
        }
        if (choice == 1) {

          Event *headEvent = curOutdatedDay->event;
          prevEvent->next = curEvent->next;
          free(curEvent);

          // If don't have any task left then free that day
          if (headEvent->next == NULL) {
            // free head of event in that day
            free(headEvent);

            // prev will keep track on node to delete that node;
            Year *outdatedHeadYear = searchByYearFromOutdated(outdated, year);
            Year *prevYear = outdatedHeadYear;
            Year *tmpYear = outdatedHeadYear->next;

            Month *outdatedHeadMonth = tmpYear->month;
            Month *prevMonth = outdatedHeadMonth;
            Month *tmpMonth =
                searchByMonth(tmpYear->month->next, &prevMonth, month);

            Day *outdatedHeadDay = tmpMonth->day;
            Day *prevDay = outdatedHeadDay;
            Day *tmpDay = searchByDay(tmpMonth->day->next, &prevDay, day);

            prevDay->next = tmpDay->next;
            free(tmpDay);
            // If don't have any task left on any days in that month then free
            // that month;
            if (outdatedHeadDay->next == NULL) {
              free(outdatedHeadDay);

              prevMonth->next = tmpMonth->next;
              free(tmpMonth);

              // If don't have any task left on any months in that year then
              // free that year;
              if (outdatedHeadMonth->next == NULL) {
                free(outdatedHeadMonth);

                prevYear->next = tmpYear->next;
                free(tmpYear);

                // shiff array

                outdatedHeadYear->next = NULL;
                int prevTop = outdated->top;
                int flag = 0;
                //  printf("Head %s\n",outdatedHeadYear->next);
                for (int i = 0; i <= prevTop; i++) {
                  if (flag == 1) {
                    
                    outdated->arr[i - 1] = outdated->arr[i];
                  }
                  if (outdated->arr[i]->next == NULL) {
                    
                    flag = 1;
                  }
                }
                if (flag == 1) {
                  outdated->top--;
                }
              }
            }
          }
          printf("Deletion Outdated Success!!!\n");
          return;
        } else {
          printf("Cancel Success!!!\n");
          return;
        }
      }
      id++;
      prevEvent = curEvent;
      curEvent = curEvent->next;
    }
  }
}

// create the task and insert into tree
void insert(Year *headYear, int year, int month, int day, char start[],
            char end[], char event[], int favorite) {

  // sort year (increasing order)
  Year *prevYear = headYear;
  Year *curYear = headYear->next;
  Year *tmpYear = searchByYear(curYear, &prevYear, year);

  //if tmpyear is NULL initialize header node for that year
  if (tmpYear == NULL) {
    Year *newYear = createYear(year);
    tmpYear = newYear;
    if (curYear == NULL) {
      headYear->next = newYear;
    } else if (curYear->year > year) {
      newYear->next = curYear;
      headYear->next = newYear;

    } else {
      while (curYear->next && curYear->next->year < year) {
        curYear = curYear->next;
      }
      newYear->next = curYear->next;
      curYear->next = newYear;
    }
    tmpYear->month = createMonth(-1);
  }

  // sort month
  Month *headMonth = tmpYear->month;
  Month *curMonth = headMonth->next;
  Month *prevMonth = headMonth;
  Month *tmpMonth = searchByMonth(curMonth, &prevMonth, month);

  //if tmpmonth is NULL initialize header node for that month
  if (tmpMonth == NULL) {
    Month *newMonth = createMonth(month);
    tmpMonth = newMonth;
    if (curMonth == NULL) {
      headMonth->next = newMonth;
    } else if (curMonth->month > month) {
      newMonth->next = curMonth;
      headMonth->next = newMonth;

    } else {
      while (curMonth->next && curMonth->next->month < month) {
        curMonth = curMonth->next;
      }
      newMonth->next = curMonth->next;
      curMonth->next = newMonth;
    }
    tmpMonth->day = createDay(-1);
  }

  // sort Day
  Day *headDay = tmpMonth->day;
  Day *curDay = headDay->next;
  Day *prevDay = headDay;
  Day *tmpDay = searchByDay(tmpMonth->day, &prevDay, day);

  //if tmpday is NULL initialize header node for that day
  if (tmpDay == NULL) {
    Day *newDay = createDay(day);
    tmpDay = newDay;
    if (curDay == NULL) {
      headDay->next = newDay;
    } else if (curDay->day > day) {
      newDay->next = curDay;
      headDay->next = newDay;

    } else {
      while (curDay->next && curDay->next->day < day) {
        curDay = curDay->next;
      }
      newDay->next = curDay->next;
      curDay->next = newDay;
    }
    tmpDay->event = createEvent("HEAD", "0", "0", -1);
  }

  // sort Star & End and if star and time is equal to another tasks it will sort by favorite (FCFS) 
  Event *headEvent = tmpDay->event;
  Event *curEvent = headEvent->next;
  Event *newEvent = createEvent(event, start, end, favorite);

  char curEventTime[12];
  char newEventTime[12];

  strcpy(newEventTime, strcat(start, end));

  if (curEvent != NULL) {
    strcpy(curEventTime, curEvent->startTime);
    strcat(curEventTime, curEvent->endTime);
    // strcpy(curEventTime,strcat(curEvent->startTime,curEvent->endTime));
  }

  if (curEvent == NULL) {
    headEvent->next = newEvent;
  }

  else if (strcmp(newEventTime, curEventTime) < 0) {
    newEvent->next = curEvent;
    headEvent->next = newEvent;
  }

  else {

    if (curEvent->next != NULL) {
      strcpy(curEventTime, curEvent->next->startTime);
      strcat(curEventTime, curEvent->next->endTime);
      while (curEvent->next && strcmp(newEventTime, curEventTime) > 0) {
        curEvent = curEvent->next;
        if (curEvent->next) {
          strcpy(curEventTime, curEvent->next->startTime);
          strcat(curEventTime, curEvent->next->endTime);
        }
      }
      if (strcmp(newEventTime, curEventTime) == 0) {
        if (favorite > curEvent->next->favorite) {
          newEvent->next = curEvent->next;

          curEvent->next = newEvent;

        } else {
          while (curEvent->next && (strcmp(newEventTime, curEventTime) == 0) &&
                 favorite <= curEvent->next->favorite) {
            curEvent = curEvent->next;

            if (curEvent->next) {
              strcpy(curEventTime, curEvent->next->startTime);
              strcat(curEventTime, curEvent->next->endTime);
            }
          }
          newEvent->next = curEvent->next;
          curEvent->next = newEvent;
        }
      }
    } else {
      newEvent->next = curEvent->next;
      curEvent->next = newEvent;
    }
  }
}


// get all input form user 
void userInput(int *year, int *month, int *day, char *start, char *end,
               char *event, int *favorite, int type) {

  // type 1 getAll (displayAll)
  // type 2 getDate (deleteEvent,editEvent(SelectPart))
  // type 3 forSearch (What to search)
  // type 4 forEdit (What to Edit)

  // get date DD/MM/YY
  // year = 20YY
  char buffer[120];
  if (type == 1 || type == 2) {

    printf("input dd/mm/yy (01/01/23): ");
    fgets(buffer, 120, stdin);
    enterRemover(buffer);
    while (!validateDate(buffer)) {
      printf("wrong format please try again\n");
      printf("input dd/mm/yy (01/01/23): ");
      fgets(buffer, 120, stdin);
      enterRemover(buffer);
    }
    sscanf(buffer, "%d/%d/%d;", day, month, year);
    
  }
  if (type == 3 || type == 4) {
    printf("input dd/mm/yy (01/01/23): ");
    fgets(buffer, 120, stdin);
    enterRemover(buffer);
    while (!findDateBlank(buffer, day, month, year)) {
      printf("wrong format please try again\n");
      printf("input dd/mm/yy (01/01/23): ");
      fgets(buffer, 120, stdin);
    }
  }

  // get start and end time XX:XX
  if (type == 4) {
    printf("input time to start and end in format (xx:yy)\n");
    printf("Time to start: ");
    fgets(start, 12, stdin);
    enterRemover(start);
    while (!findTimeBlank(start)) {
      printf("wrong format please try again\n");
      printf("input time in format (xx:yy)\n");
      printf("Time to start: ");
      fgets(start, 12, stdin);
      enterRemover(start);
    }

    printf("Time to end: ");
    fgets(end, 12, stdin);
    enterRemover(end);
    while (!findTimeBlank(end)) {
      printf("wrong format please try again\n");
      printf("input time in format (xx:yy)\n");
      printf("Time to end: ");
      fgets(end, 12, stdin);
      enterRemover(end);
    }
  }

  if (type == 1) {
    printf("input time to start and end in format (xx:yy)\n");
    printf("Time to start: ");
    fgets(start, 12, stdin);
    enterRemover(start);
    while (!validateTime(start)) {
      printf("wrong format please try again\n");
      printf("input time in format (xx:yy)\n");
      printf("Time to start: ");
      fgets(start, 12, stdin);
      enterRemover(start);
    }

    printf("Time to end: ");
    fgets(end, 12, stdin);
    enterRemover(end);
    while (!validateTime(end)) {
      printf("wrong format please try again\n");
      printf("input time in format (xx:yy)\n");
      printf("Time to end: ");
      fgets(end, 12, stdin);
      enterRemover(end);
    }

    while (!(strcmp(start, end) < 0)) {
      printf("uncorrect time period please time again\n");
      printf("input time to start and end in format (xx:yy)\n");
      printf("Time to start: ");
      fgets(start, 12, stdin);
      enterRemover(start);
      while (!validateTime(start)) {
        printf("wrong format please try again\n");
        printf("input time in format (xx:yy)\n");
        printf("Time to start: ");
        fgets(start, 12, stdin);
        enterRemover(start);
      }

      printf("Time to end: ");
      fgets(end, 12, stdin);
      enterRemover(end);
      while (!validateTime(end)) {
        printf("wrong format please try again\n");
        printf("input time in format (xx:yy)\n");
        printf("Time to end: ");
        fgets(end, 12, stdin);
        enterRemover(end);
      }
    }
  }

  //Get task name
  if (type == 1 || type == 3 || type == 4) {
    printf("Name your Task: ");
    fgets(event, 3000, stdin);
    trim(event);
    enterRemover(event);
  }

  // Get the favorite value
  if (type == 1) {
    printf("Please rate how important this task is\n");
    printf("insert \"-1\" if you think that not important\n");
    printf("input( any number that more than or equal zero ) : ");
    fgets(buffer, 120, stdin);
    enterRemover(buffer);
    sscanf(buffer, "%d", favorite);
    while (*favorite < -1) {
      printf("wrong format please try again\n");
      printf("Please rate how important this task is \n");
      printf("insert \"-1\" if you think that not important\n");
      printf("input( any number that more than zero ) : ");
      fgets(buffer, 120, stdin);
      enterRemover(buffer);
      sscanf(buffer, "%d", favorite);
    }
  }

  if (type == 4) {
    printf("Please rate how important this task is\n");
    printf("input( any number that more than or equal zero ) : ");
    fgets(buffer, 120, stdin);
    enterRemover(buffer);
    while (!findFavBlank(buffer, favorite)) {
      printf("%d\n", *favorite);
      printf("wrong format please try again\n");
      printf("Please rate how important this task is \n");
      printf("input( any number that more than zero ) : ");
      fgets(buffer, 120, stdin);
      enterRemover(buffer);
    }
  }

}
// Edit task by delete the old one and insert the edit one
void edit(Year *headYear, int year, int month, int day) {
  char buffer[120];
  Day *curDay = searchByDate(headYear, year, month, day);
  int id = 1;
  // Show the task that can be selected on that day
  if (curDay) {
    printf("Year: %d Month: %d Day: %d\n", year, month, day);
    Event *curEvent = curDay->event->next;
    while (curEvent) {
      printf("   Task#%d %s - %s: %s\n", id, curEvent->startTime,
             curEvent->endTime, curEvent->event);
      curEvent = curEvent->next;
      id++;
    }
  } else {
    printf("Sorry you don't have any task in that date\n");
    return;
  }
  // Select the task on that day
  int task = 0;
  printf("Select Task that you want to edit by number: ");
  fgets(buffer, 120, stdin);
  enterRemover(buffer);
  sscanf(buffer, "%d", &task);
  while (task < 1 || task > id) {
    printf("Please select in the range (1-%d): \n", id);
    fgets(buffer, 120, stdin);
    enterRemover(buffer);
    sscanf(buffer, "%d", &task);
  }

  int editYear = -1, editMonth = -1, editDay = -1, editFavorite = -1;
  char editStart[12], editEnd[12], editEvent[3000];

  Event *curEvent = curDay->event->next;
  Event *prevEvent = curDay->event;
  id = 1;
  while (curEvent) {
    if (id == task) {
    
      // Get What to edit
      printf("Please insert all data you want to edit\n");
      printf("(leave \"--\" if don't want to edit in that fields we will use "
             "the old ones)\n");
      userInput(&editYear, &editMonth, &editDay, editStart, editEnd, editEvent,
                &editFavorite, 4);
      
      //if that field has "--" keep old data
      if (editYear == -1)
        editYear = year;
      if (editMonth == -1)
        editMonth = month;
      if (editDay == -1)
        editDay = day;
      if (editFavorite == -2)
        editFavorite = curEvent->favorite;
      if (!strcmp(editStart, "--"))
        strcpy(editStart, curEvent->startTime);
      if (!strcmp(editEnd, "--"))
        strcpy(editEnd, curEvent->endTime);
      if (!strcmp(editEvent, "--"))
        strcpy(editEvent, curEvent->event);

      // check if user input was right 
      while (!validateDateNum(editYear, editMonth, editDay) ||
             !(strcmp(editStart, editEnd) < 0)) {
        printf("There is something wrong when using the new data and the old "
               "data together please try again\n");
        userInput(&editYear, &editMonth, &editDay, editStart, editEnd,
                  editEvent, &editFavorite, 4);
        if (editYear == -1)
          editYear = year;
        if (editMonth == -1)
          editMonth = month;
        if (editDay == -1)
          editDay = day;
        if (editFavorite == -2)
          editFavorite = curEvent->favorite;
        if (!strcmp(editStart, "--"))
          strcpy(editStart, curEvent->startTime);
        if (!strcmp(editEnd, "--"))
          strcpy(editEnd, curEvent->endTime);
        if (!strcmp(editEvent, "--"))
          strcpy(editEvent, curEvent->event);
      }

      // Delete
      Event *headEvent = curDay->event;
      prevEvent->next = curEvent->next;
      free(curEvent);

      // If don't have any task left then free that day
      if (headEvent->next == NULL) {
        // free head of event in that day
        free(headEvent);

        // prev will keep track on node to delete that node;
        Year *prevYear = headYear;
        Year *tmpYear = searchByYear(headYear->next, &prevYear, year);

        Month *headMonth = tmpYear->month;
        Month *prevMonth = headMonth;
        Month *tmpMonth =
            searchByMonth(tmpYear->month->next, &prevMonth, month);

        Day *headDay = tmpMonth->day;
        Day *prevDay = headDay;
        Day *tmpDay = searchByDay(tmpMonth->day->next, &prevDay, day);

        prevDay->next = tmpDay->next;
        free(tmpDay);
        // If don't have any task left on any days in that month then free that
        // month;
        if (headDay->next == NULL) {
          free(headDay);

          prevMonth->next = tmpMonth->next;
          free(tmpMonth);

          // If don't have any task left on any months in that year then free
          // that year;
          if (headMonth->next == NULL) {
            free(headMonth);

            prevYear->next = tmpYear->next;
            free(tmpYear);
          }
        }
      }
    }
    id++;
    prevEvent = curEvent;
    curEvent = curEvent->next;
  }

  // inserted edited data
  insert(headYear, editYear, editMonth, editDay, editStart, editEnd, editEvent,
         editFavorite);
}

///help to insert data in the right location inside stack
void stackHelper(Stack* outdated, int year, int month, int day,char start[],char end[], char event[], int favorite){
  Year *tmpYear = searchByYearFromOutdated(outdated,year);
  if (tmpYear == NULL) {
    tmpYear = createYear(-1);
    push(outdated,tmpYear);
    Year *newYear = createYear(year);
    tmpYear->next = newYear;
    tmpYear = newYear;
    tmpYear->month = createMonth(-1);
  }
  // sort month
  Month *headMonth = tmpYear->month;
  Month *curMonth = headMonth->next;
  
  Month *prevMonth = headMonth;
  
  Month *tmpMonth = searchByMonth(curMonth,&prevMonth, month);
  
  if (tmpMonth == NULL) {
    Month *newMonth = createMonth(month);
    tmpMonth = newMonth;
    if (curMonth == NULL) {
      headMonth->next = newMonth;
    } else if (curMonth->month > month) {
      newMonth->next = curMonth;
      headMonth->next = newMonth;

    } else {
      while (curMonth->next && curMonth->next->month < month) {
        curMonth = curMonth->next;
      }
      newMonth->next = curMonth->next;
      curMonth->next = newMonth;
    }
    tmpMonth->day = createDay(-1);
  }
  // sort Day
  Day *headDay = tmpMonth->day;
  Day *curDay = headDay->next;
  Day *prevDay = headDay;
  Day *tmpDay = searchByDay(tmpMonth->day, &prevDay, day);
  if (tmpDay == NULL) {
    Day *newDay = createDay(day);
    tmpDay = newDay;
    if (curDay == NULL) {
      headDay->next = newDay;
    } else if (curDay->day > day) {
      newDay->next = curDay;
      headDay->next = newDay;

    } else {
      while (curDay->next && curDay->next->day < day) {
        curDay = curDay->next;
      }
      newDay->next = curDay->next;
      curDay->next = newDay;
    }
    tmpDay->event = createEvent("HEAD", "0", "0",-1);
  }
  
  //sort Star & End and if star and time is equal to another tasks it will sort by favorite (FCFS)
  Event *headEvent = tmpDay->event;
  Event *curEvent = headEvent->next;
  Event *newEvent = createEvent(event, start, end,favorite);

  char curEventTime[12];
  char newEventTime[12];

  strcpy(newEventTime, strcat(start, end));

  if (curEvent != NULL) {
    strcpy(curEventTime, curEvent->startTime);
    strcat(curEventTime, curEvent->endTime);
    
  }

  if (curEvent == NULL) {
    headEvent->next = newEvent;
  }

  else if (strcmp(newEventTime, curEventTime) < 0) {
    newEvent->next = curEvent;
    headEvent->next = newEvent;
  }

  else {

    if (curEvent->next != NULL) {
      strcpy(curEventTime, curEvent->next->startTime);
      strcat(curEventTime, curEvent->next->endTime);
      while (curEvent->next && strcmp(newEventTime, curEventTime) > 0) {
        curEvent = curEvent->next;
        if(curEvent->next){
            strcpy(curEventTime, curEvent->next->startTime);
            strcat(curEventTime, curEvent->next->endTime);
        }
      }

        if(strcmp(newEventTime, curEventTime) == 0){
            if(favorite>curEvent->next->favorite){
                newEvent->next = curEvent->next;
                curEvent->next = newEvent;

            }
            else{
                while (curEvent->next && (strcmp(newEventTime, curEventTime) == 0) && favorite <= curEvent->next->favorite) {
                    curEvent = curEvent->next;

                    if(curEvent->next){
                        strcpy(curEventTime, curEvent->next->startTime);
                        strcat(curEventTime, curEvent->next->endTime);
                    }
                   }
                    newEvent->next = curEvent->next;
                    curEvent->next = newEvent;
                }

        }
        else{
            newEvent->next = curEvent->next;
            curEvent->next = newEvent;
        }
    }
    else{
        newEvent->next = curEvent->next;
        curEvent->next = newEvent;
    }
  }
}

// get all event that outdated and insert from function stackHelper
void insertToStack(Stack* outdated,Year* headYear){
    Year *curYear = headYear->next;
    while (curYear) {
      Month *curMonth = curYear->month->next;
      while (curMonth) {
        Day *curDay = curMonth->day->next;
        while (curDay) {
          Event *curEvent = curDay->event->next;
          while (curEvent) {
            //Check if in stack
            char tmpEvent[3000],startEvent[12],endEvent[12];
            int favoriteEvent = curEvent->favorite;
            strcpy(tmpEvent,curEvent->event);
            strcpy(startEvent,curEvent->startTime);
            strcpy(endEvent,curEvent->endTime);
            favoriteEvent = curEvent->favorite;
            stackHelper(outdated,curYear->year,curMonth->month,curDay->day,startEvent,endEvent,tmpEvent,favoriteEvent);
            curEvent = curEvent->next;
          }
          curDay = curDay->next;
        }
        curMonth = curMonth->next;
      }
      curYear = curYear->next;
    }


}

// Remove Outdated data form tree and push into out dated stack 
void cleanOutdatedData(Year* headYear,Stack* stack){

   Year *curYear = headYear->next;
    displayCurrentTime();
    if (curYear == NULL) {
        //printf("No task\n");
    }
    else {

    while (curYear) {
      Year* reuseYearnext = curYear->next;
      int status = 0;
      Year* newHeadList = createYear(-1);
      unsigned int stackCheck = 0;
      unsigned int cntDel = 0;
      Month *curMonth = curYear->month->next;
      while (curMonth) {
        Day *curDay = curMonth->day->next;
        while (curDay) {
          Event *curEvent = curDay->event->next;
          while (curEvent) {
            unsigned int check = 0;
            
            check = isOutdatedData(curYear->year,curMonth->month,curDay->day,curEvent->endTime);

            if(check == 1){
                stackCheck=1;
                //pop node from priorityQueue then create temp list for pushing on stack.
                char tmpStartTime[12];
                char tmpEndTime[12];
                char tmpEvent[3000];
                strcpy(tmpStartTime,curEvent->startTime);
                strcpy(tmpEndTime,curEvent->endTime);
                strcpy(tmpEvent,curEvent->event);
                insert(newHeadList,curYear->year,curMonth->month,curDay->day,tmpStartTime,tmpEndTime,tmpEvent,0);
            
                cntDel++;

            }
            curEvent = curEvent->next;
          }
          int prevDay = curDay->day;
          curDay = curDay->next;
          if(cntDel>0){

            deleteFirstEvent(headYear,cntDel, curYear->year, curMonth->month, prevDay, &status);
      
            cntDel=0;
          }
        }
       
        curMonth = curMonth->next;
      }
      
      if(stackCheck == 1){
        insertToStack(stack, newHeadList);
      }
      else{
        free(newHeadList);
      }
      //Year has been free ;-;
      if(status == 1){
         if(reuseYearnext != NULL)curYear = reuseYearnext;
         else curYear = NULL;
      }
      else
            curYear = curYear->next;
    }
  
  }


}
    
// Database Part

// Normal Date Event
// Save to Text File
void saveToText(Year *headYear) {
  FILE *fp = fopen("dateList.txt", "w");
  Year *curYear = headYear->next;
  if (curYear == NULL) {
    printf("No task\n");
  } else {
    while (curYear) {
      Month *curMonth = curYear->month->next;
      while (curMonth) {
        Day *curDay = curMonth->day->next;
        while (curDay) {
          Event *curEvent = curDay->event->next;
          while (curEvent) {
            fprintf(fp, "%d %d %d %s %s %s %d\n", curYear->year,
                    curMonth->month, curDay->day, curEvent->event,
                    curEvent->startTime, curEvent->endTime, curEvent->favorite);
            curEvent = curEvent->next;
          }
          curDay = curDay->next;
        }
        curMonth = curMonth->next;
      }
      curYear = curYear->next;
    }
  }
  fclose(fp);
}

// Read Text File
void readTextFile(Year *headYear) {
  FILE *fp = fopen("dateList.txt", "r");
  int year, month, day, favorite;
  char start[12], end[12], buffer[64], event[32];
  // char *event;
  while (fgets(buffer, 64, fp) != NULL) {
    if (buffer) {
      sscanf(buffer, "%d %d %d %s %s %s %d\n", &year, &month, &day, event,
             start, end, &favorite);
      insert(headYear, year, month, day, start, end, event, favorite);
    } else
      break;
  }
  
  fclose(fp);
}

// Outdated Event
// Save to outDated.txt file
void outDatedList(Year *headYear, int year) {
  Year *prevYear = headYear;
  Year *curYear = searchByYear(headYear, &prevYear, year);

  FILE *fp = fopen("dateList.txt", "a");
  if (curYear) {
    Month *curMonth = curYear->month->next;
    while (curMonth) {
      Day *curDay = curMonth->day->next;
      while (curDay) {
        Event *curEvent = curDay->event->next;
        while (curEvent) {
          fprintf(fp, "%d %d %d %s %s %s %d\n", curYear->year, curMonth->month,
                  curDay->day, curEvent->event, curEvent->startTime,
                  curEvent->endTime, 0);
          curEvent = curEvent->next;
        }
        curDay = curDay->next;
      }
      curMonth = curMonth->next;
    }
  }
  fclose(fp);
}

// Save for each year in stack
void saveToOutdated(Stack *outdated) {
  int prevTop = outdated->top;
  while (outdated->top != -1) {
    Year *outdatedHeadYear = peek(outdated);
    outDatedList(outdatedHeadYear, outdatedHeadYear->next->year);
    pop(outdated);
  }
  outdated->top = prevTop;
}
