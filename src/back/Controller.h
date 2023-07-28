#ifndef BACK_CONTROLLER_H_
#define BACK_CONTROLLER_H_

#include "Calculator.h"

namespace s21 {
class Controller {
public:
  Controller(Calculator &cal) : cal_(&cal){};
  ~Controller() = default;

  std::string Calculate(std::string input, std::string xinput) {
    try {
      cal_->CalculateAnswer(input, xinput);
    } catch (...) {
      return "error";
    }

    double result = cal_->GetAnswer();
    if (fmod(result, 1) == 0)
      return std::to_string(static_cast<int>(result));
    else
      return std::to_string(cal_->GetAnswer());
  }

  void CalculateGraph(std::string input, std::string xinput) {
    cal_->CalculateGraph(input, xinput);
  }

  std::vector<double> GetxСoordinates() { return cal_->GetxСoordinates(); }
  std::vector<double> GetyСoordinates() { return cal_->GetyСoordinates(); }

private:
  Calculator *cal_;
};

}; // namespace s21

#endif // BACK_CALCULATOR_H_
