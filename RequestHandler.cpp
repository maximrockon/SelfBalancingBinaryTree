#include "RequestHandler.h"

void RequestHandler::execute(std::istream* in,
	SelfBalancingBinaryTree<int>* tree) {
	char c = '\0';
	int k;
	while (!in->eof()) {
		in->get(c);
		if (c == '\n' || c == ' ' || c == '\t' || c == char(13)) {
			continue;
		}
		if (!in->eof() && (c == 'k' || c == 'm' || c == 'n')) {
			*in >> k;
			if (!(*in)) {
				in->clear();
				std::cin.ignore(32767, '\n');
				std::cerr << "Invalid syntax\n";
				continue;
			}
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
		} else if (!in->eof()) {
			std::cerr << "Invalid syntax\n";
			while (!(c == 'k' || c == 'm' || c == 'n') && !in->eof()) {
				in->get(c);
			}
			in->putback(c);
		}
	}
}
