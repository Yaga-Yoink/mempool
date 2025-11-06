#include "mempool.hpp"
#include <cstdio>
#include <chrono>

void compare_perf() {
  constexpr int N = 1048576;
  constexpr uint32_t BLOCK_SIZE = 4; 
  MEMPOOL<N, BLOCK_SIZE> pool{};

  auto start_pool = std::chrono::system_clock::now();
  for (int i = 0; i < N; i++) {
    pool.falloc();
  }
  auto end_pool = std::chrono::system_clock::now();

  auto start_malloc = std::chrono::system_clock::now(); 
  for (int i = 0; i < N; i++) {
    malloc(BLOCK_SIZE);
  }
  auto end_malloc = std::chrono::system_clock::now(); 
  std::cout << "Mempool took " << end_pool - start_pool << '\n';
  std::cout << "Malloc took " << end_malloc - start_malloc << '\n';
}

int main() {
  compare_perf();
  // MEMPOOL<4, 4> pool{};
  // void* block1 = pool.falloc();
  // void* block2 = pool.falloc();
  // void* block3 = pool.falloc();
  // pool.ffree(block1);
  // pool.ffree(block3);
  // void* block3_again = pool.falloc();
  // void* block1_again = pool.falloc();
  // // try {
  // //   pool.falloc();
  // //   pool.falloc();
  // //   std::cout << "here" << '\n';
  // // }
  // // catch (std::bad_alloc e) {
  // //   printf("Alloc failed \n");
  // // }


  
  // printf("block1: %p\n", block1);
  // printf("block2: %p\n", block2);
  // printf("block3: %p\n", block3);
  // printf("block3_again: %p\n", block3_again);
  // printf("block1_again: %p\n", block1_again);
}