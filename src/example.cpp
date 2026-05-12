#include <rspdlite>

//' spdlite Example using a sink for R
//'
//' A simple example invoking a logger from C++. It can interact with logging from R.
//'
//' @return None
// [[Rcpp::export]]
void exampleRsink() {

    // Direct use of the console object as in the upstream docs
    console.info("Welcome to spdlog!");
    console.error("Some error message with arg: {}", 1);
    console.warn("Easy padding in numbers like {:08d}", 12);
    console.critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    console.info("Support for floats {:03.2f}", 1.23456);
    console.info("Positional args are {1} {0}..", "too", "supported");
    console.info("{:<30}", "left aligned");

    rspdlite::level(spdlite::level::warn);

    // Or via the spdl namespace (s)
    rspdlite::info("Some more");
    rspdlite::error("Some error message with arg: {}", 1);
    rspdlite::warn("Easy padding in numbers like {:08d}", 12);
    rspdlite::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    rspdlite::info("Support for floats {:03.2f}", 1.23456);
    rspdlite::info("Positional args are {1} {0}..", "too", "supported");
    rspdlite::info("{:<30}", "left aligned");

    rspdlite::level(spdlite::level::info);
    // Or via the spdl namespace (s)
    rspdlite::info("Some more");
    rspdlite::error("Some error message with arg: {}", 1);
    rspdlite::warn("Easy padding in numbers like {:08d}", 12);
    rspdlite::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    rspdlite::info("Support for floats {:03.2f}", 1.23456);
    rspdlite::info("Positional args are {1} {0}..", "too", "supported");
    rspdlite::info("{:<30}", "left aligned");
}
