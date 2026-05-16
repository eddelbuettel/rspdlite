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
some deliberate design choices to 'keep things simple'. Configuration is mostly at compile-time,
though logging levels can of course be adjusted at run-time.  By using an `inline` instance under
the 'one definition rule', each 'application', or here each R package including the header, gets its
own instance of the logger (even if the header is included multiple times within a package). A
simple 'file sink' for logging messages can be selected at compile time.

### Examples

#### From C++

As seen in [examples/example1.cpp](inst/examples/example1.cpp), we can use the same example from the
[spdlite][spdlite] docs:

```c++
rspdlite::info("Some more");
rspdlite::error("Some error message with arg: {}", 1);
rspdlite::warn("Easy padding in numbers like {:08d}", 12);
rspdlite::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
rspdlite::info("Support for floats {:03.2f}", 1.23456);
rspdlite::info("Positional args are {1} {0}..", "too", "supported");
rspdlite::info("{:<30}", "left aligned");
```

The default logging level is 'info' so all these message appear by default. As seen in
[examples/example2.cpp](inst/examples/example2.cpp) we can also alter the logging level dynamically
to show more (or fewer) messages.

By using a `#define` also supplying a filename, we can (at compile-time) select a 'file sink'. (There
is also a rotating file sink (with a capacity limit) we could enable similarly.) Note that the
`#define` needs to precede the `#include <rspdlite>`.

```c++
#defined RSPDLITE_FILE_SINK "/tmp/my_log_file.txt"
#include <rspdlite>
```

#### From R

Following the nice user experience offered by [spdl][spdl], we similarly provide access via the
'package name colon colon' patter from R as can be seen in [examples/example.R](inst/examples/example.R)

```r
rspdlite::critical("-- level to debug")
rspdlite::set_level("debug")

rspdlite::info("Some more at info")
rspdlite::error("Some error message with arg: {}", 1)
rspdlite::error("Some error message with more args: {} and {}", 1, "abc")

rspdlite::critical("-- level to error and calling example1 and example2")
rspdlite::set_level("error")
```

Like its cousing R packages, the format string here 'resembles' the full C++ format string, but
remains simpler. As we convert each argument directly to a character (then passed on to the C++
layer) we do not offer the extra formatting options available directly from C++. We have not found
this to be an issue.

### Author

[Gabi Melman](https://github.com/gabime) is the main author of both [spdlog][spdlog] and
[spdlite][spdlite].

[Victor Zverovich](https://github.com/vitaut) is the main author of the embedded [fmt][fmt] library
offered as a fallback.

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
