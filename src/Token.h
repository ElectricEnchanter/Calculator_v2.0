#ifndef TOKEN_H_
#define TOKEN_H_

#include <cmath>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <variant>
#include <vector>

namespace s21 {

enum Priority {
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
  Token(const std::string& name, Priority priority, Associativity associativity,
        Type type, function_variant function);
  Token(const Token&) = default;
  Token(const Token&&) = delete;
  ~Token() = default;

  std::string GetName() const;
  Priority GetPriority() const;
  Associativity GetAssociativity() const;
  Type GetType() const;
  function_variant GetFunction() const;

  double GetAnswer();
  void CalculateAnswer(std::string input, std::string input_x);

 private:
  std::string name_;
  Priority priority_;
  Associativity associativity_;
  Type type_;
  function_variant function_;

  double answer_{NAN};
  double x_value_{NAN};

  std::string input_;
  std::string input_x_;
  int bracket_{0};

  static std::queue<s21::Token> queue_;
  static std::stack<s21::Token> stack_token_;
  static std::stack<s21::Token> stack_number_;
  std::map<std::string, Token> token_map_;

  void CreateTokenMap(std::map<std::string, s21::Token>& temp_map);
  std::string ReadToken(std::string& input, size_t& start_index) const;
  void ConvertToLower();
  void FindUnaries(std::string input);
  void Validator(std::string input, std::string output);
  void Parser();
  void Counting();
  void Conditions();
  void SetAnswer();
  void CleanStacks();
  double PopFromResult();
  void PushNumberToStack(double value);
  void PushTokenToQueue(std::string input);
};

int YmdToMord(const char* date);

};  // namespace s21

#endif  // TOKEN_H_
