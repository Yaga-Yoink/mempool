#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <cstdlib>
#include <exception>
#include <cstdio>
#include <cstring>
#include <iostream>

// mem pool specification from http://www.thinkmind.org/download.php?articleid=computation_tools_2012_1_10_80006

// N := number of BLOCK_SIZE byte blocks
// requires BLOCK_SIZE is a power of 2
template <std::size_t N, uint16_t BLOCK_SIZE = 4>
class MEMPOOL {
  public:
    constexpr MEMPOOL() : head{0}, num_free_block{N}, num_initialized{0} {}; 
    ~MEMPOOL() = default;
    /**
     * fujii allocate returns a pointer to a block of 'BLOCK_SIZE' contiguous memory 
     * Throws: bad_alloc if 'byte_count' requested exceeds the number of bytes available
     */
    void* falloc() {
      if (num_free_block == 0) {
        throw std::bad_alloc();
      }
      // allocating a new block
      if (head == N - num_free_block) {
        head++;
        num_free_block--;
        num_initialized++;
        return pool + ((head-1) << (BLOCK_SIZE >> 1));
      }
      uint32_t idx = (head << (BLOCK_SIZE >> 1));
      std::memcpy(&head, &pool[idx], sizeof(decltype(head)));
      num_free_block--;
      num_initialized++;
      return static_cast<void*>(pool + idx);
    }

    /**
     * fujii frees the allocation at 'address'
     */
    void ffree(void* ptr) {
      uint32_t idx = (static_cast<char*>(ptr) - pool);
      uint32_t curr = idx >> (BLOCK_SIZE >> 1);
      std::memcpy(&pool[idx], &head, sizeof(decltype(head)));
      head = curr;
      num_free_block++;
    }


  private:
    char pool[N << (BLOCK_SIZE >> 1)];
    uint32_t head;
    uint32_t num_free_block;
    uint32_t num_initialized;
};

#endif

/**
 * 2^64 num of addresses each for 1 byte
 * 64 bit addresses
 * 32 bit blocks
 * 2
 * 
 * with 4 byte head pointer, maximum pool size is 2^32 bytes
 */

 /**
  * interesting features for this
  *   option to request a new cache line
  *   multiple memory pools, possibly a cache line each?
  *   resizing / adding new portions of memory to the pool
  *   requesting multiple blocks at the same time
  */