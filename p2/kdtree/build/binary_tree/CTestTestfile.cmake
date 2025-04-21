# CMake generated Testfile for 
# Source directory: /home/dario/universidad/eedd/p2/kdtree/binary_tree
# Build directory: /home/dario/universidad/eedd/p2/kdtree/build/binary_tree
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestBTNode "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p2/kdtree/build/binary_tree//test_btree_node" "01_tests_btree_node")
set_tests_properties(TestBTNode PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p2/kdtree/binary_tree" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;23;add_test;/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;0;")
add_test(TestBTreeFoldUnfold "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p2/kdtree/build/binary_tree//test_btree" "02_tests_btree_fold_unfold")
set_tests_properties(TestBTreeFoldUnfold PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p2/kdtree/binary_tree" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;24;add_test;/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;0;")
add_test(TestBTreeHeightSize "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p2/kdtree/build/binary_tree//test_btree" "03_tests_btree_height_size")
set_tests_properties(TestBTreeHeightSize PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p2/kdtree/binary_tree" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;25;add_test;/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;0;")
add_test(TestBTreeTraversals "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p2/kdtree/build/binary_tree//test_btree" "04_tests_traversals")
set_tests_properties(TestBTreeTraversals PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p2/kdtree/binary_tree" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;26;add_test;/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;0;")
add_test(TestBTreeInOrder "/usr/bin/python3.13" "run_tests.py" "/home/dario/universidad/eedd/p2/kdtree/build/binary_tree//test_btree" "05_tests_inorder")
set_tests_properties(TestBTreeInOrder PROPERTIES  WORKING_DIRECTORY "/home/dario/universidad/eedd/p2/kdtree/binary_tree" _BACKTRACE_TRIPLES "/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;27;add_test;/home/dario/universidad/eedd/p2/kdtree/binary_tree/CMakeLists.txt;0;")
