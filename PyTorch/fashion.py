import torch
from torchvision import datasets, transforms
import matplotlib.pyplot as plt

train_data = datasets.MNIST(
    root='data',
    train=True,
    download=True,
    transform=transforms.ToTensor())
test_data = datasets.MNIST(
    root='data',
    train=False,
    download=True,
    transform=transforms.ToTensor())

labels_map = {
    0:'t-shirt/top',
    1:'trouser',
    2:'pullover',
    3:'dress',
    4:'coat',
    5:'sandal',
    6:'shirt',
    7:'sneaker',
    8:'bag',
    9:'ankle boot'}


figure = plt.figure(figsize=(10,10))
ROWS,COLS = 5,6
for i in range(1,COLS*ROWS+1):
    rand_i = torch.randint(len(train_data),size=(1,)).item()
    image,label = train_data[rand_i]
    figure.add_subplot(ROWS,COLS,i)
    plt.title(labels_map[label])
    plt.axis('off')
    plt.imshow(torch.permute(image,(1,2,0)),cmap='gray')
plt.show()