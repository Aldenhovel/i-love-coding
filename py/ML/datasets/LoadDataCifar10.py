import torch
import torchvision.transforms as transforms
import torchvision.datasets as datasets

cifar10_classes = ('plane', 'car', 'bird', 'cat','deer', 'dog', 'frog', 'horse', 'ship', 'truck')

def load_cifar10(img_size=224, batch_size=32):
    # 定义数据预处理，加入 resize 操作
    transform_train = transforms.Compose([
        transforms.RandomHorizontalFlip(),
        transforms.RandomCrop(32, padding=4),
        transforms.ToTensor(),
        transforms.Resize((img_size, img_size))
    ])

    transform_test = transforms.Compose([
        transforms.ToTensor(),
        transforms.Resize((img_size, img_size))
    ])

    # 加载训练集和测试集
    train_dataset = datasets.CIFAR10(root='./mydataset', train=True, download=True, transform=transform_train)
    valid_dataset = datasets.CIFAR10(root='./mydataset', train=True, download=True, transform=transform_test)
    test_dataset = datasets.CIFAR10(root='./mydataset', train=False, download=True, transform=transform_test)

    # 将训练集划分为训练集和验证集
    num_train = len(train_dataset)
    indices = list(range(num_train))
    split = int(num_train * 0.8)

    train_sampler = torch.utils.data.sampler.SubsetRandomSampler(indices[:split])
    valid_sampler = torch.utils.data.sampler.SubsetRandomSampler(indices[split:])

    # 定义DataLoader
    train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=batch_size, sampler=train_sampler, num_workers=4)
    valid_loader = torch.utils.data.DataLoader(valid_dataset, batch_size=batch_size, sampler=valid_sampler, num_workers=4)
    test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=batch_size, shuffle=False, num_workers=4)

    return train_loader, valid_loader, test_loader
