make
valgrind -q --leak-check=full --show-leak-kinds=all ./fdf maps/test_maps/10-70.fdf
valgrind -q --leak-check=full --show-leak-kinds=all ./fdf maps/test_maps/20-60.fdf
