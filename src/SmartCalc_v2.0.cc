#include "SmartCalc_v2.0.h"


int main(){
  std::string a = "1.23";
  std::string b;
  s21::Validator(a,b);

  return 0;
}

void s21::Validator(std::string input, std::string output) {
  std::cmatch result;
  std::regex pattern("[^-/ %.cosintaqrtlgx()^/*+0-9]");

  if (std::regex_search(input.c_str(), result, pattern))
    throw std::logic_error("Incorrect symbols");

  s21::Calculator expression;
  input = expression.ConvertToLower(input);
  for (size_t index = 0; input.length() > index; ++index){
    expression.ReadToken(input, index);
  }

}

std::string s21::Calculator::ReadToken(std::string& input, size_t & index) const{
  std::regex pattern;
  if (isdigit(input.at(index) )){
    std::cout << "число"<< std::endl;
    pattern = ("\\d+([.]\\d+)?(e([-+])?\\d+)?");
  } else if (isalpha(input.at(index))){
      std::cout << "функция"<< std::endl;
      pattern = "([%cosintaqrtlgx]+)";
  } else {
      std::cout << "знак"<< std::endl;
      pattern = "([()^/*+])";
  }
  
    std::sregex_iterator regex_iterator = std::sregex_iterator (
    input.begin() + index, input.end(), pattern);
    std::smatch match = *regex_iterator;
    index += match.length() - 1;
    return match.str();
  }


// void s21::CreateTokenMap(std::map<std::string, s21::Token> & token_map){
//   std::initializer_list<std::pair<const std::string, Token>> list = {
//     {" " , Token("space", kDefault, kNone, kNumber, nullptr)},
//   };
//   token_map.insert(list);
// }

std::string s21::Calculator::ConvertToLower(std::string input){
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  return input;
}

// void s21::Token::MakeNumber(std::string name, double value){
//   Token result(name, kDefault, kNone, kNumber, value);
//   *this = result;
// }

// void s21::Token::MakeUnaryNegation() {
//   Token result("negate", kUnaryOperator, kRight, kUnaryPrefixOperator, std::negate<double>());
//   *this = result;
// }

// void s21::Calculator::PushToken(std::string token){
//   auto token_map = token_map_.find(token);
//   if (token_map == token_map_.end()){
//     throw std::logic_error("Incorrect symbol: " + token);
//   }
//   input_.push(token_map->second);
// }

int YmdToMord(char *date) {
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
