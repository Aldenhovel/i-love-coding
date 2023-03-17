import torch
import torchvision.datasets as datasets
import torchvision.transforms as transforms
from torch.utils.data import DataLoader

def load_dtd(batch_size=32):
    data_dir = "./mydataset/dtd/images"
    # 设置数据转换
    transform = transforms.Compose([
        transforms.Resize(224),
        transforms.CenterCrop(224),
        transforms.ToTensor()
    ])

    # 创建数据集
    full_dataset = datasets.ImageFolder(root=data_dir, transform=transform)

    # 计算划分后 train/val/test 的大小
    num_samples = len(full_dataset)
    num_train = int(0.8 * num_samples)
    num_val = int(0.1 * num_samples)
    num_test = num_samples - num_train - num_val

    # 随机划分数据集
    train_dataset, val_dataset, test_dataset = torch.utils.data.random_split(
        full_dataset, [num_train, num_val, num_test])

    # 创建数据加载器
    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=4)
    val_loader = DataLoader(val_dataset, batch_size=batch_size, shuffle=False, num_workers=4)
    test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False, num_workers=4)

    return train_loader, val_loader, test_loader
