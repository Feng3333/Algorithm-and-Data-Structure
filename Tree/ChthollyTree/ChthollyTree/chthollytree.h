/* 
 * Description: 珂朵莉树的基本实现
 * Create: 2023-12-16
 * Owner: 
 */

#ifndef CHTHOLLY_TREE
#define CHTHOLLY_TREE

#include <set>

namespace Chtholly {

// 珂朵莉树的节点结构
struct ChthollyTreeNode {
    int left, right;    // 集合中每个元素中的左右端点
    mutable int val;     // 集合中每个元素的value
    ChthollyTreeNode(int a = -1, int b = -1, int c = 0) : left(a), right(b), val(c) {};

    bool operator<(const ChthollyTreeNode& node) {
        if (left == node.left) {
            return right < node.right;
        }
        return left < node.left;
    };

};

class ChthollyTree{
public:
    // 将包含pos的区间[l, r]拆分成两个区间[l, x)和[x, r]
    std::set<ChthollyTreeNode>::iterator Split(int pos);
    // 对某个区间[l, r]进行赋值
    void Assign(int l, int r, int v);
    void Insert(int l, int r, int v);

private:
    std::set<ChthollyTreeNode> tree_;
};

} // namespace Chtholly

#endif // CHTHOLLY_TREE