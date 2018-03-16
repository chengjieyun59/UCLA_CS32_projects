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
    class Stack
    {
    public:
        Stack()
        :m_head(nullptr)
        {}
        string top()
        {
            if (m_head != nullptr)
                return m_head->m_map;
            else
                return "";
        }
        void push(string newMap)
        {
            Node *temp = new Node(newMap);
            if(m_head == nullptr)
                temp->m_next = nullptr;
            else
                temp->m_next = m_head;
            m_head = temp;
        }
        void pop()
        {
            if (m_head == nullptr)
                return;
            Node* temp = m_head;
            m_head = m_head->m_next;
            delete temp;
        }
    private:
        struct Node
        {
            Node(string maps)
            :m_map(maps)
            {}
            string m_map;
            Node* m_next;
        };
        Node* m_head;
    };
    string m_currMap;
    int m_numOfPush, m_numOfPop;
    const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    MyHash<char, char> m_charMap;
    Stack m_stackOfMaps;
};

TranslatorImpl::TranslatorImpl()
:m_numOfPush(0), m_numOfPop(0), m_currMap("??????????????????????????")
{
    m_stackOfMaps.push(m_currMap);
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if (ciphertext.size() != plaintext.size())
        return false;
    if (m_stackOfMaps.top() != "")
        m_currMap = m_stackOfMaps.top();
    for (int i = 0; i < ciphertext.size(); i++)
    {
        if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
            return false;
        if (m_charMap.find(toupper(plaintext[i])) == nullptr)
            m_charMap.associate(toupper(plaintext[i]), toupper(ciphertext[i]));
        else if (*(m_charMap.find(toupper(plaintext[i]))) != toupper(ciphertext[i]))
            return false;
    }
    for (int i = 0; i < ABC.size(); i++)
        if (m_charMap.find(toupper(ABC[i])) != nullptr)
            m_currMap[i] = *(m_charMap.find(toupper(ABC[i])));
    m_stackOfMaps.push(m_currMap);
    m_numOfPush++;
    return true;
}

bool TranslatorImpl::popMapping()
{
    if (m_numOfPop >= m_numOfPush)
        return false;
    m_numOfPop++;
    m_stackOfMaps.pop();
    m_currMap = m_stackOfMaps.top();
    return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string transCiphertext;
    bool lowercase;
    for (int i = 0; i < ciphertext.size(); i++)
    {
        transCiphertext += '?';
        lowercase = false;
        if (islower(ciphertext[i]))
            lowercase = true;
        for (int j = 0; j < ABC.size(); j++)
        {
            if (toupper(ciphertext[i]) == ABC[j])
            {
                int count = 0;
                bool toAdd = false;
                for(int count = 0; count < m_currMap.size(); count++)
                    if (toupper(ciphertext[i]) == m_currMap[count])
                    {
                        char curr = ABC[count];
                        if (lowercase) curr = tolower(curr);
                        transCiphertext[i] = curr;
                        toAdd = true;
                    }
                if (toAdd)
                    break;
                if (m_currMap[count] == '?')
                    transCiphertext[i] = '?';
                else if (isalpha(m_currMap[i]) && islower(ciphertext[i]))
                    transCiphertext[i] = toupper(m_currMap[i]);
                else if (isalpha(m_currMap[i]) && isupper(ciphertext[i]))
                    transCiphertext[i];
                else
                    transCiphertext[i] = ciphertext[i];
            }
        }
    }
    return transCiphertext;
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
