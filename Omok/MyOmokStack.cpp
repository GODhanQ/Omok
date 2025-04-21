#include "MyOmokStack.h"
using namespace std;

// Node
Node::Node(const std::string(&map)[20][20]) : next(nullptr), prdv(nullptr) {
    // free store에 2차원 string 배열을 동적 할당
    data = new std::string[20][20];

    // map의 내용을 새로 할당된 메모리에 깊은 복사
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            data[i][j] = map[i][j];
        }
    }
}

Node::~Node() {
    // free store에 할당된 data 배열 해제
    delete[] data;
}


// LinkedListStack
LinkedListStack::LinkedListStack() : top(nullptr) {}

// 소멸자: 스택의 모든 노드를 해제합니다.
LinkedListStack::~LinkedListStack() {
    while (!isEmpty()) {
        pop();
        Size--;
    }
}

void LinkedListStack::push(const std::string(&map)[20][20])
{
    Node* newNode = new Node(map);
    newNode->next = top;
    top->prdv = newNode;
    top = newNode;
    Size++;
}

string(*LinkedListStack::pop())[20] {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }

    Node* temp = top;
    top = top->next;
    string(*poppedData)[20] = temp->data; // data 포인터만 반환
    temp->data = nullptr; // 이제 pop() 호출자가 메모리 소유권을 가짐
    delete temp; // 노드 자체는 해제
    top->prdv = nullptr;

    return poppedData;
}


Node* LinkedListStack::peek()
{
    return top;
}

bool LinkedListStack::isEmpty()
{
    return top == nullptr;
}

int LinkedListStack::size() const
{
    return Size;
}