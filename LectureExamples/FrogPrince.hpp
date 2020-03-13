#ifndef FROGPRINCE_HPP
#define FROGPRINCE_HPP

#include <iostream>
#include <string>

namespace Fantasy {

  class Princess;

  class FrogPrince {
    friend std::ostream& operator<<(std::ostream& os,
                                    const FrogPrince& frogprince);

  public:
    FrogPrince(const std::string& name);
    void setSpouse(Princess* theSpouse);
    const std::string& getName()
        const;  // second const is part of the prototype!

  private:
    std::string name;
    Princess* spouse;
  };

}  // namespace Fantasy

#endif
