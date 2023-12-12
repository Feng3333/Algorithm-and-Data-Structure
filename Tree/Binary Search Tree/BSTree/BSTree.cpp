#include "BSTree.h"


void BSTreeTest1()
{
    int num[] = {8, 3, 1, 2, 9, 0, 4, 7, 5, 6};
    BSTREE::BSTree<int> t1;
    for (auto i : num) {
        t1.Insert(i);
    }
    std::cout << "中序遍历: ";
    t1.InOrder();
}

int main()
{
    BSTreeTest1();
    return 0;
}