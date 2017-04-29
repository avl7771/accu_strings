#include <iostream>
#include <regex>
#include <string>

bool CheckPools(const std::string& input) {
  std::regex regex("(.*(swimming )?pool(s)?.*)|(.*bathing.*)",
                   std::regex::icase);

  std::smatch matches;
  return std::regex_match(input, matches, regex);
}

int main() {
  std::string description;
  for (std::string input_line; std::getline(std::cin, input_line);) {
    description.append(input_line);
  }
  if (CheckPools(description)) {
    std::cout << "It has a pool!" << std::endl;
  } else {
    std::cout << "There is no pool :(" << std::endl;
  }
}
