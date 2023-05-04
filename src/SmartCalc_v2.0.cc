#include "SmartCalc_v2.0.h"





int YmdToMord(char *date) {
  int new_year, new_month, new_day;
  if (sscanf(date, "%d.%d.%d", &new_year, &new_month, &new_day) != 3) {
    return -1;
  }

  int difference = (14 - new_month) / 12;
  int year = new_year - difference;          /* лет с 1 марта 0-го года */
  int month = new_month + 12 * difference - 3; /* месяцев -"- */
  return new_day + (153 * month + 2) / 5 + 365 * year + year / 4 - year / 100 + year / 400;
}

