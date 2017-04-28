#include <iostream>
#include <regex>
#include <string>

void CheckPools(const std::string& input) {
  std::regex regex("(.*(swimming )?(pool(s)?).*)|(.*(bathing).*)",
                   std::regex::icase);

  std::smatch matches;
  if (std::regex_match(input, matches, regex)) {
    std::cout << "It has a pool!" << std::endl;
  }
}

int main() {
  std::string description;
  for (std::string input_line; std::getline(std::cin, input_line);) {
    description.append(input_line);
  }
  CheckPools(description);
}
