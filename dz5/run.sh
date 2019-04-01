make clean_data
valgrind --tool=memcheck --leak-check=full --log-file=valgrind_info.log ./test.x
lcov --capture --directory . --output-file VVector.info
genhtml VVector.info --output-directory covinfo