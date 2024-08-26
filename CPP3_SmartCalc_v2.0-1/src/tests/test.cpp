#include <gtest/gtest.h>

#include "../model/model.h"

using namespace s21;

TEST(test_s21_smart_calc_1, test_1) {
  Model M("3+3=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 6.0, 0.0000001);
}

TEST(test_s21_smart_calc_2, test_2) {
  Model M("   (2.33+2.33)*10=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 46.6, 0.0000001);
}

TEST(test_s21_smart_calc_3, test_3) {
  Model M("0+0.234=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 0.234, 0.0000001);
}

TEST(test_s21_smart_calc_4, test_4) {
  Model M("10-1+2*10-5*5=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 4.0, 0.0000001);
}

TEST(test_s21_smart_calc_5, test_5) {
  Model M("cos(tan(1))=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 0.0133882, 0.0000001);
}

TEST(test_s21_smart_calc_6, test_6) {
  Model M("sin(log(2))=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 0.296504, 0.0000001);
}

TEST(test_s21_smart_calc_7, test_7) {
  Model M("log(ln(2))/10^2=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -0.001591745, 0.0000001);
}

TEST(test_s21_smart_calc_8, test_8) {
  Model M("atan(x)=", "1");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 0.7853981633, 0.0000001);
}

TEST(test_s21_smart_calc_9, test_9) {
  Model M("1++=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_10, test_10) {
  Model M("1+2+=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_11, test_11) {
  Model M("10mod7=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 3.0, 0.0000001);
}

TEST(test_s21_smart_calc_12, test_12) {
  Model M("sqrt(6)=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 2.449489742, 0.0000001);
}

TEST(test_s21_smart_calc_13, test_13) {
  Model M("sqrt(0)=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 0, 0.0000001);
}

TEST(test_s21_smart_calc_14, test_14) {
  Model M("1.22*2+(6-3.33)/log(3)=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 8.036061742, 0.0000001);
}

TEST(test_s21_smart_calc_15, test_15) {
  Model M("asin(1)=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 1.5707963267, 0.0000001);
}

TEST(test_s21_smart_calc_16, test_16) {
  Model M("acos(0)=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 1.5707963267, 0.0000001);
}

TEST(test_s21_smart_calc_17, test_17) {
  Model M("-2+3+(-2)-3-(+2)=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -6.0, 0.0000001);
}

TEST(test_s21_smart_calc_18, test_18) {
  Model M("cos(0.48) ( * ) sqrt(0.24) ()  + asin(acos(0.28)) ^ 0.33 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_19, test_19) {
  Model M("cos(0.48) *     sqrt(0.24)  + asin(acos(0.28)) ^ 0.33 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_EQ(std::isnan(M.get_data().value()), 1);
}

TEST(test_s21_smart_calc_20, test_20) {
  Model M("cos(0.48) *     sqrt(x-0.04)  + asin(x) ^ 0.33 =", "0.280000");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 1.0944567, 0.0000001);
}

TEST(test_s21_smart_calc_21, test_21) {
  Model M("4.4^3^2 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 618121.839509504, 0.0000001);
}

TEST(test_s21_smart_calc_22, test_22) {
  Model M("log(-0.20) ^ asin(-0.55) ()  ()  + asin(0.12) - 0.58 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_23, test_23) {
  Model M("log(-0.20) ^ asin(-0.55)  + asin(0.12) - 0.58   =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_EQ(std::isnan(M.get_data().value()), 1);
}

TEST(test_s21_smart_calc_24, test_24) {
  Model M("log(0.20) * asin(-0.55)  + asin(0.12) +12.58   =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 13.107345016, 0.0000001);
}

TEST(test_s21_smart_calc_25, test_25) {
  Model M("0.62 mod )  (0.97 ^ sin(-0.44) + 0.54 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_26, test_26) {
  Model M("0.62 mod 1  (0.97 ^ sin(-0.44) + 0.54 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_27, test_27) {
  Model M("2 mod 1 + (0.97 ^ sin(-0.44) + x =", "1.23.4");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_28, test_28) {
  Model M("12.2 mod 2 + (0.97 ^ sin(-0.44)) + x =", "1.234");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 2.4470583, 0.0000001);
}

TEST(test_s21_smart_calc_29, test_29) {
  Model M("12.2 mod 2 + (0.97 ^ sin(-0.44) + =x =", "1.234");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_30, test_30) {
  Model M("asin(-0.04) *  (-0.68)  ^ -0.14 / -0.12 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_EQ(std::isnan(M.get_data().value()), 1);
}

TEST(test_s21_smart_calc_31, test_31) {
  Model M("asin(-0.04)) *  (-0.68)  ^ -0.14 / -0.12 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_32, test_32) {
  Model M("asin(-0.04) *  (x)  ^ -0.14 / (x/3) =", "1234");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -0.0000359, 0.0000001);
}

TEST(test_s21_smart_calc_33, test_33) {
  Model M(
      "log(tan(0.28)) / sqrt(0.26) / atan(0.04) / atan(0.18) mod log(0.59) =",
      "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -0.147803774, 0.0000001);
}

TEST(test_s21_smart_calc_34, test_34) {
  Model M(
      "log(tan(0.28)) / ()sqrt(0.26) / atan(0.04) / atan(0.18) mod log(0.59) =",
      "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_35, test_35) {
  Model M(
      "log(tan(0.28)) / sqrt(-0.26) / atan(0.04) / atan(0.18) mod log(0.59) =",
      "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_EQ(std::isnan(M.get_data().value()), 1);
}

TEST(test_s21_smart_calc_36, test_36) {
  Model M("log(tan(0.28)) / sqrt(-0.26) / atan(0.04) / atan(0.18) mod =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_37, test_37) {
  Model M("-0.58 ^ 0.97 ^  () 0.86 / 0.85 * -0.36 = =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_38, test_38) {
  Model M("--0.58 ^ 0.97 ^ 0.86 / 0.85 * -0.36 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_39, test_39) {
  Model M("0.58 ^ 0.97 ^ 0.86 / x * -(x/0) =", "12");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_40, test_40) {
  Model M("0.58 ^ 0.97 ^ 0.86 / 0.85 * -0.36 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -0.2491311, 0.0000001);
}

TEST(test_s21_smart_calc_41, test_41) {
  Model M("0.58 ^ 0.97 ^ 0.86 / x * -(x/4.5) =", "12");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -0.130717, 0.0000001);
}

TEST(test_s21_smart_calc_42, test_42) {
  Model M("-0.93)  ( + 0.67  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_43, test_43) {
  Model M("(-0.93) + ( + 0.6712111)  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -0.2587889, 0.0000001);
}

TEST(test_s21_smart_calc_44, test_44) {
  Model M("/tan(-0.32) / atan(0.17) =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_45, test_45) {
  Model M("tan(-0.32) / atan(x) =", "0.014");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -23.6722182048, 0.0000001);
}

TEST(test_s21_smart_calc_46, test_46) {
  Model M("-0.98 mod (cos(-0.69) * ( - ln(0.84)))  =  ", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 0.0957548402, 0.0000001);
}

TEST(test_s21_smart_calc_47, test_47) {
  Model M("-0.98 mod cos(-0.69)  ( - ln(0.84)  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_48, test_48) {
  Model M("0.56 - acos(ln(0.74)) mod acos(log(-0.48)) - tan(-0.60)  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_EQ(std::isnan(M.get_data().value()), 1);
}

TEST(test_s21_smart_calc_49, test_49) {
  Model M("0.56 - acos(ln(0.74)) mod acos(log(-0.48))) - tan(-0.60)  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_50, test_50) {
  Model M("        0.56 - acos(ln(0.74)) mod acos(log(x)) - tan(-0.60)  =",
          "0.48");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -0.6325108358, 0.0000001);
}

TEST(test_s21_smart_calc_51, test_51) {
  Model M("12.321  + 12 mod 0.0 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_EQ(std::isnan(M.get_data().value()), 1);
}

TEST(test_s21_smart_calc_52, test_52) {
  Model M(
      "12."
      "321111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "11111111+"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "11111111111111111111111111111111111111=",
      "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_53, test_53) {
  Model M("12.321  + 12 MOD 0.0 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_54, test_54) {
  Model M("12.321 11.1 + 12 + 0.0 =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_55, test_55) {
  Model M("sin64.4)=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_56, test_56) {
  Model M("++1=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_57, test_57) {
  Model M("1+++1=", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_58, test_58) {
  Model M("1x=", "12");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_59, test_59) {
  Model M("-0.98 mod cos(-0.69)  ( - ln(0.84)  =", "a12");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_60, test_60) {
  Model M("-0.98 mod cos(-0.6.9) ( - ln(0.84)  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_61, test_61) {
  Model M("-0.98 mod cos(-0.69)  ( - ln(0.84)  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_62, test_62) {
  Model M("x+6 =", "0,12");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 6.12, 0.0000001);
}

TEST(test_s21_smart_calc_63, test_63) {
  Model M("6+x =", "-0,12");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 5.88, 0.0000001);
}

TEST(test_s21_smart_calc_64, test_64) {
  Model M("-0.98 mod x  =", "00012");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_65, test_65) {
  Model M("-x  =", "-1.2");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 1.2, 0.0000001);
}

TEST(test_s21_smart_calc_66, test_66) {
  Model M("-12+a.012*1  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_67, test_67) {
  Model M("-12+0.12*x  =", "1.2e7");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 1439988, 0.0000001);
}

TEST(test_s21_smart_calc_68, test_68) {
  Model M("-12+0.12*x  =", "1.2e-7");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), -11.9999999, 0.0000001);
}

TEST(test_s21_smart_calc_69, test_69) {
  Model M("-12+0.12*x  =", "1e.2e7");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_70, test_70) {
  Model M("-12+0.12*x  =", ".1");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_71, test_71) {
  Model M("-12+0.12*1e10  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 1199999988, 0.0000001);
}

TEST(test_s21_smart_calc_72, test_72) {
  Model M("1e3.3+1  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, ERROR);
  ASSERT_EQ(M.get_data().has_value(), 0);
}

TEST(test_s21_smart_calc_73, test_73) {
  Model M("12+1e-3  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 12.001, 0.0000001);
}

TEST(test_s21_smart_calc_74, test_74) {
  Model M("12+1e+3  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 1012, 0.0000001);
}

TEST(test_s21_smart_calc_75, test_75) {
  Model M("12+1.2e+3  =", "0");
  int flag = M.s21_calculate();
  ASSERT_EQ(flag, OK);
  ASSERT_NEAR(M.get_data().value(), 1212, 0.0000001);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
