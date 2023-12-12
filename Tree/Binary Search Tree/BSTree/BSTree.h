/* 
 * Description: 二叉搜索树的基本实现
 * Create: 2023-12-08
 * Owner: 
 */

#include <iostream>

namespace BSTREE {

// 定义二叉搜索树的节点
template<class K>
struct BSTreeNode {
    BSTreeNode<K>* leftSubNode;
    BSTreeNode<K>* rightSubNode;
    K val;

    BSTreeNode(const K& value) : leftSubNode(nullptr), rightSubNode(nullptr), val(value) {}
};


// 二叉搜索树
template<class K>
class BSTree {
    typedef BSTreeNode<K> Node;

public:
    BSTree() = default;           // 指定强制生成默认构造
    // BSTree() : root_(nullptr) {};  // 默认构造

    Node* Copy(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }
        Node* newRoot = new Node(root->val);
        newRoot->leftSubNode = Copy(root->leftSubNode);
        newRoot->rightSubNode = Copy(root->rightSubNode);

        return newRoot;
    };

    void BSTREE(const BSTree<K>& t) {           // 拷贝构造
        root_ = Copy(t.root_);
    };

    BSTree<K> &operator = (BSTree<K> t) {  // 赋值重载
        swap(root_, t.root_);
        return *this;
    };    
    
    void Destroy(Node*& root) {
        if (root == nullptr) {
            return;
        }

        // 后续遍历析构
        Destroy(root->leftSubNode);
        Destroy(root->rightSubNode);

        delete root;
        root = nullptr;
    };

    ~BSTree() {                     // 析构函数
        Destroy(root_);
    };

    // 插入key值
    bool Insert(const K& key) {
        // 如果root_一开始为nullptr, 需直接构造初始的根
        if (root_ == nullptr) {
            root_ = new Node(key);
            return true;
        }

        Node* parent = nullptr;
        Node* cur = root_;
        while (cur) {
            if (key < cur->val) {
                parent = cur;
                cur = cur->leftSubNode;
            } else if (key > cur->val) {
                parent = cur;
                cur = cur->rightSubNode;
            } else {
                // 如果key == cur->val, 返回false，二叉搜索树不允许值相同
                return false;
            }
        }

        cur = new Node(key);
        if (key > parent->val) {
            parent->rightSubNode = cur;
        } else if (key < parent->val) {
            parent->leftSubNode = cur;
        }

        return true;
    };

    // 递归实现插入key值
    bool InsertByRecusion(Node*& root, const K& key) {
        if (root == nullptr) {
            root = new Node(key);
            return true;
        }

        if (key > root->val) {
            return InsertByRecusion(root->rightSubNode, key);
        } else if (key < root->val) {
            return InsertByRecusion(root->leftSubNode, key);
        } else {
            return false;
        }
    };
    
    // 查找key值   
    bool Find(const K& key) {
        Node* cur = root_;
        while(cur) {
            if (key < cur->val) {
                cur = cur->leftSubNode;
            } else if (key > cur->val) {
                cur = cur->rightSubNode;
            } else {
                return true;
            }
        }

        return false;
    };

    // 递归实现 查找key值
    bool FindByRecusion(Node* root, const K& key) {
        if  (root == nullptr) {
            return false;
        }

        if (key == root->val) {
            return true;
        }

        if (key < root->val) {
            return FindByRecusion(root->leftSubNode, key);
        } else {
            return FindByRecusion(root->rightSubNode, key);
        }
        return false;
    };


