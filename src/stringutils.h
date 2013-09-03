/* stringutils.h
 * Jake Kosberg
 *
 *
 */

#ifndef _stringutils_h
#define _stringutils_h 1


#define BLOCK_SIZE 2048 // size of the block array
#define TOKEN_SIZE 2048  // size of a single token
#define TTYPE_SIZE 2048  // size of token medata array

int StrLen(char MyString[]);                    // return length of MyString
int StrCmp(char MyString[], char Compare[]);    // compare two strings
void StrCpy(char MyString[], char CopyThis[]);  // CopyThis into MyString
void StrCat(char MyString[], char CatThis[]);   // CatThis to the end of MyString

// create substring of MyString with a certain length and starting position
void SubStr(char MyString[], char Sub[], int start, int length);
// return location of FindThis in MyString
int Find(char MyString[], char FindThis[], int pos);
// find a target character starting at a particular position
int Find(char FindHere[], char target, int pos);
// return position of first occurence of anything in MyString, in FindThese
int FindAny(char MyString[], char FindThese[], int pos);
// position of first occurence of anything in MyString, not in FindThese
int FindNotAny(char MyString[], char FindThese[], int pos);

// additional functions to include:
int ToInt(char MyString[], int pos);        // return first int in MyString starting from a particular position
int AtoI(char ConvertThis[]);               // convert array of characters to an integer
int CharToInt(char ch);                     // convert array of characters to an integer
void ToLower(char MyString[]);              // makes every character in an array lowercase
bool Eq(char MyString[], char Compare[]);   // true if MyString == Compare
bool GT(char MyString[], char Compare[]);   // true if MyString > Compare
bool LT(char MyString[], char Compare[]);   // true if MyString < Compare

#endif
