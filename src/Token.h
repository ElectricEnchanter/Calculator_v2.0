#ifndef SMARTCALC_V2_0_H_
#define SMARTCALC_V2_0_H_

#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <functional>
#include <variant>
#include <initializer_list>


namespace s21 {

  using unary_function = std::function<double(double)>;
  using binary_function = std::function<double(double, double)>;
  using function_variant =
      std::variant<double, unary_function, binary_function, nullptr_t>;

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

  class Token {
  public:
    Token() = default;
    Token(const std::string& name, Precedence precedence,
          Associativity associativity, Type type, function_variant function);
    ~Token() = default;

    std::string GetName() const;
    Precedence GetPrecedence() const;
    Associativity GetAssociativity() const;
    Type GetType() const;
    function_variant GetFunction() const;

    void PushNumberToQueue(std::string name, double value);
    void MakeUnaryNegation();

  private:
    std::string name_;
    Precedence precedence_;
    Associativity associativity_;
    Type type_;
    function_variant function_;
};



	void CreateTokenMap(std::map<std::string, s21::Token>& temp_map);

	void Validator(std::string input, std::string output);

};  // namespace MyNamespace



#endif  // SMARTCALC_MODEL_MATH_TOKEN_H_