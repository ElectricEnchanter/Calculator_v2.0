#include "Token.h"
#include "Calculator.h"

int main(){
  std::string a = "1.23 2-";
  std::string b;
  s21::Validator(a,b);

  return 0;
}
std::string s21::Token::GetName() const { return name_; }

s21::Precedence s21::Token::GetPrecedence() const {
  return precedence_;
}

s21::Associativity s21::Token::GetAssociativity() const {
  return associativity_;
}

s21::Type s21::Token::GetType() const { return type_; }

s21::function_variant s21::Token::GetFunction() const {
  return function_;
}

double s21::Calculator::GetAnswer() const { return answer_; }


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
  s21::Calculator expression;
  s21:Token Number;
  input = expression.ConvertToLower(input);
  // input = expression.DeleteSpaces(input);
  std::cmatch result;
  std::regex pattern("[^-/ %.cosintaqrtlgx()^/*+0-9]");

  if (std::regex_search(input.c_str(), result, pattern))
    throw std::logic_error("Incorrect symbols");


  for (size_t index = 0; input.length() > index; ++index){
    std::string a = expression.ReadToken(input, index);
    
    if(!isdigit(a.at(0))){
      if(expression.FindToken(a)){
          std::cout << "запихал знак" << std::endl;
      }
    } else {
      expression.PushNumberToStack(stod(a));
        }
  }


  // expression.PrintToken();
  // expression.PrintNumber();
  double d = expression.PostfixNotationCalculation(0);
  std::cout << "Ответ "<< d << std::endl;
  
  // if(input_queue_.empty())
  //   std::cout << "почистился"<< std::endl;

}

std::string s21::Calculator::DeleteSpaces(std::string input){
  input.erase(remove(input.begin(),input.end(),' '),input.end());
  std::cout << "без пробелов"<< input << std::endl;
  return input;
}

std::string s21::Calculator::ReadToken(std::string& input, size_t & index) const{
  std::regex pattern;
  if (isdigit(input.at(index) )){
    // std::cout << "число ";
    pattern = ("\\d+([.]\\d+)?(e([-+])?\\d+)?");
  } else if (isalpha(input.at(index))){
      // std::cout << "функция ";
      pattern = "([%cosintaqrtlgx]+)";
  } else {
      // std::cout << "знак ";
      pattern = "([-( )^/*+])";
  }
    std::sregex_iterator regex_iterator = std::sregex_iterator (
    input.begin() + index, input.end(), pattern);
    std::smatch match = *regex_iterator;
    index += match.length() - 1;
    return match.str();
  }


// void s21::Calculator::PrintToken(){
//         std::cout << "колво операторов "<< stack_operation_.size() << std::endl;

//   while(!stack_operation_.empty()){
//     std::cout << stack_operation_.top() << std::endl;
//     stack_operation_.pop();
//   }
// }

void s21::Calculator::PrintNumber(){
      std::cout << "колво цыфор "<< stack_number_.size() << std::endl;

  while(!stack_number_.empty()){
    std::cout << stack_number_.top() << std::endl;
    stack_number_.pop();
  }
}


void s21::Calculator::PushTokenToQueue(s21::Token token){
  queue_token_.push(token);
}


double s21::Calculator::PostfixNotationCalculation(double x_value) {
  using namespace s21;
  // input_ = output_;

  while (!queue_token_.empty()) {
    // std::cout << "вытащил ебень" << std::endl;
    // std::cout << std::endl;

    std::visit(
        overloaded{
          [&](double function) { 
            std::cout << "цыфра" << std::endl;
            PushToResult(function); },
                   
          [&](unary_function function) {
            PushToResult(function(PopFromResult())); },

          [&](binary_function function) {
            double right_argument = PopFromResult();
            double left_argument = PopFromResult();
            PushToResult(function(left_argument, right_argument)); },

          [&](auto) { PushToResult(x_value); }},

         queue_token_.front().GetFunction());
  }
  answer_ = PopFromResult();
  return answer_;
}

void s21::Calculator::PushToResult(double value) {
    std::cout << value << std::endl;

  result_.push_back(value);

  queue_token_.pop();
}

double s21::Calculator::PopFromResult() {


  // queue_token_.pop();
  return stack_number_.top();
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
    {"x", Token("x", kDefault, kNone, kNumber, nullptr)},
    {"(", Token("(", kDefault, kNone, kOpenBracket, nullptr)},
    {")", Token(")", kDefault, kNone, kCloseBracket, nullptr)},
    {"cos", Token("cos", kFunction, kRight, kUnaryFunction, cosl)},
  };
  token_map.insert(list);
}

std::string s21::Calculator::ConvertToLower(std::string input){
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  return input;
}

void s21::Token::PushNumberToQueue(std::string name, double value){
  std::cout << name << std::endl;
  Token result(name, kDefault, kNone, kNumber, value);
  queue_token_.push(result);
    std::cout<< "запихал число "<<std::endl;

}

int s21::Calculator::FindToken(std::string token){
  if (token == " ") return 0;
  auto found_token = token_map_.find(token);
  if (found_token == token_map_.end() )
    throw std::logic_error("Incorrect symbol: " + token);
  
  queue_token_.push(found_token->second);
  return 1;
}


// void s21::Calculator::PushTokenToStack(std::string token){
//   stack_operation_.push(token);
// }
void s21::Calculator::PushNumberToStack(double value){
      std::cout<< "попал число "<<std::endl;

  stack_number_.push(value);
}



// void s21::Token::MakeUnaryNegation() {
//   Token result("negate", kUnaryOperator, kRight, kUnaryPrefixOperator, std::negate<double>());
//   *this = result;
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
