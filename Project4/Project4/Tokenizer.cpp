#include "provided.h"
#include <string>
#include <vector>
using namespace std;

// You must not add any additional public member functions or data members to this class other than a destructor, should you need one. You may add as many private member functions or data members as you like.
class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    bool isSeparator(const char pos) const;
    string m_separator;
};

bool TokenizerImpl::isSeparator(const char pos) const
{
    for(int i = 0; i < m_separator.size(); i++)
    {
        if(pos == m_separator[i])
            return true;
    }
    return false;
}

// The Tokenizer constructor must initialize a new Tokenizer object. When you construct a Tokenizer object, you pass in a list of separators, e.g., " ,.$-!;".
TokenizerImpl::TokenizerImpl(string separators)
:m_separator(separators)
{}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    vector<string> tokens;
    string token;
    
    for(int i = 0; i < s.size(); i++)
    {
        char pos = s[i];
        // record each full word
        if(!isSeparator(pos))
        {
            token += pos;
            continue;
        }
        // add that full word to the vector
        if(token != "")
            tokens.push_back(token);
        token = "";
    }
    return tokens;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
