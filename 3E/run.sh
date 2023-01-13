make clean;
make;
valgrind --leak-check=full --track-origins=yes ./proj3E 3E_input.pnm 3E_output.pnm

