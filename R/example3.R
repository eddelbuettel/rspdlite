
#' @rdname example1
example3 <- function() {
    set_level("debug")
    set_level("warn")

    rspdlite::info("Some more")
    rspdlite::error("Some error message with arg: {}", 1)
    rspdlite::error("Some error message with more args: {} and {}", 1, "abc")
}
