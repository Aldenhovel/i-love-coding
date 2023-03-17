import torch
import torchvision.datasets as datasets
import torchvision.transforms as transforms

def load_car(batch_size=32, img_size=224):
    
    data_dir = "./mydataset/cars/car_data/car_data"
    # 定义数据预处理
    transform = transforms.Compose([
        transforms.Resize((img_size, img_size)),
        transforms.ToTensor(),
    ])

    # 加载训练集和验证集
    train_dir = data_dir + "/train"
    train_dataset = datasets.ImageFolder(root=train_dir, transform=transform)
    num_train = len(train_dataset)
    indices = list(range(num_train))
    split = int(num_train * 0.8)
    train_idx, valid_idx = indices[:split], indices[split:]
    train_sampler = torch.utils.data.sampler.SubsetRandomSampler(train_idx)
    valid_sampler = torch.utils.data.sampler.SubsetRandomSampler(valid_idx)

    train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=batch_size, sampler=train_sampler, num_workers=4)
    valid_loader = torch.utils.data.DataLoader(train_dataset, batch_size=batch_size, sampler=valid_sampler, num_workers=4)

    # 加载测试集
    test_dir = data_dir + "/test"
    test_dataset = datasets.ImageFolder(root=test_dir, transform=transform)
    test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=batch_size, shuffle=True, num_workers=4)

    return train_loader, valid_loader, test_loader
