# LCP 02. 分式化简

有一个同学在学习分式。他需要将一个连分数化成最简分数，你能帮助他吗？

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/09/09/fraction_example_1.jpg)

连分数是形如上图的分式。在本题中，所有系数都是大于等于0的整数。

输入的`cont`代表连分数的系数（`cont[0]`代表上图的`a0`，以此类推）。返回一个长度为2的数组`[n, m]`，使得连分数的值等于`n / m`，且`n, m`最大公约数为1。

**示例 1：**

```
输入：cont = [3, 2, 0, 2]
输出：[13, 4]
解释：原连分数等价于3 + (1 / (2 + (1 / (0 + 1 / 2))))。注意[26, 8], [-13, -4]都不是正确答案。
```

**示例 2：**

```
输入：cont = [0, 0, 3]
输出：[3, 1]
解释：如果答案是整数，令分母为1即可。
```

**限制：**

1. `cont[i] >= 0`
2. `1 <= cont的长度 <= 10`
3. `cont`最后一个元素不等于0
4. 答案的 `n, m` 的取值都能被32位 `int` 整型存下（即不超过`2 ^ 31 - 1`）。

## Python

```python
class Solution(object):
    def fraction(self, cont):
        """
        :type cont: List[int]
        :rtype: List[int]
        """
        cont = cont[::-1]
        a, b = 1, cont[0]
        for i in cont[1:]:
            # 新的分子等于原有分子 + 新数通分后的分子
            a = i * b + a
            # 交换 a, b 取得倒数
            b, a = a, b
        return b, a
```

- 我们使用 `a` `b` 分别作为分子、分母，然后将序列倒转，初始化 `a=1` `b=cont[0]` 。
- 每一步我们要接收一个新的数，将这个数与原来的 `a/b` 相加得到新的 `a/b` ，再交换 `a` `b` 。
- 这样直到最后一个数完成时，恰好多交换了1次，于是返回 `b, a` 即可。

## C++

```c++
class Solution {
public:
    vector<int> fraction(vector<int>& cont) {
        vector<int> r_cont = vector<int>();
        // 注意倒序遍历 vector 时初始化是 i=cont.size()-1 ，终止为 i>=0
        for (int i = cont.size()-1; i>=0; i--) {
            r_cont.push_back(cont[i]);
        }
        int a = 1;
        int b = r_cont[0];
        int tmp;
        for (int i=1; i<r_cont.size(); i++) {
            a = a + r_cont[i] * b;
            tmp = a;
            a = b;
            b = tmp;
        }
        return vector<int>({ b, a });
    }
};
```

- `return` 时直接实例并初始化一个 `vector` ，一般用：

  ```c++
  vector<int> res = vector<int>({1, 2, 3});	
  return res;
  
  vector<int> res = {1, 2, 3};	
  return res;
  
  return vector<int>({1, 2, 3});
  ```

  

