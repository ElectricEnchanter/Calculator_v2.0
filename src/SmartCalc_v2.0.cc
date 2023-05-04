#include "SmartCalc_v2.0.h"



int YmdToMord(char *data) {
  int y1, m1, d1;
  if (sscanf(data, "%d.%d.%d", &y1, &m1, &d1) != 3) {
    return -1;
  }

  int a = (14 - m1) / 12;
  int y = y1 - a;          /* лет с 1 марта 0-го года */
  int m = m1 + 12 * a - 3; /* месяцев -"- */
  return d1 + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400;
}

