#include <iostream>
#include <string_view>

constexpr std::string_view kConstantString = "This is a constant string";

int main() {
  std::cout << kConstantString << std::endl;
}
