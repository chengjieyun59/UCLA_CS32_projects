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
string deleteSpace(string& infix);
int howValid(string infix, const Map& m);
string conversion(string infix);

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    int status = howValid(infix, values);
    
    if (status == 0 || status == 2)
        postfix = conversion(infix);
    if (status == 1 || status == 2)
        return status;
    
    stack<char> operandStack; // Initialize the operator stack to empty
    char ch;
    ValueType value; // int value
    char operand1;
    char operand2;
    int temp = 0;
    
    for (int i = 0; i < postfix.size(); i++) // For each character ch in the infix string
    {
        ch = postfix[i];
        
        // ch is an operand:
        if (values.get(ch, value))
            operandStack.push(value); // push the value that ch represents onto the operand stack
        
        // ch is a binary operator:
        else
        {
            operand2 = operandStack.top();
            operandStack.pop();
            operand1 = operandStack.top();
            operandStack.pop();
            
            switch (ch)
            {
                case '*':
                    temp = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0)
                        return 3;
                    temp = operand1 / operand2;
                    break;
                case '+':
                    temp = operand1 + operand2;
                    break;
                case '-':
                    temp = operand1 - operand2;
                    break;
                default:
                    break;
            } // apply the operation that ch represents to operand1 and operand2
            operandStack.push(temp); // push the result onto the stack
        }
    }
    result = operandStack.top(); // When the loop is finished, the operand stack will contain one item, the result of evaluating the expression
    return status;
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
string deleteSpace(string& infix)
{
    int reducedSize = (int)infix.size();
    
    for (int i = 0; i < reducedSize; i++) // For each character ch in the infix string
    {
        if (infix[i] == ' ')
        {
            infix.erase(i, 1);
            reducedSize--; //the size needed to loop through decreased
            i--; // the position must stay the same, so decrement to counteract the increment effect
        }
    }
    return infix;
}

int howValid(string infix, const Map& m)
{
    deleteSpace(infix);
    int operational = 1; // to check if the number of operands is one more than the number of operators
    int parenthesis = 0; // to check if parentheses is valid
    //stack<char> parenBalanced; // to check if parentheses are balanced. This method wasn't able to check if a closed parenthesis happen before any matching parenthesis
    char ch;

    if (infix.empty())
        return 1; // 1.a.
    
    if (infix[0] == '*' || infix[0] == '/' || infix[0] == '+' || infix[0] == '-' || infix[0] == ')')
        return 1; // 1.e.
    
    if (infix[infix.size()-1] == '*' || infix[infix.size()-1] == '/' || infix[infix.size()-1] == '+' || infix[infix.size()-1] == '-' || infix[infix.size()-1] == '(')
        return 1; // 1.f.
    
    for (int i = 0; i < infix.size(); i++) // For each character ch in the infix string
    {
        ch = infix[i];
        
        // 1.b.
        if (ch == '(')
        {
            if (infix[i+1] == '*' || infix[i+1] == '/' || infix[i+1] == '+' || infix[i+1] == '-' || infix[i+1] == ')')
                return 1; // 1.g.
            parenthesis++;
            //parenBalanced.push(ch); // push to stack if it's an open parenthesis
        }
        else if (ch == ')')
        {
            if (islower(infix[i+1]) || infix[i+1] == '(')
                return 1; // 1.h.
            parenthesis--;
            //parenBalanced.pop(); // pop from stack if it's a closed parenthesis
        }
        
        // 1.c.
        else if (ch == '*' || ch == '/' || ch == '+' || ch == '-')
        {
            if (infix[i+1] == '*' || infix[i+1] == '/' || infix[i+1] == '+' || infix[i+1] == '-' || infix[i+1] == ')')
                return 1; // 1.j.
            operational++;
        }
        else if (!islower(ch))
            return 1; // 1.d.

        if(islower(ch))
        {
            if(!m.contains(ch))
                return 2; // 2.
            if (m.contains(ch))
                operational--; // 1.c.
            if(islower(infix[i+1]) || infix[i+1] == '(')
                return 1; // 1.i
        }
        
        if (parenthesis < 0)
            return 1; // 1.k.
    }
    if (parenthesis != 0) // if (number of open parenthesis) != (number of closed parenthesis)
        return 1;
    if (operational != 0)
        return 1; // 1.c.
    
    return 0;
}
// return 1: infix syntax not valid. Need to check:
    // a. infix cannot be empty
    // b. the number of open parenthesis needs to be equal to the number of closed parenthesis
    // c. the number of operands needs to be one more than the number of operators
    // d. all char needs to be of lowercase
    // e. the first element must be an open parenthesis, a space, or an operand, nothing else
    // f. the last element cannot be an open parenthesis or an operator
    // g. the element after an open parenthesis cannot be an operator or a closed parenthesis
    // h. the element after a closed parenthesis cannot be an operand or an open parenthesis
    // i. the element after an operand cannot be another operand or a open parenthesis
    // j. the element after an operator cannot be another operator or a closed parenthesis
    // k. there's always a matching open parenthesis before a closed parenthesis, so that )a+e( wouldn't work
// return 2: infix syntax valid, but contains at least one lower case letter operant that does not appear in the values map
// return 3: infix syntax valid, all lower case operand letters appear in the values map, but attempts to divide by zero. Done in evaluate function
// return 0 otherwise

string conversion(string infix)
{
    string postfix = ""; // Initialize postfix to empty
    stack<char> operatorStack; // Initialize the operator stack to empty
    char ch;
    
    for (int i = 0; i < infix.size(); i++) // For each character ch in the infix string
    {
        ch = infix[i];
        switch (ch)
        {
            case ' ':
                continue; // skips the spaces in case it wasn't deleted in deleteSpace function

            // for parenthesis. Highest precedence than *, /, +, and -
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
            // * and / have higher precedence than + and -
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
                    postfix += ch; // append to end of postfix
                break;
        }
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
    
    assert(evaluate("a+ e", m, pf, answer) == 0  && pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("e)*(a", m, pf, answer) == 1  &&  answer == 999); // test for parenthesis

    // currently testing:
    assert(evaluate(")a", m, pf, answer) == 1  &&  answer == 999); // test for 1e
    assert(evaluate("+ab", m, pf, answer) == 1  &&  answer == 999); // test for 1e
    assert(evaluate("y(o+u))(", m, pf, answer) == 1  &&  answer == 999); // test for 1f
    assert(evaluate("(+)", m, pf, answer) == 1  &&  answer == 999); // test for 1g
    assert(evaluate("((a+i)i)", m, pf, answer) == 1  &&  answer == 999); // test for 1h
    assert(evaluate("ae +/i", m, pf, answer) == 1  &&  answer == 999); // test for 1i
    assert(evaluate("(a++i)/ji", m, pf, answer) == 1  &&  answer == 999); // test for 1j

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
    assert(evaluate("a*b", m, pf, answer) == 2  && pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  && pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  && pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  && pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  && pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}
