#include <thread>
#include <iostream>
#include <new>

int main() {
  unsigned int n = std::thread::hardware_concurrency();

  std::cout << n << " concurrent threads supported\n";

  
}