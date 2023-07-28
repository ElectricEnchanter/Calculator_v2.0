#ifndef CPP3_CALCULATOR_V2_0_BACK_CONTROLLER_H_
#define CPP3_CALCULATOR_V2_0_BACK_CONTROLLER_H_

#include "Calculator.h"

namespace s21 {
class Controller {
public:
  Controller(Calculator &cal) : cal_(&cal){};
  ~Controller() = default;

  std::string Calculate(std::string input, std::string input_x) {
    try {
      cal_->CalculateAnswer(input, input_x);
    } catch (std::string error_message) {
      return error_message;
    }

    double result = cal_->GetAnswer();
    if (fmod(result, 1) == 0)
      return std::to_string(static_cast<int>(result));
    else
      return std::to_string(cal_->GetAnswer());
  }

  std::string CalculateGraph(std::string input, std::string input_x) {
    try {
      cal_->CalculateGraph(input, input_x);
    } catch (std::string error_message) {
      return error_message;
    }
  }

  std::vector<double> GetCoordinatesX() { return cal_->GetCoordinatesX(); }
  std::vector<double> GetCoordinatesY() { return cal_->GetCoordinatesY(); }

private:
  Calculator *cal_;
};

}; // namespace s21

#endif // CPP3_CALCULATOR_V2_0_BACK_CONTROLLER_H_
