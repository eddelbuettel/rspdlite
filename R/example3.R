
#' @rdname example1
example3 <- function() {
    rspdlite::critical("-- level to debug")
    set_level("debug")

    rspdlite::info("Some more at info")
    rspdlite::error("Some error message with arg: {}", 1)
    rspdlite::error("Some error message with more args: {} and {}", 1, "abc")

    rspdlite::critical("-- level to error and calling example1 and example2")
    set_level("error")
    example1()
    example2()
}
