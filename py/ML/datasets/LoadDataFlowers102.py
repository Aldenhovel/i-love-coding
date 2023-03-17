import os
import random
from PIL import Image
import numpy as np
import torch
import torch.utils.data as data
import torchvision.transforms as transforms
import scipy.io as sio

# 定义数据集类
class Flowers102Dataset(data.Dataset):
    def __init__(self, img_paths, labels, transform=None):
        self.img_paths = img_paths
        self.labels = labels
        self.transform = transform

    def __getitem__(self, index):
        img_path = self.img_paths[index]
        img = Image.open(img_path).convert('RGB')
        label = self.labels[index]
        if self.transform is not None:
            img = self.transform(img)
        return img, label

    def __len__(self):
        return len(self.img_paths)


def load_flowers102(batch_size=32, img_size=224):
    
    data_dir = "mydataset/flowers102"
    # 定义数据预处理方式
    transform = transforms.Compose([
        transforms.Resize(img_size),
        #transforms.CenterCrop(224),
        transforms.ToTensor(),
    ])

    # 加载图像和标签
    image_dir = os.path.join(data_dir, 'jpg')
    img_paths = sorted([os.path.join(image_dir, img_name) for img_name in os.listdir(image_dir)])
    labels = sio.loadmat(os.path.join(data_dir, 'imagelabels.mat'))['labels'].squeeze() - 1
    setid = sio.loadmat(os.path.join(data_dir, 'setid.mat'))
    trnid = setid['trnid'].squeeze() - 1
    valid = setid['valid'].squeeze() - 1
    tstid = setid['tstid'].squeeze() - 1
    

    # 划分数据集
    train_img_paths = [img_paths[i] for i in trnid]
    train_labels = labels[trnid]
    valid_img_paths = [img_paths[i] for i in valid]
    valid_labels = labels[valid]
    test_img_paths = [img_paths[i] for i in tstid]
    test_labels = labels[tstid]

    # 定义数据集
    train_dataset = Flowers102Dataset(train_img_paths, train_labels, transform)
    valid_dataset = Flowers102Dataset(valid_img_paths, valid_labels, transform)
    test_dataset = Flowers102Dataset(test_img_paths, test_labels, transform)

    # 定义 DataLoader
    train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    valid_loader = torch.utils.data.DataLoader(valid_dataset, batch_size=batch_size, shuffle=False)
    test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

    return train_loader, valid_loader, test_loader
