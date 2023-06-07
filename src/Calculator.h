
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

		void PushToken(std::string token);
		std::string ConvertToLower(std::string);

		private:
		double answer_{NAN};
		double x_value_{NAN};

		std::string input;
		std::string input_x;

		std::map<std::string, Token> token_map_;
		std::queue<Token> input_;

	};

};

#endif  // SMARTCALC_MODEL_MATH_TOKEN_H_