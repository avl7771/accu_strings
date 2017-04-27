#ifndef TIME_COUNTER_H
#define TIME_COUNTER_H

#include <chrono>

class TimeCounter {
 public:
   TimeCounter() : start_(std::chrono::steady_clock::now()) {}

   std::chrono::milliseconds Elapsed() {
     auto current = std::chrono::steady_clock::now();
     return std::chrono::duration_cast<std::chrono::milliseconds>(current -
                                                                  start_);
   }

 private:
   std::chrono::steady_clock::time_point start_;
 };

#endif  // TIME_COUNTER_H
