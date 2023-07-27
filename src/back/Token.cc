#include "Token.h"

namespace s21 {

s21::Token::Token(const std::string &name, Priority priority,
                  Associativity associativity, Type type,
                  function_variant function)
    : name_(name), priority_(priority), associativity_(associativity),
      type_(type), function_(function){};

std::string s21::Token::GetName() const { return name_; }

s21::Priority s21::Token::GetPriority() const { return priority_; }

s21::Associativity s21::Token::GetAssociativity() const {
  return associativity_;
}

s21::Type s21::Token::GetType() const { return type_; }

s21::function_variant s21::Token::GetFunction() const { return function_; }

} // namespace s21

int s21::YmdToMord(const char *date) {
  int new_year, new_month, new_day;
  if (sscanf(date, "%d.%d.%d", &new_year, &new_month, &new_day) != 3) {
    return -1;
  }
  int difference = (14 - new_month) / 12;
  int year = new_year - difference; /* лет с 1 марта 0-го года */
  int month = new_month + 12 * difference - 3; /* месяцев -"- */
  return new_day + (153 * month + 2) / 5 + 365 * year + year / 4 - year / 100 +
         year / 400;
}
