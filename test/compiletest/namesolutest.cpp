#include <iostream>
#include <array>

class Solu{
public:
  Solu() = default;
  template<typename... Exts>
  Solu(Exts... exts){
    std::array<size_t,sizeof...(Exts)> ar {size_t(exts)...};
    auto it = ar.begin();
    for(;it != ar.end() ; it++){
      std::cout << *it << std::endl;
    }
  };
};

decltype(auto) main() -> int{
  Solu(1,2,3);
  return 0;
}
