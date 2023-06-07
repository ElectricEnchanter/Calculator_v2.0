#include "Token.h"
#include "Calculator.h"

int main(){
  std::string a = "1.23+2--";
  std::string b;
  s21::Validator(a,b);

  return 0;
}

s21::Calculator::Calculator() { CreateTokenMap(token_map_); }

s21::Token::Token(const std::string& name, Precedence precedence,
                          Associativity associativity, Type type,
                          function_variant function)
    : name_(name),
      precedence_(precedence),
      associativity_(associativity),
      type_(type),
      function_(function){};

void s21::Validator(std::string input, std::string input_x) {
  std::cmatch result;
  std::regex pattern("[^-/ %.cosintaqrtlgx()^/*+0-9]");

  if (std::regex_search(input.c_str(), result, pattern))
    throw std::logic_error("Incorrect symbols");

  s21::Calculator expression;
  s21:Token Number;
  input = expression.ConvertToLower(input);
  for (size_t index = 0; input.length() > index; ++index){
    // std::cout << expression.ReadToken(input, index) << std::endl;
    std::string a = expression.ReadToken(input, index);
    if(!isdigit(a.at(0)))
      expression.PushToken(a);
    else Number.MakeNumber(a, stoi(a));
  }


}

std::string s21::Calculator::ReadToken(std::string& input, size_t & index) const{
  std::regex pattern;
  if (isdigit(input.at(index) )){
    std::cout << "число ";
    pattern = ("\\d+([.]\\d+)?(e([-+])?\\d+)?");
  } else if (isalpha(input.at(index))){
      std::cout << "функция ";
      pattern = "([%cosintaqrtlgx]+)";
  } else {
      std::cout << "знак ";
      pattern = "([-()^/*+])";
  }
    std::sregex_iterator regex_iterator = std::sregex_iterator (
    input.begin() + index, input.end(), pattern);
    std::smatch match = *regex_iterator;
    index += match.length() - 1;
    return match.str();
  }


void s21::CreateTokenMap(
  std::map<std::string, s21::Token>& token_map) {
  using std::initializer_list;
  using std::pair;
  using std::string;
  using namespace s21;
  initializer_list<pair<const string, Token>> list = {
    {"+", Token("+", kLow, kLeft, kBinaryOperator, std::plus<double>())},
    {"-", Token("-", kLow, kLeft, kBinaryOperator, std::minus<double>())},

  };
  token_map.insert(list);
}

std::string s21::Calculator::ConvertToLower(std::string input){
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  return input;
}

void s21::Token::MakeNumber(std::string name, double value){
  Token result(name, kDefault, kNone, kNumber, value);
  *this = result;
}

// void s21::Token::MakeUnaryNegation() {
//   Token result("negate", kUnaryOperator, kRight, kUnaryPrefixOperator, std::negate<double>());
//   *this = result;
// }

void s21::Calculator::PushToken(std::string token){
  auto token_map = token_map_.find(token);
  if (token_map == token_map_.end()){
    throw std::logic_error("Incorrect symbol: " + token);
  }
  input_.push(token_map->second);
  std::cout<<input_.size()<<std::endl;

}

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
