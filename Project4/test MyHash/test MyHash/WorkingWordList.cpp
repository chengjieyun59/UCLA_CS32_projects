//
//  main.cpp
//  test WordList
//
//  Created by Jie-Yun Cheng on 3/14/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "MyHash.h"
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

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

class WordList
{
public:
    WordList();
    ~WordList();
    bool loadWordList(std::string filename);
    bool contains(std::string word) const;
    std::vector<std::string> findCandidates(std::string cipherWord, std::string currTranslation) const;
    // We prevent a WordList object from being copied or assigned.
    WordList(const WordList&) = delete;
    WordList& operator=(const WordList&) = delete;
private:
    WordListImpl* m_impl;
};

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

int main() {
    WordList wl;
    if ( ! wl.loadWordList("/Users/jycheng/Desktop/CS 32/UCLA_CS32_projects/Project4/wordlist.txt"))
    {
        cout << "Unable to load word list" << endl;
        return -1;
    }
    cout << "Wordlist loaded!" << endl;
    if (wl.contains("onomatopoeia"))
        cout << "I found onomatopoeia!" << endl;
    else
        cout << "Onomatopoeia is not in the word list!" << endl;
    
    string cipher = "xyqbbq";
    string decodedSoFar = "?r????";
    vector<string> v = wl.findCandidates(cipher, decodedSoFar);
    if (v.empty())
        cout << "No matches found" << endl;
    else
    {
        cout << "Found these matches:" << endl;
        for (size_t k = 0; k < v.size(); k++)
            cout << v[k] << endl; // writes grotto and troppo
    }
}
