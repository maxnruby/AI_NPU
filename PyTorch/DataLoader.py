import torch
from torch.utils.data import DataLoader
from torchvision import datasets, transforms

train_data = datasets.FashionMNIST(
    root='data',
    train=True,
    download=True,
    transform=transforms.ToTensor())
test_data = datasets.FashionMNIST(
    root='data',
    train=False,
    download=True,
    transform=transforms.ToTensor())

train_loader = DataLoader(
    train_data,
    batch_size=32,
    shuffle=True)
test_loader = DataLoader(
    test_data,
    batch_size=32,
    shuffle=True)

image,label = next(iter(train_loader))
print(image.shape, label.shape)