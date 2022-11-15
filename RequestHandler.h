#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include "SelfBalancingBinaryTree.h"
#include <fstream>

class RequestHandler {
public:
	void execute(std::istream* in,
		SelfBalancingBinaryTree<int>* tree);
};

#endif