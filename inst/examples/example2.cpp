#include <rspdlite>

//' @rdname example1
// [[Rcpp::export]]
void example2() {
    // set level to warn

    rspdlite::critical("-- level to warn");
    rspdlite::level(spdlite::level::warn);

    rspdlite::info("Some more");
    rspdlite::error("Some error message with arg: {}", 1);
    rspdlite::warn("Easy padding in numbers like {:08d}", 12);
    rspdlite::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    rspdlite::info("Support for floats {:03.2f}", 1.23456);
    rspdlite::info("Positional args are {1} {0}..", "too", "supported");
    rspdlite::info("{:<30}", "left aligned");

    // set level to info
    rspdlite::critical("-- level to info");
    rspdlite::level(spdlite::level::info);

    rspdlite::info("Some more");
    rspdlite::error("Some error message with arg: {}", 1);
    rspdlite::warn("Easy padding in numbers like {:08d}", 12);
    rspdlite::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    rspdlite::info("Support for floats {:03.2f}", 1.23456);
    rspdlite::info("Positional args are {1} {0}..", "too", "supported");
    rspdlite::info("{:<30}", "left aligned");
}
