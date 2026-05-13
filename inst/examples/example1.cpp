#include <rspdlite>

//' spdlite Example using a sink for R
//'
//' A simple example invoking a logger from C++. It can interact with logging from R.
//'
//' @return None
// [[Rcpp::export]]
void example1() {
    // Direct use of the console object as in the upstream docs
    rspdlite::console.info("Welcome to spdlog!");
    rspdlite::console.error("Some error message with arg: {}", 1);
    rspdlite::console.warn("Easy padding in numbers like {:08d}", 12);
    rspdlite::console.critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    rspdlite::console.info("Support for floats {:03.2f}", 1.23456);
    rspdlite::console.info("Positional args are {1} {0}..", "too", "supported");
    rspdlite::console.info("{:<30}", "left aligned");
}
