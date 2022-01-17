#include "demonstrations.hpp"
#include "MyTypes.hpp"
#include <iostream>
#include <optional>
#include <string_view>
#include <functional>
#include <any>
#include <type_traits>

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

namespace {

/*template <typename T>
void my_foo(T t) {
    std::cout << "my_foo Came in the copy function = " << type_name<decltype(t)>() << std::endl;
    return;
}*/

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


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
void demonstrate_decltype_auto() {
    std::cout << "demonstrating decltype and auto" << std::endl;
    const int n = 10;
    decltype(n) a = 20;             // a is an "const int" [id-expression]
    decltype((n)) b = a;            // b is an "const int &" [(n) is an lvalue]
    decltype((n)) c = 20;           // b is an "const int &" [(n) is an lvalue]
    const int& d = 30;              // const ref compiles
    // int& e = 30;                    // DOESNT COMPILE
    // A temporary cannot be bound to a non-const reference, but it can be bound to const reference.
    // const extends the life time of the temporary object being created.
    // It's scope lasts until d falls out of scope

    // Suppose trying to print type of variable
    std::cout << "typeid(a) = " << typeid(a).name() << std::endl;
    std::cout << "typeid(b) = " << typeid(b).name() << std::endl;
    std::cout << "typeid(c) = " << typeid(c).name() << std::endl;
    std::cout << "typeid(d) = " << typeid(d).name() << std::endl;
    std::cout << "typeid(n) = " << typeid(n).name() << std::endl;
    // Problem with typeid is that it discards the const, referenceness and lvalueness/rvalueness
    // Here is alternative solution using decltype
    std::cout << "type_name(n) = " << type_name<decltype(n)>() << std::endl;
    std::cout << "type_name(a) = " << type_name<decltype(a)>() << std::endl;
    std::cout << "type_name(b) = " << type_name<decltype(b)>() << std::endl;
    std::cout << "type_name(c) = " << type_name<decltype(c)>() << std::endl;
    std::cout << "type_name(d) = " << type_name<decltype(d)>() << std::endl;

    int i = 0;
    const int ci = 0;
    std::cout << "decltype(i) is " << type_name<decltype(i)>() << '\n';
    std::cout << "decltype((i)) is " << type_name<decltype((i))>() << '\n';
    std::cout << "decltype(ci) is " << type_name<decltype(ci)>() << '\n';
    std::cout << "decltype((ci)) is " << type_name<decltype((ci))>() << '\n';
    std::cout << "decltype(static_cast<int&>(i)) is " << type_name<decltype(static_cast<int&>(i))>() << '\n';
    std::cout << "decltype(static_cast<int&&>(i)) is " << type_name<decltype(static_cast<int&&>(i))>() << '\n';
    std::cout << "decltype(static_cast<int>(i)) is " << type_name<decltype(static_cast<int>(i))>() << '\n';
    std::cout << "decltype(10) is " << type_name<decltype(10)>() << '\n';

    // auto is more limited - it doesnt contain constness (usually) or referenceness, just the type
    auto ai = 0;
    std::function<const int& (void)> rets_const_ref = [](void){
        return 10;
    };
    std::function<int& (void)> rets_ref = [&ai](void) -> int& {
        return ai;
    };
    auto a1 = ci;                   // a1 is int
    auto a2 = rets_const_ref();     // a2 is int
    // but when returning references, auto can contain/add const itself
    auto& a3 = rets_const_ref();    // a3 is const ref
    auto a4 = rets_ref();           // a4 is int
    auto& a5 = rets_ref();          // a5 is non-const ref
    auto& a6 = ci;                  // a6 is const ref
    auto& a7 = ai;                  // a7 is non-const ref
    auto a8 = static_cast<int&&>(a7);   // a8 is int
    //auto& a9 = static_cast<int&&>(a7);  // DOESNT COMPILE
    // cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'int'
    auto& a10 = static_cast<const int&&>(a7);  // a10 is const int&
    auto&& a11 = static_cast<const int&&>(a7);  // a11 is const int&&
    auto&& a12 = static_cast<int&&>(a7);  // a12 is int&&
    auto a13 = &a1;  // a13 is int*
    auto a14 = &ci;  // a14 is int const *
    // auto& axx = &a2;  // Fails to compile
    // cannot bind non-const lvalue reference of type 'int*&' to an rvalue of type 'int*'
    auto const& a15 = &a2;  // a15 is int* const&
    int* pa2 = &a2;
    auto& a16 = pa2;  // a15 is (int*)&

    std::cout << "decltype(ai) is " << type_name<decltype(ai)>() << '\n';
    std::cout << "decltype(a1) is " << type_name<decltype(a1)>() << '\n';
    std::cout << "decltype(a2) is " << type_name<decltype(a2)>() << '\n';
    std::cout << "decltype(a3) is " << type_name<decltype(a3)>() << '\n';
    std::cout << "decltype(a4) is " << type_name<decltype(a4)>() << '\n';
    std::cout << "decltype(a5) is " << type_name<decltype(a5)>() << '\n';
    std::cout << "decltype(a6) is " << type_name<decltype(a6)>() << '\n';
    std::cout << "decltype(a7) is " << type_name<decltype(a7)>() << '\n';
    std::cout << "decltype(a8) is " << type_name<decltype(a8)>() << '\n';
    std::cout << "decltype(a10) is " << type_name<decltype(a10)>() << '\n';
    std::cout << "decltype(a11) is " << type_name<decltype(a11)>() << '\n';
    std::cout << "decltype(a12) is " << type_name<decltype(a12)>() << '\n';
    std::cout << "decltype(a13) is " << type_name<decltype(a13)>() << '\n';
    std::cout << "decltype(a14) is " << type_name<decltype(a14)>() << '\n';
    std::cout << "decltype(a15) is " << type_name<decltype(a15)>() << '\n';
    std::cout << "decltype(a16) is " << type_name<decltype(a16)>() << '\n';
}
#pragma GCC diagnostic pop

void demonstrate_std_any() {
    std::cout << "demonstrating std::any(x)" << '\n';
    // Avoid using because we basically give away compile type type checking
    // instead get runtime errors
    // This has nothing todo with templates btw
    std::any x = 1;
    std::cout << "decltype(x) is " << type_name<decltype(x)>() << '\n';
    std::cout << "typeid(x) is " << x.type().name() << '\n';
    std::cout << "x is " << std::any_cast<int>(x) << '\n';
    x = "JSdjks";
    std::cout << "decltype(x) is " << type_name<decltype(x)>() << '\n';
    std::cout << "typeid(x) is " << x.type().name() << '\n';
    std::cout << "x is " << std::any_cast<const char*>(x) << '\n';
    //std::cout << "x is " << std::any_cast<char*>(x) << '\n'; // should be a runtime error
    //std::cout << "x is " << std::any_cast<std::string>(x) << '\n'; // should be a runtime error

    [[maybe_unused]]
    int y = 5;
    struct MyDummy {
        int lol;
    };
    [[maybe_unused]]
    std::string z =  "HELLO";
    // dynamic_cast between non polymorphic types is a compile time error
    // std::cout << "dynamic cast of std::string* to MyDummy* = " << dynamic_cast<MyDummy*>(&z) << std::endl;
    // dynamic_cast to or from a non class type is a compile time error
    // std::cout << "dynamic cast of int* to std::string* = " << dynamic_cast<std::string*>(&y)  << std::endl;
    // std::cout << "dynamic cast of int* to float* = " << dynamic_cast<float*>(&y) << std::endl;
}

void demonstrate_lambdas() {
    int vi = 5;
    int& rvi = vi;
    int const& rci = vi;
    int tmp = 4;
    int&& rval_int = std::move(tmp);
    std::cout << "Before declaring my_lamda, rvi = " << rvi << std::endl;
    auto my_lamda = [vi, rvi, rci, rval_int](void) mutable {
        std::cout << "type of ci in my_lamda = " << type_name<decltype(vi)>() << std::endl;
        std::cout << "type of rci in my_lamda = " << type_name<decltype(rci)>() << std::endl;
        std::cout << "type of rvi in my_lamda = " << type_name<decltype(rvi)>() << std::endl;
        std::cout << "type of rval_int in my_lamda = " << type_name<decltype(rval_int)>() << std::endl;
        std::cout << "vi in my_lamda = " << vi << std::endl;
        std::cout << "rci in my_lamda = " << rci << std::endl;
        std::cout << "rvi in my_lamda = " << rvi << std::endl;
        std::cout << "rval_int in my_lamda = " <<  rval_int << std::endl;
        vi = 100;
        rvi = 200;
        //rci = 400;
        rval_int = 234;
        return;
    };
    vi = 6;
    std::cout << "After declaring my_lamda, rvi = " << rvi << std::endl;
    std::cout << "After declaring my_lamda, tmp = " << tmp << std::endl;
    std::cout << "After declaring my_lamda, rval_int = " << rval_int << std::endl;
    my_lamda();
    std::cout << "After calling my_lamda, rvi = " << rvi << std::endl;
    std::cout << "After calling my_lamda, tmp = " << tmp << std::endl;
    std::cout << "After calling my_lamda, rval_int = " << rval_int << std::endl;

    // Lesson - if not pass by reference explicitly in capture list
    // will never modify the original variables
    // even though seems like the type of the variables copied is ref/constref to something

    //Demoing std::function type conversion
    // std::function have a () operator which takes the args
    // and calls the functor's () operator with the args
    // so its possible that for e,g, - first onet takes const ref and next takes copy
    [[maybe_unused]]
    std::function<void (const int&)> f1 = [](const int&){};
    //[[maybe_unused]]
    // doesnt compile because losing constness
    //std::function<void (const int&)> f2 = [](int&){}; 
    [[maybe_unused]]
    std::function<void (const int&)> f3 = [](int){};
    [[maybe_unused]]
    std::function<void (const int&)> f4 = [](const int){};
    [[maybe_unused]]
    std::function<void (int&)> f5 = [](const int&){};
    [[maybe_unused]]
    std::function<void (int&)> f6 = [](int&){};
    [[maybe_unused]]
    std::function<void (int&)> f7 = [](int){};
    [[maybe_unused]]
    std::function<void (int&)> f8 = [](int){};
    [[maybe_unused]]
    std::function<void (const int)> f9 = [](const int&){};
    //[[maybe_unused]]
    // doesnt compile because const in declaration is removed
    // and is same as f14
    //std::function<void (const int)> f10 = [](int&){};
    [[maybe_unused]]
    std::function<void (const int)> f11 = [](const int){};
    [[maybe_unused]]
    std::function<void (const int)> f12 = [](int){};
    [[maybe_unused]]
    std::function<void (int)> f13 = [](const int&){};
    //[[maybe_unused]]
    // doesnt compile because of perfect forwarding
    // which means when f14(5), 5 is passed as is to lamda
    //std::function<void (int)> f14 = [](int&){};
    [[maybe_unused]]
    std::function<void (int)> f15 = [](const int){};
    [[maybe_unused]]
    std::function<void (int)> f16 = [](int){};
}

}

