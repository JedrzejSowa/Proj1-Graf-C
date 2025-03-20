#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

#define MAX_NODES 100

// Utility function to check if a position is already taken
int is_position_taken(int x, int y, int positions[][2], int count) {
    for (int i = 0; i < count; i++) {
        if (positions[i][0] == x && positions[i][1] == y) {
            return 1; // Position is already taken
        }
    }
    return 0; // Position is free
}

// Generate a random graph with nodes and non-overlapping positions
void generate_random_graph(int max_nodes) {
    srand(time(NULL));

    int num_nodes = (rand() % max_nodes) + 1; // Random number of nodes (1 to max_nodes)
    int positions[MAX_NODES][2]; // Array to store unique positions (x, y)
    int grid_size = 10;          // Define the size of the grid (e.g., 10x10)

    FILE *file = fopen("output.txt", "w");
    if (!file) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }

    fprintf(file, "Randomly generated graph:\n\n");

    for (int i = 0; i < num_nodes; i++) {
        int x, y;

        // Generate unique positions until a free one is found
        do {
            x = rand() % grid_size;
            y = rand() % grid_size;
        } while (is_position_taken(x, y, positions, i));

        // Store the unique position
        positions[i][0] = x;
        positions[i][1] = y;

        // Output the node's position
        fprintf(file, "Node %d: (%d, %d)\n", i + 1, x, y);
    }

    fclose(file);
    printf("Random graph saved in output.txt\n");
}

void generate_graph_from_response(const char *response, int digits_needed) {
    if (digits_needed % 2 != 0) {
        fprintf(stderr, "Invalid number of digits to generate graph.\n");
        return;
    }

    int num_pairs = digits_needed / 2;
    FILE *file = fopen("output.txt", "w");
    if (!file) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }

    fprintf(file, "Graph generated from response:\n\n");
    for (int i = 0; i < num_pairs; i++) {
        int x = response[i * 2] - '0';
        int y = response[i * 2 + 1] - '0';
        fprintf(file, "Node %d: (%d, %d)\n", i + 1, x, y);
    }

    fclose(file);
    printf("Graph saved in output.txt\n");
}
