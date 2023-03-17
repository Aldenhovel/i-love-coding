import os
import random
import torch
import torchvision.datasets as datasets
import torchvision.transforms as transforms

# 设置随机数种子以便重复实验
random.seed(1874)

def load_caltech_101(img_size=224, batch_size=32):

   # 设置随机数种子以便重复实验
    random.seed(1874)

    # 定义数据变换
    transform = transforms.Compose([
        transforms.Resize((img_size, img_size)),
        transforms.ToTensor(),
        #transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
    ])

    # 加载原始数据集
    dataset = datasets.ImageFolder(root="./mydataset/caltech-101/101_ObjectCategories",
                                   transform=transform)

    # 划分数据集
    num_samples = len(dataset)
    indices = list(range(num_samples))
    random.shuffle(indices)

    val_size = int(0.1 * num_samples)  # 验证集大小为 10%
    test_size = int(0.1 * num_samples)  # 测试集大小为 10%
    train_size = num_samples - val_size - test_size

    train_dataset, val_dataset, test_dataset = torch.utils.data.random_split(dataset, [train_size, val_size, test_size])

    # 定义数据加载器
    train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=32, shuffle=True, num_workers=4)
    val_loader = torch.utils.data.DataLoader(val_dataset, batch_size=32, shuffle=False, num_workers=4)
    test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=32, shuffle=False, num_workers=4)

    
    return train_loader, val_loader, test_loader
