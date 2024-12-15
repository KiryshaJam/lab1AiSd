#include <iostream>
#include <string>

using namespace std;

//двусвязный список
class Node {
public:
    double data;
    Node* prev, * next;
 
public:
    Node(double data) {
    this->data = data;
   this->prev = this->next = NULL;
    }
};

class LinkedList {
public:
    Node* head, * tail;

public:
    LinkedList() {
        this->head = this->tail = NULL;
    }
    ~LinkedList() {
        while (head != NULL)
            pop_front();
    }
    Node* push_front(double data) {
        Node* ptr = new Node(data);

        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;
        if (tail == NULL)
            tail = ptr;
        head = ptr;

        return ptr;
    }


    Node* push_back(double data) {
        Node* ptr = new Node(data);

        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;
        if (head == NULL)
            head = ptr;
        tail = ptr;

        return ptr;
    }
    void pop_front() {
        if (head == NULL) return;

        Node* ptr = head->next;
        if (ptr != NULL)
            ptr->prev = NULL;
        else
            tail = NULL;

        delete head;
        head = ptr;
    }


    void pop_back() {
        if (tail == NULL) return;

        Node* ptr = tail->prev;
        if (ptr != NULL)
            ptr->next = NULL;
        else
            head = NULL;

        delete tail;
        tail = ptr;
    }

    void printList() {
        Node* current = head;
        while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
        }
        cout << endl;
    }

    void clear() {
        while (head != NULL) {
            pop_front();
        }
    }


    Node* getAt(int index) {
        Node* ptr = head;
        int n = 0;

        while (n != index) {
            if (ptr == NULL)
                return ptr;
            ptr = ptr->next;
            n++;
        }

        return ptr;
    }


    Node* operator [] (int index) {
        return getAt(index);
    }

    Node* insert(int index, double data) {
        Node* right = getAt(index);
        if (right == NULL)
            return push_back(data);

        Node* left = right->prev;
        if (left == NULL)
            return push_front(data);

        Node* ptr = new Node(data);

        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;

        return ptr;
    }

    void erase(int index) {
        Node* ptr = getAt(index);
        if (ptr == NULL)
            return;

        if (ptr->prev == NULL) {
            pop_front();
            return;
        }

        if (ptr->next == NULL) {
            pop_back();
            return;
        }

        Node* left = ptr->prev;
        Node* right = ptr->next;
        left->next = right;
        right->prev = left;

        delete ptr;
    }
};

//динамический массив

class DynamicArray {
private:
    int* array;
    int capacity;
    int size;

    void resize(int newCapacity) {
        int* newArray = new int[newCapacity];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

public:
    DynamicArray() {
        array = new int[2];
        capacity = 2;
        size = 0;
    }

    ~DynamicArray() {
        delete[] array;
    }

    void addElement(int element) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        array[size] = element;
        ++size;
    }

    void getElement(int index) const {
        if (index >= 0 && index < size) {
            cout << "Элемент на индексе " << index << ": " << array[index] <<endl;
        } else {
            cout << "По данному индексу элемента не существует" <<endl;
        }
    }

    void insertElement(int index, int element) {
        if (index < 0 || index > size) {
            cout << "Данного индекса не существует" <<endl;
            return;
        }

        if (size == capacity) {
            resize(capacity * 2);
        }

        for (int i = size; i > index; --i) {
            array[i] = array[i - 1];
        }

        array[index] = element;
        ++size;
    }

    void printArray() const {
        cout << "Элементы массива: "<<endl;
        for (int i = 0; i < size; ++i) {
            cout << array[i] << " ";
        }
        cout <<endl;
    }

    void clear() {
        delete[] array;
        array = nullptr;
        size = 0;
        capacity = 0;
        cout << "Массив удален." << endl;
    }
};

//стек

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

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string shuntingYard(string expr) {
    Stack opStack(expr.length());
    string output;
    string token;
    
    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];
        
        if (isdigit(ch)) {
            output += ch;
            if (i == expr.length() - 1 || !isdigit(expr[i + 1])) {
                output += ' ';
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
            opStack.pop();
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            while (!opStack.isEmpty() && getPriority(opStack.peek()) >= getPriority(ch)) {
                output += opStack.pop();
                output += ' ';
            }
            opStack.push(ch);
        }
    }

    while (!opStack.isEmpty()) {
        output += opStack.pop();
        output += ' ';
    }

    return output;
}


