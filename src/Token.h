#ifndef SMARTCALC_V2_0_H_
#define SMARTCALC_V2_0_H_

#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <map>
#include <queue>
#include <functional>
#include <variant>
#include <initializer_list>



// namespace s21{
// using unary_function = std::function<double(double)>;
// using binary_function = std::function<double(double, double)>;
// using function_variant =
//     std::variant<double, unary_function, binary_function, nullptr_t>;

// 	enum Type {
// 	kNumber,
// 	kBinaryOperator,
// 	kUnaryPrefixOperator,
// 	kUnaryPostfixOperator,
// 	kUnaryFunction,
// 	kOpenBracket,
// 	kCloseBracket,
// 	kNumTokenTypes,
// 	};

// 	enum Priority {
// 		kDefault,
// 		kLow,
// 		kMedium,
// 		kHigh,
// 		kUnaryOperator,
// 		kFunction,
// 	};

// 	enum Associativity{
// 		kNone,
// 		kLeft,
// 		kRight,
// 	};
// };

// namespace s21{

// 	class Token {
// 		public:
// 		Token() = default;
// 		Token(const std::string& name, Priority priority,
// 				Associativity associativity, Type type, function_variant function);
// 		~Token() = default;

// 		// std::string GetName() const;
// 		// Priority GetPriority() const;
// 		// Priority GetAssociativity() const;
// 		// Type GetType() const;
// 		// function_variant GetFunction() const;

// 		void MakeNumber(std::string name, double value);
// 		void MakeUnaryNegation();

// 		private:
// 		std::string name_;
// 		Priority priority_;
// 		Associativity associativity_;
// 		Type type_;
// 		function_variant function_;
// 	};

// 	class Calculator {
// 		public:
// 		Calculator() = default;
// 		~Calculator() = default;

// 		void CalculateAnswer(const std::string& input, const std::string &input_x);
// 		std::string ReadToken (std::string& input, size_t &start_index) const;
// 		double GetAnswer() const;

// 		void PushToken(std::string token);
// 		std::string ConvertToLower(std::string);

// 		private:
// 		double answer_{NAN};
// 		double x_value_{NAN};

// 		std::string input;
// 		std::string input_x;

// 		std::map<std::string, Token> token_map_;
// 		std::queue<Token> input_;

// 	};

// 	void CreateTokenMap(std::map<std::string, s21::Token>& temp_map);
// 	// void CreateTokenMap(std::map<std::string, s21::function_variant> &token_map);
// 	void Validator(std::string input, std::string output);
// };


// int YmdToMord(char *date);

// #endif  // CPP3_S21_SMARTCALC_V2_0_H_


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

};  // namespace MyNamespace

namespace s21 {
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

  void MakeNumber(std::string name, double value);
  void MakeUnaryNegation();

 private:
  std::string name_;
  Precedence precedence_;
  Associativity associativity_;
  Type type_;
  function_variant function_;
};



// void CreateTokenMap(std::map<std::string, s21::Token>& temp_map);
	void CreateTokenMap(std::map<std::string, s21::Token>& temp_map);
// 	// void CreateTokenMap(std::map<std::string, s21::function_variant> &token_map);
	void Validator(std::string input, std::string output);

};  // namespace MyNamespace



#endif  // SMARTCALC_MODEL_MATH_TOKEN_H_