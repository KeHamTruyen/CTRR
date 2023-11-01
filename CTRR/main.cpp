#include "ctrr.h"

int main()
{
    string infix = "2 + 3";
    string logicInfix = "a&b";
    string value = "a b 1 1";
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << Infix2Postfix(infix) << endl;
    cout << "Prefix: " << Infix2Prefix(infix) << endl;
    cout << "Postfix result: " << PostfixPrefixCalculator(Infix2Postfix(infix)) << endl;
    cout << "Prefix result: " << PostfixPrefixCalculator(Infix2Prefix(infix)) << endl;
    cout << "Infix: " << logicInfix << endl;
    cout << "Postfix: " << LogicInfix2Postfix(logicInfix) << endl;
    cout << "Prefix: " << LogicInfix2Prefix(logicInfix) << endl;
    cout << "Postfix result: " << LogicPostfixPrefixCalculator(LogicInfix2Postfix(logicInfix), value) << endl;
    cout << "Prefix result: " << LogicPostfixPrefixCalculator(LogicInfix2Prefix(logicInfix), value) << endl;
    return 0;
}