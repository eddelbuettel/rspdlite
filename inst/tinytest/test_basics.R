suppressMessages(library(rspdlite))

expect_equal(rspdlite::get_level(), "info")

if (rspdlite:::cppstandard() <= 201703)
    exit_file("Skipping remaining tests")

## default level is info so these two are silent
expect_equal(rspdlite::get_level(), "info")
expect_stdout(rspdlite::log_trace("abc"), "")
expect_stdout(rspdlite::log_debug("abc"), "")
## and these create output
## regexp is a little involved as we need to \\ protect [ and ]
## first part is for [2026-01-02 03:04.05.678] digits, dash, dot, colon
## second part the log level as a single char inside [ ]
expect_stdout(rspdlite::log_info("abc"),               "^\\[[-\\.: [:digit:]]+\\] \\[INF\\] abc")
expect_stdout(rspdlite::log_warn("def {}", 1.23),      "^\\[[-\\.: [:digit:]]+\\] \\[WRN\\] def 1.23")
expect_stdout(rspdlite::log_error("ghi {}", 42),       "^\\[[-\\.: [:digit:]]+\\] \\[ERR\\] ghi 42")
expect_stdout(rspdlite::log_critical("jkl {}", "xyz"), "^\\[[-\\.: [:digit:]]+\\] \\[CRT\\] jkl xyz")


## if we set level to 'trace' all generate output
expect_silent(rspdlite::set_level("trace"))
expect_equal(rspdlite::get_level(), "trace")
expect_stdout(rspdlite::log_trace("abc"),               "^\\[[-\\.: [:digit:]]+\\] \\[TRC\\] abc")
expect_stdout(rspdlite::log_debug("def {}", "a"),       "^\\[[-\\.: [:digit:]]+\\] \\[DBG\\] def a")
expect_stdout(rspdlite::log_info("ghi {} {}", 42L, 42), "^\\[[-\\.: [:digit:]]+\\] \\[INF\\] ghi 42 42")
expect_stdout(rspdlite::log_warn("jkl {}", 1.23),       "^\\[[-\\.: [:digit:]]+\\] \\[WRN\\] jkl 1.23")
expect_stdout(rspdlite::log_error("mno {}", 42),        "^\\[[-\\.: [:digit:]]+\\] \\[ERR\\] mno 42")
expect_stdout(rspdlite::log_critical("pqr {}", "xyz"),  "^\\[[-\\.: [:digit:]]+\\] \\[CRT\\] pqr xyz")


## if we set level to 'off' none generate output
expect_silent(rspdlite::set_level("off"))
expect_equal(rspdlite::get_level(), "off")
expect_stdout(rspdlite::log_trace("abc"), "")
expect_stdout(rspdlite::log_debug("abc"), "")
expect_stdout(rspdlite::log_info("abc"), "")
expect_stdout(rspdlite::log_warn("abc"), "")
expect_stdout(rspdlite::log_error("abc"), "")
expect_stdout(rspdlite::log_critical("abc"), "")

## reset level
expect_silent(rspdlite::set_level("info"))
