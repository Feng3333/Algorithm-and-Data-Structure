# 线段树(Segment Tree)

线段树是一种二插搜索树，常用于统计区间上的信息；  
其每个节点存储的是一个区间的信息，每个节点包含三个元素：1.区间左端点、2.区间右端点、3.区间内维护的信息；

## 原理 
通过类似于二叉树的形式存储数据，能够快速de获取任意区间的可以合并的信息（最大/小值，和等）。【不能合并的信息有区间中位数，区间和，众数等等】。  时间复杂度为O（log n）

通过每数组中每两个数字组成一小组，每两小组为一个中组，每两中组为一大组等等来形成一个二叉树，如图所示：

![iamge](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/16900072b304c34cf88d0dfd8b6ae49dde09a399/Tree/Tree-Images/SegmentTree1.png)  
那么[1,2]这个区间的合并信息就能够被树节点4记录，[3,4]的合并信息被树节点5，对于区间[5,6],[7,8]同理。接着这四个小组的合并信息又会往上传，树节点4和5的合并信息能被树节点2记录，也就是说树节点2记录了区间[1,4]的信息。以这种模式一直上传到根节点为止。通过二叉树的方式总结信息，能够更快得获取信息。例如如果要知道数组1-4中最大值是多少，只需要查看树节点2储存的信息是多少，而不是通过遍历去比较，节省了很多时间。因此，一个记录二叉树的一维数组就会基于原数组诞生。

对于修改而言，由于有一个新的二叉树数组，不仅仅只是在原数组修改一个数组那么简单。由于信息是从子节点向上传递的，那么修改的信息也需要从下往上传递。  

## 代码实现  

### 创建二叉树数组
树节点记录的信息：区间左右端点、区间内维护的信息（这里以和为例子）、懒标记。
```c++
struct tree{
  int l,r; //区间左右端点
  long w,hold; //这个点（区间）的属性w 这里举得例子为和,hold表示懒标记
}t[400020]
```

对于一个节点x来说，它的子节点分别为 2\*x 和 2\*x+1 (根节点从1开始) ，并且每次区间从父节点到子节点都是一分为二，那么就可以用递归的方式从下到上填入二叉树数组里的数据：  
```c++
void build (int l, int r, int p) {
  //l,r代表左右节点，p代表此时处理二叉树数组的那个元素位置
  //一般从根节点往下走，l=1,r=nums.size(),p=1;
  
  t[p].l = l; //左节点
  t[p].r = r; //右节点
  
  //当左右节点一样时，这个二叉树数组上包含的区间就只有一个点，直接填入信息即可
  if (l==r){
    t[p].w = nums[l];
    return;
  }
  
  int mid = (l+r) >> 1;
  build(l,mid,p*2);
  build(mid+1,r,p*2+1);
  t[p].w = t[p*2].w + t[p*2+1].w; //合并两个子节点的属性
}
```
【由于每次都需要乘2，所有一般二叉树数组会开到4\*MAXN；】

### 懒标记？

修改二叉树数组需要从最底下的子节点开始修改，一点点往上修改信息，但这样效率会很低，浪费时间；  
懒标记就是为了优化这一操作；  
懒标记的作用就是使递归不再如之前"build"中的代码一样一直递归到最底下的节点再返回，而是递归到包含所需要修改的区间就开始返回，并记录修改的信息(注意：修改的信息需要是可以合并的)；--->
举个例子：如果想要修改区间[1,4],使用懒标记就不再是需要先修改树节点4和5，在修改树节点2，而是直接修改到树节点2，并记录修改的内容，等需要用到树节点4和5时，再把懒标记所蕴含的信息传下去(注意：两个子节点都要传)。  
```c++
void lazy(int p) {

 //如果懒标记有内容，就下传一次
 if (t[p].hold) { 
  t[p*2].hold += t[p].hold; //更新左儿子的内容
  t[p*2].w += t[p].hold * (t[p*2].r - t[p*2].l + 1); //更新左儿子的信息
  
  t[p*2+1].hold += t[p].hold; //更新右儿子的内容
  t[p*2+1].w += t[p].hold * (t[p*2+1].r - t[p*2+1].l + 1); //更新右儿子的信息
  
  t[p].hold = 0; //更新结束后当前节点的懒标记需要归0
 }
 
}
```

