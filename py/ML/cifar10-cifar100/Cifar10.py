DATA_DIR = "./mydataset"

import torch
import torch.nn.functional as F
import torch.nn as nn
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms
import argparse

import numpy as np
import torch
from torchvision.datasets import cifar
import torchvision.transforms as transforms
from torch.utils.data import DataLoader

import matplotlib.pyplot as plt

classes = ('plane', 'car', 'bird', 'cat','deer', 'dog', 'frog', 'horse', 'ship', 'truck')

transforms_train = transforms.Compose([
    transforms.RandomCrop(32, padding=4),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),
    transforms.Resize(64, interpolation=transforms.InterpolationMode.BICUBIC)
])

transforms_test = transforms.Compose([
    transforms.ToTensor(),
    transforms.Resize(64, interpolation=transforms.InterpolationMode.BICUBIC)
])

trainData = cifar.CIFAR10(DATA_DIR, train=True, transform=transforms_train, download=True)
testData = cifar.CIFAR10(DATA_DIR, train=False, transform=transforms_test, download=True)


train_size = int(0.9 * len(trainData))
valid_size = len(trainData) - train_size
trainData, validData = torch.utils.data.random_split(trainData, [train_size, valid_size])


x=0
for images, labels in testData:
    plt.subplot(3,3,x+1)
    plt.tight_layout()
    images = images.numpy().transpose(1, 2, 0) * 255
    plt.title(str(classes[labels]))
    plt.imshow(images.astype('uint8'))
    plt.xticks([])
    plt.yticks([])
    x+=1
    if x==9:
        break
plt.show()

print(len(trainData), len(validData), len(testData))

train_dl = DataLoader(trainData, shuffle=True, batch_size=256)
valid_dl = DataLoader(validData, shuffle=True, batch_size=256)
test_dl = DataLoader(testData, shuffle=True, batch_size=256)

for x, y in train_dl:
    break
print(x.shape, y.shape)

for x, y in valid_dl:
    break
print(x.shape, y.shape)

for x, y in test_dl:
    break
print(x.shape, y.shape)