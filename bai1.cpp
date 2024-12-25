#include <bits/stdc++.h>
using namespace std;

//ham kiem tra do uu tien cua thuat toan
int precedence(char op) {
    if (op == '!') return 3;  
    if (op == '&') return 2;  
    if (op == '|') return 1;  
    if (op == '>') return 0;  
    return -1;
}

bool isOperator(char c) {
    return c == '!' || c == '&' || c == '|' || c == '>';
}

bool isValidExpression(const string &expression) {
    stack<char> parenStack;
    for (char c : expression) {
        if (c == '(') {
            parenStack.push(c);
        } else if (c == ')') {
            if (parenStack.empty()) return false;
            parenStack.pop();
        }
    }
    return parenStack.empty();
}

vector<string> infixToPostfix(const string &expression) {
    stack<char> opStack;          
    vector<string> postfix;    
    string token;

    for (size_t i = 0; i < expression.size(); i++) {
        char c = expression[i];

        if (isalnum(c)) {
            token += c; 
            while (i + 1 < expression.size() && isalnum(expression[i + 1])) {
                token += expression[++i];
            }
            postfix.push_back(token); 
            token.clear();
        }
        else if (isOperator(c)) {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                postfix.push_back(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.push(c); 
        }
        else if (c == '(') {
            opStack.push(c);
        } 
        else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix.push_back(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.pop(); 
        }
    }
    while (!opStack.empty()) {
        postfix.push_back(string(1, opStack.top()));
        opStack.pop();
    }

    return postfix;
}
//ham danh gia bieu thuc
bool evaluatePostfix(const vector<string> &postfix, const unordered_map<char, bool> &variables) {
    stack<bool> evalStack;

    for (const auto &token : postfix) {
        if (isalnum(token[0])) {
            evalStack.push(variables.at(token[0]));
        } else {
            if (token == "!") {
                bool a = evalStack.top(); evalStack.pop();
                evalStack.push(!a);
            } else if (token == "&") {
                bool b = evalStack.top(); evalStack.pop();
                bool a = evalStack.top(); evalStack.pop();
                evalStack.push(a && b);
            } else if (token == "|") {
                bool b = evalStack.top(); evalStack.pop();
                bool a = evalStack.top(); evalStack.pop();
                evalStack.push(a || b);
            } else if (token == ">") {
                bool b = evalStack.top(); evalStack.pop();
                bool a = evalStack.top(); evalStack.pop();
                evalStack.push(!a || b);
            }
        }
    }

    return evalStack.top();
}


int main() {
    string expression;
    cout << "Nhap bieu thuc logic (dung !, &, |, > và các bien nhu A, B, C): ";
    getline(cin, expression);

    // kiem tra tinh hop le cua bieu thuc
    if (!isValidExpression(expression)) {
        cout << "bieu thuc khong hop le." << endl;
        return 1;
    }

    // Chuyyen doi bieu thuc tu Infix sang Postfix
    vector<string> postfix = infixToPostfix(expression);

    // T́m các tim cac bien logic
    unordered_map<char, bool> variables;
    for (char c : expression) {
        if (isalnum(c)) variables[c] = false;
    }

    // Nhap gia tri cho bien logic
    for (auto &var : variables) {
        cout << "Nhap gia tri cho " << var.first << " (0 or 1): ";
        cin >> var.second;
    }	
    // danh gia bieu thuc
    bool result = evaluatePostfix(postfix, variables);

    // In 
    if (result) cout<<"Bieu thuc hop le!"; else cout<<"Bieu thucc khong hop le!";
    cout<<endl;
    // GIa tri cua bieu thuc dau vao;
    cout << "Gia tri cua bieu thuc la: " << (result ? "true" : "false") << endl;

    return 0;
}
