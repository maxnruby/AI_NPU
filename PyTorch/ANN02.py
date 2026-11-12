import torch
from torch.utils.data import DataLoader
from torchvision import datasets, transforms
import matplotlib.pyplot as plt
import numpy as np

test_data = datasets.FashionMNIST(
    root='data',
    train=False,
    download=True,
    transform=transforms.ToTensor())

test_loader = DataLoader(
    test_data,
    batch_size=32,
    shuffle=True)

model = torch.load('fashion_model.pth', weights_only=False)

label_tags = {
    0: 'T-Shirt',
    1: 'Trouser',
    2: 'Pullover',
    3: 'Dress',
    4: 'Coat',
    5: 'Sandal',
    6: 'Shirt',
    7: 'Sneaker',
    8: 'Bag',
    9: 'Ankle Boot'
}

fig = plt.figure(figsize=(10,10))
ROWS,COLS=6,6
for i in range(1, COLS*ROWS+1):
    data_idx = np.random.randint(len(test_loader))
    input_img = test_data[data_idx][0].unsqueeze(dim=0)

    output = model(input_img)
    _, argmax = torch.max(output, 1)
    pred = label_tags[argmax.item()]
    label = label_tags[test_data[data_idx][1]]

    fig.add_subplot(ROWS, COLS, i)
    if pred == label:
        plt.title(pred)
        cmap = 'Greys'
    else:
        plt.title(pred + '(' + label + ')')
        cmap = 'Oranges'
    plot_img = test_data[data_idx][0][0,:,:]
    plt.imshow(plot_img, cmap=cmap)
    plt.axis('off')

plt.show()