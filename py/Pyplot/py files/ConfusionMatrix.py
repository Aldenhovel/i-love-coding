from sklearn.metrics import confusion_matrix

# 使用 sklearn.metrics.confusion_matrix 计算混淆矩阵，得到一个 [n, n] 的矩阵
pred = [1, 3, 6, 1, 2]
gt = [1, 4, 6, 1, 3]
cm = confusion_matrix(gt, pred)

# 使用 matplotlib.pyplot.imshow 绘图


import matplotlib.pyplot as plt
import numpy as np
def plot_confusion_matrix(cm, 
                          labels=None, 
                          xlabel=None,
                          ylabel=None,
                          xtickrotation=0,
                          ytickrotation=0,
                          title="Confusion Matrix",
                          figsize=[5, 5],
                          showvalue=True
                         ):
    """
    :param cm: 混淆矩阵
    :param labels: 混淆矩阵中的类别
    :param xlabel: x轴名称，如 Predict
    :param ylabel: y轴名称，如 Ground Truth
    :param xtickrotation: x轴标签名旋转角度
    :param ytickrotation: y轴标签名旋转角度
    :param title: 混淆矩阵标题
    :param figsize: 绘图尺寸，会影响内容位置和清晰度
    :param showvalue: 是否显示各类的数值
    """
    if labels == None:
        labels = [i for i in range(len(cm))]
    assert len(labels) == len(cm)
    fig = plt.figure(figsize=figsize)
    plt.imshow(cm, interpolation='nearest', cmap='Blues')
    plt.title(title)
    plt.colorbar()
    xlocations = np.array(range(len(labels)))
    plt.xticks(xlocations, labels, rotation=xtickrotation)
    plt.yticks(xlocations, labels, rotation=ytickrotation)
    if xlabel:
        plt.xlabel(xlabel)
    if ylabel:
        plt.ylabel(ylabel)
    if showvalue:
        for i in range(len(labels)):
            for j in range(len(labels)):
                val = cm[j][i]
                if val > 0:
                    if i == j:
                        plt.text(i, j, "%0.2f" % (val, ), color='white', fontsize=10, va='center', ha='center')
                    else:
                        plt.text(i, j, "%0.2f" % (val, ), color='black', fontsize=10, va='center', ha='center')
    return fig

cm = (np.random.rand(10,10)*0.5 + np.eye(10)*0.5)
fig = plot_confusion_matrix(cm, figsize=[10, 10])

# 保存
fig.savefig("demo.svg", format='svg')