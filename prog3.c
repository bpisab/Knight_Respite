/* binarySearch.c
 *    Binary search example.
 *
 * Running the program looks like:
     There were 40437 words in the dictionary, with max length 21.
     Enter word to be found: entropy
     The word "entropy" was found at position 12129
 
 and again:
     There were 40437 words in the dictionary, with max length 21.
     Enter word to be found: glorp
     The word "glorp" was not found.
 */
#include <stdio.h>
#include <string.h>   // for string length
#include <stdlib.h>   // for exit()

const int NumberOfWordsInDictionary = 40437;         // Number of words in the dictionary
const int MaxWordSize = 21 + 1;                      // Maximum size of any word in the dictionary, + 1 for null
const char DictionaryFileName[] = "dictionary.txt";  // File name for where dictionary words are found


void displayIdentifyingInformation()
{
	printf("Jonathan Munoz & Boris Pisabaj\n");
	printf("I forgot what else goes here\n\n");
}

// Use binary search to look up the word in the dictionary array, returning index if found, -1 otherwise
int binarySearch( const char searchWord[], 				  // word to be looked up
                  const char dictionary[][MaxWordSize],	  // the dictionary of words
                  int numberOfDictionaryWords)		      // number of words in the dictionary
{
    int low, mid, high;     // array indices for binary search
    int searchResult = -1;  // Stores index of word if search succeeded, else -1
    
    low = 0;
    high = numberOfDictionaryWords - 1;
    while ( low <= high)  {
        mid = (low + high) / 2;
        // searchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = strcmp( searchWord, dictionary[ mid]);
        if ( searchResult == 0)
            return mid; // Word IS in dictionary, so return the index where the word was found
        else if (searchResult < 0)
            high = mid - 1; // word should be located prior to mid location
        else
            low = mid + 1; // word should be located after mid location
    }
    
    return -1; // Word was not found
}

// Prints out # of words in dictionary and how long the longest word is
void readWordsInFromDictionaryFile(FILE *pInputFile, char dictionary[ ][ MaxWordSize])
{
    int index = 0;      // index of dictionary word being read
    int maxWordLength = 0;
    
    // Open file
    pInputFile = fopen(DictionaryFileName, "r");
    
    if (pInputFile == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", DictionaryFileName);
        exit(-1);
    }
    
    // Keep reading words while there are any
    while( fscanf(pInputFile, "%s", dictionary[ index]) != EOF) {
        int tempLength = (int)strlen( dictionary[ index]);
        if (tempLength > maxWordLength) {
            maxWordLength = tempLength;
        }
        index++;
    }
    
    printf("There were %d words in the dictionary, with max length %d. \n", index, maxWordLength);
    fclose( pInputFile);   // close the dictionary file
}


int main()
{
	displayIdentifyingInformation();

    char dictionary[ NumberOfWordsInDictionary][ MaxWordSize];
    char ikeaList[100][MaxWordSize];//i get errors when i dont put stuff in these brackets so i put some junk in there i guess
    
    // To test the program without a dictionary file , use the line below instead of the one above
    //    and at the top of the program change NumberOfWordsInDictionary to 7.
    // char dictionary[NumberOfWordsInDictionary][MaxWordSize] ={"apple", "boy", "car", "dog", "elephant", "frank", "gross"};
    
    char lookupWord[ MaxWordSize];
    FILE *pInputFile;          // file pointer
    
    pInputFile = fopen("IKEAwords.txt", "r");
    if (pInputFile == NULL) //if the file didnt open, then give up
	{
        printf("Can't open %s. Verify it is in correct location\n", "IKEAwords.txt");
        exit(-1); //leaves main (the -1 just means its an error)
    }
    
    int index, maxWordLength;
    while( fscanf(pInputFile, "%s", dictionary[ index]) != EOF)//supposed to print out all the ikeawords that are in the dictionary
	{
        int tempLength = (int)strlen( ikeaList[ index]);
        if (tempLength > maxWordLength)
            maxWordLength = tempLength;
        
        int indexIKEA = -1;
    	indexIKEA = binarySearch( lookupWord, dictionary, NumberOfWordsInDictionary);
    	if(indexIKEA != -1)
    		printf("%s\n", dictionary[index]);
    	
        index++;
    }
    
    fclose(pInputFile);
    
    //readWordsInFromDictionaryFile( pInputFile, dictionary);
    
    /* This chunk of code is for searching a word in the dictionary file
    
    printf("Enter word to be found: ");
    scanf("%s", lookupWord);   // name of an array is *already* an address, so we don't need &
    
    // Find index of word in dictionary
    int index = -1;
    index = binarySearch( lookupWord, dictionary, NumberOfWordsInDictionary);
    
    // Display results
    if( index != -1) {
        // word was found, so display it
        printf("The word \"%s\" was found at position %d\n", dictionary[ index], index);
    }
    else {
        printf("The word \"%s\" was not found. \n", lookupWord);
    }*/
    
    return 0;  
}
