
#include "substituteMyHash.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

/////////////////////////////////////// below is from translator.cpp /////////////

// const int SIZE_OF_ALPHABET = 26;
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
// const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    class Stack
    {
    public:
        Stack()
        {
            head = nullptr;
            
        }
        
        void push(string newestMap)
        {
            Node *temp = new Node(newestMap);
            if(head == NULL)
                temp->m_next = NULL;
            else
                temp->m_next = head;
            head = temp;
        }
        
        void pop()
        {
            cout << "pop from the stack" << endl;
            if (head == nullptr)
                return;
            
            Node* temp = head;
            head = head->m_next;
            delete temp;
        }
        
        string top()
        {
            if (head == nullptr)
                return "";
            else
                return head->m_map;
        }
        
    private:
        struct Node
        {
            Node(string maps)
            {    m_map = maps; }
            
            string m_map;
            Node* m_next;
        };
        
        Node* head;
    };
    
    Stack m_stackOfMaps;
    string m_currentMap;
    
    int m_pushCount;
    int m_popCount;
};

TranslatorImpl::TranslatorImpl()
{
    m_pushCount = 0;
    m_popCount = 0;
    
    m_currentMap = "??????????????????????????";
    m_stackOfMaps.push(m_currentMap);
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    //FALSE CASES
    if (ciphertext.size() != plaintext.size())
        return false;
    
    MyHash<char, char> characterMap;
    
    // if it's not the first time pushing. Never went into this...
    if (m_stackOfMaps.top() != "")
    {
        m_currentMap = m_stackOfMaps.top();
        //m_stackOfMaps.pop();
    }
    
    for (int i = 0; i < ciphertext.size(); i++)
    {
        if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
            return false;
        
        if (characterMap.find(tolower(plaintext[i])) == nullptr)
            characterMap.associate(tolower(plaintext[i]), tolower(ciphertext[i]));
        else
            if (*(characterMap.find(tolower(plaintext[i]))) != tolower(ciphertext[i]))
                return false;
    }
    
    for (int i = 0; i < ALPHABET.size(); i++)
        if (characterMap.find(tolower(ALPHABET[i])) != nullptr)
            m_currentMap[i] = *(characterMap.find(tolower(ALPHABET[i])));
    cout << "m_currentMap is: " << m_currentMap << endl;
    m_stackOfMaps.push(m_currentMap);
    m_pushCount++;
    return true;
}

bool TranslatorImpl::popMapping()
{
    if (m_popCount >= m_pushCount)
        return false;
    
    m_stackOfMaps.pop();
    m_currentMap = m_stackOfMaps.top();
    
    m_popCount++;
    return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    MyHash<char, char> characterMap;
    
    //Associate
    string translatedString;
    
    for (int i = 0; i < ciphertext.size(); i++)
    {
        // ciphertext[i] = tolower(ciphertext[i]);
        translatedString += '?';
    }
    
    for (int i = 0; i < ciphertext.size(); i++)
    {
        bool isUpper = false;
        if (isupper(ciphertext[i]))
            isUpper = true;
        for (int j = 0; j < ALPHABET.size(); j++)
        {
            if (tolower(ciphertext[i]) == ALPHABET[j])
            {
                int count = 0;
                bool addedLetter = false;
                for (int count = 0; count < m_currentMap.size(); count++)
                    if (tolower(ciphertext[i]) == m_currentMap[count])
                    {
                        char currentLetter = ALPHABET[count];
                        if (isUpper)
                            currentLetter = toupper(currentLetter);
                        translatedString[i] = currentLetter;
                        addedLetter = true;
                    }
                if (addedLetter)
                    break;
                
                if (m_currentMap[count] == '?')
                    translatedString[i] = '?';
                else if (isalpha(m_currentMap[i]))
                {
                    if (isupper(ciphertext[i]))
                        translatedString[i] = toupper(m_currentMap[i]);
                    else
                        translatedString[i];
                }
                else
                    translatedString[i] = ciphertext[i];
            }
            else if(!isalpha(ciphertext[i]))
                translatedString[i] = ciphertext[i];
        }
    }
    
    return translatedString;
}

/////////////////////////////////////// above is from translator.cpp /////////////

class TranslatorImpl;

class Translator
{
public:
    Translator();
    ~Translator();
    bool pushMapping(std::string ciphertext, std::string plaintext);
    bool popMapping();
    std::string getTranslation(const std::string& ciphertext) const;
    // We prevent an Translator object from being copied or assigned.
    Translator(const Translator&) = delete;
    Translator& operator=(const Translator&) = delete;
private:
    TranslatorImpl* m_impl;
};

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

int main()
{
    Translator t; // Define a translator object
    string secret = "Hdqlx!";
    string translated = t.getTranslation(secret);
    cout << "The translated message is: " << translated << endl; // writes The translated message is: ?????!
    
    // Submit the first collection of character mappings
    t.pushMapping("DHL", "ERD"); // D->E, H->R, L->D
    cout << t.getTranslation(secret) << endl; // writes Re?d?!
    
    // Submit a second collection of character mappings
    t.pushMapping("QX", "AY"); // Q->A, X->Y
    cout << t.getTranslation(secret) << endl; // writes Ready!
    
    // Pop the most recently pushed collection
    t.popMapping();
    cout << t.getTranslation(secret) << endl; // writes Re?d?!
    
    // Pop again
    t.popMapping();
    cout << t.getTranslation(secret) << endl; // writes ?????!
    
}
