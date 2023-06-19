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

TEST(EqualRes, test3){
s21::Token w;
  std::string a = "-2+3";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 1);
}

TEST(EqualRes, test4){
s21::Token w;
  std::string a = "+5-5";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 0);
}


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

TEST(EqualRes, test10){
	s21::Token w;
	std::string a = "cos(x)";
	std::string b = "5";
	w.CalculateAnswer(a, b);
	EXPECT_EQ(w.GetAnswer(), 0.283662);
}

TEST(EqualRes, test11){
	s21::Token w;
  std::string a = "-2+x";
  std::string b = "5";
	w.CalculateAnswer(a, b);
	EXPECT_EQ(w.GetAnswer(), 3);
}

TEST(EqualRes, test12){
	s21::Token w;
  std::string a = "sin(sin(x))";
  std::string b = "2";
	w.CalculateAnswer(a, b);
	EXPECT_EQ(w.GetAnswer(), 0.789072);
}

TEST(EqualRes, test13){
	s21::Token w;
  std::string a = "sin(sin(sin(x)))";
  std::string b = "2";
	w.CalculateAnswer(a, b);
	EXPECT_EQ(w.GetAnswer(), 0.70970);
}

TEST(EqualRes, test14){
	s21::Token w;
  std::string a = "10 * 30";
  std::string b = "";
	w.CalculateAnswer(a, b);
	EXPECT_EQ(w.GetAnswer(), 300);
}

TEST(EqualRes, test15){
s21::Token w;
  std::string a = "+5+5";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 10);
}

TEST(EqualRes, test16){
s21::Token w;
  std::string a = "+5+(-3)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 2);
}

TEST(EqualRes, test17){
s21::Token w;
  std::string a = "5+(-3)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 2);
}

TEST(EqualRes, test18){
s21::Token w;
  std::string a = "5+(+3)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 8);
}

TEST(EqualRes, test19){
s21::Token w;
  std::string a = "+5+(+3)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 8);
}

TEST(EqualRes, test20){
s21::Token w;
  std::string a = "-10-30";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), -40);
}




TEST(Fall, test1){
s21::Token w;
  std::string a = "adasdsa";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

TEST(Fall, test2){
s21::Token w;
  std::string a = "sin(sin(sin()))";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

TEST(Fall, test3){
s21::Token w;
  std::string a = "++++";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}


TEST(Fall, test4){
s21::Token w;
  std::string a = "-----";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

TEST(Fall, test5){
s21::Token w;
  std::string a = "8(9)";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
