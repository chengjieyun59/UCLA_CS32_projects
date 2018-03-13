#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    bool isSeparator(char pos);
    string m_buffer;
    string m_token;
    string m_separator;
};

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
    
    /* pseudocode
     while haven't exhausted the string yet
        while (!isSeparator(pos))
            token += pos;
            pos++;
        tokens.push_back(token);
     */
    
    return tokens;  // This compiles, but may not be correct
}

bool TokenizerImpl::isSeparator(char pos)
{
    // todo
    return false;
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

