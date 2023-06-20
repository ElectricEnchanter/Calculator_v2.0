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

TEST(EqualRes, test21){
s21::Token w;
  std::string a = "2^2^2";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 16);
}

TEST(EqualRes, test22){
  s21::Token a("-", s21::kLow, s21::kRight, s21::kUnaryPrefixOperator, std::negate<double>());
  EXPECT_EQ(a.GetAssociativity(), s21::kRight);
  EXPECT_EQ(a.GetType(), s21::kUnaryPrefixOperator);
}

TEST(EqualRes, test23){
  s21::Token w;
  std::string a = "sqrt(9)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 3);
}

TEST(EqualRes, test24){
  s21::Token w;
  std::string a = "3.4+sin(3.55)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 3.00285);
}

TEST(EqualRes, test25){
  s21::Token w;
  std::string a = "9%2";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 1);
}

TEST(EqualRes, test26){
  s21::Token w;
  std::string a = "sin(1)*2";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 1.68294);
}

TEST(EqualRes, test27){
  s21::Token w;
  std::string a = "2*4+1";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 9);
}

TEST(EqualRes, test29){
  s21::Token w;
  std::string a = "4^3-2+2";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 64);
}

TEST(EqualRes, test30){
  s21::Token w;
  std::string a = "1.53232+cos((1))";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 2.07262);
}

TEST(EqualRes, test31){
  s21::Token w;
  std::string a = "1.532327+cos((1))";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 2.07263);
}

TEST(EqualRes, test32){
  s21::Token w;
  std::string a = "1.53232/tan(1.5)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 0.108664);
}

TEST(EqualRes, test33){
  s21::Token w;
  std::string a = "atan(34)^3";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 3.66216);
}

TEST(EqualRes, test34){
  s21::Token w;
  std::string a = "sqrt(36)-16";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), -10);
}

TEST(EqualRes, test35){
  s21::Token w;
  std::string a = "acos(0.5)/6";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 0.174533);
}

TEST(EqualRes, test36){
  s21::Token w;
  std::string a = "6/acos(0.5)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 5.72956);
}

TEST(EqualRes, test37){
  s21::Token w;
  std::string a = "log(4)/50*3";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 0.0361236);
}

TEST(EqualRes, test38){
  s21::Token w;
  std::string a = "3*5^3";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 375);
}

TEST(EqualRes, test39){
  s21::Token w;
  std::string a = "5^3*3";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 375);
}

TEST(EqualRes, test40){
  s21::Token w;
  std::string a = "5-3*3";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), -4);
}

TEST(EqualRes, test41){
  s21::Token w;
  std::string a = "8^3-(2+6*8)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 462);
}

TEST(EqualRes, test42){
  s21::Token w;
  std::string a = "8^3-(2+log(37))";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 508.432);
}

TEST(EqualRes, test43){
  s21::Token w;
  std::string a = "cos(4)*sin((sin(4)))*tan(4)*ln(4)*log(10)";
  std::string b = "";
  w.CalculateAnswer(a, b);
  EXPECT_EQ(w.GetAnswer(), 0.720342);
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

// TEST(Fall, test5){
// s21::Token w;
//   std::string a = "8(9)";
//   std::string b = "";
//   EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
// }

TEST(Fall, test6){
s21::Token w;
  std::string a = "8+9-";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

TEST(Fall, test7){
s21::Token w;
  std::string a = "cis(2)";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

TEST(Fall, test8){
s21::Token w;
  std::string a = "cis(2)";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

TEST(Fall, test9){
s21::Token w;
  std::string a = "2+";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

TEST(Fall, test10){
s21::Token w;
  std::string a = "2. 2";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

TEST(Fall, test11){
s21::Token w;
  std::string a = "2.233.4+5";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

TEST(Fall, test12){
s21::Token w;
  std::string a = "2.233.4+5(4/3";
  std::string b = "";
  EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
}

// TEST(Fall, test13){
// s21::Token w;
//   std::string a = "2.233.4+sin()+3";
//   std::string b = "";
//   EXPECT_ANY_THROW(w.CalculateAnswer(a, b));

  //(\b(?:\d+\.)+\d+(?:)?)
  // 2.3.2^2
  // 2.3.2+
  // 2.233.4+sin()+3
  // 333.444.422
  // 12.34.55
  // 2.233.4+sin()+3
}

// TEST(Fall, test14){
// s21::Token w;
//   std::string a = "2--2";
//   std::string b = "";
//   EXPECT_ANY_THROW(w.CalculateAnswer(a, b));

//(\b\d+(?:(?:[+\-*\/^%]{2,}|(?!\/)\/)[\s]*)?\d+\b)
// 2--2
// 2**2
// 2++2
// 2^^2
// 2%%2
// 2//2
// но не 
// 2.2
// 2 2
// 2-2
// 2*2
// 2+2
// 2^2
// 2%2
// 2/2
// 2+cos(2)
// 2. 2
// 2 2
// }

// TEST(Fall, test15){
// s21::Token w;
//   std::string a = "2.3.2^2";
//   std::string b = "";
//   EXPECT_ANY_THROW(w.CalculateAnswer(a, b));
// }



TEST(YmdToMord, test1){

  const char *data = "2022.20.20";
  int num = 739060;
  int result_num = s21::YmdToMord(data);
  EXPECT_EQ(num, result_num);
}

TEST(YmdToMord, test2){

  const char *data = "2022.20";
  int num = -1;
  int result_num = s21::YmdToMord(data);
  EXPECT_EQ(num, result_num);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
