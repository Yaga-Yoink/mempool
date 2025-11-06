#pragma once

#include <cstdlib>
#include <initializer_list>

namespace FUJII {

template <typename T>
class vector {
  public:
    vector();
    vector(const std::initializer_list<T>& args);


    

    void push_back(const T& x);

  private:
    T* data;
    std::size_t size;
    std::size_t capacity;
};
};  // namespace FUJII