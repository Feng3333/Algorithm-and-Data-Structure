# 珂朵莉树
## 珂朵莉树的基本介绍
## 完整代码（set实现）
```cpp
class ChthollyTree{
  
  struct ChthollyNode {
    int l,r,v;
    ChthollyNode(int l,int r, int v) : l(l), r(r), v(v) {}
    bool operator<(const ChthollyNode &o) const {
      return l < o.l;
    }
  };
  
  set<ChthollyNode> tree;
  
public:
  ChthollyTree() {}
  
  set<ChthollyNode>::iterator split(int position) {
    auto it = tree.lower_bound(ChthollyNode(position,0,0)); //寻找左边大于等于position的第一个节点
    if (it != tree.end() && it->l == position) {
      return it;
    }
    it--;
    int l = it->l, r = it->r, v = it->v;
    tree.erase(it);
    tree.insert(ChthollyNode(l,position-1,v));
    return tree.insert(ChthollyNode(position,r,v)).first;
  }
  
  void assign(int l, int r, int v) {
    auto itree = split(r+1);
    auto itl = split(l);
    tree.erase(itl,itree);
    tree.insert(ChthollyNode(l,r,v));
  }
  
  bool check(int l, int r) {
    auto itree = split(r+1);
    auto itl = split(l);
    auto it = itl;
    for (; it != tree.end(); it++) {
      if (it->v == 0) return false;
    }
    
    return true;
  }
  
  void insert(int l, int r, int v) {
    tree.insert(ChthollyNode(l,r,v));
  }
  
};
```