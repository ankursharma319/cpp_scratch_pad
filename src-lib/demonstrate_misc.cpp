#include "demonstrations.hpp"
#include "MyComplex.hpp"
#include <iostream>
#include <optional>
#include <string_view>
#include <functional>
#include <any>
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

namespace {

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
    std::function<const int& (void)> rets_const_ref = [&ai](void) -> const int& {
        return ai;
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

    std::function<void (int&)> func_accepts_lvalue_ref = [](int& x) {
        std::cout << "func_accepts_lvalue_ref got " << x << std::endl;
        return;
    };
    std::function<void (int&& x)> func_accepts_rvalue_ref = [](int&& x) {
        std::cout << "func_accepts_rvalue_ref got " << x << std::endl;
        return;
    };
    int tmp = 5;
    func_accepts_lvalue_ref(ai);
    // func_accepts_lvalue_ref(ci); - doesnt compile bcoz losing constness
    int&& xval = static_cast<int&&>(tmp);
    func_accepts_lvalue_ref(xval);
    // func_accepts_lvalue_ref(std::move(tmp)); - doesnt compile bcoz rvalue doesnt bind to lvalue reference

    //func_accepts_rvalue_ref(ai); - not an rvalue
    //func_accepts_rvalue_ref(ci); - not an rvalue
    //func_accepts_rvalue_ref(xval); - not an rvalue
    func_accepts_rvalue_ref(std::move(tmp));
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
    // doesnt compile because of perfect forwarding
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
    // first its passed as a copy to std::function
    // then its perfectly forwarded to lamda
    // i.e. it becomes an rvalue reference, which doesnt bind to func accepting non const lvalue ref
    // perfect forwarding is a simple cast to && - essentially std::move in this case
    // it makes sense to std::move because std::function got a copy which it
    // doesnt need to use anymore
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
    std::optional<MyStruct> op1 = std::optional(x); // creates a copy
    std::cout << "value of x.getX() before = " << x.getX() << std::endl;
    op1.value().setX(101);
    std::cout << "value of x.getX() after = " << x.getX() << std::endl;

    //std::cout << "trying to create optional by reference" << std::endl;
    //const MyStruct& r = x;
    // DOESNT COMPILE
    // std::optional explicitly disallowes references as the type it holds
    //std::optional<const MyStruct&> op2 = std::optional(r);

    std::cout << "creating optional using reference_wrapper" << std::endl;
    [[maybe_unused]]
    std::optional<std::reference_wrapper<MyStruct>> op2 = std::optional(std::ref(x));
    std::cout << "value of x.getX() before = " << x.getX() << std::endl;
    op2.value().get().setX(101);
    std::cout << "value of x.getX() after = " << x.getX() << std::endl;

    std::cout << "creating optional using reference_wrapper with const ref" << std::endl;
    [[maybe_unused]]
    std::optional<std::reference_wrapper<const MyStruct>> op3 = std::optional(std::cref(x));
    // FAILS TO COMPILE because const ref
    //op3.value().get().setX(101);
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
