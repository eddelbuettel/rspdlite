# rspdlite: Using spdlite for R and C++ logging

[![CI](https://github.com/eddelbuettel/rspdlite/actions/workflows/ci.yaml/badge.svg)](https://github.com/eddelbuettel/rspdlite/actions/workflows/ci.yaml)
[![License](https://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](https://www.r-project.org/Licenses/GPL-2)
[![r-universe](https://eddelbuettel.r-universe.dev/badges/rspdlite)](https://eddelbuettel.r-universe.dev/rspdlite)
[![Last Commit](https://img.shields.io/github/last-commit/eddelbuettel/rspdlite)](https://github.com/eddelbuettel/rspdlite)

<!-- [![CRAN](https://www.r-pkg.org/badges/version/RcppSpdlog)](https://cran.r-project.org/package=RcppSpdlog) -->
<!-- [![Dependencies](https://tinyverse.netlify.app/badge/RcppSpdlog)](https://cran.r-project.org/package=RcppSpdlog) -->
<!-- [![Downloads](https://cranlogs.r-pkg.org/badges/RcppSpdlog?color=brightgreen)](https://www.r-pkg.org/pkg/RcppSpdlog) -->


### About

The [spdlog][spdlog] library is a widely-used and very capable C++ library for logging. We are
providing it for R users in package [RcppSpdlog][rcppspdlog] along with the additional C++/R
interface package [spdl][spdl]. For both demanding logging jobs and/or a need for customization,
these work reliably. Sometimes, however, one desires a smaller, more lightweight and minimalistic
approach. [spdlite][spdlite] answers to that need. It is a C++20 header-only library which makes
some deliberate design choices to 'keep things simple' -- resulting in a logger that is "tiny, fast,
capable" (to quote the [upstream README][spdlite]).  Configuration is mostly at compile-time, though
logging levels can of course be adjusted at run-time.  By using an `inline` instance under the 'one
definition rule', each 'application', or here each R package including the header, gets its own
instance of the logger (even if the header is included multiple times within a package). As before,
we provide a distinct 'sink' for R (to route into its output stream).  A simple 'file sink' for
logging messages can be selected at compile time.

### Examples

#### From C++

As seen in file [examples/example.cpp][ex] we can use the same C++ example from the
[spdlite][spdlite] docs, either directly accessing an instantiated `logger` object as in the first
example

```c++
// Direct use of the logger object as in the upstream docs
rspdlite::logger.info("Welcome to spdlog!");
rspdlite::logger.error("Some error message with arg: {}", 1);
rspdlite::logger.warn("Easy padding in numbers like {:08d}", 12);
rspdlite::logger.critical("Support for int: {0:d}; hex: {0:x}; oct: {0:o}; bin: {0:b}", 42);
rspdlite::logger.info("Support for floats {:03.2f}", 1.23456);
rspdlite::logger.info("Positional args are {1} {0}..", "too", "supported");
rspdlite::logger.info("{:<30}", "left aligned");
```

or, preferably, by using a level of indirection we added as shown in the second example (of which
just show the first half)

```c++
rspdlite::log_critical("-- level to warn");
rspdlite::set_level(spdlite::level::warn);

rspdlite::log_info("Some more");
rspdlite::log_error("Some error message with arg: {}", 1);
rspdlite::log_warn("Easy padding in numbers like {:08d}", 12);
rspdlite::log_critical("Support for int: {0:d}; hex: {0:x}; oct: {0:o}; bin: {0:b}", 42);
rspdlite::log_info("Support for floats {:03.2f}", 1.23456);
rspdlite::log_info("Positional args are {1} {0}..", "too", "supported");
rspdlite::log_info("{:<30}", "left aligned");
```

The default logging level is 'info' so all these message appear by default. As seen in
[examples/example.cpp][ex] we can also alter the logging level dynamically to show more (or fewer)
messages.

By using a `#define` also supplying a filename, we can (at compile-time) select a 'file sink'. (There
is also a rotating file sink (with a capacity limit) we could enable similarly.) Note that the
`#define` needs to precede the `#include <rspdlite>`.

```c++
#defined RSPDLITE_FILE_SINK "/tmp/my_log_file.txt"
#include <rspdlite>
```

#### From R

Following the nice user experience offered by [spdl][spdl], we similarly provide access via the
'package name colon colon' patter from R as can be seen in [examples/example.R][exR]

```r
rspdlite::log_critical("-- level to debug")
rspdlite::set_level("debug")

rspdlite::log_info("Some more at info")
rspdlite::log_error("Some error message with arg: {}", 1)
rspdlite::log_error("Some error message with more args: {} and {}", 1, "abc")

rspdlite::log_critical("-- level to error and calling example1 and example2")
rspdlite::set_level("error")
```

As for its cousin R packages, the format string here 'resembles' the full C++ format string, but
remains simpler. As we convert each argument directly to a character (then passed on to the C++
layer) we do not offer the extra formatting options available directly from C++. We have not found
this to be an issue.

### Design and Limitations

[spdlite][spdlite] is by _design and choice_ very lightweight---and _very fast_. There are
essentially no state variables, and nearly every part of behaviour is governed by _compile-time_
choices as core ability of modern C++ is to (allow to) shift as much as possible to compile-time
rather than run-time. For example the basic formatting abilities are passed through by invoking the
constructor of the relevant object.  So when we set one of the options individually (say via
`set_precision()` to change the time precision from the sane default of milliseconds to either
micro- or nanoseconds), an earlier formatting choice of also showing the thread id will fall back to
its default of 'off'. The best way around this is to use `set_format()` and _simulatenously_ set all
values one desires changes.

Similarly, while we offer the `null sink` in this package too, truly lightweight performance (as
demonstrated by the upstream benchmarks) only happen when the logging level is also set to `off`.
But that cannot easily be accomplished just by instantiating the `sink`.  (We have ideas about to
accommodate this in the R package so we may get to this.)

### C++ Usage Options

While this is an R package, we stress the 'symmetric' use from C++. Given the lightweight nature,
more advanced use from C++ is equally possible. One could for example use the (coloured) console
sink (but make sure not to use it in code going to CRAN as it will have issues with `R CMD check`),
or the rotating sink we do not (yet ?) expose---or the fact that from C++ it is easy to a)
instantiate multiple sinks (!!) or b) easily create multiple loggers at different levels or
configurations. The [spdlite][spdlite] documentation has of course more on this.

### Alternative Interface

The [tl][tl] package offers a thin shim permitting more compact access from R
and C++ via its shorter namespace and shorter function names offering
e.g. `tl::debug("Notice")` from both R and C++ with the same formatting
options as [rspdlite][rspdlite] which is used under its hood.

### Author

[Gabi Melman](https://github.com/gabime) is the main author of both [spdlog][spdlog] and
[spdlite][spdlite].

[Victor Zverovich](https://github.com/vitaut) is the main author of the embedded [fmt][fmt] library
offered as an alternative to the C++20 library `std::format`.

[Dirk Eddelbuettel](https://dirk.eddelbuettel.com) is author of this package and the R integration.

### License

[spdlog][spdlog], [spdlite][spdlite] and [fmt][fmt] are under the MIT license.

[rspdlite][rspdlite] is released under the GNU GPL, version 2 or later, just like R and Rcpp.

[spdlog]: https://github.com/gabime/spdlog
[rcppspdlog]: https://github.com/eddelbuettel/RcppSpdlog
[spdl]: https://github.com/eddelbuettel/spdl
[spdlite]: https://github.com/gabime/spdlite
[fmt]: https://github.com/fmtlib/fmt
[rspdlite]: https://github.com/eddelbuettel/rspdlite
[ex]: inst/examples/example.cpp
[exR]: inst/examples/example.R
[tl]: https://github.com/eddelbuettel/tl
