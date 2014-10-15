//
//  main.cpp
//  Assignment2 - C++
//
//  Created by Hassuni on 10/5/14.
//  Copyright (c) 2014 Hussein Abou Nassif Mourad. All rights reserved.
//


#include<iostream>
#include<cstring>
#include<string>
using namespace std;

/* Globally defined constants
 */
const int MAX_WORD_SIZE = 20;

/* Words structure
 *
 *	This has three member variables list: which will contain a list
 *	of cstrings, size: the max number of words the list can store and
 *	num_words: the number of cstrings in list.
 */

struct Words {
    unsigned int num_words;		// Number of words currently in list
    unsigned int max_words; // The total size allocated to the list.
    char **list;		    // The list storing the words
};



/* Function prototypes:
 *	To be implemented
 */

Words * newList(const unsigned int max_words);
Words * newList(const char words[]);
int deleteList(Words *p_w);
int printList(Words *p_w);
int appendList(Words *p_w, const char words[]);
int appendList(Words *dst, const Words *src);
char* findWord(const Words *p_w, const char word[]);
int removeWord(Words *p_w, const char word[]);



/* Main function
 *
 * Note the newList and deleteList functions must be implemented before appendList so the
 * calls to appendList are initally commented out.
 * Your code should work with the main below. Including the appendList functionality that is initially commented out.
 */


int main()
{
    Words *pokemon, *tb;
    char *word;
    int ok=0;
    string poke = "charmeleon mewtwo pikachu charmander squirtle caterpie raichu butterfree abra kadabra alakazam slowpoke spoink";
    char team_a[] = "rayquaza mew snorlax";
    string team_b = "weavile shuckle ampharos toxicroak mrmime";
    
    
    cout << poke.c_str() << endl;
    pokemon=newList(5); // 	Words * newList(const unsigned int max_words);
    ok=deleteList(pokemon); // int deleteList(Words *p_w);
    cout << "OK? "<< ok << endl;
    pokemon=newList(poke.c_str()); // Words * newList(const char words[]);
    tb=newList(team_a); // Words * newList(const char words[]);
    cout << "*pokemon" << endl;
    printList(pokemon); // int printList(Words *p_w);
    cout << "*tb"<< endl;
    printList(tb); // int printList(Words *p_w);
    
     //
     //	Note the newList and deleteList functions must be implemented before appendList so the
     // calls to appendList are initally commented out.
     
     ok=appendList(tb,team_b.c_str());  // int appendList(Words *p_w, const char words[]);
     cout << "*tb"<< endl;
     printList(tb); // int printList(Words *p_w);
     ok=appendList(pokemon,tb); // int appendList(Words *dst, const Words *src);
     cout << "*pokemon"<< endl;
     printList(pokemon); // int printList(Words *p_w);
     word=findWord(pokemon,"charmeleon"); // char* findWord(const Words *p_w, const char word[]);
     cout << "*word "<< *word << " word " << word << " address " << &word << endl;
     ok=removeWord(pokemon,"squirtle"); // int removeWord(Words *p_w, const char word[]);
     cout << "*pokemon"<< endl;
     printList(pokemon); // int printList(Words *p_w);

    return 0;
}

/* Function: newList
 *
 *
 *	Takes the max_words of the list and creates a new Words
 *	with the given max_words without assigning any words, sets
 *	num_words to zero. returns the new list to the calling function.
 *	max_words must be greater than zero, otherwise newList returns
 *	NULL.
 */

Words * newList(const unsigned int max_words)
{
    if (max_words < 1)
        return NULL;
    
    // Allocate list
    Words * p_w = new Words;
    
    // Initializing the Words struct fields
    p_w->num_words = 0;
    p_w->max_words = max_words;
    p_w->list = new char*[max_words];
    
    // Return the new word list
    return p_w;
    
}

