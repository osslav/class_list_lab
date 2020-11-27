//#pragma once

#ifndef node
#define node

#include <iostream>

class Node
{
	friend class List;
	int key_;
	Node* next_, * prev_;

	Node(int key, Node* next = nullptr, Node* prev = nullptr) { key_ = key;  next_ = next; prev_ = prev; };

public:
	int getKey() { return key_; };

	friend std::ostream& operator <<(std::ostream& f, List& term);
	friend std::istream& operator >>(std::istream& f, List& term);
};
#endif