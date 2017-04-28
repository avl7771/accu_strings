#include <iostream>
#include <string>
#include <experimental/string_view>

using std::experimental::string_view;

constexpr string_view operator"" _sv(const char *str, size_t len) noexcept {
  return string_view(str, len);
}

constexpr string_view kGood = "good"_sv;
constexpr string_view kBad = "bad"_sv;

constexpr unsigned Hash(string_view string, unsigned hash = 5381) {
  if (string.empty())
    return hash;
  return Hash(string.substr(1), hash * 33 + string.front());
}

int ToValue(string_view string) {
  switch (Hash(string)) {
    case Hash(kGood):
      return 1337;
    case Hash(kBad):
      return 666;
  }

  return 0;
}

int main() {
  for (std::string input_line; std::getline(std::cin, input_line);) {
    std::cout << ToValue(input_line) << std::endl;
  }
}
