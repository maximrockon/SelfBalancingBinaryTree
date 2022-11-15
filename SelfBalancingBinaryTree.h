#ifndef SELF_BALANCING_BINARY_TREE_H
#define SELF_BALANCING_BINARY_TREE_H
#include "MyExceptions.h"
#include "BinaryTreeIterator.h"
#include <cstdint>

template <typename T>
class SelfBalancingBinaryTree {
private:
	Node<T>* root_;
	// change the number of children
	// of all parent nodes of this node
	void changeCountChildren(Node<T>* node, bool flag);

	void rotateLeft(Node<T>* node);

	void bigRotateLeft(Node<T>* node);

	void rotateRight(Node<T>* node);

	void bigRotateRight(Node<T>* node);

	int64_t getHeightSubTree(Node<T>* node) const;

	Node<T>* iterativeSearchNode(const T& key) const;

	void checkBalance(Node<T>* node);

	void inorderWalk(Node<T>* node) const;

	void deleteSubtree(Node<T>* node);
public:
	using Iterator = BinaryTreeIterator<T>;
	
	SelfBalancingBinaryTree();
	SelfBalancingBinaryTree(const SelfBalancingBinaryTree<T>& t) = delete;
	SelfBalancingBinaryTree(SelfBalancingBinaryTree<T>&& t);

	SelfBalancingBinaryTree<T>& operator=
		(const SelfBalancingBinaryTree<T>& t) = delete;
	SelfBalancingBinaryTree<T>& operator=
		(SelfBalancingBinaryTree<T>&& t);

	virtual ~SelfBalancingBinaryTree();

	Iterator begin() const;

	Iterator end() const;

	bool iterativeSearch(const T& key) const;
	// request (k v)
	bool insert(const T& key);

	bool deleteKey(const T& key);
	// request (m i)
	T getOrderStatistic(const uint32_t k) const;
	// request (n j)
	uint32_t getNumberOfSmallerElements(const T& key) const;

	void inorderWalk() const;
};

template <typename T>
SelfBalancingBinaryTree<T>::SelfBalancingBinaryTree():
	root_(nullptr) {}

template <typename T>
SelfBalancingBinaryTree<T>::
	SelfBalancingBinaryTree(SelfBalancingBinaryTree<T>&& t) {
	*this = move(t);
}

template <typename T>
SelfBalancingBinaryTree<T>& SelfBalancingBinaryTree<T>::
	operator= (SelfBalancingBinaryTree<T>&& t) {
	if (this != &t) {
		deleteSubtree(this->root_);
		this->root_ = t.root_;
		t.root_ = nullptr;
	}
	return *this;
}

template <typename T>
SelfBalancingBinaryTree<T>::~SelfBalancingBinaryTree() {
	deleteSubtree(root_);
}

template <typename T>
BinaryTreeIterator<T>
	SelfBalancingBinaryTree<T>::begin() const {
	Node<T>* temp = root_;
	while (temp->left_ != nullptr) {
		temp = temp->left_;
	}
	return BinaryTreeIterator<T>(temp);
}

template <typename T>
BinaryTreeIterator<T>
	SelfBalancingBinaryTree<T>::end() const {
	return BinaryTreeIterator<T>(nullptr);
}

template <typename T>
void SelfBalancingBinaryTree<T>::
	changeCountChildren(Node<T>* node, bool flag)
{
	Node<T>* temp = node->p_;
	while (temp != nullptr) {
		if (flag) {
			++temp->countChildren_;
		} else {
			--temp->countChildren_;
		}
		temp = temp->p_;
	}
}

template <typename T>
void SelfBalancingBinaryTree<T>::
	rotateLeft(Node<T>* node) {
	Node<T>* newRoot = node->right_;

	newRoot->countChildren_ = node->countChildren_;
	--node->countChildren_;
	if (newRoot->right_ != nullptr) {
		node->countChildren_ -=
			1 + newRoot->right_->countChildren_;
	}

	if (node == root_) {
		root_ = newRoot;
	} else if (node->p_->left_ == node) {
		node->p_->left_ = newRoot;
	} else {
		node->p_->right_ = newRoot;
	}
	newRoot->p_ = node->p_;
	node->right_ = newRoot->left_;
	if (newRoot->left_ != nullptr) {
		newRoot->left_->p_ = node;
	}
	newRoot->left_ = node;
	node->p_ = newRoot;
}