### 区间修改
使用递归和懒标记进行修改，但很多时候需要修改的区间并不是用一个树节点就能表示出来的;  
这里的解决方法就是相当于把要修改的区间分成不同的小块进行修改，在组合信息。分成小块时需要注意优先用能代表更大区间的树节点；举个例子，如果要修改[1,6]这个区间，因为没有一个树节点是直接代表[1,6]的，所以需要把这个区间分为[1,4]和[5,6]这两个区间，就是对树节点2和6进行修改。这里就涉及到了要优先使用代表更大区间的树节点，使用[1,4] 而不是 [1,2]和[3,4]：
```c++
void change(int p, int nl, int nr, int k) {
  //p是二叉树数组总正在处理的位置，nl,nr表示要修改区间的左右端点, k表示要修改成的目标值
  
  //如果这个数节点的区间被包含在要修改的区间中，就修改；否则继续一分为二
  if (t[p].l >= nl && t[p].r <= nr) {
    t[p].w += long(k) * (t[p].r - t[p].l + 1); //修改
    t[p].hold += k;
    return;
  }
  
  lazy(p); //因为p位置不满足条件，就继续分成两个更小的小块，那么就需要用到懒标记
  int mid = (t[p].r + t[p].l ) >> 1;
  if (nl <= mid) change(p*2,nl,nr,k);
  if (nr > mid) change(p*2+1,nl,nr,k);
  t[p].w = t[p*2].w + [p*2+1].w;
}
```

### 区间询问
询问的原理与修改的原理大致相同，只不过不是修改信息而是获取信息：  
```c++
//p是二叉树数组正在处理的位置，nl 和 nr 是要询问区间的左右端点
long query(int p, int nl, int nr) {
  if (t[p].l >= nl && t[p].r <= nr) return t[p].w;
  
  lazy(p); //使用懒标记
  int mid = (t[p].l+t[p].r) >> 1;
  long ans = 0;
  if (nl <= mid) ans = query(p*2,nl,nr);
  if (nr > mid) ans = query(p*2+1,nl,nr);
  
  return ans;
}
```

## 完整代码
```c++
#include <iostream>

using namespace std;

int n,m;
int MAXN = 100000;
int nums[100020];

struct tree{
  int l,r; 
  long w,hold; 
} t[400020];

//建立线段树
void build (int l, int r, int p) {
  t[p].l = l; //左节点
  t[p].r = r; //右节点
  
  if (l==r){
    t[p].w = nums[l];
    return;
  }
  
  int mid = (l+r) >> 1;
  build(l,mid,p*2);
  build(mid+1,r,p*2+1);
  t[p].w = t[p*2].w + t[p*2+1].w; //合并两个子节点的属性
}

//懒标记
void lazy(int p) {
 if (t[p].hold) { 
  t[p*2].hold += t[p].hold; 
  t[p*2].w += t[p].hold * (t[p*2].r - t[p*2].l + 1); 
  t[p*2+1].hold += t[p].hold; 
  t[p*2+1].w += t[p].hold * (t[p*2+1].r - t[p*2+1].l + 1); 
  t[p].hold = 0; 
 }
 
 //区间修改
 void change(int p, int nl, int nr, int k) {
 
  if (t[p].l >= nl && t[p].r <= nr) {
    t[p].w += long(k) * (t[p].r - t[p].l + 1); //修改
    t[p].hold += k;
    return;
  }
  
  lazy(p); 
  int mid = (t[p].r + t[p].l ) >> 1;
  if (nl <= mid) change(p*2,nl,nr,k);
  if (nr > mid) change(p*2+1,nl,nr,k);
  t[p].w = t[p*2].w + [p*2+1].w;
}

//区间询问
long query(int p, int nl, int nr) {
  if (t[p].l >= nl && t[p].r <= nr) return t[p].w;
  
  lazy(p);
  int mid = (t[p].l+t[p].r) >> 1;
  long ans = 0;
  if (nl <= mid) ans = query(p*2,nl,nr);
  if (nr > mid) ans = query(p*2+1,nl,nr);
  
  return ans;
}

int main(int argc, const char argv[]) {
  cin >> n >> m;
  for (int i=0; i<n; i++) {
    cin >> a[i];
  }
  
  build(1,n,1);
  for (int i=1; i <= m; i++) {
    int t;
    cin >> t;
    if (t == 1) {
      int nl,nr,k;
      cin >> nl >> nr >> k;
      change(1,nl,nr,k);
    }
    else {
      int nl,nr;
      cin >> nl >> nr;
      long ans1 = query(1,nl,nr);
      cout << ans1 << endl;
    }
  }
  
  return 0;
}

```
