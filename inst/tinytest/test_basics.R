suppressMessages(library(rspdlite))

## default level is info so these two are silent
expect_equal(rspdlite::get_level(), "info")
expect_silent(rspdlite::trace("abc"))
expect_silent(rspdlite::debug("abc"))
## and these create output
expect_stdout(rspdlite::info("abc"), "?I? abc$")
expect_stdout(rspdlite::warn("def {}", 1.23), "?W? def 1.23$")
expect_stdout(rspdlite::error("ghi {}", 42), "?E? ghi 42$")
expect_stdout(rspdlite::critical("jkl {}", "xyz"), "?C? jkl xyz$")


## if we set level to 'trace' all generate output
expect_silent(rspdlite::set_level("trace"))
expect_equal(rspdlite::get_level(), "trace")
expect_stdout(rspdlite::trace("abc"), "?T? abc$")
expect_stdout(rspdlite::debug("def {}", "a"), "?D? def a$")
expect_stdout(rspdlite::info("ghi {} {}", 42L, 42), "?I? ghi 42 42$")
expect_stdout(rspdlite::warn("jkl {}", 1.23), "?W? jkl 1.23$")
expect_stdout(rspdlite::error("mno {}", 42), "?E? mno 42$")
expect_stdout(rspdlite::critical("pqr {}", "xyz"), "?C? pqr xyz$")


## if we set level to 'off' none generate output
expect_silent(rspdlite::set_level("trace"))
expect_equal(rspdlite::get_level(), "trace")
expect_silent(rspdlite::trace("abc"))
expect_silent(rspdlite::debug("abc"))
expect_silent(rspdlite::info("abc"))
expect_silent(rspdlite::warn("abc"))
expect_silent(rspdlite::error("abc"))
expect_silent(rspdlite::critical("abc"))
