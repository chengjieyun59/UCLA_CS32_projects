//
//  main.cpp
//  Homework2 #5 infix postfix
//
//  Created by Jie-Yun Cheng on 2/3/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

// declarations of additional functions
string conversion(string infix, const Map& m, bool& isValid);

int evaluate(string infix, const Map& values, string& postfix, int& result){
    
    
    
    /*
     pseudocode for the evaluation of the postfix expression:
     
     Initialize the operand stack to empty
     For each character ch in the postfix string
     if ch is an operand
     push the value that ch represents onto the operand stack
     else // ch is a binary operator
     set operand2 to the top of the operand stack
     pop the stack
     set operand1 to the top of the operand stack
     pop the stack
     apply the operation that ch represents to operand1 and
     operand2, and push the result onto the stack
     When the loop is finished, the operand stack will contain one item,
     the result of evaluating the expression
     */
    return 0;
}
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.

// implementations of additional functions
string conversion(string infix, const Map& m, bool& isValid) {
    string postfix = ""; // Initialize postfix to empty
    stack<char> operatorStack; // Initialize the operator stack to empty
    stack<char> parenBalanced; // to check if parentheses are balanced
    isValid = true;
    
    for (int i = 0; i < infix.size(); i++) // For each character ch in the infix string
    {
        char ch = infix[i];
        switch (ch) {
            case ' ':
                continue;

            // for parenthesis
            case '(':
                operatorStack.push(ch);
                break;
            case ')':
                while (operatorStack.top() != '(') // until meets a matching '('
                {
                    postfix += operatorStack.top(); //  append char onto the postfix string
                    operatorStack.pop(); // pop operators off the stack
                }
                operatorStack.pop(); // pop the matching '('
                break;
                
            // for operators: Pop all operators with greater or equal precedence off the stack and append them on the postfix string. Stop when you reach an operator with lower precedence or a (. Push the new operator on the stack.
            case '*':
            case '/':
                while (!operatorStack.empty() && operatorStack.top() != '(' && operatorStack.top() != '+' && operatorStack.top() != '-')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
                
            //always of less than or equal precedence
            case '+':
            case '-':
                while (!operatorStack.empty() && operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
                
            // for operands
            default:
                if (m.contains(ch))
                {
                    postfix += ch; // append to end of postfix
                }
                else if (!m.contains(ch) || !islower(ch))
                {
                    isValid = false;
                    return infix;
                }
                break;
        }
        
        if (infix[i] == '(')
            parenBalanced.push(infix[i]);
        if (infix[i] == ')')
            parenBalanced.pop();
    }
    
    if (!parenBalanced.empty())
    {
        isValid = false;
        return infix;
    }
    
    while (!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    } // When all infix tokens are gone, pop each operator and append it to the postfix string
    return postfix;
} // converting from infix to postfix

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    
    bool is;
    conversion("(a+(i-o)", m, is);
    assert(is == false); // unbalanced parenthesis is not valid
    
    conversion("A+(i-o)", m, is);
    assert(is == false); // uppercase letter is not valid
    
    conversion("5/o", m, is);
    assert(is == false); // number is not valid
    
    conversion("(a+e)*o/y", m, is);
    assert(is == true); // valid expression

    conversion("(e-o/(y + y)) * i", m, is);
    assert(is == true); // valid expression

    
    /*
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
           pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
           pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
     */
}
