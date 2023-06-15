#ifndef TOKEN_H_
#define TOKEN_H_

#include <cmath>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <stack>
#include <variant>
#include <vector>
#include <sstream>

namespace s21 {

enum Precedence {
  kDefault,
  kLow,
  kMedium,
  kHigh,
  kUnaryOperator,
  kFunction,
};

enum Type {
  kNumber,
  kBinaryOperator,
  kUnaryPrefixOperator,
  kUnaryPostfixOperator,
  kUnaryFunction,
  kOpenBracket,
  kCloseBracket,
  kNumTokenTypes,
};

enum Associativity {
  kNone,
  kLeft,
  kRight,
};

using unary_function = std::function<double(double)>;
using binary_function = std::function<double(double, double)>;
using function_variant =
    std::variant<double, unary_function, binary_function, nullptr_t>;

/// @brief template class for redefining lambda expressions in std::visit
/// @tparam ...Ts - accepted type of lambda expression
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};

/// @brief method of redefining the list of arguments of the overloaded method
/// into classes
/// @tparam ...Ts - accepted type of lambda expression
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

class Token {
 public:
  Token() = default;
  Token(const std::string& name, Precedence precedence,
        Associativity associativity, Type type, function_variant function);
  Token(const Token&) = default;
  Token(const Token&& ) = delete;

  ~Token() = default;

  void Counting(double x_value);

  std::string GetName() const;
  Precedence GetPrecedence() const;
  Associativity GetAssociativity() const;
  Type GetType() const;
  function_variant GetFunction() const;
  void SetFunction();
  double GetAnswer();
  void SetAnswer();
  void CalculateAnswer(std::string input, std::string input_x);
  void Conditions();
  void Counting();

  std::string ReadToken(std::string& input, size_t& start_index) const;
  int TryToPushTokenToStack(std::string token);

  void CreateTokenMap(std::map<std::string, s21::Token>& temp_map);

  void PushNumberToStack(std::string name, double value);

  void FindSpacesAndUnaries();
  void Validator(std::string input, std::string output);
  void ConvertToLower();

  void PostfixNotationCalculation(double x_value);
  double PopFromResult();
  void PushToResult(double value);
  void PushTokenToQueue(std::string input);


  std::map<std::string, Token> token_map_;

  std::string input_;
  std::string input_x_;

  double answer_{NAN};
  double x_value_{NAN};





static  std::queue<s21::Token> queue_;

static std::stack<s21::Token> queue_token_;
static std::stack<s21::Token> queue_number_;

 private:
  std::string name_;
  Precedence precedence_;
  Associativity associativity_;
  Type type_;
  function_variant function_;
};

int YmdToMord(char* date);

};  // namespace s21

#endif  // TOKEN_H_