template <typename T>
void SelfBalancingBinaryTree<T>::
	bigRotateLeft(Node<T>* node) {
	Node<T>* newRoot = node->right_->left_;

	newRoot->countChildren_ = node->countChildren_;
	node->countChildren_ -= 2;
	if (node->right_->right_ != nullptr) {
		node->countChildren_ -=
			1 + node->right_->right_->countChildren_;
	}
	if (newRoot->right_ != nullptr) {
		node->countChildren_ -=
			1 + newRoot->right_->countChildren_;
	}
	--node->right_->countChildren_;
	if (newRoot->left_ != nullptr) {
		node->right_->countChildren_ -=
			1 + newRoot->left_->countChildren_;
	}

	if (node == root_) {
		root_ = newRoot;
	} else if (node->p_->left_ == node) {
		node->p_->left_ = newRoot;
	} else {
		node->p_->right_ = newRoot;
	}
	newRoot->p_ = node->p_;
	Node<T>* rightNode = node->right_;
	rightNode->left_ = newRoot->right_;
	if (newRoot->right_ != nullptr) {
		newRoot->right_->p_ = rightNode;
	}
	node->right_ = newRoot->left_;
	if (newRoot->left_ != nullptr) {
		newRoot->left_->p_ = node;
	}
	newRoot->right_ = rightNode;
	rightNode->p_ = newRoot;
	newRoot->left_ = node;
	node->p_ = newRoot;
}

template <typename T>
void SelfBalancingBinaryTree<T>::
	rotateRight(Node<T>* node) {
	Node<T>* newRoot = node->left_;

	newRoot->countChildren_ = node->countChildren_;
	--node->countChildren_;
	if (newRoot->left_ != nullptr) {
		node->countChildren_ -=
			1 + newRoot->left_->countChildren_;
	}

	if (node == root_) {
		root_ = newRoot;
	} else if (node->p_->left_ == node) {
		node->p_->left_ = newRoot;
	} else {
		node->p_->right_ = newRoot;
	}
	newRoot->p_ = node->p_;
	node->left_ = newRoot->right_;
	if (newRoot->right_ != nullptr) {
		newRoot->right_->p_ = node;
	}
	newRoot->right_ = node;
	node->p_ = newRoot;
}

template <typename T>
void SelfBalancingBinaryTree<T>::
	bigRotateRight(Node<T>* node) {
	Node<T>* newRoot = node->left_->right_;

	newRoot->countChildren_ = node->countChildren_;
	node->countChildren_ -= 2;
	if (node->left_->left_ != nullptr) {
		node->countChildren_ -=
			1 + node->left_->left_->countChildren_;
	}
	if (newRoot->left_ != nullptr) {
		node->countChildren_ -=
			1 + newRoot->left_->countChildren_;
	}
	--node->left_->countChildren_;
	if (newRoot->right_ != nullptr) {
		node->left_->countChildren_ -=
			1 + newRoot->right_->countChildren_;
	}

	if (node == root_) {
		root_ = newRoot;
	} else if (node->p_->left_ == node) {
		node->p_->left_ = newRoot;
	} else {
		node->p_->right_ = newRoot;
	}
	newRoot->p_ = node->p_;
	Node<T>* leftNode = node->left_;
	leftNode->right_ = newRoot->left_;
	if (newRoot->left_ != nullptr) {
		newRoot->left_->p_ = leftNode;
	}
	node->left_ = newRoot->right_;
	if (newRoot->right_ != nullptr) {
		newRoot->right_->p_ = node;
	}
	newRoot->left_ = leftNode;
	leftNode->p_ = newRoot;
	newRoot->right_ = node;
	node->p_ = newRoot;
}

template <typename T>
int64_t SelfBalancingBinaryTree<T>::
	getHeightSubTree(Node<T>* node) const {
	Node<T>* current = node;
	if (current != nullptr) {
		int height = std::max(getHeightSubTree(current->left_),
			getHeightSubTree(current->right_)) + 1;
		return height;
	}
	return -1;
}

template <typename T>
void SelfBalancingBinaryTree<T>::checkBalance(Node<T>* node) {
	while (node != nullptr) {
		int64_t heightLeftSubTree = getHeightSubTree(node->left_);
		int64_t heightRightSubTree = getHeightSubTree(node->right_);
		if (heightLeftSubTree - heightRightSubTree == 0) {
			return;
		} else if ((heightLeftSubTree - heightRightSubTree) == 1
			|| (heightLeftSubTree - heightRightSubTree) == -1) {
			node = node->p_;
		} else if (heightLeftSubTree - heightRightSubTree == 2) {
			if (getHeightSubTree(node->left_->right_) <=
				getHeightSubTree(node->left_->left_)) {
				rotateRight(node);
			} else {
				bigRotateRight(node);
			}
			return;
		} else if (heightRightSubTree - heightLeftSubTree == 2) {
			if (getHeightSubTree(node->right_->left_) <=
				getHeightSubTree(node->right_->right_)) {
				rotateLeft(node);
			} else {
				bigRotateLeft(node);
			}
			return;
		}
	}
}

template <class T>
void SelfBalancingBinaryTree<T>::deleteSubtree(Node<T>* node)
{
	if (node != nullptr)
	{
		deleteSubtree(node->left_);
		deleteSubtree(node->right_);
		delete node;
	}
}