/* Function: newList
 *
 *	Overloaded version of newList, this one takes a character
 *	array with words separated by spaces, for example:
 *
 *	"charmeleon mewtwo pikachu charmander squirtle caterpie raichu butterfree abra kadabra alakazam slowpoke spoink"
 *
 *	has four words.  This newList will allocate enough space
 *	for the words, then the list will be initialized to those
 *	words and returns the list to the calling function. If
 *	words is empty, newList does nothing and returns NULL.
 */

Words * newList(const char words[])
{
    // duplicate the words to handle literal input
    char *dup = strdup(words);
    int len = strlen(dup);
    
    // Can't allocate zero memory
    if (len == 0)
        return NULL;
    
    // Set pointer to null
    Words *p_w = NULL;
    
    // Initialize spaces and c to 0
    int c = 0, spaces = 0;
    
    // Go through words, and find how many spaces are in it
    while (c != len) {
        if (words[c] == ' ') {
            spaces += 1;
            c++;
        }
        c++;
    }
    
    // Add 1 since there is 1 more word
    spaces++;
    
    // Initialize the list of words
    p_w = newList(spaces);

    // Create the cstr
    char * cstr = new char[len];
    
    // Copy the words to cstr
    std::strcpy(cstr, words);
    
    // cstr now contains a c-string copy of str
    int count = 0, numW = 0;
    char * p = std::strtok(cstr, " ");
    while (p != 0)
    {
        p_w->list[count] = p; // Place the char into the array
        p = std::strtok(NULL, " "); // Split by the space delemeter
        count = count + 1; // Increase the count to fill the array
        numW++; // Adding string to array cell
    }
    
    // Update number of words
    p_w->num_words = numW;
    
    // Return the words struct
    return p_w;
}

/* Function: deleteList
 *
 *	Takes a dynamically allocated Words and deletes
 *	the list and then the Words itself, returns 0.
 *	If the Words is NULL deleteList does nothing and
 *	returns -1;
 */
int deleteList(Words *p_w)
{
    if(p_w == NULL)
        return -1;
    
    // Delete the list itself
    delete[] p_w->list;
    
    // Delete the words itself
    delete p_w;
    
    // Return 0 since we deleted the Words
    return 0;
    
}

/* Function: printList
 *
 *	Prints the words in the Words on a single Line
 *	with a single space between words. There is no
 *	space after the last word, but there is a newline,
 *	returns 0 for successful print. If p_w is NULL,
 *	printList does nothing returns -1.
 */

int printList(Words *p_w)
{
    
    //
    cout << "The Pokemons are: " << endl;
    
    if(p_w == NULL)
        return -1;
    
    // Print the list of words in the Words struct
    for (int i = 0; i < p_w->num_words; i++) {
        if (i == p_w->num_words - 1) {
            cout << p_w->list[i] << endl << endl;
        }
        else {
            cout << p_w->list[i] << " ";
        }
    }
    
    // Return that the print has occured
    return 0;
}

/* Function: appendList
 *
 *	Takes a Words and a character array consisting of words
 *	separated by spaces, for example:
 *
 *	"charmander squirtle caterpie raichu"
 *
 *	Contains four words. appendList will take the Words
 *	and append these words to list.  If the Words does not
 *	have enough space, appendList will dynamically allocate
 *	more space to list to allow these new words to fit.
 *	Returns the number of words appended.  If words is empty
 *	or if p_w is NULL then appendList does nothing and returns -1.
 */