int main() {
    int chose_op = 0;
    system("clear");
    while (1)
    {
        system("clear");
        cout<< "Выберите операцию"<<endl;
        cout<<"1. Работа с двусвязным списком"<<endl;
        cout<< "2. Работа с динамическим массивом" <<endl;
        cout<< "3. Работа с сортировочной станцией"<<endl;
        cin>>chose_op;

        if (chose_op == 1) {
            
            LinkedList lst;
            system("clear");
            int actionLst = 1;
            while (actionLst != 9)
            {
                system("clear");
                cout<<"1. Добавить элемент в конец списка"<<endl;
                cout<<"2. Добавить элемент в начало списка"<<endl;
                cout<<"3. Добавить элемент по индексу"<<endl;
                cout<<"4. Удалить первый элемент"<<endl;
                cout<<"5. Удалить последний элемент"<<endl;
                cout<<"6. Удалить элемент по индексу"<<endl;
                cout<<"7. Вывести список"<<endl;
                cout<<"8. Удалить список"<<endl;
                cout<<"9. Выйти из взаимодействия со списком"<<endl;
                cin>>actionLst;
            
           
                if (actionLst == 1) {
                    system("clear");
                    float numberToInput = 0;
                    cout<<"Введите число которое хотите добавить"<<endl;
                    cin>>numberToInput;
                    lst.push_back(numberToInput);
                }

                if (actionLst == 2) {
                    system("clear");
                    float numberToInput = 0;
                    cout<<"Введите число которое хотите добавить"<<endl;
                    cin>>numberToInput;
                    lst.push_front(numberToInput);
                }

                if (actionLst == 3) {
                    system("clear");
                    int index = 0;
                    float numberToInput = 0;
                    cout<<"Введите индекс, по которому хотите добавить элемент"<<endl;
                    cin>>index;
                    cout<<"Введите число, которое хотите добавить"<<endl;
                    cin>>numberToInput;
                    lst.insert(index, numberToInput);
                }
                
                if (actionLst == 4) {
                    system("clear");
                    lst.pop_front();
                }
                if (actionLst == 5) {
                    system("clear");
                    lst.pop_back();
                }

                if (actionLst == 6) {
                    system("clear");
                    int indexToDel = 0;
                    cout<<"Введите индекс по которому надо удалить элемент"<<endl;
                    cin>>indexToDel;
                    lst.erase(indexToDel);
                }

                if (actionLst == 7) {
                    system("clear");
                    int pause = 0;
                    lst.printList();
                    cout<<"Введите 1 для продолжения"<<endl;
                    cin>>pause;
                }

                if (actionLst == 8) {
                    lst.clear();
                }

                if (actionLst == 9) {
                    lst.clear();
                }
                
            }
        }

        if (chose_op == 2) {
            DynamicArray arr;
            system("clear");
            int actionArr = 1;
            while (actionArr != 6)
            {
                system("clear");
                cout<<"1. Добавить элемент в конец массива"<<endl;
                cout<<"2. Вывести элемент по индексу"<<endl;
                cout<<"3. Добавить элемент по индексу"<<endl;
                cout<<"4. Вывести весь массив"<<endl;
                cout<<"5. Удалить массив"<<endl;
                cout<<"6. Выйти из взаимодействия с массивом"<<endl;
                cin>>actionArr;

                if (actionArr == 1) {
                    system("clear");
                    int numberToInput = 0;
                    cout<<"Введите число, которое хотите добавить"<<endl;
                    cin>>numberToInput;
                    arr.addElement(numberToInput);
                }

                if (actionArr == 2) {
                    system("clear");
                    int pause = 0;
                    int indexToOutput = 0;
                    cout<<"Введите индекс по которому хотите вывести элемент"<<endl;
                    cin>>indexToOutput;
                    arr.getElement(indexToOutput);
                    cout<<endl<<"Введите 1 для продолжения"<<endl;
                    cin>>pause;
                }

                if (actionArr == 3) {
                    system("clear");
                    int indexToInput = 0, numberToInput = 0;
                    cout<<"Введите индекс по котором хотите добавить элемент"<<endl;
                    cin>>indexToInput;
                    cout<<"Введите число, которое хотете добавить по заданному индексу"<<endl;
                    cin>>numberToInput;
                    arr.insertElement(indexToInput, numberToInput);
                }

                if (actionArr == 4) {
                    system("clear");
                    int pause = 0;
                    arr.printArray();
                    cout<<"Введите 1 для продолжения"<<endl;
                    cin>>pause;
                }

                if(actionArr == 5) {
                    arr.clear();
                }
                
                if (actionArr == 6) {
                    arr.clear();
                }
            }    
        }

        if (chose_op == 3) {
            system("clear");
            cout<<"Введите исходную строку без пробелов"<< endl;
            int pause = 0;
            string expression = "";
            cin>>expression;
            cout<<"Входные данные: " << expression << endl;
            cout << "Выходные данные: " << shuntingYard(expression) << endl;
            cout<<"Введите 1 для продолжения"<<endl;
            cin>>pause;
        }
    }
    


}
