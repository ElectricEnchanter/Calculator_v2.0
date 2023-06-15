#include "Token.h"


  // std::string a = "-10-30";
// std::string a = "cos(x";

// int main() {
//   s21::Token w;
//   std::string a = "cos(2+3)+4-x";
//   // std::string a = "x+2";
//   std::string b = "5";
//   w.CalculateAnswer(a, b);
//   w.GetAnswer();

//  std::cout << "ответ " << w.GetAnswer() << std::endl;

//  return 1; 
// }

// унарники и пробелы


namespace s21 {

s21::Token::Token(const std::string& name, Precedence precedence,
                  Associativity associativity, Type type,
                  function_variant function)
    : name_(name),
      precedence_(precedence),
      associativity_(associativity),
      type_(type),
      function_(function){};


std::queue<Token> Token::queue_;
std::stack<s21::Token> Token::queue_token_;
std::stack<s21::Token> Token::queue_number_;


// std::queue<Token> Token::queue_token_;
// std::queue<Token> Token::queue_number_;

std::string s21::Token::GetName() const { return name_; }

s21::Precedence s21::Token::GetPrecedence() const { return precedence_; }

s21::Associativity s21::Token::GetAssociativity() const {
  return associativity_;
}

s21::Type s21::Token::GetType() const { return type_; }

s21::function_variant s21::Token::GetFunction() const { return function_; }

double s21::Token::GetAnswer() { return answer_; }

void s21::Token::SetAnswer() {

  std::cout << queue_number_.top().GetName() <<std::endl;
  answer_ = stod(queue_number_.top().GetName());
  queue_number_.pop();
}

void s21::Token::CalculateAnswer(std::string input, std::string input_x) {
  if (input.empty())  throw std::string("EMPTY LINE");

  CreateTokenMap(token_map_);
  ConvertToLower();
  Validator(input, input_x);
  FindSpacesAndUnaries();
 
  SetAnswer();
 
}

void s21::Token::FindSpacesAndUnaries(){

  while (!queue_.empty()){

    std::string token = queue_.front().GetName();
    if (token == " ")
    queue_.pop();
    // continue;
    if (token == "-"){

    }

    if(token == ")") {
      while(queue_token_.top().GetName() != "("){
        Counting();
      }
      queue_token_.pop();
    }
    if (token == "x"){
      std::ostringstream ost;
      ost << x_value_;
       Token result(ost.str(), kDefault, kNone, kNumber, x_value_);
      queue_number_.push(result);
    }
    if (isdigit(token.at(0))){
      queue_number_.push(queue_.front());
    }else if(queue_token_.empty() && token != "x"){
       queue_token_.push(queue_.front());
    }
    else if(token == "("){
      queue_token_.push(queue_.front());
    } 
    else if (token != ")" && token != "x" )
      Conditions();

    
    queue_.pop();
  }

//   while (!queue_number_.empty()){
//   std::string token = queue_number_.top().GetName();
//     std::cout <<  token << std::endl;
//     queue_number_.pop();
//   }
//  std::cout <<  " sssssssssssssssssss" << std::endl;
//   while (!queue_token_.empty()){
//   std::string token = queue_token_.top().GetName();
//     std::cout <<  token << std::endl;
//     queue_token_.pop();
//   }
  

  while(!queue_token_.empty()){
    Counting();
  }


  








  //   double queue_size = queue_.size();
  //   // std::cout << queue_.size() << std::endl;

  // for(size_t i = 0; i < queue_size; ++i){
  //   std::string buffer = queue_.front().GetName();
  //   if (buffer == "-"){
  //     if (i == 0) {
  //       queue_.pop();
  //       buffer = queue_.front().GetName();
  //       if (isdigit(buffer.at(0)))
  //         TryToPushTokenToStack("neg");
  //       i++;
  //     }
  //   }
  //   if (buffer == "+" && i == 0) {
  //       // i++;
  //   }
  //   // if (buffer == " "){
      
   
  //   if (std::isdigit(buffer.at(0))) {
  //     PushNumberToStack(buffer, std::stod(buffer));
  //   } else if (buffer == "x") {
  //     PushNumberToStack(input_x_, std::stod(input_x_));
  //   } else {
  //     TryToPushTokenToStack(buffer);
  //   }
  //   queue_.pop();
  // }
}

void s21::Token::Conditions(){
  std::cout << "Условия" << std::endl;
  std::cout <<queue_token_.top().GetName() <<queue_token_.top().GetPrecedence() << std::endl;
  std::cout <<queue_.front().GetName() <<queue_.front().GetPrecedence() << std::endl;


  if(queue_token_.top().GetPrecedence() > queue_.front().GetPrecedence() || queue_token_.top().GetPrecedence() == queue_.front().GetPrecedence() ){
    
    Counting();
    queue_token_.push(queue_.front());
  }else {
    queue_token_.push(queue_.front());
  }
}

void s21::Token::SetFunction(){
  std::string name = name_;
  if(isdigit(name.at(0)))
  function_ = std::negate<double>(); 
}



void s21::Token::Validator(std::string input, std::string input_x) {
  if(!input_x.empty())
  x_value_ = stod(input_x);

  std::cmatch result;
  std::regex pattern("[^-/ %.cosintaqrtlgx()^/*+0-9]");

  if (std::regex_search(input.c_str(), result, pattern))
    throw std::string("INVALID CHARACTER(S)");

  //  pattern = "^[^0-9]";
  // if (std::regex_search(input.c_str(), result, pattern) && !isdigit(stod(input_x)))
  // throw std::string("INVALID CHARACTER(S)");

  if (std::regex_search(input_x.c_str(), result, pattern))
    throw std::string("INVALID CHARACTER(S)");

  for (size_t index = 0; input.length() > index; ++index) {
    std::string token = ReadToken(input, index);
    if (isdigit(token.at(0))){
      Token result(token, kDefault, kNone, kNumber, stod(token));
      queue_.push(result);
    } else PushTokenToQueue(token);
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

void s21::Token::Counting() {

  using namespace s21;

   

        std::cout<< "now token   "<<queue_token_.top().GetName() << std::endl;
    std::visit(
        overloaded{
          [&](double function) {
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

          [&](auto) {
          std::cout << "скобка" << std::endl;
          std::string bracet = queue_token_.top().GetName();
          if (bracet != "(" && bracet != ")") PushToResult(x_value_); 
          else if (bracet == ")") {
            while (queue_token_.top().GetName() != "("){
              
              queue_token_.pop();
              queue_token_.top().GetFunction();
              PostfixNotationCalculation(x_value_);
            }
          }}},

        queue_token_.top().GetFunction()
        );
         queue_token_.pop();

}


void s21::Token::PostfixNotationCalculation(double x_value) {

  using namespace s21;

  while (!queue_token_.empty()) {
        std::cout<< "now token   "<<queue_token_.top().GetName() << std::endl;
    std::visit(
        overloaded{
          // [&](kNumber function){
          // std::cout << "цыфра" << std::endl;
          //   PushToResult(kNumber);

          // },
          [&](double function) {
            std::cout << "цыфра" << std::endl;
            PushToResult(function);
          },

          [&](unary_function function) {
            PushToResult(function(PopFromResult()));
          },

          [&](binary_function function) {
            double right_argument = PopFromResult();
            double left_argument = PopFromResult();
            PushToResult(function(right_argument, left_argument));
          },

          [&](auto) {
          std::cout << "скобка" << std::endl;
          std::string bracet = queue_token_.top().GetName();
          if (bracet != "(" && bracet != ")") PushToResult(x_value); 
          else if (bracet == ")") {
            while (queue_token_.top().GetName() != "("){
              
              queue_token_.pop();
              queue_token_.top().GetFunction();
              PostfixNotationCalculation(x_value);
            }
          }}},

        queue_token_.top().GetFunction()
        );
      // std::cout<< queue_token_.top().GetName() << std::endl;

        queue_token_.pop();
  }


}

void s21::Token::PushNumberToStack(std::string name, double value) {
  std::cout << "пушу " <<  value  << std::endl;
  Token result(name, kDefault, kNone, kNumber, value);
  queue_number_.push(result);
}

int s21::Token::TryToPushTokenToStack(std::string token) {
    // std::cout << "token "<< token << std::endl;

  if (token == " ") return 0;
  auto found_token = token_map_.find(token);
  if (found_token == token_map_.end())
    throw std::string("INVALID CHARACTER(S) " + token);

  queue_token_.push(found_token->second);
  return 1;
}

void s21::Token::PushTokenToQueue(std::string input){
  auto found_token = token_map_.find(input);
  if (found_token == token_map_.end())
    throw std::string("INVALID CHARACTER(S) " + input);

  queue_.push(found_token->second);
}



void s21::Token::PushToResult(double value) {
  std::ostringstream token;
  token << value;
  std::string str = token.str();
  PushNumberToStack(str, value);
}

double s21::Token::PopFromResult() {
  if(queue_number_.empty())
   throw std::string("NOT ENOUGH NUMBERS");
  else {
  s21::Token s = queue_number_.top();
  std::string a = s.GetName();
  std::cout << "беру       "<< stod(a) << std::endl;
  queue_number_.pop();
  return stod(a);
  }

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
