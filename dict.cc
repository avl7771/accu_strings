#include <iostream>
#include <map>
#include <string>

#include "time_counter.h"

struct Dictionary {
  bool Add(const std::string& key, const int value) {
    auto result = data_.emplace(key, value);
    return result.second;
  }

  int GetValue(const std::string& key) const {
    auto found = data_.find(key);
    if (found == data_.end())
      return 0;
    return found->second;
  }

  std::map<std::string, int> data_;
};

int main() {
  Dictionary dict;
  for (int i = 1; i < 1000; ++i) {
    std::string key = "QuiteRandomString" + std::to_string(i);
    dict.Add(key, i);
  }

  TimeCounter counter;

  int sum = 0;
  for (unsigned i = 0; i < 100000; ++i) {
    sum += dict.GetValue("QuiteRandomString9");
  }

  std::cout << counter.Elapsed().count()
            << " ms" << std::endl;
}
