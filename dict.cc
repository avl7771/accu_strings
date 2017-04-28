#include <iostream>
#include <map>
#include <string>

#include "time_counter.h"

template<typename K, typename V>
struct Dictionary {
  bool Add(const K& key, const V& value) {
    auto result = data_.emplace(key, value);
    return result.second;
  }

  V GetValue(const K& key) const {
    auto found = data_.find(key);
    if (found == data_.end())
      return 0;
    return found->second;
  }

  std::map<K, V> data_;
};

int main() {
  Dictionary<std::string, int> dict;
  for (int i = 1; i < 200; ++i) {
    std::string key = "QuiteRandomString" + std::to_string(i);
    dict.Add(key, i);
  }

  TimeCounter counter;

  int sum = 0;
  for (unsigned i = 0; i < 1000000; ++i) {
    sum += dict.GetValue("QuiteRandomString9");
  }

  std::cout << counter.Elapsed().count()
            << " ms" << std::endl;
}
