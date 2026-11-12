import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader
from torchvision import datasets, transforms
from tqdm import tqdm

# 1. CIFAR100 데이터셋 및 데이터로더 준비
# CIFAR100도 CIFAR10과 동일하게 32x32 크기의 RGB 컬러(3채널) 이미지입니다.
train_data = datasets.CIFAR100(
    root='data', 
    train=True, 
    download=True, 
    transform=transforms.ToTensor()
)
test_data = datasets.CIFAR100(
    root='data', 
    train=False, 
    download=True, 
    transform=transforms.ToTensor()
)

train_loader = DataLoader(train_data, batch_size=32, shuffle=True)
test_loader = DataLoader(test_data, batch_size=32, shuffle=False)

# 2. 모델 구조 정의 (CIFAR100 레이블 수에 맞게 출력층 수정)
model = nn.Sequential(
    nn.Flatten(),
    nn.Linear(32 * 32 * 3, 256),  # 입력 차원은 3072로 동일, 복잡한 데이터이므로 은닉층 노드를 256으로 확장
    nn.ReLU(),
    nn.Linear(256, 100)           # 최종 출력 노드 수를 10에서 100으로 변경!
)

loss_fn = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

# 3. 학습(Train) 함수
def model_fit(model, loss_fn, optimizer, data_loader, epoch):
    model.train()
    sum_loss, hit = 0, 0
    
    progress_bar = tqdm(data_loader, desc=f"Epoch {epoch+1:02d} [Train]")
    for image, label in progress_bar:
        pred = model(image)
        loss = loss_fn(pred, label)
        
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        
        _, pred_cls = pred.max(dim=1)
        hit += pred_cls.eq(label).sum().item()
        sum_loss += loss.item() * image.size(0)
        
    avg_loss = sum_loss / len(data_loader.dataset)
    avg_acc = hit / len(data_loader.dataset)
    return avg_loss, avg_acc

# 4. 검증(Test) 함수
def model_evaluate(model, loss_fn, data_loader):
    model.eval()
    sum_loss, hit = 0, 0
    
    with torch.no_grad():
        for image, label in data_loader:
            pred = model(image)
            loss = loss_fn(pred, label)
            
            _, pred_cls = pred.max(dim=1)
            hit += pred_cls.eq(label).sum().item()
            sum_loss += loss.item() * image.size(0)
            
    avg_loss = sum_loss / len(data_loader.dataset)
    avg_acc = hit / len(data_loader.dataset)
    return avg_loss, avg_acc

# 5. 실행 루프
for epoch in range(5):
    train_loss, train_acc = model_fit(model, loss_fn, optimizer, train_loader, epoch)
    test_loss, test_acc = model_evaluate(model, loss_fn, test_loader)
    
    print(f"  ↳ [Result] Train Loss: {train_loss:.4f} | Train Acc: {train_acc*100:.2f}% "
          f"// Test Loss: {test_loss:.4f} | Test Acc: {test_acc*100:.2f}%\n")