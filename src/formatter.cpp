
// add ', cpp' for callable interface
// [[Rcpp::interfaces(r)]]

#include <rspdlite>

//' (Internal) Simple Pass-Through Forwarder to \code{fmt::format()}
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
//' @noRd
// [[Rcpp::export]]
std::string formatter_(const std::string s, std::vector<std::string> v) {
    if (v.size() > max_args)
        Rcpp::warning("Only up to " + std::to_string(max_args) + " arguments support for now.");
    return forward_to_format(s, v);
}

// [[Rcpp::export]]
void trace_(std::string s) { rspdlite::logger.trace(std::string_view(s)); }

// [[Rcpp::export]]
void debug_(std::string s) { rspdlite::logger.debug(std::string_view(s)); }

// [[Rcpp::export]]
void info_(std::string s) { rspdlite::logger.info(std::string_view(s)); }

// [[Rcpp::export]]
void warn_(std::string s) { rspdlite::logger.warn(std::string_view(s)); }

// [[Rcpp::export]]
void error_(std::string s) { rspdlite::logger.error(std::string_view(s)); }

// [[Rcpp::export]]
void critical_(std::string s) { rspdlite::logger.critical(std::string_view(s)); }

// [[Rcpp::export]]
void set_level_(std::string s) { rspdlite::logger.set_log_level(rspdlite::stringToLevel(s)); }

// [[Rcpp::export]]
std::string get_level_() { return rspdlite::levelToString(rspdlite::logger.get_log_level()); }

// [[Rcpp::export]]
void set_name_(const std::string& s) { rspdlite::logger.set_name(s); }

// [[Rcpp::export]]
std::string get_name_()       { return std::string(rspdlite::logger.get_name()); }

#if  __cplusplus >= 202002L

// [[Rcpp::export]]
void set_precision_(const std::string& s) {
    rspdlite::logger.set_format_options({.precision = rspdlite::stringToTimeprecision(s)});
}

// [[Rcpp::export]]
void show_thread_id_(const bool b) { rspdlite::logger.set_format_options({.show_thread_id = b}); }

// [[Rcpp::export]]
void show_date_(const bool b) { rspdlite::logger.set_format_options({.show_date = b}); }

// [[Rcpp::export]]
void show_utc_(const bool b) { rspdlite::logger.set_format_options({.utc = b}); }

// [[Rcpp::export]]
void set_format_(const bool utc, const bool show_date, const bool show_thread_id,
                 const std::string& precision) {
    rspdlite::logger.set_format_options({
            .utc = utc,
            .show_date = show_date,
            .show_thread_id = show_thread_id,
            .precision = rspdlite::stringToTimeprecision(precision)
        });
}

#else

void set_precision_(const std::string&) { }
void show_thread_id_(const bool) { }
void show_date_(const bool) { }
void show_utc_(const bool) { }
void set_format_(const bool, const bool, const bool, const std::string&) { }

#endif

// [[Rcpp::export]]
int cppstandard() { return __cplusplus; }
