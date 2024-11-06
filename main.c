#include <stdio.h>
#include "A3.h"

int main()
{
    WordData *lexicon = NULL;
    int wordCount = 0;
    readLexiconFile("vader_lexicon.txt", &lexicon, &wordCount);

    char sentence[] = "VADER is very smart, handsome, and funny.";
    float compoundScore = calculateCompoundScore(sentence, lexicon, wordCount);
    printf("Compound score: %f\n", compoundScore);

    free(lexicon);
    return 0;
}
