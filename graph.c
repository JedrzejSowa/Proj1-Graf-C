#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "extract.h"

#define MAX_CORNERS 10

void generateGraph(int corners, int directed) {
    if (corners > MAX_CORNERS) {
        printf("This format only supports up to %d corners.\n", MAX_CORNERS);
        return;
    }

    FILE *file = fopen("output.txt", "w");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Generated Graph:\n\n");

 
    int grid[MAX_CORNERS][MAX_CORNERS];
    for (int i = 0; i < corners; i++) {
        for (int j = 0; j < corners; j++) {
            grid[i][j] = -1; 
        }
    }

   
    int startX = rand() % corners;
    int startY = rand() % corners;
    grid[startX][startY] = 0;


    for (int i = 1; i < corners; i++) {
        int placed = 0;
        while (!placed) {
            int x = rand() % corners;
            int y = rand() % corners;

            if (grid[x][y] == -1) {

                if ((x > 0 && grid[x - 1][y] != -1) ||  
                    (x < corners - 1 && grid[x + 1][y] != -1) ||  
                    (y > 0 && grid[x][y - 1] != -1) ||  
                    (y < corners - 1 && grid[x][y + 1] != -1)) {  
                    grid[x][y] = i;
                    placed = 1;
                }
            }
        }
    }


    int connections[MAX_CORNERS][MAX_CORNERS] = {0};


    if (directed) {
        for (int i = 0; i < corners; i++) {
            for (int j = 0; j < corners; j++) {
                if (grid[i][j] != -1) {

                    if (i > 0 && grid[i - 1][j] != -1 && !connections[grid[i][j]][grid[i - 1][j]]) { 
                        int direction = rand() % 3;
                        if (direction == 0) {
                            fprintf(file, "[%d] --> [%d]\n", grid[i][j], grid[i - 1][j]);
                        } else if (direction == 1) {
                            fprintf(file, "[%d] <-- [%d]\n", grid[i][j], grid[i - 1][j]);
                        } else {
                            fprintf(file, "[%d] <-> [%d]\n", grid[i][j], grid[i - 1][j]);
                        }
                        connections[grid[i][j]][grid[i - 1][j]] = 1;
                        connections[grid[i - 1][j]][grid[i][j]] = 1;
                    }
                    if (i < corners - 1 && grid[i + 1][j] != -1 && !connections[grid[i][j]][grid[i + 1][j]]) {  // Bottom
                        int direction = rand() % 3;
                        if (direction == 0) {
                            fprintf(file, "[%d] --> [%d]\n", grid[i][j], grid[i + 1][j]);
                        } else if (direction == 1) {
                            fprintf(file, "[%d] <-- [%d]\n", grid[i][j], grid[i + 1][j]);
                        } else {
                            fprintf(file, "[%d] <-> [%d]\n", grid[i][j], grid[i + 1][j]);
                        }
                        connections[grid[i][j]][grid[i + 1][j]] = 1;
                        connections[grid[i + 1][j]][grid[i][j]] = 1;
                    }
                    if (j > 0 && grid[i][j - 1] != -1 && !connections[grid[i][j]][grid[i][j - 1]]) {  // Left
                        int direction = rand() % 3;
                        if (direction == 0) {
                            fprintf(file, "[%d] --> [%d]\n", grid[i][j], grid[i][j - 1]);
                        } else if (direction == 1) {
                            fprintf(file, "[%d] <-- [%d]\n", grid[i][j], grid[i][j - 1]);
                        } else {
                            fprintf(file, "[%d] <-> [%d]\n", grid[i][j], grid[i][j - 1]);
                        }
                        connections[grid[i][j]][grid[i][j - 1]] = 1;
                        connections[grid[i][j - 1]][grid[i][j]] = 1;
                    }
                    if (j < corners - 1 && grid[i][j + 1] != -1 && !connections[grid[i][j]][grid[i][j + 1]]) {  // Right
                        int direction = rand() % 3;
                        if (direction == 0) {
                            fprintf(file, "[%d] --> [%d]\n", grid[i][j], grid[i][j + 1]);
                        } else if (direction == 1) {
                            fprintf(file, "[%d] <-- [%d]\n", grid[i][j], grid[i][j + 1]);
                        } else {
                            fprintf(file, "[%d] <-> [%d]\n", grid[i][j], grid[i][j + 1]);
                        }
                        connections[grid[i][j]][grid[i][j + 1]] = 1;
                        connections[grid[i][j + 1]][grid[i][j]] = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < corners; i++) {
        for (int j = 0; j < corners; j++) {
            if (grid[i][j] == -1) {
                fprintf(file, "[-]");
            } else {
                fprintf(file, "[%d]", grid[i][j]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Graph saved in output.txt\n");
}

int main() {
    char choice;
    int corners;
    int directed = 0;

    printf("Do you want to choose the number of corners? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        char input[256];
        printf("Enter your prompt: ");
        scanf(" %255[^\n]", input);

        corners = extract_number(input);
        if (corners == -1) {
            fprintf(stderr, "No valid number found in the prompt. Please try again.\n");
            return 1;
        }

        printf("Do you want the graph to be directed? (y/n): ");
        char directed_choice;
        scanf(" %c", &directed_choice);

        if (directed_choice == 'y' || directed_choice == 'Y') {
            directed = 1;
        }
    } else if (choice == 'n' || choice == 'N') {
        srand(time(0));
        corners = (rand() % 10) + 1;
        printf("Randomly generated number of corners: %d\n", corners);

        printf("Do you want the graph to be directed? (y/n): ");
        char directed_choice;
        scanf(" %c", &directed_choice);

        if (directed_choice == 'y' || directed_choice == 'Y') {
            directed = 1;
        }
    } else {
        fprintf(stderr, "Invalid choice. Please enter 'y' or 'n'.\n");
        return 1;
    }

    if (corners <= 0 || corners > MAX_CORNERS) {
        printf("Number of corners must be between 1 and %d!\n", MAX_CORNERS);
        return 1;
    }

    srand(time(0));
    generateGraph(corners, directed);

    return 0;
}
