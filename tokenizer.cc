#include <iostream>
#include <string>

const std::string kTokenOr = "OR";
const std::string kTokenAnd = "AND";
const std::string kTokenParenOpen = "(";
const std::string kTokenParenClose = ")";
const std::string kWhitespace = "\t\n\r ";
const std::string kTokenSeparators = "\t\n\r ()";

void WriteToken(const std::string& token) {
  std::cout << token << std::endl;
}

size_t EatToken(const std::string& text) {
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

  std::string token = text.substr(0, token_size);

  if (token == kTokenOr) {
    WriteToken(kTokenOr);
  } else if (token == kTokenAnd) {
    WriteToken(kTokenAnd);
  } else {
    WriteToken(token);
  }

  return token_size;
}

void Tokenize(const std::string& line) {
  for (auto current = line.begin(); current != line.end();) {
    current = current + EatToken(std::string(current, line.end()));
  }
}

int main() {
  // Version with std::string
  std::string input_line;
  while (std::getline(std::cin, input_line)) {
    Tokenize(input_line);
  }
}
