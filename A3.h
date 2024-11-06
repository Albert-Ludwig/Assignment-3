#define ARRAY_SIZE 10
#define MAX_STRING_LENGTH 50 // Adjust if needed

typedef struct
{
    char word[MAX_STRING_LENGTH];
    float value1;             // Mean sentiment value
    float value2;             // Standard deviation
    int intArray[ARRAY_SIZE]; // Sentiment distribution array
} WordData;

void readLexiconFile(const char *filename, WordData **lexicon, int *wordCount);
float calculateCompoundScore(const char *sentence, WordData *lexicon, int wordCount);
