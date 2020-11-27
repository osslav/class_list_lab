#include "List.h"



Node* List::searchKey(int key)
{
	if (isEmpty()) return nullptr;
	
	Node* newPosition = head_;

	while (newPosition->key_ != key)
	{
		newPosition = newPosition->next_;
		if (newPosition == nullptr) return nullptr;
	}

	return newPosition;
};


Node* List::searchIndex(int index)
{
	if (index < 0) return nullptr;

	Node* newPosition = head_;
	for (int i = 0; i < index; i++)
	{
		if (newPosition == nullptr) return nullptr;
		newPosition = newPosition->next_;
	}

	return newPosition;
};

List::List(int* arr, int count)
{
	head_ = tail_ = nullptr;
	for (int i = 0; i < count; i++)
		addTail(arr[i]);
}

List::List(const List &copy)
{
	head_ = tail_ = nullptr;
	
	if (copy.head_ != nullptr)
	{
		Node* copyElem = copy.head_;
		do
		{
			addTail(copyElem->key_);
			copyElem = copyElem->next_;
		} while (copyElem != nullptr);
	}	
}

void List::addHead(int key)
{
	Node* newElem = new Node(key, head_);
	if (!isEmpty()) head_->prev_ = newElem;
	else tail_ = newElem;
	head_ = newElem;
};


void List::addTail(int key)
{
	Node* newElem = new Node(key, nullptr, tail_);
	if (tail_ != nullptr) tail_->next_ = newElem;
	else head_ = newElem;
	tail_ = newElem;
};


void List::addAfterFirstKey(int findKey, int newKey)
{	
	Node* keyPosition = searchKey(findKey);
	if (keyPosition == nullptr) return;

	if (keyPosition->next_ != nullptr)
	{
		keyPosition->next_->prev_ = new Node(newKey, keyPosition->next_, keyPosition);
		keyPosition->next_ = keyPosition->next_->prev_;
	}
	else addTail(newKey);
};


void List::addByIndex(int index, int newKey)
{
	if (index < 0) return;

	if (index == 0)
	{
		addHead(newKey);
		return;
	}
	
	Node* newPosition = searchIndex(index - 1);

	if (newPosition != nullptr)
	{
		newPosition = newPosition->next_;
		if (newPosition != nullptr)
		{
			newPosition->prev_ = new Node(newKey, newPosition, newPosition->prev_);
			if (newPosition != head_) newPosition->prev_->prev_->next_ = newPosition->prev_;
			else head_ = newPosition->prev_;
		}
		else addTail(newKey);
	}
};


void List::outputByHead()
{
	Node* elem = head_;
	if (isEmpty()) std::cout << "List is empty.";
	else
	do
	{
		std::cout << elem->key_ << "  ";
		elem = elem->next_;
	} while (elem != nullptr);
	
	std::cout << '\n';
};


void List::outputByTail()
{
	Node* elem = tail_;
	if (isEmpty()) std::cout << "List is empty.";
	else
	do
	{
			std::cout << elem->key_ << "  ";
			elem = elem->prev_;
	} while (elem != nullptr);
	
	std::cout << '\n';
};


void List::deleteHead()
{
	if (!isEmpty())
	{
		Node* oldHead = head_;

		head_ = head_->next_;
		if (head_ != nullptr) head_->prev_ = nullptr;
		else tail_ = nullptr;

		delete oldHead;
	}
};


void List::deleteTail()
{
	if (!isEmpty())
	{
		Node* oldTail = tail_;

		tail_ = tail_->prev_;
		if (tail_ != nullptr)tail_->next_ = nullptr;
		else head_ = nullptr;

		delete oldTail;
	}
};


void List::deleteFirstKey(int findKey)
{
	Node* keyPosition = searchKey(findKey);
	if (keyPosition == nullptr) return;

	if (keyPosition->next_ != nullptr)
		if (keyPosition->prev_ != nullptr)
		{
			keyPosition->prev_->next_ = keyPosition->next_;
			keyPosition->next_->prev_ = keyPosition->prev_;
			delete keyPosition;
		}
		else deleteHead();
	else deleteTail();
};


