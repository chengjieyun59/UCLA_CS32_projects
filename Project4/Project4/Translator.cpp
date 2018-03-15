#include "provided.h"
#include <string>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    string m_map;
    struct Node
    {
        // constructor
        Node(string maps)
        :m_data(maps){
            m_next = NULL;
        }
        
        // in each node
        string m_data;
        Node* m_next;
    };
    Node* m_head;
    
    void push(string maps)
    {
        Node *temp = new Node(maps);
        if(m_head == NULL)
            temp->m_next = NULL;
        else
            temp->m_next = m_head;
        m_head = temp;
    }
    
    void pop()
    {
        if(m_head == NULL)
            return;
        Node *temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
    
    string top()
    {
        if(m_head == NULL)
            return "";
        return m_head->m_data;
    }
};

TranslatorImpl::TranslatorImpl()
:m_map("??????????????????????????")
{
    m_head = NULL;
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if(ciphertext.size() != plaintext.size())
        return false;
    for(int i = 0; i < ciphertext.size(); i++)
    {
        if(!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
            return false;
    }
    // TODO: if the new character mappings they specify, together with the current collection of character mappings, would be inconsistent, then this function must return false
    
    
    
    return true;  // This compiles, but may not be correct
}

bool TranslatorImpl::popMapping()
{
    return false;  // This compiles, but may not be correct
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    return ""; // This compiles, but may not be correct
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}

