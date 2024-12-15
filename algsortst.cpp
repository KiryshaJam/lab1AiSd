#include <iostream>
#include <string>

using namespace std;

// Структура стека для хранения символов операторов
class Stack {
    char* arr;
    int top;
    int capacity;

public:
    Stack(int size) {
        arr = new char[size];
        capacity = size;
        top = -1;
    }
    
    ~Stack() {
        delete[] arr;
    }

    void push(char x) {
        if (top < capacity - 1) {
            arr[++top] = x;
        }
    }

    char pop() {
        if (top >= 0) {
            return arr[top--];
        }
        return '\0';
    }

    char peek() {
        if (top >= 0) {
            return arr[top];
        }
        return '\0';
    }

    bool isEmpty() {
        return top == -1;
    }
};

// Функция для определения приоритета операторов
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Алгоритм сортировочной станции для преобразования инфиксного выражения в постфиксное
string shuntingYard(string expr) {
    Stack opStack(expr.length()); // стек для операторов
    string output;  // строка для результата в постфиксной форме
    string token;   // текущий токен
    
    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];
        
        if (isdigit(ch)) {
            output += ch;
            if (i == expr.length() - 1 || !isdigit(expr[i + 1])) {
                output += ' '; // добавляем пробел после числа
            }
        } 
        else if (ch == 's' && expr.substr(i, 3) == "sin") {
            opStack.push('s');
            i += 2;
        } 
        else if (ch == 'c' && expr.substr(i, 3) == "cos") {
            opStack.push('c');
            i += 2;
        }
        else if (ch == '(') {
            opStack.push(ch);
        }
        else if (ch == ')') {
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                output += opStack.pop();
                output += ' ';
            }
            opStack.pop(); // удаляем '('
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            while (!opStack.isEmpty() && getPriority(opStack.peek()) >= getPriority(ch)) {
                output += opStack.pop();
                output += ' ';
            }
            opStack.push(ch);
        }
    }

    // Выгружаем оставшиеся операторы из стека
    while (!opStack.isEmpty()) {
        output += opStack.pop();
        output += ' ';
    }

    return output;
}

int main() {
    system("clear");
    string expression = "";
    cin>>expression;
    cout << "Infix expression: " << expression << endl;
    cout << "Postfix expression: " << shuntingYard(expression) << endl;
    return 0;
}
