#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "time_counter.h"

class StringHash {
 public:
  bool Exists(const std::string& item_hash) {
    return hashes_.find(item_hash) != std::string::npos;
  }

  void Add(const std::string& item_hash) {
    hashes_ = hashes_ + item_hash;
  }

 private:
  std::string hashes_;
};

std::string SomeItemHash(unsigned item) {
  std::stringstream stream;
  stream << std::setfill('0') << std::setw(32) << std::hex << item;
  return stream.str();
}

int main() {
  StringHash hash_store;
  for (unsigned i = 0; i < 100000; ++i)
    hash_store.Add(SomeItemHash(i));

  std::vector<std::string> incoming_hashes;
  for (unsigned i = 0; i < 30; ++i)
    incoming_hashes.push_back(SomeItemHash(i + 1232134));

  TimeCounter counter;
  for (const auto &incoming_hash : incoming_hashes) {
    if (!hash_store.Exists(incoming_hash))
      hash_store.Add(incoming_hash);
  }
  std::cout << counter.Elapsed().count()
            << " ms" << std::endl;
}
