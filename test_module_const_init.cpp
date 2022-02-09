// test_module_const_init.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <format>

import my_module;

namespace {
    // same as my_module

    /* struct */
    struct s_color_t {
        uint8_t r, g, b, a;;
    };

    /* union-struct */
    union u_color_t {
        struct { uint8_t r, g, b, a; } e;
        uint32_t cr;
    };

    /* anonymous union-struct */
    union ua_color_t {
        struct { uint8_t r, g, b, a; };
        uint32_t cr;
    };


    // variables : normal variable, const variable, constexp variable
    s_color_t  s_variable {255, 255, 255, };
    u_color_t  u_variable {255, 255, 255, };
    ua_color_t ua_variable {255, 255, 255, };

    s_color_t const   s_const_variable { 255, 255, 255, };
    u_color_t const   u_const_variable { 255, 255, 255, };
    ua_color_t const ua_const_variable { 255, 255, 255, };

    constexpr  s_color_t const  s_constexpr_const_variable { 255, 255, 255, };
    constexpr  u_color_t const  u_constexpr_const_variable { 255, 255, 255, };
    constexpr ua_color_t const ua_constexpr_const_variable { 255, 255, 255, };
}

// just format specifiers
template <> struct std::formatter<s_color_t> : public std::formatter<std::string> {
public:
    auto format(s_color_t color, std::format_context& ctx) {
        return std::formatter<std::string>::format(
            std::format("{}, {}, {}, {}", color.r, color.g, color.b, color.a), ctx);
    }
};
template <> struct std::formatter<u_color_t> : public std::formatter<std::string> {
public:
    auto format(u_color_t color, std::format_context& ctx) {
        return std::formatter<std::string>::format(
            std::format("{}, {}, {}, {}", color.e.r, color.e.g, color.e.b, color.e.a), ctx);
    }
};
template <> struct std::formatter<ua_color_t> : public std::formatter<std::string> {
public:
    auto format(ua_color_t color, std::format_context& ctx) {
        return std::formatter<std::string>::format(
            std::format("{}, {}, {}, {}", color.r, color.g, color.b, color.a), ctx);
    }
};

// just format specifiers for my_module. (NOT working if belows moved to my_moudule. template specifiers are NOT working in module my_module)
template <> struct std::formatter<my_module::s_color_t> : public std::formatter<std::string> {
public:
    auto format(my_module::s_color_t color, std::format_context& ctx) {
        return std::formatter<std::string>::format(
            std::format("{}, {}, {}, {}", color.r, color.g, color.b, color.a), ctx);
    }
};
template <> struct std::formatter<my_module::u_color_t> : public std::formatter<std::string> {
public:
    auto format(my_module::u_color_t color, std::format_context& ctx) {
        return std::formatter<std::string>::format(
            std::format("{}, {}, {}, {}", color.e.r, color.e.g, color.e.b, color.e.a), ctx);
    }
};
template <> struct std::formatter<my_module::ua_color_t> : public std::formatter<std::string> {
public:
    auto format(my_module::ua_color_t color, std::format_context& ctx) {
        return std::formatter<std::string>::format(
            std::format("{}, {}, {}, {}", color.r, color.g, color.b, color.a), ctx);
    }
};



int main() {

    auto PrintOut = [](std::string const& name, auto const& value) {
        std::cout << std::format("{:>40} ==> {}\n", name, value);
    };

    std::cout << "All variables are initialized as 255, 255, 255, 0\n\n";

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 1. initialized global variables. ALL OK.
    std::cout << "*** Global Variable.\n";
    PrintOut("::s_variable",  :: s_variable);
    PrintOut("::u_variable",  :: u_variable);
    PrintOut("::ua_variable", ::ua_variable);
    std::cout << "\n";

    PrintOut("::s_const_variable",  :: s_const_variable);
    PrintOut("::u_const_variable",  :: u_const_variable);
    PrintOut("::ua_const_variable", ::ua_const_variable);
    std::cout << "\n";

    PrintOut("::s_constexpr_const_variable",  :: s_constexpr_const_variable);
    PrintOut("::u_constexpr_const_variable",  :: u_constexpr_const_variable);
    PrintOut("::ua_constexpr_const_variable", ::ua_constexpr_const_variable);
    std::cout << "\n";

    std::cout << "\n";
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 2. initialized global variables in my_module. const variables are NOT OK.
    std::cout << "*** Variable inside module.\n";
    PrintOut("my_module::s_variable",  my_module:: s_variable);
    PrintOut("my_module::u_variable",  my_module:: u_variable);
    PrintOut("my_module::ua_variable", my_module::ua_variable);
    std::cout << "\n";

    PrintOut("my_module::s_const_variable",  my_module:: s_const_variable);		// ==> 0,0,0. NOT EXPECTED.
    PrintOut("my_module::u_const_variable",  my_module:: u_const_variable);		// ==> 0,0,0. NOT EXPECTED.
    PrintOut("my_module::ua_const_variable", my_module::ua_const_variable);		// ==> 0,0,0. NOT EXPECTED.
    std::cout << "\n";

    PrintOut("my_module::s_constexpr_const_variable",  my_module:: s_constexpr_const_variable);
    PrintOut("my_module::u_constexpr_const_variable",  my_module:: u_constexpr_const_variable);
    //PrintOut("my_module::ua_constexpr_const_variable", my_module::ua_constexpr_const_variable);	// NOT COMPILES
    PrintOut("my_module::ua_constexpr_const_variable", "! NOT COMPILES !");
    std::cout << "\n";
}


#if 0
import my_module_simple;

int main() {
    auto v = my_module::const_variable;
    std::cout << std::format("{}, {}, {}, {}\n", v.r, v.g, v.b, v.a);
}
#endif

