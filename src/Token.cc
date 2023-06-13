#include "Token.h"

// int main() {
//   s21::Token w;
//   std::string a = "1+3.2";
//   std::string b = "";
//   w.CalculateAnswer(a, b);
//   w.GetAnswer();

//  std::cout << "ответ " << w.GetAnswer() << std::endl;
//  return 1;
//}

namespace s21 {

std::stack<Token> Token::stack_token_;
std::stack<Token> Token::stack_number_;

std::string s21::Token::GetName() const { return name_; }

s21::Precedence s21::Token::GetPrecedence() const { return precedence_; }

s21::Associativity s21::Token::GetAssociativity() const {
  return associativity_;
}

s21::Type s21::Token::GetType() const { return type_; }

s21::function_variant s21::Token::GetFunction() const { return function_; }

double s21::Token::GetAnswer() { return answer_; }

void s21::Token::SetAnswer(std::vector<double> result_) {
  answer_ = result_.back();
}

void s21::Token::CalculateAnswer(std::string input, std::string input_x) {

  CreateTokenMap(token_map_);
  ConvertToLower(input);
  Validator(input, input_x);
  PostfixNotationCalculation(1);
  SetAnswer(result_);
}

s21::Token::Token(const std::string& name, Precedence precedence,
                  Associativity associativity, Type type,
                  function_variant function)
    : name_(name),
      precedence_(precedence),
      associativity_(associativity),
      type_(type),
      function_(function){};

void s21::Token::Validator(std::string input, std::string input_x) {
  input_x = 1;

  std::cmatch result;
  std::regex pattern("[^-/ %.cosintaqrtlgx()^/*+0-9]");

  if (std::regex_search(input.c_str(), result, pattern))
    throw std::logic_error("Incorrect symbols");

  for (size_t index = 0; input.length() > index; ++index) {
    std::string token = ReadToken(input, index);
    if (!isdigit(token.at(0)))
      TryToPushTokenToStack(token);
    else
      PushNumberToStack(token, stod(token));
  }
}

std::string s21::Token::ConvertToLower(std::string input) {
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  return input;
}

std::string s21::Token::ReadToken(std::string& input, size_t& index) const {
  std::regex pattern;
  if (isdigit(input.at(index))) {
    // std::cout << "число ";
    pattern = ("\\d+([.]\\d+)?(e([-+])?\\d+)?");
  } else if (isalpha(input.at(index))) {
    // std::cout << "функция ";
    pattern = "([%cosintaqrtlgx]+)";
  } else {
    // std::cout << "знак ";
    pattern = "([-( )^/*+])";
  }
  std::sregex_iterator regex_iterator =
      std::sregex_iterator(input.begin() + index, input.end(), pattern);
  std::smatch match = *regex_iterator;
  index += match.length() - 1;
  return match.str();
}

void s21::Token::CreateTokenMap(std::map<std::string, s21::Token>& token_map) {
  using std::initializer_list;
  using std::pair;
  using std::string;

  initializer_list<pair<const string, Token>> list = {
      {"+", Token("+", kLow, kLeft, kBinaryOperator, std::plus<double>())},
      {"-", Token("-", kLow, kLeft, kBinaryOperator, std::minus<double>())},
      {"*",
       Token("*", kMedium, kLeft, kBinaryOperator, std::multiplies<double>())},
      {"x", Token("x", kDefault, kNone, kNumber, nullptr)},
      {"(", Token("(", kDefault, kNone, kOpenBracket, nullptr)},
      {")", Token(")", kDefault, kNone, kCloseBracket, nullptr)},
      {"/", Token("/", kMedium, kLeft, kBinaryOperator, std::divides<double>())},
      {"^", Token("^", kHigh, kRight, kBinaryOperator, powl)},
      {"%", Token("mod", kMedium, kLeft, kBinaryOperator, fmodl)},
      {"cos", Token("cos", kFunction, kRight, kUnaryFunction, cosl)},
      {"sin", Token("sin", kFunction, kRight, kUnaryFunction, sinl)},
      {"tan", Token("tan", kFunction, kRight, kUnaryFunction, tanl)},
      {"acos", Token("acos", kFunction, kRight, kUnaryFunction, acosl)},
      {"asin", Token("asin", kFunction, kRight, kUnaryFunction, asinl)},
      {"atan", Token("atan", kFunction, kRight, kUnaryFunction, atanl)},
      {"sqrt", Token("sqrt", kFunction, kRight, kUnaryFunction, sqrtl)},
      {"ln", Token("ln", kFunction, kRight, kUnaryFunction, logl)},
      {"log", Token("log", kFunction, kRight, kUnaryFunction, log10l)},
  };
  token_map.insert(list);
}

void s21::Token::PushNumberToStack(std::string name, double value) {
  std::cout << name << std::endl;
  Token result(name, kDefault, kNone, kNumber, value);
  stack_number_.push(result);
}

int s21::Token::TryToPushTokenToStack(std::string token) {
  if (token == " ") return 0;
  auto found_token = token_map_.find(token);
  if (found_token == token_map_.end())
    throw std::logic_error("Incorrect symbol: " + token);

  stack_token_.push(found_token->second);
  return 1;
}

void s21::Token::PostfixNotationCalculation(double x_value) {
  using namespace s21;

  while (!stack_token_.empty()) {
    std::visit(
        overloaded{[&](double function) {
                     std::cout << "цыфра" << std::endl;
                     PushToResult(function);
                   },

                   [&](unary_function function) {
                     PushToResult(function(PopFromResult()));
                   },

                   [&](binary_function function) {
                     double right_argument = PopFromResult();
                     double left_argument = PopFromResult();
                     PushToResult(function(left_argument, right_argument));
                   },

                   [&](auto) { PushToResult(x_value); }},

        stack_token_.top().GetFunction());
  }
}

void s21::Token::PushToResult(double value) {
  std::cout << value << std::endl;

  result_.push_back(value);

  stack_token_.pop();
}

double s21::Token::PopFromResult() {
  s21::Token s = stack_number_.top();
  std::string a = s.GetName();
  answer_ = stod(a);
  stack_number_.pop();

  return answer_;
}

// void s21::Token::MakeUnaryNegation() {
//   Token result("negate", kUnaryOperator, kRight, kUnaryPrefixOperator,
//   std::negate<double>()); *this = result;
// }

}  // namespace s21

int s21::YmdToMord(char* date) {
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
