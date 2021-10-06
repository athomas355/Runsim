Description:

How To Use:

Successes:

Issues/Bugs:

TODO list:
    1) Make a Makefile compiles two source files
    2) Create semaphore
    2) Request to raise semaphore and block
    3) Lower semaphone
    4) Create shared memory
    5) Write to shared memory
    6) Read from shared memory
    7) fork arbitrary number of testsim
    8) Automate testing

Test Cases:
    # of instances of testsim < number of liceses
    # of instances of testsim == number of licenses
    # number of instances of test > number of licenses
    # timeout
    # Share memory not available
    # semaphore failure?
        # testsim ends prematurely (stretch test)
    # Easy to understand error messages from perror
    # Makefile clean and builds all executables
        # Compiler has no warnings and code is pedantic?  (-Werror  -Wpedantic
    #README.md


Useful links:
    https://www.geeksforgeeks.org/bakery-algorithm-in-process-synchronization/
    https://en.wikipedia.org/wiki/Lamport%27s_bakery_algorithm
    https://stackoverflow.com/questions/42295035/implementation-of-bakery-algorithm-in-c-for-forked-processes
    https://elexfocus.com/interprocess-communication-shared-memory-with-linux-in-c/
    https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c#5656561
    https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
    https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html#Overall-Options describes what the -c option dopes
    https://www.man7.org/linux/man-pages/man3/shm_open.3.html
    https://stackoverflow.com/questions/3673226/how-to-print-time-in-format-2009-08-10-181754-811#3673291
    https://linux.die.net/man/3/strcat
    https://linux.die.net/man/3/fputs
    https://www.geeksforgeeks.org/fork-system-call/
    https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
    https://manpages.ubuntu.com/manpages/xenial/man2/execve.2.html
    https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-itoa-convert-int-into-string
    https://linux.die.net/man/3/sprintf