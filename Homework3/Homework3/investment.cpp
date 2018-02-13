//
//  main.cpp
//  Homework3
//
//  Created by Jie-Yun Cheng on 2/7/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <iostream>
using namespace std;

//////////////////////
// Investment class //
//////////////////////

class Investment
{
public:
    Investment(string name, int value);
    virtual ~Investment();
    string name() const;
    int purchasePrice() const;
    virtual bool fungible() const;
    virtual string description() const = 0;
private:
    string m_name;
    int m_value;
};

////////////////////
// Painting class //
////////////////////

class Painting: public Investment
{
public:
    Painting(string name, int value);
    virtual ~Painting();
    virtual string description() const;
};

/////////////////
// Stock class //
/////////////////

class Stock: public Investment
{
public:
    Stock(string name, int value, string ticker);
    virtual ~Stock();
    virtual bool fungible() const;
    virtual string description() const;
private:
    string m_ticker;
};

/////////////////
// House class //
/////////////////

class House: public Investment
{
public:
    House(string name, int value);
    virtual ~House();
    virtual string description() const;
};

////////////////////////////
// Class member functions //
////////////////////////////

Investment::Investment(string name, int value)
: m_name(name), m_value(value) {}

Investment::~Investment() {}

string Investment::name() const
{
    return m_name;
}

int Investment::purchasePrice() const
{
    return m_value;
}

bool Investment::fungible() const
{
    return false;
}

Painting::Painting(string name, int value)
: Investment(name, value) {}

Painting::~Painting()
{
    cout << "Destroying " << name() << ", a painting" << endl;
}

string Painting::description() const
{
    return "painting";
}

Stock::Stock(string name, int value, string ticker)
: Investment(name, value), m_ticker(ticker) {}

Stock::~Stock()
{
    cout << "Destroying " << name() << ", a stock holding" << endl;
}

bool Stock::fungible() const
{
    return true;
}

string Stock::description() const
{
    return ("stock trading as " + m_ticker);
}

House::House(string name, int value)
: Investment(name, value) {}

House::~House()
{
    cout << "Destroying the house " << name() << endl;
}

string House::description() const
{
    return "house";
}

/////////////////////
// Given functions //
/////////////////////

void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

int main(int argc, const char * argv[]) {
    Investment* portfolio[4];
    // Investment test("testing", 1); // this should throw an error
    
    portfolio[0] = new Painting("Salvator Mundi", 450300000);
    // Stock holdings have a name, value, and ticker symbol
    portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
    portfolio[2] = new Stock("Symantec", 50000, "SYMC");
    portfolio[3] = new House("4 Privet Drive", 660000);
    
    for (int k = 0; k < 4; k++)
        display(portfolio[k]);
    
    // Clean up the investments before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete portfolio[k];
}
