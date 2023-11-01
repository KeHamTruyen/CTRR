#ifndef __CTRR_H__
#define __CTRR_H__

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

class Stacked
{
private:
    char *arr;
    int top;
    int capacity;

public:
    Stacked(int size)
    {
        capacity = size;
        arr = new char[capacity];
        top = -1;
    }

    ~Stacked()
    {
        delete[] arr;
    }

    void push(char c)
    {
        if (isFull())
        {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++top] = c;
    }

    char pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow!" << endl;
            return '\0';
        }
        return arr[top--];
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == capacity - 1;
    }

    char peek()
    {
        if (isEmpty())
        {
            return '\0';
        }
        return arr[top];
    }
};
bool isOperator(char c);
int precedence(char op);
bool isNumber(char c);
string Infix2Postfix(string infix);
string Infix2Prefix(string infix);
double calculate(double operand1, double operand2, char op);
string PostfixPrefixCalculator(string input);

//*********************************//

int getPriority(string s);
bool greaterOrEqualThan(string a, string b);
bool Operator(char s);
bool isOperand(char s);
string LogicInfix2Postfix(string infix);
string LogicInfix2Prefix(string infix);
void CreateTruthTable(string value);
string OperatorPostfix(string input, int &index);
string OperatorPrefix(string input, int &index);
bool Calculate(bool left, bool right, string x);
string LogicPostfixPrefixCalculator(string input, string value);

#endif