    // 删除key值    
    bool Erase(const K& key) {
        Node* parent = nullptr;
        Node* cur = root_;
        while (cur) {
            if (key > cur->val) {
                parent = cur;
                cur = cur->rightSubNode;
            } else if (key < cur->val) {
                parent = cur;
                cur = cur->leftSubNode;
            } else {
                // 开始删除
                // 如果要删除的cur左边是nullptr, 那么就进行判断, 判断cur在parent的左子树还是右子树,
                // 如果是左子树, 那么就由parent的left指向cur的右子树, 如果是右子树，那就由parent的right指向cur的右子树
                if (cur->leftSubNode == nullptr) {
                    if (cur == root_) {
                        root_ = cur->rightSubNode;
                    } else {
                        if (parent->leftSubNode == cur) {
                            parent->leftSubNode = cur->rightSubNode;
                        } else {
                            parent->rightSubNode = cur->rightSubNode;
                        }
                    }

                    delete cur;
                } else if (cur->rightSubNode == nullptr) {  // cur的右边为nullptr
                    if (cur == root_) {
                        root_ = cur->leftSubNode;
                    } else {
                        if (parent->leftSubNode == cur) {
                            parent->leftSubNode = cur->leftSubNode;
                        } else {
                            parent->rightSubNode = cur->leftSubNode;
                        }
                    }

                    delete cur;
                } else {
                    // cur的左右子树都不为nullptr时, 用被删除的cur的左子树的最大节点，右子树的最大节点替换

                    // 找到cur右子树的最大节点
                    Node* pminRight = cur;
                    Node* minRight = cur->rightSubNode;

                    // 找到右子树, 右子树的最小位置在右子树的左边
                    while (minRight->leftSubNode) {
                        pminRight = minRight;
                        minRight = minRight->leftSubNode;
                    }

                    // 找到最小的值赋值给cur
                    cur->val = minRight->val;

                    // pminRight->leftSubNode == minRight, 那么左边已经是最小的了，所以minRight的左子树肯定为空了
                    // 那么可能minRight还有右子树, 需要pminRight来领养
                    if (pminRight->leftSubNode == minRight) {
                        pminRight->leftSubNode = minRight->rightSubNode;
                    } else {
                        // 如果不是，比如删除根节点, 那么就需要将 pminRight->rightSubNode 指向 minRight->rightSubNode (最小值左边一定为nullptr, 不需要领养)
                        // minRight 是其父节点的右孩子
                        pminRight->rightSubNode = minRight->rightSubNode;
                    }

                    delete minRight;
                }

                return true;
            }
        }

        return false;
    };

    /* 递归实现, 删除key值: 
    *  若树为空树, 则删除节点失败, 返回false;
    *  若所给key值小于树根节点的值, 则问题变为删除左子树当中值为key的节点
    *  若所给key值大于树根节点的值, 则问题变为删除右子树当中值为key的节点
    *  若所给key值等于树根节点的值, 则根据根节点左右子树的存在情况不同, 进行处理
    */
    bool EraseByRecusion(Node*& root, const K& key) {
        if (root == nullptr) {
            return false;
        }

        if (key < root->val) {
            return EraseByRecusion(root->leftSubNode, key);
        } else if (key > root->val) {
            return EraseByRecusion(root->rightSubNode, key);
        } else {
            Node* del = root;
            // 开始准备删除, root谁上层
            if (root->leftSubNode == nullptr) {
                root = root->rightSubNode;
            } else if (root->rightSubNode == nullptr) {
                root = root->leftSubNode;
            } else {
                Node* maxLeft = root->leftSubNode;
                // 找最大，最大在右子树这里
                while (maxLeft->rightSubNode) {
                    maxLeft = maxLeft->rightSubNode;
                }

                swap(root->val, maxLeft->val);

                // 转换在子树去删除
                // 这里不能传maxLeft, maxLeft是局部变量
                return EraseByRecusion(root->leftSubNode, key);
            }

            delete del;
            return true;
        }

        return false;
    };

    // 递归查找     
    bool FindR(const K& key) {
        return FindByRecusion(root_, key);
    };

    // 递归插入
    bool InsertR(const K& key) {
        return InsertByRecusion(root_, key);
    };

    // 递归删除
    bool EraseR(const K& key) {
        return EraseByRecusion(root_, key);
    };

    // 中序遍历
    void InOrderTraverse(Node* root) {
        if (root == nullptr) {
            return;
        }
        InOrderTraverse(root->leftSubNode);
        std::cout << root->val << " ";
        InOrderTraverse(root->rightSubNode);
    };

    void InOrder() {
        InOrderTraverse(root_);
    };

private: 
    Node* root_ = nullptr;
};

} // BSTREE
