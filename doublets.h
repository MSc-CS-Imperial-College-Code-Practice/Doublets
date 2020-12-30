/*  This pre-supplied function looks up a given word in the dictionary
    of approved words. It is assumed that the input word is in uppercase.
    The function returns true if the word is in the dictionary.
    Otherwise returns false. */

bool dictionary_search(const char *word);

/* add your function prototypes here */

// 1) Main Functions Prototypes
bool valid_step(const char *current_word, const char *next_word);
bool display_chain(const char* chain[], ostream &out);
bool valid_chain(const char* chain[]);
bool find_chain(const char *start_word, const char *target_word, 
   const char* answer_chain[], int max_steps);


// 2) Auxiliar Functions Prototypes
int getChainLenght(const char* chain[]);
void toLowerCase(char* word);
void copyWord(const char* word_original, char* word_copy);
bool isChainComplete(const char* chain[], int length);