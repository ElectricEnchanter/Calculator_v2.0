#include "Calculator.h"

namespace s21 {

std::queue<Token> Calculator::queue_;
std::stack<s21::Token> Calculator::stack_token_;
std::stack<s21::Token> Calculator::stack_number_;

double s21::Calculator::GetAnswer() { return answer_; }

void s21::Calculator::CalculateAnswer(std::string input, std::string input_x) {
  if (input.empty())
    throw std::string("EMPTY LINE");
  CreateTokenMap(token_map_);
  ConvertToLower();
  Validator(input, input_x);
  FindUnaries(input);
  Parser();
  SetAnswer();
  CleanStacks();
}

void s21::Calculator::CleanStacks() {
  if (!stack_number_.empty() || !stack_token_.empty())
    throw std::string("INVALID CHARACTER(S)");
  queue_ = std::queue<Token>();
  stack_token_ = std::stack<Token>();
  stack_number_ = std::stack<Token>();
}

void s21::Calculator::CreateTokenMap(
    std::map<std::string, s21::Token> &token_map) {
  using std::initializer_list;
  using std::pair;
  using std::string;

  initializer_list<pair<const string, Token>> list = {
      {"+", Token("+", kLow, kLeft, kBinaryOperator, std::plus<double>())},
      {"-", Token("-", kLow, kLeft, kBinaryOperator, std::minus<double>())},
      {"%", Token("mod", kMedium, kLeft, kBinaryOperator, fmodl)},
      {"*",
       Token("*", kMedium, kLeft, kBinaryOperator, std::multiplies<double>())},
      {" ", Token(" ", kDefault, kNone, kNumber, nullptr)},
      {"x", Token("x", kDefault, kNone, kNumber, nullptr)},
      {"(", Token("(", kDefault, kNone, kOpenBracket, nullptr)},
      {")", Token(")", kDefault, kNone, kCloseBracket, nullptr)},
      {"/",
       Token("/", kMedium, kLeft, kBinaryOperator, std::divides<double>())},
      {"^", Token("^", kHigh, kRight, kBinaryOperator, powl)},
      {"cos", Token("cos", kFunction, kRight, kUnaryFunction, cosl)},
      {"sin", Token("sin", kFunction, kRight, kUnaryFunction, sinl)},
      {"tan", Token("tan", kFunction, kRight, kUnaryFunction, tanl)},
      {"acos", Token("acos", kFunction, kRight, kUnaryFunction, acosl)},
      {"asin", Token("asin", kFunction, kRight, kUnaryFunction, asinl)},
      {"atan", Token("atan", kFunction, kRight, kUnaryFunction, atanl)},
      {"sqrt", Token("sqrt", kFunction, kRight, kUnaryFunction, sqrtl)},
      {"ln", Token("ln", kFunction, kRight, kUnaryFunction, logl)},
      {"log", Token("log", kFunction, kRight, kUnaryFunction, log10l)},
      {"neg",
       Token("-", kLow, kRight, kUnaryPrefixOperator, std::negate<double>())},
  };
  token_map.insert(list);
}

std::string s21::Calculator::ReadToken(const std::string &input,
                                       size_t &index) const {
  std::regex pattern;
  if (isdigit(input.at(index)))
    pattern = ("\\d+([.]\\d+)?(e([-+])?\\d+)?");
  else if (isalpha(input.at(index)))
    pattern = "([%ecosintaqrtlgx]+)";
  else
    pattern = "([-( )^%*+\\/])";

  std::sregex_iterator regex_iterator =
      std::sregex_iterator(input.begin() + index, input.end(), pattern);
  std::smatch match = *regex_iterator;
  index += match.length() - 1;
  return match.str();
}

void s21::Calculator::ConvertToLower() {
  std::transform(input_.begin(), input_.end(), input_.begin(), ::tolower);
}

void s21::Calculator::Validator(const std::string &input,
                                const std::string &input_x) {
  if (!input_x.empty())
    x_value_ = stod(input_x);

  std::cmatch result;
  std::regex pattern;
  int i{0};

  while (i < 4) {
    switch (i) {
    case 0:
      pattern = "[^-/ %.cosintaqrtlgx()^/*+0-9]";
      break;
    case 1:
      pattern = ".*\\. \\d.*";
      break;
    case 2:
      pattern = "(\\b\\d+\\.\\d+\\.\\d+\\b)";
      break;
    case 3:
      pattern = "((\\d+(?:\\.\\d+)?)[+\\-*/^%]{2,}(\\d+(?:\\.\\d+)?))";
      break;
    }
    if (std::regex_search(input.c_str(), result, pattern))
      throw std::string("INVALID CHARACTER(S)");
    ++i;
  }
}

void s21::Calculator::FindUnaries(const std::string &input) {
  for (size_t index = 0; input.length() > index; ++index) {
    try {
      if (input.at(index) == '.')
        throw std::string("INVALID CHARACTER(S)");
      std::string token = ReadToken(input, index);
      if (isdigit(token.at(0))) {
        queue_.emplace(token, kDefault, kNone, kNumber, stod(token));
      } else if (token == " ")
        continue;
      else if (index == 0 && (token == "+" || token == "-")) {
        if (token == "+")
          continue;
        else if (token == "-") {
          queue_.emplace("-", kLow, kRight, kUnaryPrefixOperator,
                         std::negate<double>());
        }
      } else if (token == "(") {
        PushTokenToQueue(token);
        token = ReadToken(input, ++index);
        if (token == "+")
          continue;
        else if (token == "-") {
          Token a("-", kLow, kRight, kUnaryPrefixOperator,
                  std::negate<double>());
          queue_.push(a);
        } else if (isdigit(token.at(0))) {
          queue_.emplace(token, kDefault, kNone, kNumber, stod(token));
        } else
          PushTokenToQueue(token);
      } else
        PushTokenToQueue(token);
    } catch (std::string error_message) {
      ;
    }
  }
}

void s21::Calculator::Parser() {
  int size = queue_.size();
  std::string token;
  for (int i{0}; i < size; ++i) {
    if (queue_.empty())
      break;
    token = queue_.front().GetName();
    if (isdigit(token[0]))
      stack_number_.push(queue_.front());
    else if (token == "x")
      PushNumberToStack(x_value_);
    else if (token == "(")
      stack_token_.push(queue_.front());
    else if (token == ")") {
      if (stack_token_.top().GetName() == "(") {
        stack_token_.pop();
        queue_.pop();
        continue;
      } else
        while (stack_token_.top().GetName() != "(")
          Counting();
      stack_token_.pop();
    } else {
      if (stack_token_.empty())
        stack_token_.push(queue_.front());
      else
        Conditions();
    }
    if (!queue_.empty())
      queue_.pop();
  }
  while (!stack_token_.empty())
    Counting();
}

void s21::Calculator::Counting() {
  std::visit(overloaded{[&](unary_function function) {
                          PushNumberToStack(function(PopFromResult()));
                        },

                        [&](binary_function function) {
                          double right_argument = PopFromResult();
                          double left_argument = PopFromResult();
                          PushNumberToStack(
                              function(left_argument, right_argument));
                        },

                        [&](auto) {}},

             stack_token_.top().GetFunction());
  stack_token_.pop();
}

void s21::Calculator::Conditions() {
  int lastToken = stack_token_.top().GetPriority();
  int currentToken = queue_.front().GetPriority();

  if (lastToken > currentToken || lastToken == currentToken) {
    Counting();
    stack_token_.push(queue_.front());
  } else
    stack_token_.push(queue_.front());
}

void s21::Calculator::SetAnswer() {
  answer_ = stod(stack_number_.top().GetName());
  stack_number_.pop();
}

double s21::Calculator::PopFromResult() {
  if (stack_number_.empty())
    throw std::string("NOT ENOUGH NUMBERS");

  s21::Token number = stack_number_.top();
  stack_number_.pop();
  return stod(number.GetName());
}

void s21::Calculator::PushNumberToStack(const double &value) {
  std::ostringstream token;
  token << value;
  std::string name = token.str();
  Token result(name, kDefault, kNone, kNumber, value);
  stack_number_.push(result);
}

void s21::Calculator::PushTokenToQueue(const std::string &input) {
  auto found_token = token_map_.find(input);
  if (found_token == token_map_.end())
    throw std::string("INVALID CHARACTER(S)");
  queue_.push(found_token->second);
}

void s21::Calculator::ClearСoordinates() {
  coordinates_x_.clear();
  coordinates_y_.clear();
};

void s21::Calculator::CalculateGraph(std::string input, std::string input_x) {
  ClearСoordinates();
  double dot = stod(input_x);
  for (double x = -dot; x <= fabs(dot); x += 0.01) {
    CalculateAnswer(input, std::to_string(x));
    coordinates_x_.push_back(x);
    coordinates_y_.push_back(GetAnswer());
  }
}

const std::vector<double> &s21::Calculator::GetCoordinatesX() {
  return coordinates_x_;
}

const std::vector<double> &s21::Calculator::GetCoordinatesY() {
  return coordinates_y_;
}

} // namespace s21