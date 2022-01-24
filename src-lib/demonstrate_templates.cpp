#include "demonstrations.hpp"
#include "MyComplex.hpp"
#include "my_span.hpp"
#include <iostream>
#include <type_traits>

template <typename T>
constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

template<typename T, std::size_t SIZE>
T& MyArray<T, SIZE>::operator[](std::size_t idx) {
    return arr_[idx];
}

template<typename T, std::size_t SIZE>
const T& MyArray<T, SIZE>::operator[](std::size_t idx) const {
    return arr_[idx];
}

template<typename T, std::size_t SIZE>
constexpr size_t MyArray<T, SIZE>::size() const {
    return SIZE;
}

template<typename T, std::size_t SIZE>
T* MyArray<T, SIZE>::data() {
    return std::addressof(arr_[0]);
}

template<typename T, std::size_t SIZE>
T* MyArray<T, SIZE>::begin() {
    return data();
}

template<typename T, std::size_t SIZE>
T* MyArray<T, SIZE>::end() {
    return data() + size();
}

template<typename T, std::size_t SIZE>
template<typename U>
void MyArray<T, SIZE>::addToEachElement(const U& u) {
    for (auto it = begin(); it != end(); it++) {
        *it += u;
    }
}

namespace {

template <size_t N>
constexpr auto my_size(char (&)[N]) {
    return N;
}

template<typename T>
T my_min(const T& x, const T& y) {
    std::cout << "Normal Template function min" << std::endl;
    if (x > y) {
        return y;
    }
    return x;
}

template<>
double my_min(const double& x, const double& y) {
    std::cout << "Template specialization function for double min" << std::endl;
    if (x > y) {
        return y;
    }
    return x;
}

template<>
std::string my_min(const std::string& x, const std::string& y) {
    std::cout << "Template specialization function for std::string min" << std::endl;
    if (x.size() > y.size()) {
        return y;
    }
    return x;
}

Complex my_min(Complex& x, Complex& y) {
    std::cout << "my_min overload for complex numbers called" << std::endl;
    if (x > y) {
        return y;
    }
    return x;
}

template<typename T>
bool my_equals(const T& x, const T& y, std::true_type) {
    return std::abs(x - y) < 0.01f;
}

template<typename T>
bool my_equals(const T& x, const T& y, std::false_type) {
    return x == y;
}

template<typename T>
bool my_equals(const T& x, const T& y) {
    return my_equals(
        x, y,
        typename std::conditional<
            std::is_floating_point<T>::value,
            std::true_type,
            std::false_type
        >::type {}
    );
    // for exlpanation of typename here like this
    // https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords
}

template<typename T>
std::enable_if_t<std::is_floating_point<T>::value, bool> my_not_equals(const T& x, const T& y) {
    return std::abs(x - y) > 0.01f;
}

template<typename T>
std::enable_if_t<!std::is_floating_point<T>::value, bool> my_not_equals(const T& x, const T& y) {
    return x != y;
}

void intFoo(int const& x) {
    std::cout << "came in intFoo LValueRef with val = " << x << std::endl;
}

void intFoo(int&& x) {
    std::cout << "came in intFoo RValueRef with val = " << x << std::endl;
}

template <typename T>
void my_single_forwarding_foo(T&& t) {
    std::cout << "my_single_forwarding_foo came in the function, type T&& = " << type_name<decltype(t)>() << std::endl;
    std::cout << "my_single_forwarding_foo, type std::forward<T>(t) = " << type_name<decltype(std::forward<T>(t))>() << std::endl;
    std::cout << "passing value with simple value" << std::endl;
    intFoo(t);
    std::cout << "passing value with static_cast<T&&>" << std::endl;
    intFoo(static_cast<T&&>(t));
    std::cout << "passing value with std::forward<T>(t)" << std::endl;
    intFoo(std::forward<T>(t));
    std::cout << "passing value with std::move" << std::endl;
    intFoo(std::move(t));
    return;
}

template <typename T>
void my_second_forwarding_foo(T t) {
    std::cout << "my_second_forwarding_foo came in the function, type T = " << type_name<decltype(t)>() << std::endl;
    std::cout << "my_second_forwarding_foo, type std::forward<T>(t) = " << type_name<decltype(std::forward<T>(t))>() << std::endl;
    std::cout << "passing value with simple value" << std::endl;
    intFoo(t);
    std::cout << "passing value with static_cast<T&&>" << std::endl;
    intFoo(static_cast<T&&>(t));
    std::cout << "passing value with std::forward<T>(t)" << std::endl;
    intFoo(std::forward<T>(t));
    std::cout << "passing value with std::move" << std::endl;
    intFoo(std::move(t));
    return;
}

template <typename T>
void my_foo(T& t) {
    std::cout << "my_foo Came in the ref function = " << type_name<decltype(t)>() << std::endl;
    return;
}

template <typename T>
void my_foo(T&& t) {
    std::cout << "my_foo Came in the rvalue function = " << type_name<decltype(t)>() << std::endl;
    return;
}

template <typename T>
void my_rvalue_foo(T&& t) {
    std::cout << "my_rvalue_foo Came in the only rvalue function = " << type_name<decltype(t)>() << std::endl;
    return;
}

template <typename T>
void my_pointer_foo(T* t) {
    std::cout << "my_pointer_foo Came in the only function = " << type_name<decltype(t)>() << std::endl;
    return;
}

template <typename T>
void my_const_foo(T const& t) {
    std::cout << "my_const_foo Came in the const ref function = " << type_name<decltype(t)>() << std::endl;
    return;
}

template <typename T>
void my_const_foo(T const&& t) {
    std::cout << "my_const_foo Came in the const rvalue function = " << type_name<decltype(t)>() << std::endl;
    return;
}

template <typename T>
void my_const_foo(T * const t) {
    std::cout << "my_const_foo Came in the const pointer to variable value function = " << type_name<decltype(t)>() << std::endl;
    return;
}


/*template <typename T>
void my_const_foo(T const * t) {
    std::cout << "my_const_foo Came in the variable pointer to const value function = " << type_name<decltype(t)>() << std::endl;
    return;
}*/

// This one is a compile error because this conflicts with T const *
// The first const from the right is discarded
template <typename T>
void my_const_foo(T const * const t) {
    std::cout << "my_const_foo Came in the const pointer to const value function = " << type_name<decltype(t)>() << std::endl;
    return;
}

template <typename T>
struct my_templated_foo {
    using current_type = T;
    void foo(T t) {
        std::cout << "my_templated_foo::foo with T = " << type_name<decltype(t)>() << std::endl;
    }

