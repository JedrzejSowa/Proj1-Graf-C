#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include "extract.h"

struct response_buffer {
    char *data;
    size_t size;
};

// Callback function for handling server responses
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
    response->data[response->size] = '\0';
    return total_size;
}

// Function to extract a number from a string
int extract_number(const char *input) {
    char word[16];
    const char *ptr = input;
    while (*ptr) {
        if (isdigit(*ptr)) {
            return atoi(ptr);
        }
        if (isalpha(*ptr)) {
            int i = 0;
            while (isalpha(*ptr) && i < (int)(sizeof(word) - 1)) {
                word[i++] = *ptr;
                ptr++;
            }
            word[i] = '\0';

            int number = word_to_number(word);
            if (number != -1) {
                return number;
            }
        } else {
            ptr++;
        }
    }
    return -1;
}

// Function to send an HTTP request
char *send_http_request(const char *prompt) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    struct response_buffer response = {NULL, 0};

    curl = curl_easy_init();
    if (curl) {
        char json_data[2048];
        snprintf(json_data, sizeof(json_data),
                 "{\"model\":\"gemma3:1b\", \"prompt\":\"%s in format A(x,y)\", \"stream\":false}", prompt);
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:11434/api/generate");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(response.data);
            return NULL;
        }
        return response.data;
    } else {
        fprintf(stderr, "Failed to initialize libcurl!\n");
        return NULL;
    }
}

// Function to filter response digits
void filter_response_digits(char *response, int digits_needed) {
    char *write_ptr = response;
    int digit_count = 0;

    for (char *read_ptr = response; *read_ptr != '\0'; read_ptr++) {
        if (isdigit(*read_ptr)) {
            *write_ptr++ = *read_ptr;
            digit_count++;
            if (digit_count == digits_needed) {
                break;
            }
        }
    }
    *write_ptr = '\0';
}

// Utility function to map words to numbers
int word_to_number(const char *word) {
    if (strcasecmp(word, "zero") == 0) return 0;
    if (strcasecmp(word, "one") == 0) return 1;
    if (strcasecmp(word, "two") == 0) return 2;
    if (strcasecmp(word, "three") == 0) return 3;
    if (strcasecmp(word, "four") == 0) return 4;
    if (strcasecmp(word, "five") == 0) return 5;
    if (strcasecmp(word, "six") == 0) return 6;
    if (strcasecmp(word, "seven") == 0) return 7;
    if (strcasecmp(word, "eight") == 0) return 8;
    if (strcasecmp(word, "nine") == 0) return 9;
    if (strcasecmp(word, "ten") == 0) return 10;
    return -1;
}
