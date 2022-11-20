# 面试题 17.11. 单词距离

有个内含单词的超大文本文件，给定任意两个`不同的`单词，找出在这个文件中这两个单词的最短距离(相隔单词数)。如果寻找过程在这个文件中会重复多次，而每次寻找的单词不同，你能对此优化吗?

**示例：**

```
输入：words = ["I","am","a","student","from","a","university","in","a","city"], word1 = "a", word2 = "student"
输出：1
```

提示：

- `words.length <= 100000`

## Python

```python
class Solution(object):
    def findClosest(self, words, word1, word2):
        """
        :type words: List[str]
        :type word1: str
        :type word2: str
        :rtype: int
        """
        # 初始化两个位置记录器，分别记录 word1 word2 位置
        idx1, idx2 = -1, -1
        res = len(words)
        # 遍历 words ，每次碰到 word1 word2 就更新它们的位置，然后计算距离
        # 始终保持距离最小，遍历完了之后得到的距离一定是最小距离
        # 因此要初始化 res 一个较大值，比如 len(words) ，因为它最大不会超过这个数
        for i, word in enumerate(words):
            if word == word1:
                idx1 = i
            if word == word2:
                idx2 = i
            if idx1 >=0 and idx2 >= 0:
                res = min(res, abs(idx2 - idx1))
        return res
```

## C++

```c++
class Solution {
public:
    int findClosest(vector<string>& words, string word1, string word2) {
        int idx1 = -1;
        int idx2 = -1;
        int res = words.size();
        for (int i=0; i<words.size(); i++) {
            if (words[i] == word1) idx1 = i;
            if (words[i] == word2) idx2 = i;
            if (idx1 >= 0 && idx2 >= 0) res = min(res, abs(idx2 - idx1));
        }
        return res;
    }
};
```

- 注意 `min()` `max()` `abs()` 这些函数可用直接使用。

