#ifndef TOKEN_H_
#define TOKEN_H_

#include <cmath>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <regex>
#include <stack>
#include <variant>

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
	using function_variant = std::variant<double, unary_function, binary_function, nullptr_t>;

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
  ~Token() = default;

  std::string GetName() const;
  Precedence GetPrecedence() const;
  Associativity GetAssociativity() const;
  Type GetType() const;
  function_variant GetFunction() const;

  std::string ReadToken(std::string& input, size_t& start_index) const;
  int TryToPushTokenToStack(std::string token);


  void CreateTokenMap(std::map<std::string, s21::Token>& temp_map);

  void PushNumberToStack(std::string name, double value);
  void MakeUnaryNegation();

  void Validator(std::string input, std::string output);
	std::string ConvertToLower(std::string);


  double PostfixNotationCalculation(double x_value);
  double PopFromResult();
  void PushToResult(double value);

  std::map<std::string, Token> token_map_;
  // std::queue<Token> queue_token_;

  std::stack<Token> stack_token_;
  std::stack<Token> stack_number_;

    double answer_;
		double x_value_;
    vector<double> result_;

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