void demonstrate_operators() {
    std::cout << "demonstrating operators" << std::endl;
    Complex c1 {1, 2};
    c1 = {3, 4};
    Complex c2 = {7, 8};
    Complex c3 (10, 20);
    //Complex c4 = (30, 40); //error
    std::cout << "c1 = " << c1 << std::endl << "c2 = " << c2 << std::endl;
    std::string c3_as_string = c3;
    std::cout << "c3_as_string = " << c3_as_string << std::endl;
    std::cout << "static_cast<std::string>(c3) = " << static_cast<std::string>(c3) << std::endl;
    // Complex c5 = static_cast<Complex>(3); //error
    Complex c6 = !c3;
    std::cout << "Conjugate !c3 = " << c6 << std::endl;
    Complex c7 = c3 + c2;
    std::cout << "c3 + c2 = " << c7 << std::endl;
    Complex c8 = c3 - c2;
    std::cout << "c3 - c2 = " << c8 << std::endl;
    Complex c9 = c3++;
    std::cout << "c3++ = " << c9 << std::endl;
    Complex c10 = 77_im;
    std::cout << "77_im = " << c10 << std::endl;
}

namespace {

class MyStruct {
public:
    MyStruct() : x_{42} {
        std::cout << "MyStruct:: default constructor" << std::endl;
    }
    MyStruct(int x) : x_{x} {
        std::cout << "MyStruct:: 2nd constructor" << std::endl;
    }
    ~MyStruct() {
        std::cout << "MyStruct:: destructor" << std::endl;
    }
    MyStruct(const MyStruct& m) : x_{m.getX()} {
        std::cout << "MyStruct:: copy constructor" << std::endl;
    }
    MyStruct(MyStruct&& m) : x_{std::move(m.getX())} {
        std::cout << "MyStruct:: move constructor" << std::endl;
    }
    friend void swap(MyStruct& m1, MyStruct& m2);
    MyStruct& operator=(MyStruct m) {
        std::cout << "MyStruct:: assignment operator" << std::endl;
        swap(*this, m);
        return *this;
    }
    int getX() const {
        return x_;
    }
    void setX(const int& x) {
        x_ = x;
    }
private:
    int x_;
};

inline void swap(MyStruct& m1, MyStruct& m2) {
    // enable ADL (not necessary in our case, but good practice)
    using std::swap;
    // by swapping the members of two objects,
    // the two objects are effectively swapped
    swap(m1.x_, m2.x_);
}

/*void func_accepting_MyStruct(MyStruct&& m) {
    std::cout << "inside func_accepting_MyStruct rvalue for m.getX() = " << m.getX() << std::endl;
}*/

int func_accepting_MyStruct(const MyStruct& m) {
    std::cout << "inside func_accepting_MyStruct const ref for m.getX() = " << m.getX() << std::endl;
    std::cout << "type of std::move(m) = " << type_name<decltype(std::move(m))>() << std::endl;
    // this doesnot infact move, but instead copy - because m is const - https://stackoverflow.com/questions/28595117/why-can-we-use-stdmove-on-a-const-object
    MyStruct y = std::move(m);
    std::cout << "done std::move to create y with y.getX() = " << y.getX() << std::endl;
    return y.getX();
}

void demonstrate_reference_wrapper() {
    std::cout << "demonstrating reference wrapper" << std::endl;
    MyStruct x(99);
    std::cout << "creating optional normally" << std::endl;
    [[maybe_unused]]
    std::optional<MyStruct> op1 = std::optional(x);

    //std::cout << "trying to create optional by reference" << std::endl;
    //const MyStruct& r = x;
    // DOESNT COMPILE
    // std::optional explicitly disallowes references as the type it holds
    //std::optional<const MyStruct&> op2 = std::optional(r);

    std::cout << "demonstrating reference wrapper" << std::endl;
    /*MyStruct x(99);
    std::cout << "creating optional normally" << std::endl;
    [[maybe_unused]]
    std::optional<MyStruct> op1 = std::optional(x);*/

}

}

