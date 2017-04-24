#include <iostream>
#include <string>
#include <experimental/string_view>

using std::experimental::string_view;

const string_view kTokenOr = "OR";
const string_view kTokenAnd = "AND";
const string_view kTokenParenOpen = "(";
const string_view kTokenParenClose = ")";
const string_view kWhitespace = "\t\n\r ";
const string_view kTokenSeparators = "\t\n\r ()";

void WriteToken(string_view token) {
  std::cout << token << std::endl;
}

size_t EatToken(string_view text) {
  // Skip whitespace
  size_t next_token = text.find_first_not_of(kWhitespace);
  if (next_token == std::string::npos)
    return text.length();
  if (next_token > 0)
    return next_token;

  // Check for separator tokens
  if (text.substr(0, kTokenParenOpen.length()) == kTokenParenOpen) {
    WriteToken(kTokenParenOpen);
    return 1;
  }
  if (text.substr(0, kTokenParenClose.length()) == kTokenParenClose) {
    WriteToken(kTokenParenClose);
    return 1;
  }

  size_t token_size = text.find_first_of(kTokenSeparators);
  if (token_size == std::string::npos)
    token_size = text.length();

  string_view token = text.substr(0, token_size);

  if (token == kTokenOr) {
    WriteToken(kTokenOr);
  } else if (token == kTokenAnd) {
    WriteToken(kTokenAnd);
  } else {
    WriteToken(token);
  }

  return token_size;
}

void Tokenize(string_view line) {
  for (string_view current = line; current.length() > 0;) {
    current = current.substr(EatToken(current));
  }
}

int main() {
  // Version with std::string
  std::string input_line;
  while (std::getline(std::cin, input_line)) {
    Tokenize(input_line);
  }
}
