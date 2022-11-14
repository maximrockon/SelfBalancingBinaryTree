#include "RequestHandler.h"

void RequestHandler::execute(std::istream* in,
	SelfBalancingBinaryTree<int>* tree) {
	char c = '\0';
	int k;
	while (!in->eof()) {
		in->get(c);
		if (c == 'k' || c == 'm' || c == 'n') {
			in->get();
			*in >> k;
			in->get();
			if (c == 'k') {
				tree->insert(k);
			}
			else if (c == 'm') {
				try {
					std::cout << tree->getOrderStatistic(k) << '\n';
				} catch (StatisticOutOfRange& exc) {
					std::cerr << "Exception: "  << exc.what() << '\n';
				}
			}
			else {
				std::cout << tree->getNumberOfSmallerElements(k) << '\n';
			}
		} else {
			std::cerr << "Invalid syntax\n";
			while (!(c == 'k' || c == 'm' || c == 'n') && !in->eof()) {
				in->get(c);
			}
			in->putback(c);
		}
	}
}