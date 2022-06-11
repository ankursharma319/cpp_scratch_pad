#include "big_math.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <cmath>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>
#include <cassert>

namespace {

std::uint8_t hex_char_to_value(char c) {
    //std::cout << "hex_char_to_value:: c = " << c << std::endl;
    assert((c >= '0' && c <= '9') 
        || (c >= 'A' && c <= 'F') 
        || (c >= 'a' && c <= 'f'));
    if (c >= '0' && c <= '9') {
        return c-'0';
    } else if (c >= 'A' && c <= 'F') {
        return c-'A' + 10;
    } else {
        return c-'a' + 10;
    }
}

char value_to_hex_char(std::uint8_t val) {
    assert(val < 16);
    if (val < 10) {
        return '0' + val;
    }
    return 'A' + val - 10;
}

void remove_leading_char(std::string &str, const char charToRemove) {
    str.erase(0, std::min(str.find_first_not_of(charToRemove), str.size() - 1));
}

template<typename base_type>
std::string vec_to_string(std::vector<base_type> const& vec) {
    std::string res = "";
    for (auto elem: vec) {
        res += std::to_string(elem) + ", ";
    }
    return res;
}

template<typename base_type>
void trim_leading_zeros(std::vector<base_type>& x) {
    for (std::size_t i = x.size(); i > 0; i--) {
        if (x.at(i-1) == 0) {
            continue;
        }
        x.erase(x.begin()+i, x.end());
        return;
    }
}

template<typename base_type>
bool is_zero(std::vector<base_type>& x) {
    for (std::size_t i = x.size(); i > 0; i--) {
        if (x.at(i-1) != 0) {
            return false;
        }
    }
    return true;
}

template<typename base_type>
std::vector<base_type> parse_into_vector_from_hex(std::string_view const& sv) {
    static_assert(std::is_integral_v<base_type>, "Need integral base type");
    static_assert(std::is_unsigned_v<base_type>, "Need unsigned integral base type");
    constexpr std::size_t n_hex_digits_per_base_type_value = sizeof(base_type) * 8 / 4;
    static_assert(n_hex_digits_per_base_type_value > 0, "base_type not big enough");

    assert(sv.size() >= 1);
    std::vector<base_type> result {};
    for (std::size_t i=sv.size()-1; i < std::numeric_limits<std::size_t>::max();) {
        base_type current_num = 0;
        for(
            std::size_t j=0;
            j < n_hex_digits_per_base_type_value &&
            i < std::numeric_limits<std::size_t>::max();
            j++, i--
        ) {
            //std::cout << "parse_into_vector_from_hex:: i = " << i << ", j = " << j << std::endl;
            std::uint8_t hex_digit = hex_char_to_value(sv[i]);
            assert(hex_digit < 16);
            current_num += hex_digit * base_type(pow(16, j));
        }
        result.push_back(current_num);
    }
    return result;
}

template<typename base_type>
std::string to_hex_string_from_vector(std::vector<base_type> const& vec) {
    //std::cout << "to_hex_string_from_vector:: vec = ";
    //for (auto elem: vec) {
    //    std::cout << elem << ", ";
    //}
    //std::cout << std::endl;
    static_assert(std::is_integral_v<base_type>, "Need integral base type");
    static_assert(std::is_unsigned_v<base_type>, "Need unsigned integral base type");
    constexpr std::size_t n_hex_digits_per_base_type_value = sizeof(base_type) * 8 / 4;
    static_assert(n_hex_digits_per_base_type_value > 0, "base_type not big enough");
    std::string result = "";
    for(std::size_t i = vec.size() - 1; i < std::numeric_limits<std::size_t>::max(); i--) {
        base_type current_val = vec.at(i);
        std::string current_hex_string = "";
        for (std::size_t j = 0; j < n_hex_digits_per_base_type_value; j++) {
            std::uint8_t hex_digit = current_val % 16;
            current_val = current_val / 16;
            // equivalently could do left shift by 4 and
            // then AND with 16 to get right most 4 digits
            char c = value_to_hex_char(hex_digit);
            current_hex_string = c + current_hex_string;
        }
        result += current_hex_string;
    }
    remove_leading_char(result, '0');
    return result;
}

template<typename base_type = std::uint8_t, std::size_t input_base = 16>
class big_integer {
public:
    big_integer(): number_(), isNegative_(false) {}
    big_integer(std::string const& num): big_integer() {
        static_assert(input_base==16 || input_base==10, "Unsupported input base");
        assert(num.size() >= 1);
        //std::cout << "Creating big_integer out of num " << num << " with base_type::max = " << std::numeric_limits<base_type>::max() << std::endl;
        std::size_t highest_bit_index = 0;
        if (num.at(0) == '-') {
            assert(num.size() >= 2);
            isNegative_ = true;
            highest_bit_index = 1;
        }
        std::string_view sv(num);
        sv.remove_prefix(highest_bit_index);
        assert(input_base == 16);
        number_ = parse_into_vector_from_hex<base_type>(sv);
    }
    big_integer(std::vector<base_type> const& num, bool is_negative)
    : number_(num), isNegative_(is_negative)
    {}