void List::deleteByIndex(int index)
{
	Node* indexPosition = searchIndex(index);
	if (indexPosition == nullptr) return;

	if (indexPosition->next_ != nullptr)
		if (indexPosition->prev_ != nullptr)
		{
			indexPosition->prev_->next_ = indexPosition->next_;
			indexPosition->next_->prev_ = indexPosition->prev_;
			delete indexPosition;
		}
		else deleteHead();
	else deleteTail();
};

void List::clear()
{
	while (!isEmpty())
		deleteHead();
};

Node* List::searchMin()
{
	if (isEmpty()) return nullptr;
	
	Node* minElem = head_;
	Node* checkElem = head_->next_;

	while(checkElem != nullptr)
	{
		if (minElem->key_ > checkElem->key_) minElem = checkElem;
		checkElem = checkElem->next_;
	}

	return minElem;
};

Node* List::searchMax()
{
	if (isEmpty()) return nullptr;

	Node* maxElem = head_;
	Node* checkElem = head_->next_;

	while (checkElem != nullptr)
	{
		if (maxElem->key_ < checkElem->key_) maxElem = checkElem;
		checkElem = checkElem->next_;
	}

	return maxElem;
};

List& List::operator =(const List& term)
{
	Node* thisElem = head_;
	Node* termElem = term.head_;
	while (termElem != nullptr)
	{
		if (thisElem != nullptr)
		{
			tail_ = thisElem;		
			thisElem->key_ = termElem->key_;
			thisElem = thisElem->next_;
		}
		else
		{
			addTail(termElem->key_);
			thisElem = tail_->next_;
		}
		termElem = termElem->next_;
	}
	
	if (term.head_ == nullptr)
	{
		tail_ = nullptr;
		head_ = nullptr;
	}
	else tail_->next_ = nullptr;

	while (thisElem != nullptr)
	{
		Node* prevThisElem = thisElem;
		thisElem = thisElem->next_;
		delete prevThisElem;
	}
	
	/*
	clear();
		
	Node* termElem = term.head_;
	while (termElem != nullptr)
	{
		addTail(termElem->key_);
		termElem = termElem->next_;
	}*/
	
	return *this;
};

bool List::operator ==(const List& term)
{
	Node* thisElem = head_;
	Node* termElem = term.head_;

	while ((thisElem != nullptr) && (termElem != nullptr))
	{
		if (thisElem->key_ != termElem->key_) return false;
		thisElem = thisElem->next_;
		termElem = termElem->next_;
	}

	return ((thisElem == nullptr) && (termElem == nullptr));
};

bool List::operator !=(const List& term)
{
	Node* thisElem = head_;
	Node* termElem = term.head_;

	while ((thisElem != nullptr) && (termElem != nullptr))
	{
		if (thisElem->key_ != termElem->key_) return true;
		thisElem = thisElem->next_;
		termElem = termElem->next_;
	}

	return ((thisElem != nullptr) || (termElem != nullptr));
};

List List::operator +(const List& term)
{
	List result(*this);

	Node* termElem = term.head_;
	while (termElem != nullptr)
	{
		result.addTail(termElem->key_);
		termElem = termElem->next_;
	}

	return result;
};



std::ostream& operator <<(std::ostream& f, List& term)
{
	Node* elem = term.head_;
	if (term.isEmpty()) f << "List is empty.";
	else
		do
		{
			f << elem->key_ << "  ";
			elem = elem->next_;
		} while (elem != nullptr);

	std::cout << '\n';
	return f;
};

std::istream& operator >>(std::istream& f, List& term)
{
	int count;
	std::cout << "Enter count of elements: ";
	f >> count;

	while (count < 0)
	{
		std::cout << "Count must be < 0. Enter here again: ";
		f >> count;
	}

	if (count != 0) std::cout << "Enter list: ";

	Node* termElem = term.head_;
	for (int newKey, i = 0; i < count; i++)
	{
		f >> newKey;
		if (termElem != nullptr)
		{
			term.tail_ = termElem;
			termElem->key_ = newKey;
			termElem = termElem->next_;
		}
		else
		{
			term.addTail(newKey);
			termElem = term.tail_->next_;
		}
	}

	if (count == 0)
	{
		term.tail_ = nullptr;
		term.head_ = nullptr;
	}
	else term.tail_->next_ = nullptr;

	while (termElem != nullptr)
	{
		Node* prevTermElem = termElem;
		termElem = termElem->next_;
		delete prevTermElem;
	}

	return f;
};