import torch
import torch.nn as nn
import torch.optim as optim

X = torch.FloatTensor([[.05,.10]]) # 입력데이터
YT = torch.FloatTensor([[.01,.99]]) # 목표데이터(라벨)
W = torch.FloatTensor([[.15,.20],[.25,.30]]) # 가중치
B = torch.FloatTensor([.35,.35]) # 편향
W2 = torch.FloatTensor([[.40,.45],[.50,.55]]) # 가중치2
B2 = torch.FloatTensor([.60,.60]) # 편향2

model = nn.Sequential(
    nn.Linear(2,2),
    nn.ReLU(),
    nn.Linear(2,2),
    #nn.Sigmoid()
)# 입력 층, 출력 층 노드의 개수를 각각 1로 설정합니다. 12 ) # 신경망 모양 결정(W, B 내부적 준비)
print(model) # 신경망 모양 출력

with torch.no_grad():
    model[0].weight = nn.Parameter(W)
    model[0].bias = nn.Parameter(B)
    model[2].weight = nn.Parameter(W2)
    model[2].bias = nn.Parameter(B2)

loss_fn = nn.MSELoss() # 2공식, 오차 계산 함수
optimizer = optim.SGD(model.parameters(), lr=0.01)

for epoch in range(600):
 
    Y = model(X) # 1공식, 순전파
    E = loss_fn(Y, YT) # 2공식, 오차계산
    optimizer.zero_grad()
    E.backward() # 6공식, 오차역전파
    optimizer.step() # 7공식, 학습

    if epoch%100 == 99:
        print(epoch, E.item())

print(f'W = {model[0].weight.data}')
print(f'B = {model[0].bias.data}')
print(f'W2 = {model[2].weight.data}')
print(f'B2 = {model[2].bias.data}')

Y = model(X)
print(Y.data)