    void fooRef(T& t) {
        std::cout << "my_templated_foo::fooRef with T& = " << type_name<decltype(t)>() << std::endl;
    }
};

template <typename T>
struct my_const_templated_foo {
    using current_type = T;
    void foo(const T t) {
        std::cout << "my_templated_foo::foo with const T = " << type_name<decltype(t)>() << std::endl;
    }

    void fooRef(const T& t) {
        std::cout << "my_templated_foo::fooRef with const T& = " << type_name<decltype(t)>() << std::endl;
    }
};

template <typename T>
void single_template_func(T lol) {
    (void) lol;
    return;
}

void demonstrate_templates_type_deduction() {
    std::cout << "demonstrating templates type deduction" << std::endl;
    int vi = 10;
    int const ci = 20;
    int* vip = &vi;
    int const * cip = &ci;
    int const * const cicp = &ci;
    my_foo(&vi);
    my_foo(&ci);
    my_foo(101);
    my_foo(vip);
    my_foo(cip);
    my_foo(cicp);
    my_rvalue_foo(&vi);
    my_rvalue_foo(&ci);
    my_rvalue_foo(101);
    my_rvalue_foo(vip);
    my_rvalue_foo(cip);
    my_rvalue_foo(cicp);
    my_pointer_foo(&vi);
    my_pointer_foo(&ci);
    //my_pointer_foo(101); // Doesnt compile and rightly so
    my_pointer_foo(vip);
    my_pointer_foo(cip);
    my_pointer_foo(cicp);
    my_const_foo(&vi);
    my_const_foo(&ci);
    my_const_foo(101);
    my_const_foo(vip);
    my_const_foo(cip);
    my_const_foo(cicp);

    std::cout << "Trying int as template to class -- " << type_name<decltype(my_templated_foo<int>())>() << std::endl;
    my_templated_foo<int>().foo(vi);
    my_templated_foo<int>().fooRef(vi);
    my_templated_foo<int>().foo(ci);
    //my_templated_foo<int>().fooRef(ci);

    std::cout << "Trying const int as template to class -- " << type_name<decltype(my_templated_foo<const int>())>() << std::endl;
    my_templated_foo<const int>().foo(vi);
    my_templated_foo<const int>().fooRef(vi);
    my_templated_foo<const int>().foo(ci);
    my_templated_foo<const int>().fooRef(ci);

    std::cout << "Trying int& as template to class -- " << type_name<decltype(my_templated_foo<int&>())>() << std::endl;
    my_templated_foo<int&>().foo(vi);
    my_templated_foo<int&>().fooRef(vi);
    //my_templated_foo<int&>().foo(ci);
    //my_templated_foo<int&>().fooRef(ci);

    std::cout << "Trying const int& as template to class -- " << type_name<decltype(my_templated_foo<const int&>())>() << std::endl;
    my_templated_foo<const int&>().foo(vi);
    my_templated_foo<const int&>().fooRef(vi);
    my_templated_foo<const int&>().foo(ci);
    my_templated_foo<const int&>().fooRef(ci);

    std::cout << "Trying int as template to class -- " << type_name<decltype(my_const_templated_foo<int>())>() << std::endl;
    my_const_templated_foo<int>().foo(vi);
    my_const_templated_foo<int>().fooRef(vi);
    my_const_templated_foo<int>().foo(ci);
    my_const_templated_foo<int>().fooRef(ci);

    std::cout << "Trying const int as template to class -- " << type_name<decltype(my_const_templated_foo<const int>())>() << std::endl;
    my_const_templated_foo<const int>().foo(vi);
    my_const_templated_foo<const int>().fooRef(vi);
    my_const_templated_foo<const int>().foo(ci);
    my_const_templated_foo<const int>().fooRef(ci);

    std::cout << "Trying int& as template to class -- " << type_name<decltype(my_const_templated_foo<int&>())>() << std::endl;
    // STRANGE BEHAVIOUR - const gets dropped in the foo and fooRef - due to https://stackoverflow.com/questions/27727637/why-does-the-const-in-a-const-t-parameter-disappear-when-t-is-a-reference-type
    my_const_templated_foo<int&>().foo(vi);
    my_const_templated_foo<int&>().fooRef(vi);
    //my_const_templated_foo<int&>().foo(ci);
    //my_const_templated_foo<int&>().fooRef(ci);

    std::cout << "Trying const int& as template to class -- " << type_name<decltype(my_const_templated_foo<const int&>())>() << std::endl;
    my_const_templated_foo<const int&>().foo(vi);
    my_const_templated_foo<const int&>().fooRef(vi);
    my_const_templated_foo<const int&>().foo(ci);
    my_const_templated_foo<const int&>().fooRef(ci);

    single_template_func<int>(vi);
    single_template_func<int&>(vi);
    single_template_func<int&&>(std::move(vi));
    single_template_func<int&&>(8);
    single_template_func<const int&>(8);
    //single_template_func<int&>(8); - fails to cpmile

    int& rvi = vi;
    std::cout << "Trying my_single_forwarding_foo" << std::endl;
    my_single_forwarding_foo(vi);
    my_single_forwarding_foo(ci);                   //only wants to go to lvalue ref func because it accepts const
    my_single_forwarding_foo(101);
    my_single_forwarding_foo(std::move(ci));        //only wants to go to lvalue ref func because it accepts const
    my_single_forwarding_foo(rvi);

    std::cout << "Trying my_second_forwarding_foo" << std::endl;
    my_second_forwarding_foo(vi);
    my_second_forwarding_foo(ci);                   //only wants to go to lvalue ref func because it accepts const
    my_second_forwarding_foo(101);
    my_second_forwarding_foo(std::move(ci));        //only wants to go to lvalue ref func because it accepts const
    my_second_forwarding_foo(rvi);

    static_assert(
        std::is_same<
            my_templated_foo<int>::current_type,
            int
        >::value,
        "Something wriong"
    );
    static_assert(
        std::is_same<
            my_templated_foo<int*>::current_type,
            int*
        >::value,
        "Something wriong"
    );
}

void demonstrate_func_templates() {
    std::cout << "demonstrating function templates" << std::endl;
    char buffer[16]{};
    std::cout << "Size of buffer is = " << my_size(buffer) << std::endl;

    // rvalues do bind to const ref
    //This one goes to the normal template func
    int minInt = my_min(4, -10);
    std::cout << "Min between two ints 4, -10 is " <<  minInt << std::endl;

    std::string x("hi");
    std::string y("hey");
    std::string minString { my_min(x, y) };
    //This one goes to the template specialization func
    std::cout << "Min between two strings " << x << ", " << y << " is " <<  minString << std::endl;

    double dx{0.567}, dy{10.56};
    double minDouble {my_min(dx, dy)};
    //This one goes to the template specialization func
    std::cout << "Min between two doubles " << dx << ", " << dy << " is " <<  minDouble << std::endl;

    Complex c1{4, 2};
    Complex c2{-1, 5};
    Complex minC {my_min(c1, c2)};
    //This one goes to the overloaded func
    std::cout << "Min between two complexes " << c1 << ", " << c2 << " is " <<  minC << std::endl;

    //This one goes to the normal template
    // because rvalue dont bind to non const ref
    Complex minC2 {my_min(Complex{0, 0}, Complex{1, 2})};
    std::cout << "Min between two rvalue complexes (0, 0) and (1, 2) is " <<  minC2 << std::endl;

    //This one goes to the template specialization func
    std::cout << "0.567f my_equals 0.5670009f is " << my_equals(0.576f, 0.5670009f) << std::endl;

    //This one goes to the main template func
    std::cout << "23 my_equals 24 is " << my_equals(23, 24) << std::endl;
    std::cout << "0.567f my_not_equals 0.5670009f is " << my_not_equals(0.576f, 0.5670009f) << std::endl;
}

template <size_t N>
using MyCharArray = MyArray<char, N>;

void demonstrate_class_templates() {
    std::cout << "demonstrating class templates" << std::endl;
    MyArray<int, 5> primes {2, 3, 5, 7, 11};
    std::cout << "Created array with " << primes.size() << " primes" << std::endl;
    std::cout << "Element at begin = " << *primes.begin() << std::endl;
    std::cout << "Address at begin = " << primes.begin() << std::endl;
    std::cout << "Address at end = " << primes.end() << std::endl;
    std::cout << "Element at 2th index = " << primes[2] << std::endl;

    //Create array of 0 ints - gives error because cannot declar int arr_[0] 
    //MyArray<int, 0> zeroLenArray {};
    //std::cout << "Created array with " << zeroLenArray.size() << " ints" << std::endl;

    MyArray<float, 3> floats {1.5, 4.0f, 5.5f};
    std::cout << "Created array with " << floats.size() << " floats" << std::endl;
    std::cout << "Element at 2th index = " << floats[2] << std::endl;
    floats.addToEachElement(5);
    std::cout << "Element at 2th index after addToEachElement(5) = " << floats[2] << std::endl;

    MyCharArray<4> my_chars {"hey"};
    std::cout << "Created array with " << my_chars.size() << " chars" << std::endl;
}

void demonstrate_my_span() {
    std::cout << "Demonstrating my_span" << std::endl;
    int arr[3] = {23, 4, 6};
    int * ptr = new int[3];
    ptr[0] = 90;
    ptr[1] = 2;
    ptr[2] = 5;
    std::array<int, 2> stdarr {{3, 4}};
    my_span<int> a(arr);
    my_span<int> b(ptr, 3);
    my_span<int> c(stdarr);
    my_span<int> d;

    std::cout << "Looping through my_span created from int array" << std::endl;
    for (const auto& val: a) {
        std::cout << "val = " << val << std::endl;
    }
    std::cout << "Looping through my_span created from int ptr" << std::endl;
    for (const auto& val: b) {
        std::cout << "val = " << val << std::endl;
    }
    std::cout << "Looping through my_span created from std array" << std::endl;
    for (const auto& val: c) {
        std::cout << "val = " << val << std::endl;
    }
    std::cout << "Looping through empty my_span" << std::endl;
    for (const auto& val: d) {
        std::cout << "val = " << val << std::endl;
    }
    delete[] ptr;
}

template<typename T>
constexpr auto my_variadic_sum(T t) {
    return t;
}

template<typename T, typename... Ts>
constexpr auto my_variadic_sum(T t, Ts... ts) {
    return t + my_variadic_sum(ts...);
}

template<typename T, typename... Ts>
constexpr auto my_variadic_sum_alternate(T t, Ts... ts) {
    if constexpr (sizeof...(ts) == 0) {
        return t;
    } else {
        return t + my_variadic_sum_alternate(ts...);
    }
}

// forward declare primary template
template<int...>
struct static_add;

// no args specialization
template<>
struct static_add<>
{
  static constexpr int value = 0;
};

// the real template
template<int i, int... tail>
struct static_add<i, tail...>
{
  static constexpr int value = i + static_add<tail...>::value;
};

void demonstrate_variadic_templates() {
    std::cout << "Demonstrating veriadic templates" << std::endl;

    // Write a function template that accepts any number
    // of parameters and returns the sum of the values.
    std::cout << "Sum is = " << my_variadic_sum(3, 5, 7) << std::endl;
    std::cout << "Sum is = " << my_variadic_sum_alternate(3, 5.5) << std::endl;
    [[maybe_unused]]
    int x = 42;
    static_assert(26 == my_variadic_sum(7, 9, 10), "expect 26");
    // static_assert(84 == my_variadic_sum(x, x), "expect 84"); - doesnt compile

    // Calculate the sum of values guaranteed 
    // at compile time using variadic templates.
    static_assert(9 == static_add<2, 3, 4>::value, "Expect 9");
    //static_assert(12.0f == static_add<4.0f, 3.5, 4.5>::value, "Expect 12.0f");
}

}

void demonstrate_templates() {
    (void) demonstrate_func_templates;
    //demonstrate_func_templates();
    (void) demonstrate_class_templates;
    //demonstrate_class_templates();
    (void) demonstrate_templates_type_deduction;
    //demonstrate_templates_type_deduction();
    (void) demonstrate_my_span;
    //demonstrate_my_span();
    (void) demonstrate_variadic_templates;
    demonstrate_variadic_templates();
}
