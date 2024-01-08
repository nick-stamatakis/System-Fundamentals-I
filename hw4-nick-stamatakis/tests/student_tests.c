#include "global.h"
#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, name_of_test, .description="description of test") {
    // Steps of unit test go here
}
*/

/*[RUN ] base_suite::SparseMatrix_full
[----]   Full Sparse Matrix
[----] tests/unit_tests.c:65: Assertion Failed
[----]   
[----]   Return value was 4, but it should have been 3.
[----]   
[----] tests/unit_tests.c:66: Assertion Failed
[----]   
[----]   Contents of matrix incorrect. See unit_tests.c for expected values.
[----]   
[FAIL] base_suite::SparseMatrix_full: (0.00s)
libgcov profiling error:/home/student/Documents/CSE 220/hw4-nick-stamatakis/build/matrix.gcda:overwriting an existing profile data with a different timestamp
[RUN ] base_suite::SparseMatrix_full_valgrind
[----] tests/unit_tests.c:38: Assertion Failed
[----]   
[----]   Valgrind reported errors -- see tests.out/SparseMatrix_full.log
[----]   
==5367== Memcheck, a memory error detector
==5367== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==5367== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==5367== Command: ./bin/SparseMatrix_full
==5367== 
==5367== Invalid read of size 4
==5367==    at 0x10A757: SparseMatrix (matrix.c:10)
==5367==    by 0x10A62A: main (SparseMatrix_full.c:7)
==5367==  Address 0x4a980a8 is 0 bytes after a block of size 8 alloc'd
==5367==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==5367==    by 0x10B894: initializeMatrix (matrix.c:201)
==5367==    by 0x10A593: main (SparseMatrix_full.c:4)
==5367== 
==5367== Invalid read of size 4
==5367==    at 0x10A81D: SparseMatrix (matrix.c:21)
==5367==    by 0x10A62A: main (SparseMatrix_full.c:7)
==5367==  Address 0x4a980a8 is 0 bytes after a block of size 8 alloc'd
==5367==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==5367==    by 0x10B894: initializeMatrix (matrix.c:201)
==5367==    by 0x10A593: main (SparseMatrix_full.c:4)
==5367== 
==5367== 
==5367== HEAP SUMMARY:
==5367==     in use at exit: 0 bytes in 0 blocks
==5367==   total heap usage: 13 allocs, 13 frees, 1,233 bytes allocated
==5367== 
==5367== All heap blocks were freed -- no leaks are possible
==5367== 
==5367== ERROR SUMMARY: 8 errors from 2 contexts (suppressed: 0 from 0)
==5367== 
==5367== 4 errors in context 1 of 2:
==5367== Invalid read of size 4
==5367==    at 0x10A81D: SparseMatrix (matrix.c:21)
==5367==    by 0x10A62A: main (SparseMatrix_full.c:7)
==5367==  Address 0x4a980a8 is 0 bytes after a block of size 8 alloc'd
==5367==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==5367==    by 0x10B894: initializeMatrix (matrix.c:201)
==5367==    by 0x10A593: main (SparseMatrix_full.c:4)
==5367== 
==5367== 
==5367== 4 errors in context 2 of 2:
==5367== Invalid read of size 4
==5367==    at 0x10A757: SparseMatrix (matrix.c:10)
==5367==    by 0x10A62A: main (SparseMatrix_full.c:7)
==5367==  Address 0x4a980a8 is 0 bytes after a block of size 8 alloc'd
==5367==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==5367==    by 0x10B894: initializeMatrix (matrix.c:201)
==5367==    by 0x10A593: main (SparseMatrix_full.c:4)
==5367== 
==5367== ERROR SUMMARY: 8 errors from 2 contexts (suppressed: 0 from 0)
[FAIL] base_suite::SparseMatrix_full_valgrind: (0.64s)
[RUN ] base_suite::addition_case_no
[----]   Matrices are compatible for addition, but not A. A also contains garbage values
*/
