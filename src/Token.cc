#include "Token.h"

int main(){
  std::string a = "1.53232+cos((1))";
  std::string b = "";
  s21::Token w;
  w.CalculateAnswer(a, b);


  std::cout << "otvet:  " << w.GetAnswer() << std::endl;
  return 0;
}


namespace s21 {
std::queue<Token> Token::queue_;
std::stack<s21::Token> Token::stack_token_;
std::stack<s21::Token> Token::stack_number_;

s21::Token::Token(const std::string& name, Priority priority,
                  Associativity associativity, Type type,
                  function_variant function)
    : name_(name),
      priority_(priority),
      associativity_(associativity),
      type_(type),
      function_(function){};


std::string s21::Token::GetName() const { return name_; }

s21::Priority s21::Token::GetPriority() const { return priority_; }

s21::Associativity s21::Token::GetAssociativity() const {
  return associativity_;
}

s21::Type s21::Token::GetType() const { return type_; }

s21::function_variant s21::Token::GetFunction() const { return function_; }

double s21::Token::GetAnswer() { return answer_; }

void s21::Token::CalculateAnswer(std::string input, std::string input_x) {
  if (input.empty()) throw std::string("EMPTY LINE");
  CreateTokenMap(token_map_);
  ConvertToLower();
  Validator(input, input_x);
  Parser();
  SetAnswer();
}

void s21::Token::CreateTokenMap(std::map<std::string, s21::Token>& token_map) {
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
      {"/", Token("/", kMedium, kLeft, kBinaryOperator, std::divides<double>())},
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
      {"neg", Token("-", kLow, kRight, kUnaryPrefixOperator, std::negate<double>())},
  };
  token_map.insert(list);
}

std::string s21::Token::ReadToken(std::string& input, size_t& index) const {
  std::regex pattern;
  if (isdigit(input.at(index))) 
    pattern = ("\\d+([.]\\d+)?(e([-+])?\\d+)?");
  else if (isalpha(input.at(index))) 
    pattern = "([%cosintaqrtlgx]+)";
  else pattern = "([-( )^%*+\\/])";

  std::sregex_iterator regex_iterator =
      std::sregex_iterator(input.begin() + index, input.end(), pattern);
  std::smatch match = *regex_iterator;
  index += match.length() - 1;
  return match.str();
}

void s21::Token::ConvertToLower() {
  std::transform(input_.begin(), input_.end(), input_.begin(), ::tolower);
}

void s21::Token::Validator(std::string input, std::string input_x) {
  if(!input_x.empty()) x_value_ = stod(input_x);

  std::cmatch result;
  std::regex pattern;
  int i {0};
  
  while(i < 4){
    switch(i){
      case 0: pattern = "[^-/ %.cosintaqrtlgx()^/*+0-9]";
        break;
      case 1: pattern = ".*\\. \\d.*";
        break;
      case 2: pattern = "(\\b\\d+\\.\\d+\\.\\d+\\b)";
        break;
      case 3: pattern = "((\\d+(?:\\.\\d+)?)[+\\-*/^%]{2,}(\\d+(?:\\.\\d+)?))";
        break;
    }
    if (std::regex_search(input.c_str(), result, pattern))
    throw std::string("INVALID CHARACTER(S)");
    ++i;
  }

  for (size_t index = 0; input.length() > index; ++index) {
    try{
      if (input.at(index) == '.')
      throw std::string("INVALID CHARACTER(S)");
      std::string token = ReadToken(input, index);
      if (isdigit(token.at(0))){
        Token result(token, kDefault, kNone, kNumber, stod(token));
        queue_.push(result);
      }
      else if (token == " ") continue;
      else PushTokenToQueue(token);
    } catch (std::string error_message){}
  }
}

void s21::Token::Parser(){
  int size = queue_.size();
  // возможно попать в конце
  // передавать токен в рекурсию
  //бесконечные скобки
  for (int i = 0; i < size; ++i, queue_.pop()){
    std::string token = queue_.front().GetName();

    if(token == "("){
      ++i;
      ++bracket_;
      stack_token_.push(queue_.front());
      queue_.pop();
      token = queue_.front().GetName();
      if (isdigit(token[0])) stack_number_.push(queue_.front());
      else if (token == "+") continue;
      else if (token == "-"){
        Token a("-", kLow, kRight, kUnaryPrefixOperator, std::negate<double>());
        stack_token_.push(a);
      }
      else if (token == "(") {
        ++i;
        ++bracket_;
        queue_.pop();
        Parser();
      }
      else if (token == "x") PushNumberToStack(x_value_);
      else stack_token_.push(queue_.front());
    }
    else if (i == 0 && token == "+") continue;
    else if (i == 0 &&token == "-") {
        Token a("-", kLow, kRight, kUnaryPrefixOperator, std::negate<double>());
        stack_token_.push(a);
    }
    else if (token == "x") PushNumberToStack(x_value_);
    else if(token == ")") {
      --bracket_;
      if (bracket_ < 0)
        throw std::string("скобка");

        //хуита
      if(stack_token_.top().GetName() != "("){
        while(stack_token_.top().GetName() != "("){
        std::cout << stack_token_.top().GetName() << std::endl;
        Counting();
        }
      } else {
        stack_token_.pop();
      }

      }
    
    else if (isdigit(token[0])) stack_number_.push(queue_.front());
    else if(stack_token_.empty()){
      if (token == "(") ++bracket_;
      stack_token_.push(queue_.front());
    }
    else if (token != ")") Conditions();

  }
  while(!stack_token_.empty()) Counting();
}

void s21::Token::Counting() {
  std::visit(
      overloaded{
        [&](unary_function function) {
          PushNumberToStack(function(PopFromResult()));
        },

        [&](binary_function function) {
          double right_argument = PopFromResult();
          double left_argument = PopFromResult();
          PushNumberToStack(function(left_argument, right_argument));
        },

        [&](auto) {}
        },

      stack_token_.top().GetFunction()
      );
      stack_token_.pop();
}

void s21::Token::Conditions(){
  int lastToken = stack_token_.top().GetPriority();
  int currentToken = queue_.front().GetPriority();

  if (lastToken > currentToken || lastToken == currentToken ){
    Counting();
    stack_token_.push(queue_.front());
  } else stack_token_.push(queue_.front());
}

void s21::Token::SetAnswer() {
  answer_ = stod(stack_number_.top().GetName());
  stack_number_.pop();
}

double s21::Token::PopFromResult() {
  if(stack_number_.empty())
   throw std::string("NOT ENOUGH NUMBERS");

  s21::Token number = stack_number_.top();
  std::string name = number.GetName();
  stack_number_.pop();
  return stod(name);
}

void s21::Token::PushNumberToStack(double value) {
  std::ostringstream token;
  token << value;
  std::string name = token.str();
  Token result(name, kDefault, kNone, kNumber, value);
  stack_number_.push(result);
}


void s21::Token::PushTokenToQueue(std::string input){
  auto found_token = token_map_.find(input);
  if (found_token == token_map_.end())
    throw std::string("INVALID CHARACTER(S)");
  queue_.push(found_token->second);
}

}  // namespace s21

int s21::YmdToMord(const char* date) {
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
