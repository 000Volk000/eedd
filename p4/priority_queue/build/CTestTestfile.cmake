# CMake generated Testfile for 
# Source directory: /home/dario/universidad/eedd/p4/priority_queue
# Build directory: /home/dario/universidad/eedd/p4/priority_queue/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestHeapEditing "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p4/priority_queue/build//test_heap" "01_heap_editing")
set_tests_properties(TestHeapEditing PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p4/priority_queue" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p4/priority_queue/CMakeLists.txt;28;add_test;/home/dario/universidad/eedd/p4/priority_queue/CMakeLists.txt;0;")
add_test(TestHeapify "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p4/priority_queue/build//test_heap" "02_heapify")
set_tests_properties(TestHeapify PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p4/priority_queue" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p4/priority_queue/CMakeLists.txt;29;add_test;/home/dario/universidad/eedd/p4/priority_queue/CMakeLists.txt;0;")
add_test(TestHeapsort "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p4/priority_queue/build//test_heap" "03_heapsort")
set_tests_properties(TestHeapsort PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p4/priority_queue" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p4/priority_queue/CMakeLists.txt;30;add_test;/home/dario/universidad/eedd/p4/priority_queue/CMakeLists.txt;0;")
add_test(TestPQueue "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p4/priority_queue/build//test_pqueue" "04_pqueue")
set_tests_properties(TestPQueue PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p4/priority_queue" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p4/priority_queue/CMakeLists.txt;31;add_test;/home/dario/universidad/eedd/p4/priority_queue/CMakeLists.txt;0;")
