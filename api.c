#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Bufor na zapisanie odpowiedzi
struct response_buffer {
    char *data;
    size_t size;
};

// Funkcja zwrotna do obslugi i przechowywania odpowiedzi serwera
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    struct response_buffer *response = (struct response_buffer *)userdata;
    char *new_data = realloc(response->data, response->size + total_size + 1);
    if (new_data == NULL) {
        fprintf(stderr, "Failed to allocate memory for response.\n");
        return 0;
    }
    response->data = new_data;
    memcpy(&(response->data[response->size]), ptr, total_size);
    response->size += total_size;
    response->data[response->size] = '\0'; // Zakoncz ciag znakiem null
    return total_size;
}

// Funkcja do czyszczenia i wypisywania czytelnej odpowiedzi
void clean_and_print_response(const char *response) {
    const char *key = "\"response\":\"";
    char *start = strstr(response, key);
    if (start) {
        start += strlen(key); // Przesun za klucz
        char *end = strchr(start, '"');
        if (end) {
            char output[1024];
            size_t length = end - start;
            if (length > sizeof(output) - 1) {
                length = sizeof(output) - 1;
            }
            strncpy(output, start, length);
            output[length] = '\0'; // Zakoncz ciag znakiem null
            // Usun niechciane sekwencje (np. "\u003cthink\u003e")
            const char *unwanted = "\\u003cthink\\u003e\\n\\n\\u003c/think\\u003e\\n\\n";
            char *match;
            while ((match = strstr(output, unwanted)) != NULL) {
                size_t len = strlen(unwanted);
                memmove(match, match + len, strlen(match + len) + 1); // Przesun reszte ciagu
            }
            printf("Response: %s\n", output);
        } else {
            printf("Failed to find end of 'response' field.\n");
        }
    } else {
        printf("Failed to find 'response' field in JSON.\n");
    }
}

int main() {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    // Inicjalizacja bufora odpowiedzi
    struct response_buffer response = {NULL, 0};
    char prompt[256]; // Bufor na przechowywanie danych uzytkownika
    printf("Enter your prompt: "); // Zachowano wiadomosc
    scanf("%255[^\n]", prompt); // Wczytaj do 255 znakow, konczac na nowej linii

    // Inicjalizacja CURL
    curl = curl_easy_init();
    if (curl) {
        // Ustaw adres URL dla zadania
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:11434/api/generate");
        // Okresl metode POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        // Dane JSON tworzone dynamicznie na podstawie wejscia uzytkownika
        char json_data[512];
        snprintf(json_data, sizeof(json_data), "{\"model\":\"gemma3:1b\", \"prompt\":\"%s\", \"stream\":false}", prompt);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
        // Ustaw naglowek Content-Type na application/json
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // Ustaw funkcje zwrotna zapisu do przechwytywania odpowiedzi
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Wykonaj zadanie HTTP POST
        res = curl_easy_perform(curl);
        // Sprawdz, czy wystapily bledy
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)); // Zachowano wiadomosc
        } else {
            // Parsuj i wypisz czyste pole "response" z odpowiedzi JSON
            clean_and_print_response(response.data);
        }
        // Czyszczenie
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        free(response.data); // Zwolnij bufor odpowiedzi
    } else {
        fprintf(stderr, "Failed to initialize libcurl!\n"); // Zachowano wiadomosc
    }
    return 0;
}
