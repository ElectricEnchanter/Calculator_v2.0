#ifndef BACK_TOKEN_H_
#define BACK_TOKEN_H_

#include <functional>
#include <initializer_list>
#include <iostream>
#include <variant>

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

class Token {
public:
  Token() = default;
  Token(const std::string &name, Priority priority, Associativity associativity,
        Type type, function_variant function);
  Token(const Token &) = default;
  Token(const Token &&) = delete;
  ~Token() = default;

  std::string GetName() const;
  Priority GetPriority() const;
  Associativity GetAssociativity() const;
  Type GetType() const;
  function_variant GetFunction() const;

private:
  std::string name_;
  Priority priority_;
  Associativity associativity_;
  Type type_;
  function_variant function_;
};

int YmdToMord(const char *date);

}; // namespace s21

#endif // BACK_TOKEN_H_
