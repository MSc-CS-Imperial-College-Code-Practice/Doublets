#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include <string>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */

// ============================================================================
// I) MAIN FUNCTIONS
// ============================================================================

// 1) VALID STEP
// Function that looks in a doublet chain if a a valid step is valid between 
// two words
bool valid_step(const char *current_word, const char *next_word) {
   
   // ****************************************************************
   // 1) Auxiliar Variables
   // ****************************************************************

   // Counter
   int number_of_different_letters = 0;
   // Length of words
   int current_word_length = strlen(current_word);
   int next_word_length = strlen(next_word);

   // ****************************************************************
   // 2) Checks
   // ****************************************************************

   // If the words have different lenght, not valid step -> Return false
   if(current_word_length != next_word_length){
      cout << "Lenght_Error" << endl;
      return false;
   }
      
   
   // Else if "current_word" or "next_word" are not a valid word in dictionary, 
   // not valid step -> Return false
   else if (!dictionary_search(next_word) || !dictionary_search(current_word)){
      cout << "Dictionary_Error" << endl;
      return false;
   }

   // Traverse through "next_word" and do cheks
   for (int i = 0; next_word[i] != '\0'; i++){
         
         // Count number of times a letter is different between "current_word"
         // "next_word"
         if (current_word[i] != next_word[i])
            number_of_different_letters++;
         
         // If there is more than a different letter, not valid step -> Return
         //  false
         if(number_of_different_letters > 1){
            cout << "Repetition_Error" << endl;
            return false;
         }
   }
   // If all validations are OK, then it is a valid -> Return true
   return true;
}

// 2) DISPLAY CHAIN
// Function that writes a given chain of words to an output and checks if
// this output was succesfully written in the output stream
bool display_chain(const char* chain[], ostream &out){

   // ****************************************************************
   // 1) Auxiliar Variables
   // ****************************************************************
   
   // Lengths of a chain and words in it
   int chain_length = getChainLenght(chain);
   int word_length = strlen(chain[0]);
   
   // Char array in lower case
   char lower_case_word[word_length];
   
   // ****************************************************************
   // 2) Checks
   // ****************************************************************

   // Check output stram. If "out" has an error don't display change -> 
   // Return false 
   if(out.fail())
      return false;

   // Traverse Chain and write to the "out" ostream
   for (int i = 0; i < chain_length ; i++){
      // Print capital letters for first and last word
      if (i == 0 || i == chain_length - 1)
         out << chain[i] << endl;
      // Print lower case letters for rest of the words
      else{
         copyWord(chain[i], lower_case_word); 
         toLowerCase(lower_case_word);
         out << lower_case_word << endl;
      } 
   }
   // If all validations are OK, then return true
   return true;
}

// 3) VALID CHAIN
// Function that checks if a given doublet chain is a valid chain
bool valid_chain(const char* chain[]){
   
   // ****************************************************************
   // 1) Auxiliar Variables
   // ****************************************************************

   // Length of chain
   int chain_length = getChainLenght(chain);

   // ****************************************************************
   // 2) Auxiliar Variables
   // ****************************************************************

   // A change must consist of 2 words at least. If not, return false
   if (chain_length < 2){
      cout << "One_Single_Word_Error" << endl;
      return false;
   }

   // Traverse the chain
   for (int i = 1; i < chain_length ; i++){
      
      // A chain cannot have duplicate words. If not, return false
      for (int j = i; j < chain_length; j++){
         if(strcmp(chain[i-1],chain[j]) == 0){
            cout << "Duplicate_Words_Error" << endl;
            return false;
         }
      }
      // A step between a word and the next word has to be valid. If not,
      // return false
      if(!valid_step(chain[i-1],chain[i])){
         cout << "Invalid_Step_Error" << endl;
         return false;
      }
   }
   // If all validations are OK, then return true
   return true;
}

// 4) FIND CHAIN
// Function that ....

bool find_chain(const char* start_word, const char* target_word, 
   const char* answer_chain[], int max_steps){

   // ****************************************************************
   // 1) Auxiliar Variables
   // ****************************************************************

   static bool init_flag = true;
   static int words_used;
   static int word_length;
   if(init_flag){
      cout << "RESETING..." << endl;
      words_used = 0;
      word_length = strlen(start_word);
      answer_chain[0] = start_word;
      for(int i = 1; answer_chain[i] == NULL; i++)
         answer_chain[0] = "";
      init_flag = false;
   }

   // ****************************************************************
   // 2) Recursive Solution
   // ****************************************************************

   // Base case -> All attemps for forming a doublet chain are used
   if(words_used > max_steps - 1){
      cout << "Max Words used..."<< endl;
      return false;
   }
   
   // Recursive case -> Solve for different combinations of chains through
   // a recursive implementation
   char *temp_word = new char[word_length];
   strcpy(temp_word, start_word);
   cout << "Temp Word and Start Word are: " << temp_word 
        << " | " << start_word<< endl;  
   for(int i=0; i < word_length; i++){
      for(char letter = 'A'; letter <= 'Z'; letter++){
         temp_word[i] = letter;
         cout << "--------------------------------" << endl;
         cout << "Words testing..."<< endl;
         cout << start_word << endl;
         cout << temp_word << endl;
         cout << endl;

         cout << "Words in chain before change..."<< endl;
         display_chain(answer_chain, cout);
         cout << endl;
          
         words_used++;
         answer_chain[words_used] = temp_word;
         
         if(strcmp(temp_word,target_word) == 0){
            cout << "Valid chain found" << endl;
            init_flag = true;
            return true;
         }

         cout << "Words in chain after change..."<< endl;
         display_chain(answer_chain, cout);
         cout << endl;

         if(valid_chain(answer_chain)){
            cout << "Is Valid Chain! Continue..." << endl;
            if(find_chain(temp_word, target_word, answer_chain, max_steps)){
               return true;
            }
         }
         
         cout << "Deleting..." << endl;
         //delete answer_chain[words_used];
         answer_chain[words_used] = NULL;
         words_used--;
   
      }
      temp_word[i] = start_word[i];
   }
   

   // If no combination is found -> Return false
   return false;

}

// ============================================================================
// II) Auxiliar Functions
// ============================================================================

int getChainLenght(const char* chain[]){
   int counter = 0;
   for (int i = 0; chain[i] != NULL; i++)
      counter++;
   return counter;
}

void toLowerCase(char* word){
   for (int i = 0; word[i] != '\0'; i++)
       word[i] = tolower(word[i]);
}

void copyWord(const char* word_original, char* word_copy){

   for (int i = 0; word_original[i] != '\0'; i++)
      word_copy[i] = word_original[i];
}
