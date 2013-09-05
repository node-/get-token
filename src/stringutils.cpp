/* stringutils.cpp
 * Jake Kosberg
 *
 *
 */

#include "stringutils.h"
#include <cmath>


void StrCat(char MyString[], char CatThis[])
{
    int appendVal = StrLen(MyString)-1; // starting point for cat is length, without \0
    int i = 0;
    char ch;
    while ((ch = CatThis[i]) != '\0')
    {
        MyString[i+appendVal] = ch;
        i++;
    }
    MyString[i+appendVal] = '\0';
}

int StrLen(char* MyString)
{
    int length = 0;
    while (*MyString != '\0') {
        // loop through memory until MyString[i] is null
        MyString++; length++;
    }
    return length + 1;
    // the +1 compensates for the null character
}

void StrCpy(char* MyString, char* CopyThis)
{
    int CopyThisLen = StrLen(CopyThis);
    for (int i = 0; CopyThisLen != i; i++) // max index is the length of the copied string
    {
        *MyString = *CopyThis;
        MyString++; CopyThis++;
        // set MyString at index equal to CopyThis at index
    }
}

int StrCmp(char *MyString, char *Compare)
{
    int largestStrLen = StrLen(MyString) > StrLen(Compare) ? StrLen(MyString) : StrLen(Compare);
    // set largestStrLen to the length of whichever string has higher length
    for (int i = 0; largestStrLen != i; i++) {
        if ((*MyString != '\0' || *Compare != '\0') && (*MyString != *Compare)) {
            // if the strings aren't equal AND neither characters are NULL characters
            return *MyString > *Compare ? 1 : -1;
            // return 1 if the ascii value for MyString[i] is higher, -1 for inverse
            }
        MyString++; Compare++;
    }
    return 0;
    // return 0 if the strings match and the NULL character is reached
}

void SubStr(char* MyString, char* Sub, int start, int length)
{
    int j = 0;
    MyString += start;
    int MyStringLen = StrLen(MyString);
    for (int i = start; (i <= MyStringLen) && (j <= length - 1); i++) {
        // the Sub array will have one less index value
        // j keeps track of which iteration of the loop we're on
        // i keeps track of the index for the char we are appending to Sub from MyString
        *Sub = *MyString;
        j++; Sub++; MyString++;
    }
    *Sub = '\0';
}

int FindAny(char MyString[], char FindThese[], int pos)
{
    int i = pos;
    int MyStringLen = StrLen(MyString);
    for (; i < MyStringLen; i++)
    {
        for (int j = 0; j<StrLen(FindThese) && MyString[i] != '\0'; j++) {
            // loops through all of FindThese chars for every MyString char
            if (MyString[i] == FindThese[j]){
                return i; // return index value at this point
            }
        }
    }
    return -1; // if it wasn't found, return -1
}

// -- Overloaded Functions

int Find(char MyString[], char FindThis[], int pos)
{
    int j = 0, i = pos; // i is determined by the starting position
    // i - the index value for iterating through each character of MyString
    // j - the index value for iterating through FindThis and comparing each character to MyString
    int MyStringLen = StrLen(MyString);
    for (;i < MyStringLen; i++)
    {
        if (FindThis[j] != '\0'){ // if FindThis isn't finished
            if (MyString[i] == FindThis[j]) {
                // if the characters are the same, look at the next character
                j++;
            } else if (MyString[i] == FindThis[0]) {
                // if the chars are not equal, check if the MyString char is equal to the first FindThis char
                j = 1;
            } else {
                // start j over, continue this process until FindThis hits an esc char
                j = 0;
            }
        }
        else { // when FindThis is finished
            return i-j; // return the length of MyString minus the length of FindThis when FindThis[j] is \0
        }
    }
    // if esc char is never reached in FindThis, this point is reached
    return -1; // returns -1 if there is no match
}

int Find(char FindHere[], char target, int pos)
{
    int i = 0; // start at index pos
    int FindHereLen = StrLen(FindHere);
    for (; i < FindHereLen; i++)
    {
        if (FindHere[i] == target) {
            return i;
        }
    }
    return -1;
}

// -- End Overloaded Functions

int FindNotAny(char MyString[], char FindThese[], int pos)
{
    int i = pos;
    int MyStringLen = StrLen(MyString);
    int FindTheseLen = StrLen(FindThese);
    bool found = false;
    for (; i < MyStringLen && MyString[i] != '\0'; i++) {
        found = false;
        for (int j =0; j < FindTheseLen && FindThese[j] != '\0'; j++) {
            if (MyString[i] == FindThese[j]) {
                found = true;
            }
        }
        if (found != true) {
            return i;
        }
    }
    return -1;
}

int ToInt(char MyString[], int pos)
{
    int i = pos;
    char digits[] = "1234567890"; // all digits in a char array, iterate through it similarly to FindAny()
    int MyStringLen = StrLen(MyString);
    for (; i < MyStringLen && MyString[i] != '\0'; i++) {
        for (int j = 0; j <= 10; j++) {
            if (MyString[i] == digits[j]) {
                return CharToInt(digits[j]); // i think this might be pretty hackish, but it works lol
            }
        }
    }
    return -1;
}

int AtoI(char ConvertThis[])
{
    int returnVal = 0;
    int ConvertThisLen = StrLen(ConvertThis);
    for(int i = 0; i <= ConvertThisLen && ConvertThis[i] != '\0'; i++)
    {
        // multiply the digit by 10^(whichever place it's in... 1s, 10s, 100s etc)
        // -2 to compensate for the index's value and the null character
        returnVal += CharToInt(ConvertThis[i])*pow(10.0,ConvertThisLen-i-2);
    }
    return returnVal;
}

int CharToInt(char ch) { // converts char to int
    return ch - '0';
}

void ToLower(char MyString[]) {
    int MyStringLen = StrLen(MyString);
    for (int i = 0; i < MyStringLen; i++) {
        if ('A' <= MyString[i] && MyString[i] <= 'Z'){ // if the char is between uppercase A and Z
                MyString[i] = char(((int)MyString[i]) + 32);
                // add 32 to the ascii value of the char, making it lowercase
        }
    }
}

bool Eq(char MyString[], char Compare[]) {
    return StrCmp(MyString, Compare) == 0;
}
bool GT(char MyString[], char Compare[]) {
    return StrCmp(MyString, Compare) > 0;
}
bool LT(char MyString[], char Compare[]) {
    return StrCmp(MyString, Compare) < 0;
}

