#ifndef EXTRACT_H
#define EXTRACT_H

int extract_number(const char *input);
char *send_http_request(const char *prompt);
void filter_response_digits(char *response, int digits_needed);
int word_to_number(const char *word); // Dodano deklarację tej funkcji

#endif
