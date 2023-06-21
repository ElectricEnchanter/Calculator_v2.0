#include "Token.h"

// int main(){
//   std::string a = ".2-.4";
//   std::string b = "";
//   s21::Token w;
//   w.CalculateAnswer(a, b);

//   std::cout << "otvet:  " << w.GetAnswer() << std::endl;
//   return 0;
// }


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
  int size = queue_.size();
  int openBracket = 0;
  int closeBracket = 0;
  
  for (int i = 0; i < size; ++i, queue_.pop()){
    std::string token = queue_.front().GetName();

    if(token == ")") {
      closeBracket++;
      if (closeBracket > openBracket)
      throw std::string("скобка");


      std::cout << queue_token_.top().GetName()<< std::endl;
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
    }else if (i == 0 && (token == "+" || token == "-")){
        if (token == "+") continue;
        if (token == "-") {
          Token a("-", kLow, kRight, kUnaryPrefixOperator, std::negate<double>());
          queue_token_.push(a);
        }
    }else if(queue_token_.empty() && token != "x"){
      if (token == "(") openBracket++;
       queue_token_.push(queue_.front());
    }
    else if(token == "("){
      i++;
      openBracket++;
      queue_token_.push(queue_.front());
      queue_.pop();
      token = queue_.front().GetName();
      if (isdigit(token.at(0))) queue_number_.push(queue_.front());
      else if (token == "+") continue;
      else if (token == "-"){
        Token a("-", kLow, kRight, kUnaryPrefixOperator, std::negate<double>());
        queue_token_.push(a);
      }
      else if (token == "(") {
        queue_token_.push(queue_.front());
        openBracket++;
      }
      else if (token == "x") {
        std::ostringstream ost;
      ost << x_value_;
      Token result(ost.str(), kDefault, kNone, kNumber, x_value_);
      queue_number_.push(result);
      }
      else queue_token_.push(queue_.front());

    } 
    else if (token != ")" && token != "x" )
      Conditions();

    
    
  }
  while(!queue_token_.empty()){
    Counting();
  }
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




void s21::Token::Validator(std::string input, std::string input_x) {
  if(!input_x.empty())
  x_value_ = stod(input_x);
  std::cmatch result;
  std::regex pattern;
  int i = 0;
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

void s21::Token::ConvertToLower() {
  std::transform(input_.begin(), input_.end(), input_.begin(), ::tolower);
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

void s21::Token::Counting() {


        std::cout<< "now token   "<<queue_token_.top().GetName() << std::endl;
    std::visit(
        overloaded{
          
          [&](unary_function function) {
            PushToResult(function(PopFromResult()));
          },

          [&](binary_function function) {
            double right_argument = PopFromResult();
            double left_argument = PopFromResult();
            PushToResult(function(left_argument, right_argument));
          },

          [&](auto) {}
          },

        queue_token_.top().GetFunction()
        );
         queue_token_.pop();

}



void s21::Token::PushNumberToStack(std::string name, double value) {
  std::cout << "пушу " <<  value  << std::endl;
  Token result(name, kDefault, kNone, kNumber, value);
  queue_number_.push(result);
}


void s21::Token::PushTokenToQueue(std::string input){
  auto found_token = token_map_.find(input);
  if (found_token == token_map_.end())
    throw std::string("INVALID CHARACTER(S)");

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
