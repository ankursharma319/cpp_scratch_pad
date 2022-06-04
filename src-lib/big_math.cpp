#include "big_math.hpp"
#include <cstdint>
#include <vector>

namespace {

template<typename base_type = std::uint8_t>
class big_integer {
public:
    big_integer(): number_() {}
    big_integer(std::string const& num): big_integer() {
        (void) num;
    }
private:
    std::vector<base_type> number_;
};

}

namespace big_math {

std::string add_integers(std::string const&, std::string const&) {
    return "";
}

}
