#include "provided.h"
#include "MyHash.h"
// #include "substituteMyHash.h"
#include <string>
#include <vector>
#include <functional>
using namespace std;

template<typename KeyType, typename ValueType>
class MyHash;

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
    MyHash<string, vector<string>> m_wordlist;
};

WordListImpl::WordListImpl()
{
    
}

WordListImpl::~WordListImpl()
{
    
}

bool WordListImpl::loadWordList(string filename)
{
    
    
    return false;  // This compiles, but may not be correct
}

bool WordListImpl::contains(string word) const
{
    return false; // This compiles, but may not be correct
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    return vector<string>();  // This compiles, but may not be correct
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

