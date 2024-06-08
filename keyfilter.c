#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 101
#define MAX_RESULTS 1000

void make_upper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
    str[strlen(str)] = '\0';
}

void sort_array(char arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap the characters if they are out of order.
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int find_match(char *line, char *city){
    for (int i = 0; city[i] != '\0' ; i++) {
        if (line[i] != city[i]) {
            return 0;
        }
    }
    return 1;
}

void make_unique(char str[]) {
    // If the string is empty or has only one character, it's already unique.
    int len = strlen(str);
    if (len <= 1) {
        return;
    }
    
    int tail = 1;
    for (int i = 1; i < len; i++) {
        int j;
        for (j = 0; j < tail; j++) {
            // Character is a duplicate, break the inner loop.
            if (str[i] == str[j]) {
                break; 
            }
        }
        // If no duplicate is found, append the character to the unique portion of the string.
        if (j == tail) {
            str[tail] = str[i];
            tail++;
        }
    }
    str[tail] = '\0'; 
}


// Function to find matching strings in the lines read from stdin with the given city (case-insensitive)
void find_cities(const char *input) {
    char line[MAX_STR_LEN];
    char results[MAX_RESULTS][MAX_STR_LEN];
    int resultCount = 0;
    char city[MAX_STR_LEN];

    // Make a copy of the input string and convert it to uppercase
    strcpy(city, input);
    make_upper(city);

    while (fgets(line, MAX_STR_LEN, stdin)) {
        int lineLength = strlen(line);
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            // Remove the newline character from the end of the line
            line[lineLength - 1] = '\0';
        }

        // convert the line to uppercase for case-insensitive comparison
        make_upper(line);

        // if there is a match, add the line to the results array
        if (find_match(line, city)) {
            if (resultCount < MAX_RESULTS) {
                strcpy(results[resultCount], line);
                resultCount++;
            }
        }
    }

    if (resultCount == 0) {
        printf("Not found\n");
    } else if (resultCount == 1) {
        printf("Found: %s\n", results[0]);
    } else {
        // make an array of recommended chars from the results
        char recommendedchars[MAX_STR_LEN];
        for (int i = 0; i < resultCount; i++) {
            recommendedchars[i] = results[i][strlen(city)];
        }
        recommendedchars[resultCount] = '\0';

        // make the array unique and sort it
        make_unique(recommendedchars);
        sort_array(recommendedchars, strlen(recommendedchars));

        printf("Enable: %s\n", recommendedchars);
    }
}

void print_all(){
    char line[MAX_STR_LEN];
    char recommended_chars[MAX_RESULTS];
    int i = 0;
    while (fgets(line, sizeof(line), stdin)) {
        int lineLength = strlen(line);
        // Remove the newline character from the end of the line
        if (lineLength > 0 && line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }
        recommended_chars[i++] = line[0];
    }
    recommended_chars[i] = '\0';
    // make the array unique and sort it
    make_unique(recommended_chars);
    sort_array(recommended_chars, strlen(recommended_chars));
    printf("Enable: %s\n", recommended_chars);
}

int main(int argc, char *argv[]) {
    if (argc == 1){
        print_all();
        return 0;
    }
    else if (argc == 2){
        find_cities(argv[1]);
        return 0;
    }
    else{
        fprintf(stderr, "too many arguments provided\n");
        return 1;
    }
}
