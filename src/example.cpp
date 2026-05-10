
#include <Rcpp/Lighter>
#include <spdlite/logger.h>
//#include <spdlite/sinks/color_sink.h>

namespace spdlite {
    struct r_sink {
        explicit r_sink() {}
        void write(const log_msg &msg) { Rcpp::Rcout << std::string_view(msg.formatted.data(), msg.formatted.size()); }
        void flush() { Rcpp::Rcout << std::flush; }
    };
}

static spdlite::logger_st console("", spdlite::r_sink{}); //spdlite::console_sink{});

using namespace spdlite;

namespace spdl {
    template <typename... Args>
    void trace(format_string_t<Args...> fmt, Args&&... args) /*const noexcept*/ {
        console.log(level::trace, fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void debug(format_string_t<Args...> fmt, Args&&... args) /*const noexcept*/ {
        console.log(level::debug, fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void info(format_string_t<Args...> fmt, Args&&... args) /*const noexcept*/ {
        console.log(level::info, fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void warn(format_string_t<Args...> fmt, Args&&... args) /*const noexcept*/ {
        console.log(level::warn, fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void error(format_string_t<Args...> fmt, Args&&... args) /*const noexcept*/ {
        console.log(level::err, fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void critical(format_string_t<Args...> fmt, Args&&... args) /*const noexcept*/ {
        console.log(level::critical, fmt, std::forward<Args>(args)...);
    }
};

//' spdlite Example using a sink for R
//'
//' A simple example invoking a derived R/Rcpp logger. Also demonstrates the
//' stopwatch feature. For more features see the 'spdlog' documnetation.
//'
//' @return None
//' @examples
//' exampleRsink()
// [[Rcpp::export]]
void exampleRsink() {

    //std::string logname = "fromR"; 							// fix a name for this logger
    //auto sp = spdlite::get(logname);       					// retrieve existing one
    //if (sp == nullptr) sp = spdlite::r_sink_mt(logname);   	// or create new one if needed
    //spdlite::set_default_logger(sp);                         // and set as default

    //spdlite::stopwatch sw;       							// instantiate a stop watch
    //spdlite::logger_st console(logname, spdlite::r_sink{}); //spdlite::console_sink{});

    // change log pattern (changed from [%H:%M:%S %z] [%n] [%^---%L---%$] )
    //spdlite::set_pattern("[%H:%M:%S.%f] [%n] [%^%L%$] [thread %t] %v");

    console.info("Welcome to spdlog!");
    console.error("Some error message with arg: {}", 1);
    //spdlite::info("Elapsed time: {}", sw);

    console.warn("Easy padding in numbers like {:08d}", 12);
    console.critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    console.info("Support for floats {:03.2f}", 1.23456);
    console.info("Positional args are {1} {0}..", "too", "supported");
    console.info("{:<30}", "left aligned");
    //spdlite::info("Elapsed time: {}", sw);

    spdl::info("Some more");
    spdl::error("Some error message with arg: {}", 1);
    spdl::warn("Easy padding in numbers like {:08d}", 12);
    spdl::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdl::info("Support for floats {:03.2f}", 1.23456);
    spdl::info("Positional args are {1} {0}..", "too", "supported");
    spdl::info("{:<30}", "left aligned");

}

// ' spdlog Logging Lever Setter
// '
// ' A helper function to turn a logging level given as string
// ' into the current logging level
// '
// ' @param name A string with the logging level. Value understood are,
// ' in decreasing verbosity \sQuote{trace}, \sQuote{debug}, \sQuote{info},
// ' \sQuote{warning}, \sQuote{error}, \sQuote{critical}, and \sQuote{off}.
// ' Unrecognised names are equivalent to \sQuote{off}.
// ' @return Nothing is returned.
// [ [ Rcpp::export]]
// void setLogLevel(const std::string &name) {
//    spdlite::set_level(spdlite::level::from_str(name));
//}
