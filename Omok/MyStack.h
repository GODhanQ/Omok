#ifndef MYSTACK_H
#define MYSTACK_H

#include <stdexcept> // std::out_of_range

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& val) : data(val), next(nullptr) {}
};

template <typename T>
class MyHistoryStack {
private:
    Node<T>* head; // 스택의 top (최근 상태)
    int stackSize;
    int currentIndex; // 현재 히스토리 포인터 (0은 가장 오래된 상태)

    // 특정 인덱스의 노드를 찾는 Helper 함수
    Node<T>* getNodeAt(int index) const;

public:
    MyHistoryStack();
    ~MyHistoryStack();

    bool empty() const;
    int size() const;

    void push(const T& value);
    T pop();
    T top() const;

    const T& operator[](int index) const;
    T& operator[](int index);

    bool undo();
    bool redo();

    T getCurrentState() const;
};

// 템플릿 클래스의 멤버 함수 구현은 헤더 파일에 포함하는 경우가 많음
template <typename T>
Node<T>* MyHistoryStack<T>::getNodeAt(int index) const {
    if (index < 0 || index >= stackSize) {
        return nullptr;
    }
    Node<T>* current = head;
    for (int i = 0; i < currentIndex - index; ++i) {
        current = current->next;
    }
    return current;
}

template <typename T>
MyHistoryStack<T>::MyHistoryStack() : head(nullptr), stackSize(0), currentIndex(-1) {}

template <typename T>
MyHistoryStack<T>::~MyHistoryStack() {
    Node<T>* current = head;
    while (current) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
bool MyHistoryStack<T>::empty() const {
    return head == nullptr;
}

template <typename T>
int MyHistoryStack<T>::size() const {
    return stackSize;
}

template <typename T>
void MyHistoryStack<T>::push(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = head;
    head = newNode;
    stackSize++;
    currentIndex++;
}

template <typename T>
T MyHistoryStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("History is empty");
    }
    T value = head->data;
    Node<T>* temp = head;
    head = head->next;
    delete temp;
    stackSize--;
    currentIndex--;
    return value;
}

template <typename T>
T MyHistoryStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("History is empty");
    }
    return head->data;
}

template <typename T>
const T& MyHistoryStack<T>::operator[](int index) const {
    Node<T>* node = getNodeAt(index);
    if (node) {
        return node->data;
    }
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
T& MyHistoryStack<T>::operator[](int index) {
    Node<T>* node = getNodeAt(index);
    if (node) {
        return node->data;
    }
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
bool MyHistoryStack<T>::undo() {
    if (currentIndex > 0) {
        currentIndex--;
        return true;
    }
    return false;
}

template <typename T>
bool MyHistoryStack<T>::redo() {
    if (currentIndex < size() - 1) {
        currentIndex++;
        return true;
    }
    return false;
}

template <typename T>
T MyHistoryStack<T>::getCurrentState() const {
    Node<T>* current = getNodeAt(currentIndex);
    if (current) {
        return current->data;
    }
    throw std::out_of_range("No current state");
}

#endif // MYSTACK_H