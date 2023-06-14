#include "Token.h"

int main() {
  s21::Token w;
  std::string a = "-2+2";
  std::string b = "";
  w.CalculateAnswer(a, b);
  w.GetAnswer();

 std::cout << "ответ " << w.GetAnswer() << std::endl;
 return 1; 
}

// унарники и пробелы


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

void s21::Token::SetAnswer() {
  answer_ = stod(stack_number_.top().GetName());
}

void s21::Token::CalculateAnswer(std::string input, std::string input_x) {
  if (input.empty())  throw std::string("EMPTY LINE");
  double x = 0;
  input_ = input;
  input_x_ = input_x;

  CreateTokenMap(token_map_);
  ConvertToLower();
  Validator(input, input_x);
  FindSpacesAndUnaries();
 
  if(input_x.empty()) x = 0;
  else x = stod(input_x);
  PostfixNotationCalculation(x);
  SetAnswer();
 
 
}

void s21::Token::FindSpacesAndUnaries(){
  // std::string buffer;
  //   for(int i = 0; i != input_.length(); i++){
  //       if (input_.at(i) != ' '){
  //         buffer += input_.at(i);
  //       } else if (input_.at(i) == '+'){
            
  //       } else if (input_.at(i) != '-'){
  //         if (i == 1) MakeUnaryNegation()
  //     }
  //   }
    double queue_size = queue_.size();
    // std::cout << queue_.size() << std::endl;

  for(size_t i = 0; i < queue_size; ++i){
    std::string buffer = queue_.front().GetName();
    if (buffer == "-"){
      if (i == 0) {
        queue_.pop();
        buffer = queue_.front().GetName();
        if (isdigit(buffer.at(0)))
          TryToPushTokenToStack("neg");
        //  queue_.front().SetFunction();
        // MakeUnaryNegation();
        i++;
      }
    }
    // if (buffer == "+"){
      
    // }
    // if (buffer == " "){
      
    // }
    // std::cout << std::stod(buffer) << std::endl;
    // double q = stod(buffer);
    // std::cout << q << std::endl;
    // std::cout << isdigit(q) << std::endl;


   
    if (std::isdigit(buffer.at(0))) {
      PushNumberToStack(buffer, std::stod(buffer));
    } else if (buffer == "x") {
      PushNumberToStack(input_x_, std::stod(input_x_));
    } else {
      TryToPushTokenToStack(buffer);
    }
    queue_.pop();
  }      
}

void s21::Token::SetFunction(){
  std::string name = name_;
  if(isdigit(name.at(0)))
  function_ = std::negate<double>(); 
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

  std::cmatch result;
  std::regex pattern("[^-/ %.cosintaqrtlgx()^/*+0-9]");

  if (std::regex_search(input.c_str(), result, pattern))
    throw std::string("INVALID CHARACTER(S)");

  if (std::regex_search(input_x.c_str(), result, pattern))
    throw std::string("INVALID CHARACTER(S)");

  for (size_t index = 0; input.length() > index; ++index) {
    std::string token = ReadToken(input, index);
    if (isdigit(token.at(0))){
      Token result(token, kDefault, kNone, kNumber, stod(token));
      queue_.push(result);
    } else PushTokenToQueue(token);
  //   if (token.at(0) == 'x')
  //     PushNumberToStack(input_x, std::stod(input_x));
  //   else 
  //   if (!isdigit(token.at(0)))
  //     TryToPushTokenToStack(token);
  //   else
  //     PushNumberToStack(token, std::stod(token));
  }
}

void s21::Token::ConvertToLower() {
  std::transform(input_.begin(), input_.end(), input_.begin(), ::tolower);
}

std::string s21::Token::ReadToken(std::string& input, size_t& index) const {
  std::regex pattern;
  if (isdigit(input.at(index))) 
    pattern = ("\\d+([.]\\d+)?(e([-+])?\\d+)?");
  else if (isalpha(input.at(index))) 
    pattern = "([%cosintaqrtlgx]+)";
  else pattern = "([-( )^/*+])";

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
      {"neg", Token("-", kLow, kRight, kUnaryPrefixOperator, std::negate<double>())},

  };
  token_map.insert(list);
}

void s21::Token::PushNumberToStack(std::string name, double value) {
  std::cout << "num " <<  value  << std::endl;
  Token result(name, kDefault, kNone, kNumber, value);
  stack_number_.push(result);
}

int s21::Token::TryToPushTokenToStack(std::string token) {
    std::cout << "token "<< token << std::endl;

  if (token == " ") return 0;
  auto found_token = token_map_.find(token);
  if (found_token == token_map_.end())
    throw std::string("INVALID CHARACTER(S) " + token);

  stack_token_.push(found_token->second);
  return 1;
}

void s21::Token::PushTokenToQueue(std::string input){
  // if (input == " ") return 0;
  auto found_token = token_map_.find(input);
  if (found_token == token_map_.end())
    throw std::string("INVALID CHARACTER(S) " + input);

  queue_.push(found_token->second);
}

void s21::Token::PostfixNotationCalculation(double x_value) {

  using namespace s21;

  while (!stack_token_.empty()) {
    std::visit(
        overloaded{[&](double function) {
            // std::cout << "цыфра" << std::endl;
            PushToResult(function);
          },

          [&](unary_function function) {
            // std::cout << "унарка" << std::endl;
            PushToResult(function(PopFromResult()));
          },

          [&](binary_function function) {
          // std::cout << "бинарка" << std::endl;
            double right_argument = PopFromResult();
            double left_argument = PopFromResult();
            PushToResult(function(left_argument, right_argument));
          },

          [&](auto) {
          std::cout << "икс" << std::endl;
          PushToResult(x_value); }},

        stack_token_.top().GetFunction());
        stack_token_.pop();
  }
}

void s21::Token::PushToResult(double value) {
  std::ostringstream token;
  token << value;
  std::string str = token.str();
  PushNumberToStack(str, value);
}

double s21::Token::PopFromResult() {
  s21::Token s = stack_number_.top();
  std::string a = s.GetName();
  stack_number_.pop();
  std::cout << "беру       "<< stod(a) << std::endl;
  return stod(a);
}

void s21::Token::MakeUnaryNegation() {
  Token result("negate", kUnaryOperator, kRight, kUnaryPrefixOperator, std::negate<double>()); 
  // *this = result;
}

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
