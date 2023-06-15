#include "Token.h"

#include <gtest/gtest.h>

TEST(EqualRes, test1){
s21::Token w;
  std::string a = "2+2";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 4);
}

TEST(EqualRes, test2){
s21::Token w;
  std::string a = "22-30";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), -8);
}

// TEST(EqualRes, test3){
// s21::Token w;
//   std::string a = "-2+3";
//   std::string b = "";
//   w.CalculateAnswer(a, b);
//   EXPECT_EQ(w.GetAnswer(), 1);
// }

// TEST(EqualRes, test4){
// s21::Token w;
//   std::string a = "+5-5";
//   std::string b = "";
//   w.CalculateAnswer(a, b);
//   EXPECT_EQ(w.GetAnswer(), 10);
// }


TEST(EqualRes, test5){
s21::Token w;
  std::string a = "cos(2)+2";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 1.58385);
}

TEST(EqualRes, test6){
s21::Token w;
  std::string a = "cos(2)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), -0.416147);
}

TEST(EqualRes, test7){
s21::Token w;
  std::string a = "cos(2)+2";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 1.58385);
}

TEST(EqualRes, test8){
	s21::Token w;
	std::string a = "cos(2+3)+4-5";
	std::string b = "";
	w.CalculateAnswer(a, b);
	EXPECT_EQ(w.GetAnswer(), -0.71634);
}

TEST(EqualRes, test9){
	s21::Token w;
	std::string a = "cos(2+3)+4-x";
	std::string b = "5";
	w.CalculateAnswer(a, b);
	EXPECT_EQ(w.GetAnswer(), -0.71634);
}



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
