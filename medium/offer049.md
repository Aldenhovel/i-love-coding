# 剑指 Offer II 049. 从根节点到叶节点的路径数字之和

给定一个二叉树的根节点 `root` ，树中每个节点都存放有一个 `0` 到 `9` 之间的数字。

每条从根节点到叶节点的路径都代表一个数字：

- 例如，从根节点到叶节点的路径 `1 -> 2 -> 3` 表示数字 `123` 。

计算从根节点到叶节点生成的 **所有数字之和** 。**叶节点** 是指没有子节点的节点。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/02/19/num1tree.jpg)

```
输入：root = [1,2,3]
输出：25
解释：
从根到叶子节点路径 1->2 代表数字 12
从根到叶子节点路径 1->3 代表数字 13
因此，数字总和 = 12 + 13 = 25
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2021/02/19/num2tree.jpg)

```
输入：root = [4,9,0,5,1]
输出：1026
解释：
从根到叶子节点路径 4->9->5 代表数字 495
从根到叶子节点路径 4->9->1 代表数字 491
从根到叶子节点路径 4->0 代表数字 40
因此，数字总和 = 495 + 491 + 40 = 1026
```

**提示：**

- 树中节点的数目在范围 `[1, 1000]` 内
- `0 <= Node.val <= 9`
- 树的深度不超过 `10`

## Python

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def _sumNumbers(self, root, val, res):
        # 先更新此节点的 val 值，为父节点 * 10 + 本节点
        val = 10 * val + root.val
        # 尝试遍历左子树
        if root.left:
            res = self._sumNumbers(root.left, val, res)
        # 尝试遍历右子树
        if root.right:
            res = self._sumNumbers(root.right, val, res)
        # 没有左右子树，说明是叶子节点，可以将本节点 val 值加上去
        if not root.left and not root.right:
            res += val
        # 遍历完本节点及左右子树，将 res 返回
        return res
    def sumNumbers(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        res = self._sumNumbers(root, 0, 0)
        return res
```

- 是一个先序遍历子树的算法，关键是计算每一层节点的方法，以及判断是否叶子节点。

## C++

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        return _sumNumbers(root, 0, 0);
    }
    int _sumNumbers(TreeNode* root, int val, int res){
        val = 10 * val + root->val;
        if (root->left) res = _sumNumbers(root->left, val, res);
        if (root->right) res = _sumNumbers(root->right, val, res);
        if (!root->left && !root->right) return res + val;
        return res;
    }
};
```

