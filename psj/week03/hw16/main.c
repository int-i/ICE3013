#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("Enter a sentence\n");
    char sentence[100];
    fgets(sentence, 100, stdin);
    printf("You entered %s\n", sentence);
    char* words[100];
    char* word = strtok(sentence, " ");
    int word_count = 0;
    while (word != NULL) {
        words[word_count] = (char*) malloc(sizeof(char) * (strlen(word) + 1));
        strcpy(words[word_count], word);
        word_count += 1;
        word = strtok(NULL, " ");
    }
    printf("There were %d words\n", word_count);
    for (int i = 0; i < word_count; i += 1) {
        printf("%s\n", words[i]);
    }
    printf("The original sentence was: ");
    for (int i = 0; i < word_count; i += 1) {
        printf("%s ", words[i]);
    }
    return 0;
}
