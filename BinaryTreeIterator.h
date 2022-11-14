#ifndef BINARY_TREE_ITERATOR_H
#define BINARY_TREE_ITERATOR_H
#include "Node.h"
#include <iterator>

template <typename T>
class BinaryTreeIterator: public
	std::iterator<std::bidirectional_iterator_tag, T> {
	template <typename T>
	friend class SelfBalancingBinaryTree;
private:
	Node<T>* current_;
	BinaryTreeIterator();
	BinaryTreeIterator(Node<T>* node);

public:
	bool operator==(const BinaryTreeIterator<T>& it) const;
	bool operator!=(const BinaryTreeIterator<T>& it) const;

	T& operator*() const;
	T* operator->() const;

	BinaryTreeIterator<T>& operator++();
	BinaryTreeIterator<T> operator++(int);

	BinaryTreeIterator<T>& operator--();
	BinaryTreeIterator<T> operator--(int);
};

template <typename T>
BinaryTreeIterator<T>::BinaryTreeIterator() :
	current_(nullptr) {}

template <typename T>
BinaryTreeIterator<T>::BinaryTreeIterator(Node<T>* node) :
	current_(node) {}

template <typename T>
bool BinaryTreeIterator<T>::
	operator==(const BinaryTreeIterator<T>& it) const {
	return current_ == it.current_;
}
template <typename T>
bool BinaryTreeIterator<T>::
	operator!=(const BinaryTreeIterator<T>& it) const {
	return current_ != it.current_;
}

template <typename T>
T& BinaryTreeIterator<T>::operator*() const {
	if (current_ == nullptr) {
		throw NullPointerDereference();
	}
	return current_->key_;
}

template <typename T>
T* BinaryTreeIterator<T>::operator->() const {
	if (current_ == nullptr) {
		throw NullPointerDereference();
	}
	return &current_->key_;
}

template <typename T>
BinaryTreeIterator<T>& BinaryTreeIterator<T>::operator++() {
	if (current_ == nullptr) {
		throw NullPointerDereference();
	}
	if (current_->right_ != nullptr) {
		current_ = current_->right_;
		while (current_->left_ != nullptr) {
			current_ = current_->left_;
		}
	} else {
		while (current_->p_ != nullptr &&
			current_->p_->right_ == current_) {
			current_ = current_->p_;
		}
		current_ = current_->p_;
	}
	return *this;
}

template <typename T>
BinaryTreeIterator<T> BinaryTreeIterator<T>::operator++(int) {
	BinaryTreeIterator<T> temp(*this);
	this->operator++();
	return temp;
}

template <typename T>
BinaryTreeIterator<T>& BinaryTreeIterator<T>::operator--() {
	if (current_ == nullptr) {
		throw NullPointerDereference();
	}
	if (current_->left_ != nullptr) {
		current_ = current_->left_;
		while (current_->right_ != nullptr) {
			current_ = current_->right_;
		}
	}
	else {
		while (current_->p_ != nullptr &&
			current_->p_->left_ == current_) {
			current_ = current_->p_;
		}
		current_ = current_->p_;
	}
	return *this;
}

template <typename T>
BinaryTreeIterator<T> BinaryTreeIterator<T>::operator--(int) {
	BinaryTreeIterator<T> temp(*this);
	this->operator--();
	return temp;
}
#endif