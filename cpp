#include <iostream>
#include <string>
#include <cctype>
#include <stack>

using namespace std;

class Interpreter {
public:
    int evaluate(const string& expression) {
        stack<int> values;
        stack<char> ops;
        
        int n = expression.length();
        for (int i = 0; i < n; ++i) {
            // Skip white spaces
            if (isspace(expression[i])) continue;

            // If the current character is a number, push it to the stack
            if (isdigit(expression[i])) {
                int value = 0;
                while (i < n && isdigit(expression[i])) {
                    value = value * 10 + (expression[i] - '0');
                    ++i;
                }
                --i; // Adjust the index after the number
                values.push(value);
            }
            // If the current character is an operator
            else if (expression[i] == '+' || expression[i] == '-' ||
                     expression[i] == '*' || expression[i] == '/') {
                // Process any operators already in the stack
                while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                    int val2 = values.top();
                    values.pop();
                    int val1 = values.top();
                    values.pop();
                    char op = ops.top();
                    ops.pop();
                    
                    values.push(applyOperator(val1, val2, op));
                }
                ops.push(expression[i]);
            }
        }

        // Process the remaining operators
        while (!ops.empty()) {
            int val2 = values.top();
            values.pop();
            int val1 = values.top();
            values.pop();
            char op = ops.top();
            ops.pop();
            
            values.push(applyOperator(val1, val2, op));
        }

        return values.top();
    }

private:
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    int applyOperator(int a, int b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            default: return 0;
        }
    }
};

int main() {
    Interpreter interpreter;
    string expression;
    
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    try {
        int result = interpreter.evaluate(expression);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cout << "Error: Invalid expression!" << endl;
    }

    return 0;
}
