##' Convenience Wrappers for 'spdlite' Logging
##'
##' Several short wrappers for functions from 'spdlite' are provided as a convenience.
##'
##' @param level Character value for the logging level
##' @param s Character value for filename, pattern, level, or logging message
##' @param b Boolean flag to select or unselect a formatting option
##' @param ... Supplementary arguments for the logging string
##' @return Nothing is returned from these functions (with the exception of
##' \code{get_level()}) as they are invoked for their side-effects.
trace       <- function(s, ...)  trace_(fmt(s,...))

##' @rdname trace
debug       <- function(s, ...)  debug_(fmt(s,...))

##' @rdname trace
info        <- function(s, ...)  info_(fmt(s,...))

##' @rdname trace
warn        <- function(s, ...)  warn_(fmt(s,...))

##' @rdname trace
error       <- function(s, ...)  error_(fmt(s,...))

##' @rdname trace
critical    <- function(s, ...)  critical_(fmt(s,...))

##' @rdname trace
set_level   <- function(level)  set_level_(level)

##' @rdname trace
get_level   <- function()       get_level_()

##' @rdname trace
set_name   <- function(s)       set_name_(s)

##' @rdname trace
get_name   <- function()        get_name_()

##' @rdname trace
set_precision <- function(s)    set_precision_(s)

##' @rdname trace
show_thread_id <- function(b = TRUE)   show_thread_id_(b)

##' @rdname trace
show_date <- function(b = TRUE) show_date_(b)

##' @rdname trace
show_utc <- function(b = TRUE) show_utc_(b)

##' @rdname trace
set_format <- function(utc = FALSE,
                       show_date = TRUE,
                       show_thread_id = FALSE,
                       precision = "ms") {
    set_format_(utc, show_date, show_thread_id, precision)
}

fmt <- function(s, ...) {
    n <- ...length()
    v <- character(n)
    for (i in seq_len(n)) v[i] <- format(...elt(i)[1])
    formatter(s, v)
}
