# Binary Search Tree 二叉搜索树
## 目录
 - [1.0 基本介绍](#1-基本介绍)
 - [2.0 基本操作](#2-基本操作)
 - 
 ## 1.0 基本介绍
二叉搜索树又称二叉排序树，他具有以下性质:  
  1. 若他的左子树不为空，则其左子树上所有节点的值都小于根节点上的值;  
  2. 若他的右子树不为空，则其右子树上所有节点的值都大于根节点上的值;
  3. 左右子树也为二叉搜索树;  

具体图示:  
![iamge](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/58ecdba48b267b3cf73e435699d0965aa8f381cf/Tree/Tree-Images/BST-1.PNG)

## 2.0 基本操作

### 查找操作
由于二叉搜索树的性质,每次查找元素的值时遇到比他大的就往右子树找, 遇到比他小的就往左子树找
```c++
Node* Find(const K& target){
    Node* cur = root;
    while (cur) {
        if (target > cur->val) {
            cur = cur->right;
        }
        else if (target < cur->val) {
            cur = cur->left;
        }
        else {
            return cur;
        }
    }
    return nullptr;
}
```

