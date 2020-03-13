#ifndef PRINCESS_HPP
#define PRINCESS_HPP

#include <iostream>
#include <string>

namespace Fantasy {

  class FrogPrince;

  class Princess {
    friend std::ostream& operator<<(std::ostream& os, const Princess& princess);

  public:
    Princess(const std::string& name);
    void marries(FrogPrince& betrothed);

  private:
    std::string name;
    FrogPrince* spouse;
  };

}  // namespace Fantasy

#endif
