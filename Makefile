CC = gcc
CFLAGS = -Wall -Werror

test_adjacency_list:
	$(CC) $(CFLAGS) -DUSE_LIST_IMPLEMENTATION test/test_graph.c src/adjacency_list.c -o test_adjacency_list.o

test_adjacency_matrix:
	$(CC) $(CFLAGS) -DUSE_MATRIX_IMPLEMENTATION test/test_graph.c src/adjacency_matrix.c -o test_adjacency_matrix.o

test_dfs_list:
	$(CC) $(CFLAGS) -DUSE_LIST_IMPLEMENTATION test/test_dfs.c src/dfs.c src/adjacency_list.c -o test_dfs_list.o

test_dfs_matrix:
	$(CC) $(CFLAGS) -DUSE_MATRIX_IMPLEMENTATION test/test_dfs.c src/dfs.c src/adjacency_matrix.c -o test_dfs_matrix.o

test_bfs_list:
	$(CC) $(CFLAGS) -DUSE_LIST_IMPLEMENTATION test/test_bfs.c src/bfs.c src/queue.c src/adjacency_list.c -o test_bfs_list.o

test_bfs_matrix:
	$(CC) $(CFLAGS) -DUSE_MATRIX_IMPLEMENTATION test/test_bfs.c src/bfs.c src/queue.c src/adjacency_matrix.c -o test_bfs_matrix.o

clean:
	rm -f *.o
