#include <rspdlite>

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

/*** R
example2()
*/

// One can run this example from R quite easily via Rcpp:
//
// Sys.setenv(PKG_CPPFLAGS=paste0("-std=c++20 -I", system.file("include", package="rspdlite")))
// Rcpp::sourceCpp( system.file("examples", "example2.cpp", package="rspdlite") )
//
// which should build it on any suitable platform, and also run the example.
//
//
// One can then show that setting a 'null logger' suppressed the output by adding the define:
//
// Sys.setenv(PKG_CPPFLAGS=paste0("-std=c++20 -DRSPDLITE_NULL_SINK ",
//                                "-I", system.file("include", package="rspdlite")))
// Rcpp::sourceCpp( system.file("examples", "example2.cpp", package="rspdlite"), rebuild=TRUE )
//
// where the rebuild=TRUE flag forces a recompilation under the added define.