int appendList(Words *p_w, const char words[])
{
    // duplicate the words to handle literal input
    char *dup = strdup(words);
    int len = strlen(dup);
    
    // Check if either is null or 0
    if(p_w == NULL || len == 0)
        return -1;

    // Initialize spaces and c to 0
    int c = 0, word_count = 0;
    
    // Word count
    while (c != len) {
        if (words[c] == ' ') {
            word_count += 1;
            c++;
        }
        c++;
    }
    
    // The total words
    word_count++;
    
    // Array of the words received
    char **temp = new char*[word_count];
    
    // The cstr
    char * cstr = new char[len];
    
    // Copy the str
    std::strcpy(cstr, words);
    
    // cstr now contains a c-string copy of str
    int count = 0, numW = 0;
    char * p = std::strtok (cstr, " ");
    while (p != 0)
    {
        temp[count] = p; // Place the char into the array
        //     std::cout << p << '\n'; output to make sure its right
        p = std::strtok(NULL, " "); // Split by the space delemeter
        count = count + 1; // Increase the count to fill the array
        numW++; // Adding string to array cell
    }
    
    // How much available space
    if (p_w->num_words + word_count <= p_w->max_words) {
        int index = p_w->num_words;
        for (int i = 0; index < p_w->max_words; i++, index++) {
            p_w->list[index] = temp[i];
            
        }
    }
    else {
        // New list with new size
        char **temp2 = new char*[p_w->num_words + word_count];
        
        // Transfer everything from old list to new one
        for (int i = 0; i < p_w->max_words; i++) {
            temp2[i] = p_w->list[i];
        }
        
        // Update max words
        p_w->max_words = (p_w->num_words + word_count);
        
        // Add new words into it
        int pointer = p_w->num_words;
        for (int i = 0; pointer < p_w->max_words; i++, pointer++) {
            temp2[pointer] = temp[i];
        }
        
        p_w->num_words += word_count;
        
        // Point to the new temp
        p_w->list = temp2;
    }
    
    // Return how many words were appended
    return word_count;
}

/* Function: appendList
 *
 *	Takes two Wordss, appends the contents of src
 *	to dst.  If dst does not have enough space
 *	appendList should dynamically allocate additional space
 *	then append the contents of src to dst, returns
 *	0 on success.  If either Words is NULL appendList does
 *	nothing and returns -1.
 */

int appendList(Words *dst, const Words *src)
{
    if(dst == NULL || src == NULL)
        return -1;
    
    // index where to start adding
    int index = dst->num_words;
    
    // Update number of words
    int newNum = dst->num_words + src->num_words;
    
    // Array of the words received
    char **temp = new char*[newNum];
    
    // Check if there is space
    if (dst->num_words + src->num_words <= dst->max_words) {
        for (int i = 0; i < src->num_words; i++) {
            dst->list[index] = src->list[i];
        }
    }
    else {
        // Move everything from dst to new array list
        for (int i = 0; i < dst->num_words; i++) {
            temp[i] = dst->list[i];
        }
        
        // Now move everything from src to dst
        for(int i = 0; index < newNum; i++, index++) {
            temp[index] = src->list[i];
        }
        
        
    }
    
    // Assign new list to temp we already defined
    dst->list = temp;
    dst->num_words = index;
    dst->max_words = index;
    
    
    // Return 0 if appending was successful
    return 0;
}

/* Function: findWord
 *
 *	Finds the first occurrence of the word in the Words
 *	returns a pointer to that word in the list.  Otherwise
 *	returns NULL. If p_w is NULL return NULL
 */

char* findWord(const Words *p_w, const char word[])
{
    // Find the word address
    for(int i = 0; i < p_w->num_words; i++) {
        if (strcmp(p_w->list[i], word)) {
            return p_w->list[i - 1];
        }
    }
    
    // Return NULL since we didn't find the word
    return NULL;
}


/* Function: removeWord
 *	
 *	If p_w is null, returns -1.  Otherwise, searches for every 
 *	occurrence of word[], and removes that word of the list, returns 
 *	the number of words removed.
 *	
 */

int removeWord(Words *p_w, const char word[])
{
    if(p_w == NULL)
        return -1;
    
    // How many words are removed
    int num_removed = 0;
    
    // Go through the list and find the word
    for (int i = 0; i < p_w->num_words; i++) {
        if (!(strcmp(p_w->list[i], word))) {
            p_w->list[i] = ""; // Remove the word
            num_removed += 1;
        }
    }
    
    // Return how many of that words were removed
    return num_removed;
}


