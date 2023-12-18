/* 
 * Description: 珂朵莉树的基本实现
 * Create: 2023-12-16
 * Owner: 
 */

#include "chthollytree.h"

namespace Chtholly {

std::set<ChthollyTreeNode>::iterator ChthollyTree::Split(int pos)
{
    if (pos > tree_.size()) {
        return tree_.end();
    }

    auto it = tree_.upper_bound(ChthollyTreeNode{pos, 0, 0});  // 寻找左边大于等于pos的第一个节点
    --it;
    if (it->left == pos) {
        return it;
    }
    int l = it->left, r = it->right, val = it->val;
    tree_.erase(it);
    tree_.insert(ChthollyTreeNode(l, pos - 1, val));
    return tree_.insert(ChthollyTreeNode(pos, r, val)).first;
}

void ChthollyTree::Assign(int l, int r, int v)
{
    auto itRight = Split(r + 1), itLeft = Split(l);
    tree_.erase(itLeft, itRight);
    tree_.insert(ChthollyTreeNode(l, r, v));
}

void ChthollyTree::Insert(int l, int r, int v)
{
    tree_.insert(ChthollyTreeNode(l, r, v));
}

} // namespace Chtholly