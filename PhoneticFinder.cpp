#include "PhoneticFinder.hpp" //header
#include <map> // map
#include <stdexcept>//exception


namespace phonetic //our namespace
{
    //start the map(all combination)
    std::map<char, const char*> replacementCharsMap = 
    {
        {'v', "w"},
        { 'w', "v"},
        { 'b', "fp"},
        { 'f', "bp"},
        { 'p', "bf"},
        { 'g', "j"},
        { 'j', "g"},
        { 'c', "kq"},
        { 'k', "cq"},
        { 'q', "kc"},
        { 's', "z"},
        { 'z', "s"},
        { 'd', "t"},
        { 't', "d"},
        { 'o', "u"},
        { 'u', "o"},
        { 'i', "y"},
        { 'y', "i"},
    };

    //the function checks if the string starting at startIndex and ending at endIndex is equal to searchWord
    bool are_words_equal(std::string text, std::string searchWord, int startIndex, int endIndex)
    {
        int textWordLength = endIndex - startIndex; //length of the word in the text string

        if(textWordLength != searchWord.length()) { // checking if the length is not equal return false
            return false;
        }
     
        for(int i = 0; i < textWordLength; i++)
        {
            char searchWordLetterLower = tolower(searchWord[i]);
            char textLetterLower = tolower(text[startIndex + i]);
            
            if(searchWordLetterLower != textLetterLower)//if the char equal to other char
            {
                if(replacementCharsMap.count(searchWordLetterLower) == 1)//replacementCharsMap.count return 0 or 1  
                {
                    const char* replacments = replacementCharsMap[searchWordLetterLower]; // replacement 

                    bool replacementFound = false;

                    for(int j = 0; replacments[j] != '\0'; j++)//running on the replacement string
                    {
                        if(textLetterLower == replacments[j])// checking if the char equal to other char, if they are equals return true
                        {
                           replacementFound = true;
                           break; 
                        }
                    }

                    if(!replacementFound)//not found replacement return false
                    {
                        return false;
                    } 
                }
                else //replacementCharsMap.count = 0 return false
                {
                    return false;
                }              
            }
        }
        return true;
    }

    std::string find(std::string text, std::string word)
    {
        int i = 0;
	    std::string newWord;
	    if(word.length() == 0)
	    {
            throw std::invalid_argument("User can't search empty word");
	    }
        while(text[i] != '\0') // not end of the string text
        {
            if(text[i] == ' ') // space move on
            {
                ++i;
            }
            else // text[i] != ' '
            {
                int endWordIndex;
                for(endWordIndex = i; text[endWordIndex] != ' ' && text[endWordIndex] != '\0'; endWordIndex++) // endWordIndex to end of the new word on the text string
                {

                }
                
                if(are_words_equal(text, word, i, endWordIndex)) // our function is checking start index to end index for one word, if found the word return the newWord
                {
                    while(i<endWordIndex)
                    {
                        newWord += text.at(i);
                        i++;
	            }	
                    return newWord; // found the word in the text return this word in the text
                }
                else // not found the word, update the endWordIndex
                {
                    i = endWordIndex;
                }
                
            }
            
        }
        //not found the word
        throw std::invalid_argument("Did not find the word '" + word + "' in the text"); // not found word like that
        
    }
}
