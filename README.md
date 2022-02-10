# matrix_multiplication_threads
Matrix Multiplication
It is required to implement two variations of this algorithm:
1. The computation of each element of the output matrix happens in a thread.
2. The computation of each row of the output matrix happens in a thread.
For both variations, you have to compute the elapsed time for each of them, compare
them and justify your answer.
The program should read two input matrices from a file in the following format:

[number of rows of 1st matrix] [number of columns of 1st matrix]
1st matrix entries
[number of rows of 2nd matrix] [number of columns of 2nd matrix]
2nd matrix entries

Note: [] for clarity
example input:

3 5
1 -2 3 4 5
1 2 -3 4 5
-1 2 3 4 5
5 4
-1 2 3 4
1 -2 3 4
1 2 -3 4
1 2 3 -4
-1 -2 -3 -4

output format:

[result matrix entries]
END1 [elapsed time of procedure 1]
[result matrix entries]
END2 [elapsed time of procedure 2]
