//#pragma once

#ifndef list
#define list

#include "Node.h"

enum NodeErrorCode
{
	indexPositionOutRange = 1,
};

class List
{
	Node* head_, * tail_;

	Node* searchKey(int key);
	Node* searchIndex(int key);

public:
	List() { head_ = tail_ = nullptr; };
	explicit List(int key) { tail_ = head_ = new Node(key); };
	List(int* arr, int count);
	List(const List& copy);
	~List() { clear(); };

	void addHead(int key);
	void addTail(int key);
	void addAfterFirstKey(int findKey, int newKey);
	void addByIndex(int index, int newKey);                     //исправить? 

	void deleteHead();
	void deleteTail();
	void deleteFirstKey(int findKey);
	void deleteByIndex(int index);                                 //доделать +

	bool isEmpty() { return (head_ == nullptr); };

	void outputByHead();
	void outputByTail();

	void clear();

	Node* searchMin();
	Node* searchMax();

	List& operator =(const List& term);                          //оптимизировать +

	int& operator[](int index) { Node* indexPosition = searchIndex(index); if (indexPosition == nullptr) throw indexPositionOutRange; return indexPosition->key_; };

	bool operator ==(const List& term);
	bool operator !=(const List& term); 

	List operator +(const List& term);               //исправить +

	friend std::ostream& operator <<(std::ostream& f, List& term);
	friend std::istream& operator >>(std::istream& f, List& term);              //исправить +
};

#endif