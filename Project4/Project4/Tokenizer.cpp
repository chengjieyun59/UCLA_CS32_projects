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
    bool isSeparator(char pos) const;
    string m_buffer;
    string m_token;
    string m_separator;
};

bool TokenizerImpl::isSeparator(char pos) const
{
    for(int i = 0; i < m_separator.length(); i++)
    {
        if(pos == m_separator[i])
            return true;
    }
    return false;
}

// The Tokenizer constructor must initialize a new Tokenizer object. When you construct a Tokenizer object, you pass in a list of separators, e.g., " ,.$-!;".
TokenizerImpl::TokenizerImpl(string separators)
:m_buffer(""), m_token(""), m_separator(separators)
{
    Tokenizer t(separators);
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    vector<string> tokens;
    string token;
    
    for(int i = 0; i < s.length(); i++)
    {
        char pos = s[i];
        // record each full word
        while(!isSeparator(pos))
        {
            token += pos;
            i++;
        }
        // add that full word to the vector
        tokens.push_back(token);
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

