#include <gtest/gtest.h>
#include "SelfBalancingBinaryTree.h"
#include <cstdlib>
#include <set>

TEST(tree, getOrderStatistic) {
    SelfBalancingBinaryTree<int> t1;
    SelfBalancingBinaryTree<int> t2;
    SelfBalancingBinaryTree<int> t3;
    std::set<int> s;
    const uint32_t size = 100;
    int temp;

    for (int i = 0; i < size; ++i) {
        t1.insert(i);
        t2.insert(size - i - 1);
        temp = std::rand();
        s.insert(temp);
        t3.insert(temp);
    }

    ASSERT_THROW(t1.getOrderStatistic(0), StatisticOutOfRange);
    ASSERT_THROW(t2.getOrderStatistic(0), StatisticOutOfRange);
    ASSERT_THROW(t3.getOrderStatistic(0), StatisticOutOfRange);
    
    ASSERT_THROW(t1.getOrderStatistic(size + 1), StatisticOutOfRange);
    ASSERT_THROW(t2.getOrderStatistic(size + 1), StatisticOutOfRange);
    ASSERT_THROW(t3.getOrderStatistic(size + 1), StatisticOutOfRange);
    auto it = s.begin();
    for (int i = 0; i < size; ++i, ++it) {
        ASSERT_EQ(t1.getOrderStatistic(i + 1), i);
        ASSERT_EQ(t2.getOrderStatistic(i + 1), i);
        ASSERT_EQ(t3.getOrderStatistic(i + 1), *it);
    }
}

TEST(tree, getNumberOfSmallerElements) {
    SelfBalancingBinaryTree<int> t1;
    SelfBalancingBinaryTree<int> t2;
    const uint32_t size = 100;

    for (int i = 0; i < size; ++i) {
        t1.insert(2 * i);
        t2.insert(2* (size - i - 1));
    }

    ASSERT_EQ(t1.getNumberOfSmallerElements(-1), 0);
    ASSERT_EQ(t2.getNumberOfSmallerElements(-1), 0);

    for (int i = 0; i < 2 * size; ++i) {
        ASSERT_EQ(t1.getNumberOfSmallerElements(i), (i + 1) / 2);
        ASSERT_EQ(t2.getNumberOfSmallerElements(i), (i + 1) / 2);
    }
}

TEST(tree, begin_end) {
    SelfBalancingBinaryTree<int> t1;
    SelfBalancingBinaryTree<int> t2;
    SelfBalancingBinaryTree<int> t3;
    const uint32_t size = 100;

    for (int i = 0; i < size; ++i) {
        t1.insert(i);
        t2.insert(size - i - 1);
        t3.insert(std::rand());
    }

    
    auto it1 = t1.begin();
    auto it2 = t2.begin();
    auto it3 = t3.begin();

    for (int i = 0; i < size; ++i) {
        ASSERT_EQ(*(it1++), t1.getOrderStatistic(i + 1));
        ASSERT_EQ(*(it2++), t2.getOrderStatistic(i + 1));
        ASSERT_EQ(*(it3++), t3.getOrderStatistic(i + 1));
    }

    ASSERT_THROW(*it1, NullPointerDereference);
    ASSERT_THROW(*it2, NullPointerDereference);
    ASSERT_THROW(*it3, NullPointerDereference);
}