template <typename T>
bool SelfBalancingBinaryTree<T>::insert(const T& key) {
	if (root_ == nullptr) {
		root_ = new Node<T>(key);
		return 1;
	} else {
		Node<T>* current = root_;
		while (current->key_ != key
			&& (current->right_ != nullptr || key < current->key_)
			&& (current->left_ != nullptr || key > current->key_)) {
			if (key > current->key_) {
				current = current->right_;
			} else {
				current = current->left_;
			}
		}
		if (current->key_ == key) {
			return false;
		} else {
			Node<T>* newNode = new Node<T>(key);
			newNode->p_ = current;
			if (key > current->key_) {
				current->right_ = newNode;
			} else {
				current->left_ = newNode;
			}
			changeCountChildren(newNode, true);
			checkBalance(newNode->p_);
			return true;
		}
	}
}

template <typename T>
bool SelfBalancingBinaryTree<T>::deleteKey(const T& key) {
	Node<T>* deleteNode = iterativeSearchNode(key);
	if (deleteNode == nullptr) {
		return false;
	} else {
		if (deleteNode->left_ == nullptr &&
			deleteNode->right_ == nullptr) {
			if (deleteNode->p_ == nullptr) {
				root_ = nullptr;
				delete deleteNode;
			} else {
				changeCountChildren(deleteNode, false);
				if (deleteNode->p_->left_ == deleteNode) {
					deleteNode->p_->left_ = nullptr;
				} else {
					deleteNode->p_->right_ = nullptr;
				}
				Node<T>* node = deleteNode->p_;
				delete deleteNode;
				checkBalance(node);
			}
		} else if (deleteNode->left_ == nullptr
			&& deleteNode->right_->left_ == nullptr
			&& deleteNode->right_->right_ == nullptr) {
			Node<T>* deleteNodeRight = deleteNode->right_;
			changeCountChildren(deleteNodeRight, false);
			deleteNode->key_ = deleteNodeRight->key_;
			deleteNode->right_ = nullptr;
			delete deleteNodeRight;
			checkBalance(deleteNode);
		} else if (deleteNode->right_ == nullptr 
			&& deleteNode->left_->left_ == nullptr
			&& deleteNode->left_->right_ == nullptr) {
			Node<T>* deleteNodeLeft = deleteNode->left_;
			changeCountChildren(deleteNodeLeft, false);
			deleteNode->key_ = deleteNodeLeft->key_;
			deleteNode->left_ = nullptr;
			delete deleteNodeLeft;
			checkBalance(deleteNode);
		} else {
			Node<T>* current = nullptr;
			if (deleteNode->right_ == nullptr)
			{
				current = deleteNode->left_;
				while (current->right_ != nullptr)
				{
					current = current->right_;
				}
			}
			else
			{
				current = deleteNode->right_;
				while (current->left_ != nullptr)
				{
					current = current->left_;
				}
			}
			T newKey = current->key_;
			deleteKey(current->key_);
			deleteNode->key_ = newKey;
		}
		return true;
	}
}

template <typename T>
T SelfBalancingBinaryTree<T>::
	getOrderStatistic(const uint32_t k) const {
	Node<T>* current = root_;
	uint32_t comp = 0;
	while (current != nullptr) {
		if (current->left_ != nullptr) {
			if (k == (current->left_->countChildren_ + 2 + comp)) {
				return current->key_;
			} else if (k <
				(current->left_->countChildren_ + 2 + comp)) {
				current = current->left_;
				continue;
			} else {
				comp += current->left_->countChildren_ + 2;
				current = current->right_;
			}
		} else {
			if (k == (1 + comp)) {
				return current->key_;
			} else if (k < (1 + comp)) {
				current = current->left_;
				continue;
			} else {
				++comp;
				current = current->right_;
			}
		}
	}
	if (current == nullptr) {
		throw StatisticOutOfRange();
	}
}

template <typename T>
uint32_t SelfBalancingBinaryTree<T>::
	getNumberOfSmallerElements(const T& key) const {
	Node<T>* current = root_;
	uint32_t comp = 0;
	while (current != nullptr) {
		if (current->key_ == key) {
			if (current->left_ != nullptr) {
				return current->left_->countChildren_ + 1 + comp;
			} else {
				return comp;
			}
		} else if (current->key_ > key) {
			if (current->left_ != nullptr) {
				current = current->left_;
				continue;
			} else {
				return comp;
			}
		} else {
			++comp;
			if (current->left_ != nullptr) {
				comp += current->left_->countChildren_ + 1;
			}
			if (current->right_ != nullptr) {
				current = current->right_;
				continue;
			} else {
				return comp;
			}
		}
	}
}

template <typename T>
Node<T>* SelfBalancingBinaryTree<T>::
	iterativeSearchNode(const T& key) const {
	Node<T>* current = root_;
	while (current != nullptr && current->key_ != key)
	{
		if (key > current->key_)
		{
			current = current->right_;
		}
		else
		{
			current = current->left_;
		}
	}
	return current;
}

template <typename T>
void SelfBalancingBinaryTree<T>::
	inorderWalk(Node<T>* node) const {
	if (node != nullptr)
	{
		inorderWalk(node->left_);
		std::cout << '(' << node->key_ << "; "
			<< node->countChildren_ << ")\n";
		inorderWalk(node->right_);
	}
}

template <typename T>
void SelfBalancingBinaryTree<T>::inorderWalk() const {
	inorderWalk(root_);
}

#endif