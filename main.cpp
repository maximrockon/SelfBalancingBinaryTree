#include "RequestHandler.h"
#include <vector>


int main(int argc, char* argv[]) {
	if (argc > 2) {
		std::cerr << "Invalid number of args\n";
		return -1;
	} else {
		RequestHandler handler;
		if (argc == 2) {
			std::ifstream in(argv[1]);
			if (!in.is_open()) {
				std::cerr << "Invalid filename\n";
				return -1;
			}
			handler.execute(&in, new SelfBalancingBinaryTree<int>());
		} else {
			handler.execute(&std::cin, new SelfBalancingBinaryTree<int>());
		}
	}
	
	return 0;
}