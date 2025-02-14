#pragma once
#ifndef LIB_HPP
#define LIB_HPP

#include <string>

namespace testLib {

void func1_numeralSort(std::string& str);
int func2_sumAllNumerals(const std::string& str);
bool func3_isMultipleOf32(const int number);

}  // namespace testLib

#endif