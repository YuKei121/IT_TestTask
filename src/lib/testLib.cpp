#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

namespace testLib {

void func1_numeralSort(std::string& str) {
  std::string str2;
  // перебираем всю строку, вычищая из неё все символы - на всякий случай
  for (char& c : str) {
    if (std::isdigit(c)) {
      str2 += c;
    }
  }

  std::sort(str2.begin(), str2.end());

  str.clear();
  for (char& c : str2) {
    if ((c - '0') % 2 == 0) {
      str += "KB";
    } else {
      str += c;
    }
  }
}

int func2_sumAllNumerals(const std::string& str) {
  int sum = 0;
  for (const char& c : str) {
    if (std::isdigit(c)) {
      sum += c - '0';
    }
  }
  return sum;
}

bool func3_isMultipleOf32(const int number) {
  return number > 2 && number % 32 == 0;
}

}  // namespace testLib