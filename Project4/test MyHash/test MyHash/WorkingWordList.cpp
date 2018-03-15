//
//  main.cpp
//  test WordList
//
//  Created by Jie-Yun Cheng on 3/14/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "MyHash.h"
#include "Tokenizer.h"
#include <string>
#include <vector>
#include <algorithm>

#include <functional>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cassert> //TODO remove later
using namespace std;

//////////////////////////////////// start of WordList.cpp ////////////////////////
class WordListImpl
{
public:
    
    ~WordListImpl();
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
    
private:
    
    void checkDuplicate (const string& w, vector<string>& vec);
    bool validWord(const string& w) const;
    bool validTranslation(const string& w) const;
    static string pattern(const string& s) ;
    
    bool caseInsensitiveStringCompare(const string& str1, const string& str2) const;
    bool caseInsensitiveCharCompare(const char& chr1, const char& chr2) const;
    
    MyHash<string,vector<string>> m_hash;
    vector<vector<string>*> m_todelete;
    
};

WordListImpl::~WordListImpl()
{
    for (int i = 0; i < m_todelete.size(); i++)
    {
        delete m_todelete[i];
    }
}

bool WordListImpl::caseInsensitiveStringCompare(const string& str1, const string& str2) const {
    
    if (str1.size() != str2.size())
    {
        return false;
    }
    
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2)
    {
        if (tolower(*c1) != tolower(*c2)) {
            return false;
        }
    }
    return true;
}

bool WordListImpl::caseInsensitiveCharCompare(const char& chr1, const char& chr2) const
{
    
    if ( tolower(chr1) != tolower(chr2) )
        return false;
    return true;
}

bool WordListImpl::validWord(const string& w) const
{
    for (int i=0; i < w.size(); i++)
    {
        if (!isalpha(w[i]))
            if (w[i]!='\'')
                return false;
    }
    
    return true;
}

bool WordListImpl::validTranslation(const string& w) const
{
    for (int i=0; i < w.size(); i++)
    {
        if (!isalpha(w[i]))
            if (w[i]!='\'' && w[i]!='?')
                return false;
        
    }
    
    return true;
}


void WordListImpl::checkDuplicate (const string& w, vector<string> & vec)
{
    vector<string> :: const_iterator it;
    
    it = find(vec.begin(), vec.end(), w);
    
    if (it != vec.end())
        it = vec.erase(it);
    
}


string WordListImpl::pattern(const string& s)
{
    MyHash<char, char> m_labels;
    
    string word = s;
    string upper = "";
    
    for (int i=0; i < word.size(); i++) //made to upper
    {
        char temp = toupper(word[i]);
        upper += toupper(temp);
    }
    
    const char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int count = 0;
    
    for (int i = 0; i < upper.size(); i++)
    {
        char * k = m_labels.find(upper[i]);
        
        //no valuetype associated with letter upper[i]
        if (k == nullptr)
        {
            if (isalpha(upper[i]))
            {
                m_labels.associate(upper[i], alphabets[count]);
                count++;
                
                //assert(count <= 26);
                
            }
            else if ( upper[i] == '\'')
                m_labels.associate(upper[i], '\'');
        }
        
    }
    
    string value = "";
    for (int i=0; i < upper.size(); i++)
    {
        char * temp = m_labels.find(upper[i]);
        /*
        assert (temp != nullptr);
        {
            char mapping = *temp;
            value += mapping;
        }
         */
    }
    
    return value;
}

bool WordListImpl::loadWordList(string filename)
{
    ifstream infile(filename);
    if ( ! infile )
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return false;
    }
    
    m_hash.reset();
    
    string s = "";
    string add = "";
    vector<string> words;
    
    while (getline(infile, add))
    {
        s += add + " ";
        add = "";
    }
    
    Tokenizer split(" ");
    words = split.tokenize(s);
    
    
    for (int i=0; i < words.size(); i++)
    {
        if (validWord(words[i]))
        {
            string key = pattern(words[i]);
            vector<string>* temp = m_hash.find(key);
            
            if (temp == nullptr)
            {
                temp = new vector<string>; //dynamically allocated
                m_todelete.push_back(temp); //add to vector of pointers
                temp->push_back(words[i]);
                m_hash.associate(key, *temp);
            }
            else
            {
                checkDuplicate(words[i], *temp);
                temp->push_back(words[i]);
            }
        }
        
    }
    
    return true;
}

bool WordListImpl::contains(string word) const
{
    
    string k = pattern(word);
    
    const vector<string>* vp = m_hash.find(k); //returns a vector of words with same pattern
    
    if (vp == nullptr)
        return false;
    
    else
    {
        vector<string> :: const_iterator it;
        //it = find ((*vp).begin(),(*vp).end(), upperCandidate);
        
        for (it = (*vp).begin(); it != (*vp).end(); it++)
        {
            if ( caseInsensitiveStringCompare((*it), word) )
                return true;
        }
        return false;
    }
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation)  const
{
    vector<string> vec;
    if (!validWord(cipherWord)||!validTranslation(currTranslation)||cipherWord.size()!=currTranslation.size())
        return vec;
    
    //normalize cipherWord and currTranslation for comparison
    //string cw = cipherWord;
    
    string k = pattern(cipherWord);
    
    const vector<string>* vp = m_hash.find(k);
    
    if (vp == nullptr)
        return vec;
    
    else
    {
        for (int j=0; j < currTranslation.size(); j++)
        {
            if (isalpha(currTranslation[j]) || currTranslation[j] == '?')
            {
                if (!isalpha(cipherWord[j]))
                    return vec;
            }
            else if (currTranslation[j] == '\'')
            {
                if (cipherWord[j] != '\'')
                    return vec;
            }
        }
        
        //compare current translation with each word from vector
        vector<string> :: const_iterator it;
        
        for (it = (*vp).begin(); it != (*vp).end(); it++) //iterate through words
        {
            int i = 0;
            for (; i < currTranslation.size(); i++)
            {
                if ( currTranslation[i] == '?' && !isalpha((*it)[i]) )
                    break;
                
                else if (isalpha(currTranslation[i]) || currTranslation[i] == '\'')
                    if ( !caseInsensitiveCharCompare(currTranslation[i], ((*it)[i])) )
                        break;
            }
            
            if (i == currTranslation.size())
                vec.push_back(*it);
        }
        
        return vec;
    }
    
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

//////////////////////////////////// end of WordList.cpp ////////////////////////

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

