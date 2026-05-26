#include <rspdlite>
#include <spdlite/sinks/console_sink.h> // for example 3, do not use in R packages though

//' spdlite Example using a sink for R
//'
//' A simple example invoking a logger from C++. It can interact with logging from R.
//'
//' @return None
// [[Rcpp::export]]
void example1() {
    // Direct use of the logger object as in the upstream docs
    rspdlite::logger.info("Welcome to spdlog!");
    rspdlite::logger.error("Some error message with arg: {}", 1);
    rspdlite::logger.warn("Easy padding in numbers like {:08d}", 12);
    rspdlite::logger.critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    rspdlite::logger.info("Support for floats {:03.2f}", 1.23456);
    rspdlite::logger.info("Positional args are {1} {0}..", "too", "supported");
    rspdlite::logger.info("{:<30}", "left aligned");
}

//' @rdname example1
// [[Rcpp::export]]
void example2() {
    // set level to warn

    rspdlite::log_critical("-- level to warn");
    rspdlite::set_level(spdlite::level::warn);

    rspdlite::log_info("Some more");
    rspdlite::log_error("Some error message with arg: {}", 1);
    rspdlite::log_warn("Easy padding in numbers like {:08d}", 12);
    rspdlite::log_critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    rspdlite::log_info("Support for floats {:03.2f}", 1.23456);
    rspdlite::log_info("Positional args are {1} {0}..", "too", "supported");
    rspdlite::log_info("{:<30}", "left aligned");

    // set level to info
    rspdlite::log_critical("-- level to info, name to 'demo'");
    rspdlite::set_name("demo");
    rspdlite::set_level(spdlite::level::info);

    rspdlite::log_info("Some more");
    rspdlite::log_error("Some error message with arg: {}", 1);
    rspdlite::log_warn("Easy padding in numbers like {:08d}", 12);
    rspdlite::log_critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    rspdlite::log_info("Support for floats {:03.2f}", 1.23456);
    rspdlite::log_info("Positional args are {1} {0}..", "too", "supported");
    rspdlite::log_info("{:<30}", "left aligned");
}

//' @rdname example1
// [[Rcpp::export]]
void example3() {
    // try local instance
    //using namespace spdlite;
    spdlite::logger_st<spdlite::console_sink> log(spdlite::console_sink{});
    log.info("hello world");
    log.set_name("bob");
    log.info("another world");

    log.set_format_options({.utc = true});
    log.info("another world");
    log.set_format_options({.show_date = false});
    log.info("another world");
    log.set_format_options({.show_date = true});
    log.info("another world");
    log.set_format_options({.precision = spdlite::time_precision::ns});
    log.warn("another world");
    log.set_format_options({.show_thread_id = true});
    log.error("another world");
    log.set_name("bill");
    log.set_format_options({.show_date = false, .precision = spdlite::time_precision::us});
    log.critical("another world");
    log.set_name("roger");
    log.info("another world");

}

/*** R
example1()
example2()
example3()
*/

// One can run this example from R quite easily via Rcpp:
//
// Sys.setenv(PKG_CPPFLAGS=paste0("-std=c++20 -I", system.file("include", package="rspdlite")))
// Rcpp::sourceCpp( system.file("examples", "example.cpp", package="rspdlite") )
//
// which should build it on any suitable platform, and also run the example.
//
//
// One can then show that setting a 'null logger' suppressed the output by adding the define:
//
// Sys.setenv(PKG_CPPFLAGS=paste0("-std=c++20 -DRSPDLITE_NULL_SINK ",
//                                "-I", system.file("include", package="rspdlite")))
// Rcpp::sourceCpp( system.file("examples", "example.cpp", package="rspdlite"), rebuild=TRUE )
//
// where the rebuild=TRUE flag forces a recompilation under the added define.
