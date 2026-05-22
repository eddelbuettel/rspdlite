#include <rspdlite>

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

/*** R
example1()
*/

// One can run this example from R quite easily via Rcpp:
//
// Sys.setenv(PKG_CPPFLAGS=paste0("-std=c++20 -I", system.file("include", package="rspdlite")))
// Rcpp::sourceCpp( system.file("examples", "example1.cpp", package="rspdlite") )
//
// which should build it on any suitable platform, and also run the example.
//
//
// One can then show that setting a 'null logger' suppressed the output by adding the define:
//
// Sys.setenv(PKG_CPPFLAGS=paste0("-std=c++20 -DRSPDLITE_NULL_SINK ",
//                                "-I", system.file("include", package="rspdlite")))
// Rcpp::sourceCpp( system.file("examples", "example1.cpp", package="rspdlite"), rebuild=TRUE )
//
// where the rebuild=TRUE flag forces a recompilation under the added define.
