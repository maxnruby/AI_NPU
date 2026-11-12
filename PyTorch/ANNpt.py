import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader
from torchvision import datasets, transforms
from tqdm import tqdm

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
model = nn.Sequential(
    nn.Flatten(),
    nn.Linear(28*28,128),
    nn.ReLU(),
    nn.Linear(128,10)
)

loss_fn = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

def model_fit(model, loss_fn, optimizer, data_loader):
    sum_loss,hit = 0,0
    progress_bar = tqdm(data_loader)
    for image, label in progress_bar:
        pred = model(image) # 1공식, 순전파
        loss = loss_fn(pred, label) # 2공식, 오차계산
        optimizer.zero_grad()
        loss.backward() # 6공식, 오차역전파
        optimizer.step() # 7공식, 학습

        _,pred = pred.max(dim=1)
        hit += pred.eq(label).sum().item()
        sum_loss += loss.item()*image.size(0)

    avg_loss = sum_loss/len(data_loader.dataset)
    avg_acc = hit/len(data_loader.dataset)
    return avg_loss, avg_acc

def model_evaluate(model, loss_fn, data_loader):
    with torch.no_grad():
            sum_loss,hit = 0,0
            for image, label in data_loader:
                pred = model(image)
                loss = loss_fn(pred, label)

                _,pred = pred.max(dim=1)
                hit += pred.eq(label).sum().item()
                sum_loss += loss.item()*image.size(0)

    avg_loss = sum_loss/len(data_loader.dataset)
    avg_acc = hit/len(data_loader.dataset)
    return avg_loss, avg_acc

for epoch in range(5):
    train_loss,train_acc = model_fit(
            model, loss_fn, optimizer, train_loader)
    print(f'epoch {epoch+1:02d}, loss: {train_loss:.5f}, acc: {train_acc:.5f}')

    valid_loss,valid_acc = model_evaluate(
        model, loss_fn, test_loader)
    print(' '*8, f'vloss: {valid_loss:.5f},vacc: {valid_acc:.5f}')

torch.save(model, 'fashion_model.pth')
    
    