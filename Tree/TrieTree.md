# 前缀树
## 1、什么是Trie树?
Trie树，即前缀树，又称单词查找树，字典树，是一种树形结构，是一种哈希树的变种。典型应用是用于统计和排序大量的字符串（但不仅限于字符串），所以经常被搜索引擎系统用于文本词频统计。
  
Trie树的核心思想是空间换时间，利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的。 它的优点是：最大限度地减少无谓的字符串比较，查询效率比哈希表高。
  
**它有3个基本性质：**
  
a.根节点不包含字符，除根节点外每一个节点都只包含一个字符。root节点不含字符的目的是为了能够包括所有字符串。  
  
b.从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串。  
  
c.每个节点的所有子节点包含的字符都不相同，也就是找到对应单词，字符是唯一的。 

![image](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/2c5e4ee589a50a399f06bfc2be62f29fbf3c6756/Tree/Tree-Images/TrieTree1.png)

## 设计实现字典树(以字符串中只包含26个小写字母为例)

实现 Trie 类:   
Trie() 初始化前缀树对象;  
void insert(String word) 向前缀树中插入字符串 word;  
bool search(String word) 查看word是否在字符串中;  
bool startWith(String prefix) 检查之前插入的word的前缀是否为prefix;  

如何设计字典树？  
要带根节点root；  
用isEnd表示是否为某个字符串的末尾。


## 、实现

```c++
#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int path;
	int end;
	int count = 0;
	Node* nexts[26];
};

class Trie
{
private: 

	Node *root;
  
public:

	Trie(){
		root = new Node();//每个Node后面都挂26个Node
	}
  
	void insert(string word)
	{
		if (word.empty())
			return ;
		Node* ptr = root;
		int index = 0;
		for (int i = 0; i < word.size(); i++)
		{
			index = word[i] - 'a';
			if (ptr->nexts[index] == nullptr)
				ptr->nexts[index] = new Node();
			ptr = ptr->nexts[index];
			(*ptr).path++;
		}
		(*ptr).end++;
	}
  
	int search(string word)
	{
		if (word.empty())
			return 0;
		Node* ptr = root;
		int index = 0;
		for (int i = 0; i < word.size(); i++)
		{
			index = word[i] - 'a';
			ptr = ptr->nexts[index];
		}
		return (*ptr).end;
	}
  
	void delete_(string word)
	{
		if (search(word) != 0)
		{
			Node* ptr = root;//每次都需要回到根节点
			int index = 0;
			for (int i = 0; i < word.size(); i++)
			{
				index = word[i] - 'a';
				if (--(*(ptr->nexts[index])).path == 0) {//判断时已经相减
					ptr->nexts[index] = nullptr;//重新置空
					return;
				}
				ptr = ptr->nexts[index];
			}
			ptr->end--;
		}
	}
  
	int prefixNumber(string pre)
	{
		if (pre.empty())
			return 0;
		Node* ptr = root;//每次都需要回到根节点
		int index = 0;
		for (int i = 0; i < pre.size(); i++)
		{
			index = pre[i] - 'a';
			if (ptr->nexts[index]== nullptr) {
				return 0;
			}
			ptr = ptr->nexts[index];
			return ptr->path;
		}
	}
  
};


int main()
{
	Trie sol;
	sol.insert("hello ya");
	sol.insert("how are you");
	sol.insert("hello ya");
	sol.insert("hello ya");
	sol.insert("hello ya");
	sol.insert("how do you do");
	sol.insert("what's up");
	sol.insert("whoo");
	sol.insert("bye");
	cout<<"repeated word num:"<<sol.search("hello ya")<<endl;
	cout << "repeated prefix num:" << sol.prefixNumber("wh") << endl;;
	sol.delete_("hello ya");
	cout << "repeated word num:" << sol.search("hello ya") << endl;
	system("pause");
	return 0;
}
```
