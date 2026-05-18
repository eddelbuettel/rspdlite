
// In order to survive on CRAN, we have to cope with non-C++20 compilation
#if  __cplusplus >= 202002L

#include <rspdlite>

constexpr int max_args = 15;            // Arbitrary but 'smallish'

template<class... Args>
std::string forward_to_format(const std::string s,
                              const std::vector<std::string>& v,
                              const Args... args) {
    if (v.size() == sizeof...(args)) {
#if defined(SPDLITE_USE_STD_FORMAT) && __cplusplus >= 202002L
        return std::vformat(std::string_view(s), std::make_format_args(args...));
#elif __cplusplus >= 202002L
        return fmt::format(fmt::runtime(s), args...);
#else
        #error "Compiling spdlite requires C++20"
#endif
    }
    if constexpr(sizeof...(args) < max_args) {
        return forward_to_format(s, v, args..., v[sizeof...(args)]);
    }
    return std::string(""); // not reached
}

#else

#include <Rcpp/Lighter>

constexpr int max_args = 15;            // Arbitrary but 'smallish'
enum class level : int { off = 0, on = 1, info = 2 };

std::string forward_to_format(const std::string, const std::vector<std::string>&) {
    Rcpp::message(Rcpp::wrap("No spdlite support without C++20. Sorry."));
    return std::string("");
}

namespace rspdlite {
    enum level stringToLevel(std::string) { return level::info; }
    std::string levelToString(enum level) { return std::string("info"); }
    struct dummy_console {
        void trace(std::string_view) {}
        void debug(std::string_view) {}
        void info(std::string_view) {}
        void warn(std::string_view) {}
        void error(std::string_view) {}
        void critical(std::string_view) {}
        void log_level(enum level) {}
        enum level log_level() { return level::info; }
    };
    dummy_console console;
}

#endif

//' Simple Pass-Through Formatter to \code{fmt::format()}
//'
//' The C-level interface of R does not make it easy to pass \code{...}  arguments.
//' This helper function assumes it has already been called with \code{format()}
//' on each argument (as a wrapper can do) so it just spreads out the class to
//' \code{fmt::format{}} which, being C++, uses variadic templates to receive the
//' arguments. The main motivation for this function to able to format string as
//' use by the \sQuote{fmtlib::fmt} library included in \sQuote{spdlog} to write
//' similar debug strings in both R and C++. This function permits R calls with
//' multiple arguments of different types which (by being formatted on the R side)
//' are handled as strings (whereas C++ logging has access to the templating logic).
//'
//' @param s A character variable with a format string for \sQuote{fmtlib::fmt}
//' @param v A character vector with the logging string arguments.
//' @return A single (formatted) string
//' @seealso https://github.com/fmtlib/fmt
// [[Rcpp::export]]
std::string formatter(const std::string s, std::vector<std::string> v) {
    if (v.size() > max_args)
        Rcpp::warning("Only up to " + std::to_string(max_args) + " arguments support for now.");
    return forward_to_format(s, v);
}

// [[Rcpp::export]]
void trace_(std::string s) { rspdlite::console.trace(std::string_view(s)); }

// [[Rcpp::export]]
void debug_(std::string s) { rspdlite::console.debug(std::string_view(s)); }

// [[Rcpp::export]]
void info_(std::string s) { rspdlite::console.info(std::string_view(s)); }

// [[Rcpp::export]]
void warn_(std::string s) { rspdlite::console.warn(std::string_view(s)); }

// [[Rcpp::export]]
void error_(std::string s) { rspdlite::console.error(std::string_view(s)); }

// [[Rcpp::export]]
void critical_(std::string s) { rspdlite::console.critical(std::string_view(s)); }

// [[Rcpp::export]]
void set_level_(std::string s) { rspdlite::console.log_level(rspdlite::stringToLevel(s)); }

// [[Rcpp::export]]
std::string get_level_() { return rspdlite::levelToString(rspdlite::console.log_level()); }

// [[Rcpp::export]]
void set_name_(const std::string& s) { rspdlite::console.name(s); }

// [[Rcpp::export]]
std::string get_name_()       { return rspdlite::console.name(); }

// #else

// #include <Rcpp/Lighter>

// // Either insufficient C++20, or C++17 or older so no rspdlite for us
// inline void badCpp() { Rcpp::message(Rcpp::wrap("Insufficient compiler. Sorry.")); }

// // [[Rcpp::export]]
// std::string formatter(const std::string s, std::vector<std::string> v) {
//     badCpp();
//     return s + v[0];
// }

// // [[Rcpp::export]]
// void trace_(std::string s) { badCpp(); }

// // [[Rcpp::export]]
// void debug_(std::string s) { badCpp(); }

// // [[Rcpp::export]]
// void info_(std::string s) { badCpp(); }

// // [[Rcpp::export]]
// void warn_(std::string s) { badCpp(); }

// // [[Rcpp::export]]
// void error_(std::string s) { badCpp(); }

// // [[Rcpp::export]]
// void critical_(std::string s) { badCpp(); }

// // [[Rcpp::export]]
// void set_level_(std::string s) { badCpp(); }

// // [[Rcpp::export]]
// std::string get_level_() { return std::string("info"); }

// #endif

// [[Rcpp::export]]
int cppstandard() { return __cplusplus; }
