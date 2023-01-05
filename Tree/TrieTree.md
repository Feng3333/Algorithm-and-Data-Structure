# 前缀树
## 目录
 - [1. 什么是Trie树](#1-什么是trie树)
 - [2. 设计实现字典树](#2-设计实现字典树)
   - [2.1. 基本实现](#21-基本实现)
 -
 

## 1. 什么是Trie树?
Trie树，即前缀树，又称单词查找树，字典树，是一种树形结构，是一种哈希树的变种。典型应用是用于统计和排序大量的字符串（但不仅限于字符串），所以经常被搜索引擎系统用于文本词频统计。
  
Trie树的核心思想是空间换时间，利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的。 它的优点是：最大限度地减少无谓的字符串比较，查询效率比哈希表高。
  
**它有3个基本性质：**
  
a.根节点不包含字符，除根节点外每一个节点都只包含一个字符。root节点不含字符的目的是为了能够包括所有字符串。  
  
b.从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串。  
  
c.每个节点的所有子节点包含的字符都不相同，也就是找到对应单词，字符是唯一的。 

![image](https://github.com/Feng3333/Algorithm-and-Data-Structure/blob/2c5e4ee589a50a399f06bfc2be62f29fbf3c6756/Tree/Tree-Images/TrieTree1.png)

## 2. 设计实现字典树
对于字典树而言, 不同的场景或者需求设计上可能会有一些略微的差别, 但整体上来说字典树一般的操作有: 插入、查询(指定字符串)、查询(前缀)、删除.  
#### 插入
从字典树的跟开始插入字符串. 对于当前字符对应的子节点, 有两种情况:  
- 子节点存在: 沿着指针移动到子节点, 继续处理下一个字符;  
- 子节点不存在: 创建一个新的子节点, 记录在children数组的对应位置上,然后沿着指针移动到子节点, 继续搜索下一个字符;  
- 重复上述步骤直到处理字符串的最后一个字符, 然后将当前节点标记为字符串的结尾, 即当前节点的 isEnd 设置为 true;  
  
#### 查找
从根开使查找,也是两种情况：
- 子节点存在: 沿着指针移动到子节点, 继续搜索下一个字符;
- 子节点不存在: 说明字典树中不包含该字符串, 返回false;
- 重复上述步骤, 直到返回 false 或者搜索完字符串的最后一个字符;  
- 若搜到了字符串的末尾, 且字符串末尾对应节点的 isEnd 为 true, 则说明字典树中存在该字符串;  

#### 删除
从根开始删除, 每次删除一个节点, 主要分两种情况:
- 若当前累计删除字符长度小于字符串的长度, 递归删除子节点后, 将当前节点删除;  
- 若当前累计删除字符长度等于字符串的长度, 将当前节点的 isEnd 置为 false; 
- 重复上述步骤纸质删除完所有节点, 判断当前节点对应的 isEnd 是否为 false, 如果是则说明删除成功, 否则失败; 

### 2.1 基本实现
```c++
#include <iostream>
#include <string>
#include <vector>

class Trie {
private:
    std::vector<Trie*> children; //孩子节点
    bool isEnd; //完整字符串标志位
public:
    Trie() {
        children.resize(26, nullptr); //这里以字符串中存26个小写字母为例
        isEnd = false;
    }

    void Insert(std::string word) {
        Trie* node = this;
        for (auto& ch : word) {
            int pos = ch - 'a';
            if (node->children[pos] == nullptr) {
                node->children[pos] = new Trie();
            }
            node = node->children[pos];
        }
        node->isEnd = true;
    }

    bool Search(std::string word) {
        Trie* node = this;
        for (auto& ch : word) {
            int pos = ch - 'a';
            if (node->children[pos] == nullptr) {
                return false;
            }
            node = node->children[pos];
        }
        return node != nullptr && node->isEnd;
    }

    bool Del(Trie* node, std::string word, int pos) {
        node = this;
        if (pos == word.size()) {
            node->isEnd = false;
        } else {
            char ch = word[pos];
            ch -= 'a';
            if (node->children[ch] != nullptr) {
                Del(node->children[ch], word, pos + 1);
                node->children[ch] = nullptr;
            }
        }
        return !node->isEnd;
    }
};

int main() {
    Trie* trie = new Trie();
    trie->Insert("to");
    trie->Insert("in");
    trie->Insert("tea");
    trie->Insert("ted");
    trie->Insert("ten");
    trie->Insert("inner");
    std::cout << "search \"to\": " << trie->Search("to") << std::endl;
    std::cout << "search \"inn\": " << trie->Search("inn") << std::endl;
    std::cout << "search \"in\": " << trie->Search("in") << std::endl;
    std::cout << "search \"inner\": " << trie->Search("inner") << std::endl;
    std::cout << "search \"ten\": " << trie->Search("ten") << std::endl;
    std::cout << "delete \"ten\": " << trie->Del(trie, "ten", 0) << std::endl;
    std::cout << "search \"ten\": " << trie->Search("ten") << std::endl;
    return 0;
}
```
