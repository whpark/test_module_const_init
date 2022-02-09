module;

#include <format>

export module my_module;

export namespace my_module {

    //------------------------------------------------


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


#if 0   // template specialization NOT working in module.
export template <> struct std::formatter<my_module::s_color_t> : public std::formatter<std::string> {
public:
    auto format(my_module::s_color_t color, std::format_context& ctx) {
        return std::formatter<std::string>::format(
            std::format("{}, {}, {}, {}", color.r, color.g, color.b, color.a), ctx);
    }
};
export template <> struct std::formatter<my_module::u_color_t> : public std::formatter<std::string> {
public:
    auto format(my_module::u_color_t color, std::format_context& ctx) {
        return std::formatter<std::string>::format(
            std::format("{}, {}, {}, {}", color.e.r, color.e.g, color.e.b, color.e.a), ctx);
    }
};
export template <> struct std::formatter<my_module::ua_color_t> : public std::formatter<std::string> {
public:
    auto format(my_module::ua_color_t color, std::format_context& ctx) {
        return std::formatter<std::string>::format(
            std::format("{}, {}, {}, {}", color.r, color.g, color.b, color.a), ctx);
    }
};
#endif
