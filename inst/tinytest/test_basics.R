library(rspdlite)

expect_stdout(rspdlite::info("abc"), "\\[I\\] abc$")
