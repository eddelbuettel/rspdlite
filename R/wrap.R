##' Convenience Wrappers for 'spdlite' Logging
##'
##' Several short wrappers for functions from 'spdlite' are provided as a convenience.
##'
##' @param level Character value for the logging level
##' @param s Character value for filename, pattern, level, or logging message
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

fmt <- function(s, ...) {
    n <- ...length()
    v <- character(n)
    for (i in seq_len(n)) v[i] <- format(...elt(i)[1])
    formatter(s, v)
}
