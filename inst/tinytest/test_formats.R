suppressMessages(library(rspdlite))

if (rspdlite:::cppstandard() <= 201703)
    exit_file("Skipping remaining tests")

expect_stdout(rspdlite::log_info("abc"), "^\\[[-\\.: [:digit:]]{23}\\] \\[INF\\] abc") # 23 digits in '2026-01-02 03:04:05:678' format
expect_silent(rspdlite::set_precision("us"))
expect_stdout(rspdlite::log_info("abc"), "^\\[[-\\.: [:digit:]]{26}\\] \\[INF\\] abc") # plus three for us (microsec)
expect_silent(rspdlite::set_precision("ns"))
expect_stdout(rspdlite::log_info("abc"), "^\\[[-\\.: [:digit:]]{29}\\] \\[INF\\] abc") # plus three for ns (nanosec)
expect_silent(rspdlite::set_precision("none"))
expect_stdout(rspdlite::log_info("abc"), "^\\[[-\\.: [:digit:]]{19}\\] \\[INF\\] abc") # minus 10 for none (nine digits and dot)
expect_silent(rspdlite::set_precision("ms"))
expect_stdout(rspdlite::log_info("abc"), "^\\[[-\\.: [:digit:]]{23}\\] \\[INF\\] abc") # 23 digits in '2026-01-02 03:04:05:678' format

expect_silent(rspdlite::show_date(FALSE))
expect_stdout(rspdlite::log_info("abc"), "^\\[[-\\.: [:digit:]]{12}\\] \\[INF\\] abc") # minus 11 for removal of 'yyyy-mm-dd '
expect_silent(rspdlite::show_date(TRUE))

expect_silent(rspdlite::set_name("logger"))
expect_stdout(rspdlite::log_info("abc"), "^\\[[-\\.: [:digit:]]{23}\\] \\[logger\\] \\[INF\\] abc") # 23 digits in '2026-01-02 03:04:05:678' format
expect_silent(rspdlite::set_name(""))
expect_stdout(rspdlite::log_info("abc"), "^\\[[-\\.: [:digit:]]{23}\\] \\[INF\\] abc") # minus 11 for removal of 'yyyy-mm-dd '

expect_silent(rspdlite::show_thread_id(TRUE))
expect_stdout(rspdlite::log_info("abc"), "^\\[[-\\.: [:digit:]]{23}\\] \\[.*\\] \\[INF\\] abc") # 23 digits in '2026-01-02 03:04:05:678' format
expect_silent(rspdlite::show_thread_id(FALSE))
