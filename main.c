#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extract.h"
#include "graph.h"

int main() {
    char choice;
    printf("Do you want to choose how the graph is generated? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        char prompt[1024];
        printf("Enter your prompt: ");
        scanf(" %1023[^\n]", prompt);

        int corners = extract_number(prompt);
        if (corners == -1) {
            fprintf(stderr, "No valid number found in the prompt. Please try again.\n");
            return 1;
        }

        char *response = send_http_request(prompt);
        if (!response) {
            fprintf(stderr, "Failed to fetch response from server.\n");
            return 1;
        }

        int digits_needed = corners * 2;
        filter_response_digits(response, digits_needed);
        generate_graph_from_response(response, digits_needed);

        free(response);
    } else if (choice == 'n' || choice == 'N') {
        printf("Generating random graph...\n");
        generate_random_graph(10); // Generate a random graph with up to 10 nodes
    } else {
        fprintf(stderr, "Invalid choice. Please enter 'y' or 'n'.\n");
        return 1;
    }

    return 0;
}
