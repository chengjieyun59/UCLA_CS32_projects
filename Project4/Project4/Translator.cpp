#include "provided.h"
#include "MyHash.h"
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
    
    class selfMadeStack
    {
    public:
        selfMadeStack()
        {
            m_head = NULL;
        }
        
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
    private:
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
    };
    
    selfMadeStack m_stack;
};

TranslatorImpl::TranslatorImpl()
:m_map("??????????????????????????")
{
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if(ciphertext.size() != plaintext.size())
        return false;
    // if the new character mappings they specify, together with the current collection of character mappings, would be inconsistent, then this function must return false
    MyHash<char, char> checkConsistency;
    for(int i = 0; i < ciphertext.size(); i++)
    {
        if(!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
            return false;
        if(checkConsistency.find(ciphertext[i]) == NULL)
            checkConsistency.associate(ciphertext[i], plaintext[i]);
        else if (ciphertext[i] != *(checkConsistency.find(ciphertext[i])))
            return false;
    }
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

