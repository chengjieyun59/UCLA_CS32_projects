#include "provided.h"
#include "MyHash.h"
// #include "substituteMyHash.h"
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

template<typename KeyType, typename ValueType>
class MyHash;
class Translator;

// Your WordList implementation must use your MyHash class template in the implementation of its data structures and must not use any STL containers as data members, although you may use string, vector, list, and array in template arguments to your MyHash class template. Within the implementations of your WordList member functions, you must not use any STL containers other than string, vector, list, and array. You must use your MyHash class template for any map-like data structures.
class WordListImpl
{
public:
    WordListImpl();
    ~WordListImpl();
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<char, char> charMap;
    MyHash<string, bool> containWord;
    MyHash<string, vector<string>> patternwordlist; // map to capitalized A to Z. Pattern, and the word
    string patternTranslator(const string word) const;
};

WordListImpl::WordListImpl()
{}

WordListImpl::~WordListImpl()
{}

bool WordListImpl::loadWordList(string filename)
{
    patternwordlist.reset();
    ifstream infile(filename);
    // path: "/Users/jycheng/Desktop/CS 32/UCLA_CS32_projects/Project4/wordlist.txt"
    if(! infile)
        return false; // cannot open the file
    string eachWord;
    vector<string> allWords;
    bool doesIgnore = false;
    
    while(getline(infile, eachWord))
    {
        for(int i = 0; i < eachWord.size(); i++)
        {
            if(eachWord[i] != '\'' && !isalpha(eachWord[i])) // not a letter or an apostrophe
                doesIgnore = true;
        }
        if(!doesIgnore)
        {
            containWord.associate(eachWord, true);
            string translatedPattern = patternTranslator(eachWord);
            vector<string>* linkedlist = patternwordlist.find(translatedPattern);
            
            vector<string> temp;
            temp.push_back(eachWord);
            
            if(linkedlist != NULL)
            {
                linkedlist->push_back(eachWord);
                patternwordlist.associate(translatedPattern, *linkedlist);
                // m_allWords.push_back(eachWord);
            }
            else
                patternwordlist.associate(translatedPattern, temp);
        }
        eachWord = "";
    }
    return true;
}

bool WordListImpl::contains(string word) const
{
    string lowercase_word = "";
    for(int i = 0; i < word.size(); i++)
        lowercase_word += tolower(word[i]);
    return containWord.find(lowercase_word);
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    MyHash<char, char> charMap;
    string patternCipherWord = patternTranslator(cipherWord);
    vector<string> linkedlist = *(patternwordlist.find(patternCipherWord));
    
    if (cipherWord.size() != currTranslation.size())
        return vector<string>();
    
    for(int i = 0; i < cipherWord.size() && i < currTranslation.size(); i++)
    {
        if (isalpha(currTranslation[i]) && charMap.find(cipherWord[i]) == nullptr)
            charMap.associate(cipherWord[i], currTranslation[i]);
        if((isalpha(currTranslation[i]) && currTranslation[i] != *(charMap.find(cipherWord[i]))) ||
           (isalpha(currTranslation[i]) && !isalpha(cipherWord[i])) ||
           (currTranslation[i] == '?' && !isalpha(cipherWord[i])) ||
           (currTranslation[i] == '\'' && cipherWord[i] != '\'') ||
           (!isalpha(cipherWord[i]) && cipherWord[i] != '\''))
            return vector<string>();
    }
    for(vector<string>::iterator index = linkedlist.begin(); index != linkedlist.end(); )
    {
        bool doesMatch = false;
        string possibleWord = *index;
        for (int i = 0; i < possibleWord.size(); i++)
        {
            if (currTranslation[i] == '?')
                continue;
            if (tolower(currTranslation[i]) != tolower(possibleWord[i]))
                doesMatch = true;
        }
        if (doesMatch)
            index = linkedlist.erase(index);
        else
            index++;
    }
    return linkedlist;
}

string WordListImpl::patternTranslator(const string word) const
{
    string result = "";
    string match = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < word.size(); i++)
    {
        bool hasOccured = false;
        for(int j = 0; j <= i; j++)
        {
            if(i != j && word[i] == word[j])
            {
                hasOccured = true;
                result += match[j];
            }
        }
        if(hasOccured == false)
            result += match[i];
    }
    return result;
}

//***** hash functions for string, int, and char *****
// may call from our MyHash class to obtain an unsigned int value between 0 and roughly 4 billion
unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
    return m_impl->findCandidates(cipherWord, currTranslation);
}

