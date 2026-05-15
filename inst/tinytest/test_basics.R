suppressMessages(library(rspdlite))

## default level is info so these two are silent
expect_equal(rspdlite::get_level(), "info")
expect_silent(rspdlite::trace("abc"))
expect_silent(rspdlite::debug("abc"))
## and these create output
expect_stdout(rspdlite::info("abc"), "\\[I\\] abc$")
expect_stdout(rspdlite::warn("def {}", 1.23), "\\[W\\] def 1.23$")
expect_stdout(rspdlite::error("ghi {}", 42), "\\[E\\] ghi 42$")
expect_stdout(rspdlite::critical("jkl {}", "xyz"), "\\[C\\] jkl xyz$")
