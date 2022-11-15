#ifndef NODE_H
#define NODE_H

// binary tree node
template <typename T>
class Node {
	template <typename T1>
	friend class SelfBalancingBinaryTree;
	template <typename T2>
	friend class BinaryTreeIterator;
private:
	T key_;
	// number of children of this node
	uint32_t countChildren_;
	Node<T>* p_;
	Node<T>* left_;
	Node<T>* right_;

	Node(T key, uint32_t countChildren = 0, Node<T>* p = nullptr,
		Node<T>* left = nullptr, Node<T>* right = nullptr) :
		key_(key), countChildren_(countChildren), p_(p), left_(left), right_(right) {}
};

#endif