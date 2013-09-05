/* gettoken.cpp
 * Jake Kosberg
 *
 *
 */

// -- Headers

#include <iostream> // for console io
#include <fstream>  // for file io
#include "stringutils.h"

using namespace std;

// -- Function Declaration

// Quicksorts data
void quickSort(char** tokenList, char alltokenTypes[], int left, int right);
// removes all duplicates in a list
void dedupe(char** tokenList, int tokenCountList[], char allTokenTypes[],int& tokenCount);

// Creates a substring of characters from MyString
// that can be found inside a character
// set, starting from a particular position.
int Zorg(char MyString[], char CharSet[], char Substring[], int pos); 
// Determines what type of token a character represents,
// and creates an array containing the token.
bool GetToken(char Block[], char Token[], char &tokenType, int& pos); 

// -- Globals

char Alpha[] = "'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char Num[] = "1234567890";
char Punc[] = "’'[](){}<>~!.-?‘’“”'\";/\\·,$&*@•^+|";
char Whitespace[] = " \n\t";

// -- Main Function

int main ()
{

    char * allTokens[TOKEN_SIZE];   // MD Array of all tokens
    char Token[TOKEN_SIZE];         // Token char array, temp
    char Block[BLOCK_SIZE];         // Full unannotated text
    char alltokenTypes[TTYPE_SIZE]; // Array of all token types, matching indexes to allTokens
    char tokenType;                 // Token type, temp

    int tokenCountList[TTYPE_SIZE] = {0};
    int tokenCount = 0;
    int pos = 0; // start at first pos

    ifstream readFile;
    readFile.open("unannotated.txt");
    for (int i = 0; !readFile.eof(); i++) {
        readFile.read(Block, sizeof(Block));
    }
    readFile.close();

    while (GetToken(Block, Token, tokenType, pos)) // This processes every Token by changing pos
    {
        // Ignore whitespace type
        if (tokenType != 'w') {
            allTokens[tokenCount] = new char [StrLen(Token)];   // Create a new char array under allTokens
            StrCpy(allTokens[tokenCount], Token);               // Copies data into the allocated char array
            alltokenTypes[tokenCount] = tokenType;              // Append the token type to alltokenTypes
            tokenCount++; // basically index
        }
    }
    tokenCount -= 1; // prevents reading overflow of data -- potential segfault

    // Write newly obtained data to cout and 'annotated_sorted.txt'
    ofstream writeFile;
    writeFile.open("annotated_sorted.txt");
    
    quickSort(allTokens, alltokenTypes, 0, tokenCount);
    dedupe(allTokens, tokenCountList, alltokenTypes, tokenCount);

    cout << "| Count\t| Type\t|  Token" << endl;
    cout << "|_______|_______|_______" << endl;
    writeFile << "Count\tType\tToken" << endl;
    for (int j = 0; j < tokenCount; j++) {
        int block = allTokens[j][0];
        cout << "|  " << tokenCountList[j] << "\t"
             << "|  " << alltokenTypes[j] << "\t"
             << "|  '" << allTokens[j] << "'" << endl;
        writeFile << tokenCountList[j] << "\t"
             << alltokenTypes[j] << "\t"
             << allTokens[j] << endl;
    }
    writeFile.close();

    return 0;
}

void quickSort(char **tokenList, char alltokenTypes[], int left, int right) {
    int i = left, j = right;
    char * tmpToken;
    char tmpTokenType;
    char * pivot = tokenList[(left + right) / 2];
    // Straight-forward recursive quicksort algorithm

    while (i <= j) {
        while (StrCmp(tokenList[i], pivot) < 0) // uses StrCmp
            i++;
        while (StrCmp(tokenList[j], pivot) > 0)
            j--;
        if (i <= j) {
            tmpToken = tokenList[i];
            tokenList[i] = tokenList[j];
            tokenList[j] = tmpToken;

            tmpTokenType = alltokenTypes[i];
            alltokenTypes[i] = alltokenTypes[j];
            alltokenTypes[j] = tmpTokenType;
            i++; j--;
        }
    }
    if (left < j)
        quickSort(tokenList, alltokenTypes, left, j);
    if (i < right)
        quickSort(tokenList, alltokenTypes, i, right);
}

void dedupe(char **tokenList, int tokenCountList[], char alltokenTypes[], int &tokenCount)
{
    char * ch;
    char * tmpList[TOKEN_SIZE];
    char tmpTokenTypes[TTYPE_SIZE];
    bool killValue[tokenCount];
    bool ascending = true;
    int killCount = 0;
    int j, i = 0;
    killValue[0] = false;

    /* This algorithm basically goes through the data and marks the indexes for the duplicates.
     * Then the index descends and each index is checked to see if it already exists, and if it does,
     * add to the new list. Then it goes over the new list and writes it into memory. Perhaps it
     * could be faster if I was better with pointers
     */
    while (!(!ascending && i == -1)) // when i is descending and it hits -1, stop looping
    {
        if (i == tokenCount) {
            ascending = false;
            j = tokenCount - killCount;
        }
        if (ascending) {
            if (StrCmp(tokenList[i], tokenList[i+1]) == 0) {
                killValue[i] = true;
                killCount++;
            } else {
                killValue[i] = false;
            }
            i++;
        } else {
            if (killValue[i] == false) {
                tmpList[j] = new char [sizeof tokenList[i]]; // allocates space for char in new list
                StrCpy(tmpList[j], tokenList[i]); // copies into new position
                tmpTokenTypes[j] = alltokenTypes[i];
                j--;
                tokenCountList[j+1] = 1;
            } else {
                tokenCountList[j+1]++;
            }
            i--;
        }
    }
    tokenCount -= killCount;
    // loop over tmp new list
    for (i = 0; i <= tokenCount; i++) {
        alltokenTypes[i] = tmpTokenTypes[i];
        tokenList[i] = tmpList[i];
    }
}

int Zorg(char MyString[], char CharSet[], char Substring[], int pos)
{
    int start = FindAny(MyString, CharSet, pos);
    int end = FindNotAny(MyString, CharSet, start);
    int length = end - start;
    SubStr(MyString, Substring, start, length);
    return end;
}

bool GetToken(char Block[], char Token[], char &tokenType, int &pos)
{
    int BlockLen = StrLen(Block);

    if (pos == -1 || pos >= BlockLen) {
        return false;
    } // stops when pos is -1 or if position exceeds length of block
    int tokenVal = Token[0];

    // Logic for Substring creation
    if (Find(Alpha, Block[pos], pos) != -1) {       // if type Alpha
        tokenType = 'a';
        pos = Zorg(Block, Alpha, Token, pos);
    } else if (Find(Num, Block[pos], pos) != -1) {  // if type Num
        tokenType = 'n';
        pos = Zorg(Block, Num, Token, pos);
    } else if (Find(Punc, Block[pos], pos) != -1) { // if type Punc
        tokenType = 'p';
        pos = Zorg(Block, Punc, Token, pos);
    } else if (Find(Whitespace, Block[pos], pos) != -1 || Block[pos] < 32) { // if type Whitespace
        tokenType = 'w';
        pos = Zorg(Block, Whitespace, Token, pos);
    }
    return true;
}
