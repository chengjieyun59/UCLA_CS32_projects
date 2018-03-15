//
//  main.cpp
//  test Tokenizer
//
//  Created by Jie-Yun Cheng on 3/14/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl;

class Tokenizer
{
public:
    Tokenizer(std::string separators);
    ~Tokenizer();
    std::vector<std::string> tokenize(const std::string& s) const;
    // We prevent a Tokenizer object from being copied or assigned.
    Tokenizer(const Tokenizer&) = delete;
    Tokenizer& operator=(const Tokenizer&) = delete;
private:
    TokenizerImpl* m_impl;
};

// You must not add any additional public member functions or data members to this class other than a destructor, should you need one. You may add as many private member functions or data members as you like.
class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    bool isSeparator(char pos) const;
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
:m_separator(separators)
{
    // Tokenizer t(separators); // TODO: something wrong with this?
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

int main() {
    TokenizerImpl t(" ,.!");
    
    vector<string> v = t.tokenize("This,, is a test! It's the... best!");
    // v now contains "This", "is", "a", "test", "It's", "the", and "best"
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << endl;
    
    string s = "!!!!!"; v = t.tokenize(s);
    // v is now empty
    if(v.empty())
        cout << "success!" << endl;
}
