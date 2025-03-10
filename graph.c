#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Maksymalna liczba rogów
#define MAX_CORNERS 10

void generateGraph(int corners) {
    if (corners > MAX_CORNERS) {
        printf("This format only supports up to %d corners.\n", MAX_CORNERS);
        return;
    }

    FILE *file = fopen("output.txt", "w");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    // Wygenerowany graf
    fprintf(file, "Generated Graph:\n\n");

    // Inicjalizacja siatki z -1 (puste miejsca)
    int grid[MAX_CORNERS][MAX_CORNERS];
    for (int i = 0; i < corners; i++) {
        for (int j = 0; j < corners; j++) {
            grid[i][j] = -1;
        }
    }

    // Losowe umieszczenie pierwszego rogu
    int startX = rand() % corners;
    int startY = rand() % corners;
    grid[startX][startY] = 0;

    // Umieszczanie pozostalych rogów z zapewnieniem polaczenia przez sasiadow
    for (int i = 1; i < corners; i++) {
        int placed = 0;
        while (!placed) {
            int x = rand() % corners; // Indeks wiersza
            int y = rand() % corners; // Indeks kolumny

            if (grid[x][y] == -1) {
                // Sprawdz, czy jest polaczony z istniejacym rogiem
                if ((x > 0 && grid[x - 1][y] != -1) ||  // Nad
                    (x < corners - 1 && grid[x + 1][y] != -1) ||  // Pod
                    (y > 0 && grid[x][y - 1] != -1) ||  // Lewo
                    (y < corners - 1 && grid[x][y + 1] != -1)) {  // Prawo
                    grid[x][y] = i;
                    placed = 1;
                }
            }
        }
    }

    // Tablica do sledzenia wygenerowanych polaczen
    int connections[MAX_CORNERS][MAX_CORNERS] = {0};

    // Dodanie losowych strzalek miedzy niepustymi rogami
    for (int i = 0; i < corners; i++) {
        for (int j = 0; j < corners; j++) {
            if (grid[i][j] != -1) {
                // Sprawdz niepuste sasiady i losowo dodaj strzalke
                if (i > 0 && grid[i - 1][j] != -1 && !connections[grid[i][j]][grid[i - 1][j]]) {  // Nad
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
                if (i < corners - 1 && grid[i + 1][j] != -1 && !connections[grid[i][j]][grid[i + 1][j]]) {  // Pod
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
                if (j > 0 && grid[i][j - 1] != -1 && !connections[grid[i][j]][grid[i][j - 1]]) {  // Lewo
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
                if (j < corners - 1 && grid[i][j + 1] != -1 && !connections[grid[i][j]][grid[i][j + 1]]) {  // Prawo
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

    // Wypisanie siatki do pliku
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
    int corners;
    printf("Enter the number of corners (max 10): ");
    scanf("%d", &corners);

    if (corners <= 0 || corners > MAX_CORNERS) {
        printf("Number of corners must be between 1 and %d!\n", MAX_CORNERS);
        return 1;
    }

    srand(time(0));  // Losowanie ziarna dla generatora liczb losowych
    generateGraph(corners);

    return 0;
}
