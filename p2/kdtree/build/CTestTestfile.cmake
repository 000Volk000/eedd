# CMake generated Testfile for 
# Source directory: /home/dario/universidad/eedd/p2/kdtree
# Build directory: /home/dario/universidad/eedd/p2/kdtree/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestCreateKDTree "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p2/kdtree/build//test_kdtree" "01_tests_create_kdtree")
set_tests_properties(TestCreateKDTree PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p2/kdtree" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p2/kdtree/CMakeLists.txt;31;add_test;/home/dario/universidad/eedd/p2/kdtree/CMakeLists.txt;0;")
add_test(TestKDTreeNearestL1 "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p2/kdtree/build//test_kdtree" "02_tests_find_nn_L1")
set_tests_properties(TestKDTreeNearestL1 PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p2/kdtree" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p2/kdtree/CMakeLists.txt;32;add_test;/home/dario/universidad/eedd/p2/kdtree/CMakeLists.txt;0;")
add_test(TestKDTreeNearestL2 "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p2/kdtree/build//test_kdtree" "03_tests_find_nn_L2")
set_tests_properties(TestKDTreeNearestL2 PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p2/kdtree" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p2/kdtree/CMakeLists.txt;33;add_test;/home/dario/universidad/eedd/p2/kdtree/CMakeLists.txt;0;")
subdirs("pattern")
subdirs("binary_tree")
