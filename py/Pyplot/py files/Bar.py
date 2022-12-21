import matplotlib.pyplot as plt
import numpy as np

# 生成数据
x = np.arange(20)
y = np.random.randn(20)
print(x, y)

# 普通柱状图
plt.bar(x, y)

# 柱状图子图
_, axes = plt.subplots(1, 2, figsize=(10, 5))
axes[0].bar(x, y)
axes[1].barh(x, y)
plt.show()

#设置更多属性
_, axes = plt.subplots(1, 2, figsize=(10, 5))
axes[0].bar(x, y, label='as')
axes[0].bar(x, -y, label='asx')
axes[0].set_title('Fig 1')
axes[0].set_xlabel('A')
axes[0].set_ylabel('B')
axes[0].grid(True)
axes[0].legend()
axes[1].barh(x, y)
plt.show()