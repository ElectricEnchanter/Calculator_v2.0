#ifndef BACK_CALCULATOR_H_
#define BACK_CALCULATOR_H_

#include <cmath>
#include <map>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <vector>

#include "Token.h"

namespace s21 {

/// @brief template class for redefining lambda expressions in std::visit
/// @tparam ...Ts - accepted type of lambda expression
template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

/// @brief method of redefining the list of arguments of the overloaded method
/// into classes
/// @tparam ...Ts - accepted type of lambda expression
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

class Calculator {
public:
  double GetAnswer();
  std::vector<double> GetxСoordinates();
  std::vector<double> GetyСoordinates();
  void CalculateAnswer(std::string input, std::string input_x);
  void CalculateGraph(std::string input, std::string input_x);

private:
  double answer_{NAN};
  double x_value_{NAN};

  std::string input_;
  std::string input_x_;

  std::vector<double> xСoordinates_, yСoordinates_;

  std::map<std::string, Token> token_map_;
  static std::queue<Token> queue_;
  static std::stack<Token> stack_token_;
  static std::stack<Token> stack_number_;

  void CreateTokenMap(std::map<std::string, Token> &temp_map);
  std::string ReadToken(std::string &input, size_t &start_index) const;
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
  void ClearСoordinates();
};

int YmdToMord(const char *date);

}; // namespace s21

#endif // BACK_CALCULATOR_H_
