#include "mempool.hpp"
#include <cstdio>

int main() {
  MEMPOOL<4, 4> pool{};
  void* block1 = pool.falloc();
  void* block2 = pool.falloc();
  void* block3 = pool.falloc();
  pool.ffree(block1);
  pool.ffree(block3);
  void* block3_again = pool.falloc();
  void* block1_again = pool.falloc();


  
  printf("block1: %p\n", block1);
  printf("block2: %p\n", block2);
  printf("block3: %p\n", block3);
  printf("block3_again: %p\n", block3_again);
  printf("block1_again: %p\n", block1_again);
}