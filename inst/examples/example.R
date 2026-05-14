
#' @rdname example1
example3 <- function() {
    rspdlite::critical("-- level to debug")
    rspdlite::set_level("debug")

    rspdlite::info("Some more at info")
    rspdlite::error("Some error message with arg: {}", 1)
    rspdlite::error("Some error message with more args: {} and {}", 1, "abc")

    rspdlite::critical("-- level to error and calling example1 and example2")
    rspdlite::set_level("error")
    example1()
    example2()
}

## One can run this example via
##
## source( system.file("examples", "example.R", package="rspdlite") )
##
## after the two example C++ files have been built. Depending on under which
## flags they have been compiled their behaviour may differ as using
## Rcpp::sourceCpp() leads to independent shared libraries and spdlite
## instances. Usage in a package forces a single instance so setting
## changes are 'global' to the package.
