#include "ctrr.h"

unordered_map<char, bool> truth_table;

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    {
        return true;
    }
    return false;
}

int precedence(char op)
{
    if (op == '^')
    {
        return 3;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    else if (op == '+' || op == '-')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

bool isNumber(char c)
{
    if ((c >= '0' && c <= '9'))
    {
        return true;
    }
    return false;
}

string Infix2Postfix(string infix)
{
    int size = infix.length();
    Stacked st(size);
    string postfix = "";
    string tmp = "";

    for (int i = 0; i < size; i++)
    {
        char c = infix[i];

        if (isNumber(c))
        {

            tmp += c;
        }
        else if (isOperator(c))
        {

            if (!tmp.empty())
            {
                postfix += tmp + " ";
                tmp = "";
            }
            while (!st.isEmpty() && precedence(c) <= precedence(st.peek()) && st.peek() != '(')
            {
                postfix += st.pop();
                postfix += " ";
            }
            st.push(c);
        }
        else if (c == '(')
        {
            st.push(c);
        }
        else if (c == ')')
        {

            if (!tmp.empty())
            {
                postfix += tmp + " ";
                tmp = "";
            }
            while (!st.isEmpty() && st.peek() != '(')
            {
                postfix += st.pop();
                postfix += " ";
            }
            st.pop();
        }
        else if (c == ' ')
        {

            continue;
        }
        else
        {

            return " ";
        }
    }

    if (!tmp.empty())
    {
        postfix += tmp + " ";
    }

    while (!st.isEmpty())
    {
        postfix += st.pop();
        postfix += " ";
    }

    return postfix;
}

string Infix2Prefix(string infix)
{

    reverse(infix.begin(), infix.end());

    int size = infix.length();
    Stacked st(size);
    string prefix = "";
    string tmp = "";

    for (int i = 0; i < size; i++)
    {
        char c = infix[i];

        if (isNumber(c))
        {
            tmp += c;
        }
        else if (isOperator(c))
        {
            if (!tmp.empty())
            {
                prefix += tmp + " ";
                tmp = "";
            }
            while (!st.isEmpty() && precedence(c) < precedence(st.peek()))
            {
                prefix += st.pop();
                prefix += " ";
            }
            st.push(c);
        }
        else if (c == ')')
        {
            st.push(c);
        }
        else if (c == '(')
        {
            if (!tmp.empty())
            {
                prefix += tmp + " ";
                tmp = "";
            }
            while (!st.isEmpty() && st.peek() != ')')
            {
                prefix += st.pop();
                prefix += " ";
            }
            st.pop();
        }
        else if (c == ' ')
        {
            continue;
        }
        else
        {
            return " ";
        }
    }

    if (!tmp.empty())
    {
        prefix += tmp + " ";
    }

    while (!st.isEmpty())
    {
        prefix += st.pop();
        prefix += " ";
    }
    reverse(prefix.begin(), prefix.end());
    prefix.erase(0, 1);
    return prefix;
}

double calculate(double operand1, double operand2, char op)
{
    double result = 0;
    switch (op)
    {
    case '+':
        result = operand1 + operand2;
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '*':
        result = operand1 * operand2;
        break;
    case '/':
        result = operand1 / operand2;
        break;
    case '^':
        result = pow(operand1, operand2);
        break;
    }
    return result;
}

string PostfixPrefixCalculator(string input)
{
    int size = input.length();
    double stack[size];

    int top = -1;
    double result;
    char f = input[0];
    if (isNumber(f))
    {
        int index = 0;
        while (index < size)
        {
            char c = input[index];
            if (c == ' ')
            {
                index++;
                continue;
            }
            else if (isdigit(c))
            {
                double number = 0;
                while (index < size && isdigit(c))
                {
                    number = number * 10 + (c - '0');
                    index++;
                    c = input[index];
                }
                stack[++top] = number;
            }
            else if (isOperator(c))
            {
                double operand2 = stack[top--];
                double operand1 = stack[top--];
                double result = calculate(operand1, operand2, c);
                stack[++top] = result;
            }
            index++;
        }
    }
    else
    {
        for (int i = size - 1; i >= 0; i--)
        {
            char c = input[i];
            if (c == ' ')
            {
                continue;
            }
            else if (isdigit(c))
            {
                double number = 0;
                int j = 1;
                while (i >= 0 && isdigit(c))
                {
                    number = (c - '0') * j + number;
                    j *= 10;
                    i--;
                    c = input[i];
                }
                stack[++top] = number;
            }
            else if (isOperator(c))
            {
                double operand1 = stack[top--];
                double operand2 = stack[top--];
                double result = calculate(operand1, operand2, c);
                stack[++top] = result;
            }
        }
    }
    result = stack[top--];
    double rounded_result = round(result * 10000) / 10000.0; // Làm tròn tới 4 chữ số sau dấu phẩy
    string result_str = to_string(rounded_result);
    size_t decimal_pos = result_str.find('.');
    if (decimal_pos != string::npos && result_str.length() > decimal_pos + 4)
    {
        result_str.erase(decimal_pos + 5);
        while (result_str.back() == '0')
        {
            result_str.pop_back();
        }
        if (result_str.back() == '.')
        {
            result_str.pop_back();
        }
    }
    return result_str;
}

//************************************************//

int getPriority(string s)
{
    if (s == "~")
        return 4;
    if (s == "|" || s == "&")
        return 3;
    if (s == "->")
        return 2;
    if (s == "<->")
        return 1;
    return 0;
}

bool greaterOrEqualThan(string a, string b)
{
    return getPriority(a) >= getPriority(b);
}

bool Operator(char s)
{
    return (s == '~' || s == '&' || s == '|' || s == '-' || s == '<');
}

bool isOperand(char s)
{
    return (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z');
}

string LogicInfix2Postfix(string infix)
{
    stack<string> Stack;
    string postfix = "";

    for (unsigned int i = 0; i < infix.length(); i++)
    {
        if (isOperand(infix[i]))
        {
            postfix += infix[i];
        }
        else if (infix[i] == '(')
        {
            Stack.push("(");
        }
        else if (infix[i] == ')')
        {
            while (!Stack.empty() && Stack.top() != "(")
            {
                postfix += Stack.top();
                Stack.pop();
            }
            Stack.pop();
        }
        else if (Operator(infix[i]))
        {
            string temp = "";
            if (infix[i] == '-')
            {
                temp += "->";
                i += 1;
            }
            else if (infix[i] == '<')
            {
                temp += "<->";
                i += 2;
            }
            else
            {
                temp += infix[i];
            }

            while (!Stack.empty() && Stack.top() != "(" && greaterOrEqualThan(Stack.top(), temp))
            {
                postfix += Stack.top();
                Stack.pop();
            }
            Stack.push(temp);
        }
    }

    while (!Stack.empty())
    {
        postfix += Stack.top();
        Stack.pop();
    }

    return postfix;
}

string LogicInfix2Prefix(string infix)
{
    stack<string> _stack;
    string temp = LogicInfix2Postfix(infix);
    string prefix = "";
    int size = temp.size();
    for (int i = 0; i < size; i++)
    {
        if (isOperand(temp[i]))
        {
            string alpha = "";
            if (temp[i + 1] == '~')
            {
                alpha = alpha + temp[i + 1] + temp[i];
                i++;
            }
            else
                alpha += temp[i];
            if (i == size - 1)
                return alpha;
            _stack.push(alpha);
        }
        else
        {
            string _operator("");
            string res("");
            if (temp[i] == '<' || temp[i] == '-' || temp[i] == '>')
            {
                int j = i;
                while (temp[j] == '<' || temp[j] == '-' || temp[j] == '>')
                {
                    _operator = _operator + temp[j];
                    j++;
                    if (_operator == "<->" || _operator == "->")
                        break;
                }
                i = j - 1;
            }
            else
                _operator += temp[i];
            int stack_size = _stack.size();
            for (int i = 0; i < min(2, stack_size); i++)
            {
                res = _stack.top() + res;
                _stack.pop();
            }
            res = _operator + res;
            _stack.push(res);
            prefix = _stack.top();
        }
    }
    return prefix;
}

void CreateTruthTable(string value)
{
    int value_size = value.size();
    for (int i = 0; i < value_size / 2; i++)
    {
        if (isOperand(value[i]))
        {
            int pos = value_size - (value_size / 2);
            truth_table.emplace(value[i], value[i + pos] - '0');
            i++;
        }
        else
            break;
    }
}

string OperatorPostfix(string input, int &index)
{
    string _operator = "";
    if (input[index] == '<' || input[index] == '-' || input[index] == '>')
    {
        while (input[index] == '<' || input[index] == '-' || input[index] == '>')
        {
            _operator += input[index];
            index++;
            if (_operator == "<->" || _operator == "->")
                break;
        }
        index--;
    }
    else
        _operator += input[index];
    return _operator;
}

string OperatorPrefix(string input, int &index)
{
    string _operator = "";
    if (input[index] == '<' || input[index] == '-' || input[index] == '>')
    {
        while (input[index] == '<' || input[index] == '-' || input[index] == '>')
        {
            _operator = input[index] + _operator;
            index--;
            if (input[index] != '<' && _operator == "->")
                break;
            if (_operator == "<->")
                break;
        }
        index++;
    }
    else
        _operator += input[index];
    return _operator;
}

bool Calculate(bool left, bool right, string x)
{
    if (x == "&")
        return left & right;
    if (x == "|")
        return left || right;
    if (x == "~")
        return !left;
    if (x == "->")
        return !left || right;
    return (left && right) || (!left && !right);
}

string LogicPostfixPrefixCalculator(string input, string value)
{
    if (!isOperand(input[0]))
    {
        stack<bool> truthValue;
        CreateTruthTable(value);
        int input_size = input.size();
        for (int k = input_size - 1; k >= 0; k--)
        {
            if (isOperand(input[k]))
                truthValue.push(truth_table[input[k]]);
            else
            {
                string _operator = OperatorPrefix(input, k);
                bool leftValue = truthValue.top();
                truthValue.pop();
                if (!truthValue.empty())
                {
                    if (_operator != "~")
                    {
                        bool rightValue = truthValue.top();
                        truthValue.pop();
                        truthValue.push(Calculate(leftValue, rightValue, _operator));
                    }
                    else
                        truthValue.push(Calculate(leftValue, 1, _operator));
                }
                else
                    truthValue.push(Calculate(leftValue, 1, _operator));
            }
        }
        bool res = truthValue.top();
        truthValue.empty();
        truth_table.clear();
        if (res)
            return "TRUE";
        return "FALSE";
    }
    else
    {
        stack<bool> truthValue;
        CreateTruthTable(value);
        int input_size = input.size();
        for (int i = 0; i < input_size; i++)
        {
            if (isOperand(input[i]))
                truthValue.push(truth_table[input[i]]);
            else
            {
                string _operator = OperatorPostfix(input, i);
                bool rightValue = truthValue.top();
                truthValue.pop();
                if (!truthValue.empty())
                {
                    if (_operator != "~")
                    {
                        bool leftValue = truthValue.top();
                        truthValue.pop();
                        truthValue.push(Calculate(leftValue, rightValue, _operator));
                    }
                    else
                        truthValue.push(Calculate(rightValue, 1, _operator));
                }
                else
                    truthValue.push(Calculate(rightValue, 1, _operator));
            }
        }
        bool res = truthValue.top();
        truthValue.empty();
        truth_table.clear();
        if (res)
            return "TRUE";
        return "FALSE";
    }
}
