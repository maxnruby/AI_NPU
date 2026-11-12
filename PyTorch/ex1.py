import torch
import torch.nn as nn
import torch.optim as optim

X = torch.FloatTensor([[2]]) # 입력데이터
YT = torch.FloatTensor([[10]]) # 목표데이터(라벨)
W = torch.FloatTensor([[3]]) # 가중치
B = torch.FloatTensor([1]) # 편향

model = nn.Sequential(
nn.Linear(1,1)
)# 입력 층, 출력 층 노드의 개수를 각각 1로 설정합니다. 12 ) # 신경망 모양 결정(W, B 내부적 준비)
print(model) # 신경망 모양 출력

with torch.no_grad():
 model[0].weight = nn.Parameter(W)
 model[0].bias = nn.Parameter(B)

loss_fn = nn.MSELoss() # 2공식, 오차 계산 함수
optimizer = optim.SGD(model.parameters(), lr=0.01)

for epoch in range(1000):
 
 Y = model(X) # 1공식, 순전파
 E = loss_fn(Y, YT) # 2공식, 오차계산
 optimizer.zero_grad()
 E.backward() # 6공식, 오차역전파
 optimizer.step() # 7공식, 학습

if epoch%100 == 99:
 print(epoch, E.item())

print(f'W = {model[0].weight.data}')
print(f'B = {model[0].bias.data}')

Y = model(X)
print(Y.data)