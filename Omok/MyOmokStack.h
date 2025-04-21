#pragma once
#ifndef MYOMOKSTACK_H
#define MYOMOKSTACK_H

#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    string(*data)[20]; // 20개의 string 배열을 가리키는 포인터
    Node* next;
    Node* prdv;

    Node(const std::string(&map)[20][20]);

    ~Node();
};

class LinkedListStack {
private:
    Node* top; // 스택의 맨 위 노드를 가리키는 포인터
    int Size{};

public:
    // 생성자: 스택을 초기화합니다.
    LinkedListStack();

    // 소멸자: 스택의 모든 노드를 해제합니다.
    ~LinkedListStack();
    // push: 스택의 맨 위에 새 요소를 추가합니다.
    void push(const string(&map)[20][20]);

    // pop: 스택의 맨 위 요소를 제거하고 그 값을 반환합니다.
    string(*pop())[20];

    // peek: 스택의 맨 위 요소를 반환하지만 제거하지는 않습니다.
    Node* peek();

    // isEmpty: 스택이 비어 있는지 확인합니다.
    bool isEmpty();

    // size: 스택의 현재 요소 개수를 반환합니다 (선택 사항).
    int size() const;
};

#endif