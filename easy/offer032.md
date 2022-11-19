# 剑指 Offer II 032. 有效的变位词

给定两个字符串 `s` 和 `t` ，编写一个函数来判断它们是不是一组变位词（字母异位词）。

**注意：**若 `s` 和 `t` 中每个字符出现的次数都相同且**字符顺序不完全相同**，则称 `s` 和 `t` 互为变位词（字母异位词）。

**示例 1:**

```
输入: s = "anagram", t = "nagaram"
输出: true
```

**示例 2:**

```
输入: s = "rat", t = "car"
输出: false
```

**示例 3:**

```
输入: s = "a", t = "a"
输出: false
```

**提示:**

- `1 <= s.length, t.length <= 5 * 104`
- `s` and `t` 仅包含小写字母

**进阶:** 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？

 ## Python

```python
class Solution(object):
    def isAnagram(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        # 因为这两个字符串不能完全一样，所以先判断
        if s == t:
            return False
        # 后面只要统计各个字符数量是否相等就可以了，用一个数组来统计
        charset1, charset2 = [0] * 26, [0] * 26
        for c in s:
            charset1[ord(c)-97] += 1
        for c in t:
            charset2[ord(c)-97] += 1
        # 两数组相同则说明所含字母数量也相同，满足条件
        return True if charset1 == charset2 else False
```

- `str` 转 `ascii` 使用 `ord()` ，反之使用 `chr()` ，不能像 C++ 一样直接相减。

## C++

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> charset1(26, 0);
        vector<int> charset2(26, 0);
        if (s == t) return false;
        for (char c: s) charset1[c - 'a']++;
        for (char c: t) charset2[c - 'a']++;
        return charset1 == charset2? true: false;
    }
};
```

- `vector` 初始化：

  ```c++
  vector<int> v(nums, item);
  vector<int> v = vector<int>(nums, item);
  ```

- C++ `char` 类型加减等价于 `ascii` 加减，可以直接操作，且 `int('a') = 97` 。



## 使用 unicode 怎么办？

依然可以使用一个哈希表来统计，但是由于 unicode 可能有 utf-8 或 utf-16 因此需要注重离散化的表达。

