# 并查集
并查集是一种树型的数据结构，用于处理一些不相交集合(disjoint sets)的合并及查询问题。  
并查集通常包含两种操作:  
·查找(Find):查询两个元素是否在同一集合中  
·合并(Union):把两个不想交的集合合并为一个集合  
（注意：双亲节点就是父节点）

## 并查集思想

## 并查集基本代码
(1) 初始化  

```cpp
#define MAXN 100;
int Parent[MAXN];

void init(int n) {
  for (int i=0; i<n; i++) {
    Parent[i] = i;  //存放每个节点的根节点（或者父节点）
  }
}
```
刚开始时，每个节点自己就是一个集合，所以Parent中每个数组指向的就是自己本身  
示意图：  
![image](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/04da9cf5932e2bc45dd5812bd5d841d79fd986bd/Tree/Tree-Images/Union-find1.png)  
![image](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/f1c30a895ff67518b0ea1d3e28705ff36ff18c16/Tree/Tree-Images/Union-find2.png)

(2) 查找
```c++
//查询根节点
int find(int x) {
  if(Parent[x] == x) {
    return x;
  }
  return find(Parent[x]);
}
```
使用递归的方式查找每个数所在集合中的代表（最终根节点），如果要判断两个元素是否属于同一集合，只需要查看它们的根节点是否相同即可；  
示意图：  
![image](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/abca08b5c7bcbd1e08bcaf757fdb1be28162b69b/Tree/Tree-Images/Union-find3.png)  
![image](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/abca08b5c7bcbd1e08bcaf757fdb1be28162b69b/Tree/Tree-Images/Union-find4.png)

(3) 合并
```c++
//把 j 合并到 i 中去，就是把 j 的父节点设为 i 的父节点
void merge(int i, int j) {
  Parent[find[j]] = find[i];
}
```

示意图：  
![image](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/2ab6401a4ba71f1c8bb398c1afee3416e66e07f8/Tree/Tree-Images/Union-find5.png)  
![iamge](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/2ab6401a4ba71f1c8bb398c1afee3416e66e07f8/Tree/Tree-Images/Union-find6.png)  

## 路径压缩
(1) 查找代码：  
```c++
//查询根节点
int find(int x) {
  return x == Parent[x] ? x : (Parent(x) = find(Parent[x]));
}
```
只要在查找的过程中，把沿途的每个双亲结点都设为根结点即可,这样下一次查找的时候就可以省去很多查找步骤了  

(2) 完整代码：  
```cpp
#include <iostream>

using namespace std;

#define MAXN 100;
int Parent[MAXN];

//初始化，一开始各个元素自己为一个集合
void init(int n) {
  for (int i=0; i<n; i++) {
    Parent[i] = i;  //存放每个节点的根节点（或者父节点）
  }
}

//查询根节点
int find(int x) {
  if(Parent[x] == x) {
    return x;
  }
  else{
    Parent[x] = find(Parent[x]); //路径压缩：把相关的双亲节点设为根节点
    return Parent[x];
  }
}


//合并,把 j 合并到 i 中去，就是把 j 的父节点设为 i 的父节点
void merge(int i, int j) {
  Parent[find[j]] = find[i];
}

int main() {
  
  return 0;
}
```


## 按秩合并
```c++
class DisJointSetUnion {
public:
  //初始化，构造函数
  DisJoinSetUnion (int n) {
    for(int i=0; i<n; i++) {
      parent.emplace_back(i); //初始化时，各自就是一个集合
      rank.emplace_back(1);  //rank = 1 ，此时每个节点自己就是一颗深度为 1 的树 
    }
  }
  
  //查找根节点
  int find(int x) {
    if(parent[x] == x) {
      return x;
    }
    else {
      parent[x] = find(parent[x]); //路径压缩
      return parent[x];
    }
  }
  
  //合并两个节点(两个集合的合并)
  void merge(int x, int y) {
    //先找到两者的根节点
    int rx = find(x);  
    int ry = find(y);
    
    if (rx != ry) { //如果不是同一个集合
      if (rank[rx] < rank[ry]) {
        swap(rx,ry); //这里交换是为了保证 rx 的 rank 大于 ry 的 rank ，方便下面合并
      }
      parent[ry] = rx; // 大的集合 rx 合并小的集合 ry
      if (rank[rx] == rank[ry]) {
        rank[rx] += 1;. 
      }
    }
  }
  
private:
  //所有根节点相同的节点放到同一集合中
  vector<int> parent; //双亲节点数组，记录该节点的双亲节点，用于查找该节点的根节点
  vector<int> rank;  //秩数组，记录以该节点为根节点的树的深度，主要用于优化，在合并两个集合的时候，rank大的集合合并rank小的集合
  
}

``` 
