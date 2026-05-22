#' rspdlite: Lightweight Logging From R and C++
#'
#' \pkg{rspdlite} relies on \pkg{spdlite}, a lightweight header-only C++20
#' library for logging. This package offers a simple and consistent interface
#' from both R and C++.
#'
#' \pkg{spdlite} is the \sQuote{little brother} of \pkg{spdlog} (which we have
#' available via R packages \pkg{RcppSpdlog} and \pkg{spdl}). \pkg{spdlite} is
#' on purpose smaller and simpler. It has (by choice) fewer options and
#' configuration settings keeping the core small and simple.
#'
#' By using a global \code{inline} instance, each shared library (i.e. typically
#' each package using logging) is guaranteed to have exactly one instance. So
#' setting changes such as the logging level affect both the R and C++ side. If
#' however another R package were to be compiled with the \pkg{spdlite} header,
#' its instance would be separate as it resides in a different shared library.
#' Similarly, an ad-hoc compilation via e.g. \code{Rcpp::sourceCpp()} will lead
#' to a distinct instance for the same reason.
"_PACKAGE"
