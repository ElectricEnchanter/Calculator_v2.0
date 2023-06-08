
#ifndef SMARTCALC_MODEL_MATH_TOKEN_H_
#define SMARTCALC_MODEL_MATH_TOKEN_H_

#include "Token.h"

namespace s21{
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

  	class Calculator {
		public:
		Calculator();
		~Calculator() = default;

		void CalculateAnswer(const std::string& input, const std::string &input_x);
		std::string ReadToken (std::string& input, size_t &start_index) const;
		double GetAnswer() const;

		double PostfixNotationCalculation(double x_value);
		double PopFromResult();
		void PushToResult(double value);

		
		void PushNumber(std::stack<double>, double value);
		int FindToken(std::string token);
		void PushTokenToQueue(s21::Token token);

		void PushTokenToStack(std::string);
		void PushNumberToStack(double);

		std::string DeleteSpaces(std::string);

		void PrintToken();
		void PrintNumber();

		std::string ConvertToLower(std::string);

		private:
		double answer_{NAN};
		double x_value_{NAN};

		std::string input_;
		std::string input_x;

		std::vector<double> result_;

		std::map<std::string, Token> token_map_;
		std::stack<Token> stack_token_;
		std::stack<double> stack_number_;
		// std::stack<std::string> stack_operation_;

	};
		std::queue<Token> queue_token_;

};

#endif  // SMARTCALC_MODEL_MATH_TOKEN_H_