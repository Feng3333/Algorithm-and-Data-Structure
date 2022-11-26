# Dijkstra算法
## 目录

 - [1.0 迪杰斯特拉算法的基本介绍](#10-迪杰斯特拉算法的基本介绍)
 - [2.0 具体描述](#20-具体描述)
 - [3.0 代码实现](#30-代码实现)


## 1.0 迪杰斯特拉算法的基本介绍：
Dijkstra算法算是贪心思想实现的，首先把起点到所有点的距离存下来找个最短的，然后松弛一次再找出最短的;  
所谓的松弛操作就是，遍历一遍看通过刚刚找到的距离最短的点作为中转站会不会更近，如果更近了就更新距离，这样把所有的点找遍之后就存下了起点到其他所有点的最短距离

## 2.0 具体描述
#### 问题引入&情况模拟：  
指定一个点（源点）到其余各个顶点的最短路径，也叫做“单源最短路径”。例如求下图中的1号顶点到2、3、4、5、6号顶点的最短路径：  

![iamge](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/f42f1afcb50315e59925d07cf9ba6b92d6761b52/Graph%20Theory/images-folder/Dijkstra1.PNG)

如何求点1处到其他点的最短距离呢?  
可以先用一个数据结构存储图中的信息:    

![iamge](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/d950dbedf3dfdce9ea7b706143633e9fe897d61a/Graph%20Theory/images-folder/Dijkstra2.PNG)

其次之外还需要用一个数组记录 点1 到其他点的一个初始距离:

![iamge](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/d950dbedf3dfdce9ea7b706143633e9fe897d61a/Graph%20Theory/images-folder/Dijkstra3.PNG)

接下来开始模拟具体流程:  
![iamge](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/0a03838b049e8ccc5ea9d6030ca5c159f4aa3f88/Graph%20Theory/images-folder/Dijkstra4.PNG)

## 3.0 代码实现