    bool abs_bigger_than_or_equal_to(big_integer const& other) const {
        if (other.number_.size() != number_.size()) {
            return number_.size() > other.number_.size();
        }
        for (std::size_t i = number_.size(); i > 0; i--) {
            if (other.number_.at(i-1) == number_.at(i-1)) {
                continue;
            }
            return number_.at(i-1) > other.number_.at(i-1);
        }
        return true;
    };

    big_integer operator+(big_integer const& other) const {
        std::vector<base_type> res {};
        big_integer const& x1 = abs_bigger_than_or_equal_to(other) ? *this : other;
        big_integer const& x2 = abs_bigger_than_or_equal_to(other) ? other : *this;
        bool do_subtraction = x1.isNegative_ != x2.isNegative_;
        bool final_result_is_negative = (x1.isNegative_ && x2.isNegative_) || x1.isNegative_;
        //std::cout << "adding " << x1.to_string(16) << " and " << x2.to_string(16) << std::endl;
        //std::cout << "i.e. - adding vectors x1 = " << vec_to_string(x1.number_) << " and x2 = " << vec_to_string(x2.number_) << std::endl;
        //std::cout << "do_subtraction = " << do_subtraction << std::endl;
        //std::cout << "final_result_is_negative = " << final_result_is_negative << std::endl;
        base_type overflow = 0;
        for (std::size_t i=0; i<x1.number_.size(); i++) {
            base_type upper_num = x1.number_.at(i);
            base_type lower_num = x2.number_.size() > i ? x2.number_.at(i) : 0; 
            base_type current_num = overflow;
            overflow = 0;
            if (std::numeric_limits<base_type>::max() - current_num < lower_num) {
                overflow = 1;
            }
            current_num += lower_num;
            //std::cout << "current_num after overflow and lower_num is " << current_num << std::endl;

            if (do_subtraction) {
                if (current_num > upper_num) {
                    //std::cout << "doing subtraction - with overflow" << std::endl;
                    overflow = 1;
                    current_num = current_num - upper_num;
                    current_num = std::numeric_limits<base_type>::max() - current_num + 1;
                } else {
                    //std::cout << "doing simple subtraction - no overflow" << std::endl;
                    current_num = upper_num - current_num;
                }
            } else {
                //std::cout << "doing simple addition" << std::endl;
                if (std::numeric_limits<base_type>::max() - current_num < upper_num) {
                    overflow = 1;
                }
                current_num += upper_num;
            }

            //std::cout << "'Pushing back to res, current_num = " << current_num << ", current overlfow = " << overflow << std::endl;
            res.push_back(current_num);
        }
        if (overflow == 1) {
            assert(!do_subtraction);
            res.push_back(1);
        }
        if(is_zero(res)) {
            final_result_is_negative = false;
        } else {
            trim_leading_zeros(res);
        }
        //std::cout << "result vector = " << vec_to_string(res) << std::endl;
        return big_integer(res, final_result_is_negative);
    }

    std::string to_string(std::size_t output_base) const {
        assert(output_base == 16);
        std::string res = to_hex_string_from_vector(number_);
        if (isNegative_) {
            return "-" + res;
        }
        return res;
    }
private:
    std::vector<base_type> number_;
    bool isNegative_;
};

}

namespace big_math {

std::string add_hex_integers(std::string const& s1, std::string const& s2) {
    big_integer<std::uint16_t, 16> x1 (s1);
    big_integer<std::uint16_t, 16> x2 (s2);
    big_integer<std::uint16_t, 16> y = x1 + x2;
    return y.to_string(16);
}

}
