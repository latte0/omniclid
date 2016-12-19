
#include <iostream>
#include <cstddef>
#include "../meta.h"

decltype(auto) main(void) -> int{
  if(Convertible<int, size_t>() ) std::cout << Convertible<int, size_t>() << std::endl;

  return 0;
}