void demonstrate_move_semantics() {
    std::cout << "Demonstrating move semantics" << std::endl;
    {
        MyStruct x;
        MyStruct xtmp(-20);
        MyStruct v = x;
        MyStruct tmp = std::move(xtmp);
        v.setX(5);
        std::cout << "Trying to assign x=v" << std::endl;
        x = v;
        std::cout << "Trying to assign x=MyStruct(101)" << std::endl;
        x = MyStruct(101);
        std::cout << "Trying to assign x=std::move(tmp)" << std::endl;
        x = std::move(tmp);
        std::cout << "Done demoing, should call all 3 destructors now" << std::endl;
    }
    {
        MyStruct x {9};
        func_accepting_MyStruct(x);
        func_accepting_MyStruct(MyStruct(100));
        func_accepting_MyStruct(std::move(x));
    }
}

void demonstrate_misc() {
    (void) demonstrate_decltype_auto;
    //demonstrate_decltype_auto();
    (void) demonstrate_std_any;
    //demonstrate_std_any();
    (void) demonstrate_lambdas;
    //demonstrate_lambdas();
    (void) demonstrate_move_semantics;
    //demonstrate_move_semantics();
    (void) demonstrate_reference_wrapper;
    //demonstrate_reference_wrapper();
}

void demonstrate_templates() {
    (void) demonstrate_func_templates;
    //demonstrate_func_templates();
    (void) demonstrate_class_templates;
    //demonstrate_class_templates();
    (void) demonstrate_templates_type_deduction;
    demonstrate_templates_type_deduction();
}
