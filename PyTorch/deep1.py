import torch
import torch.nn as nn
import torch.optim as optim

from _7seg_data_torch import X, YT

model = nn.Sequential(
    nn.Linear(7,8),
    nn.ReLU(),
    nn.Linear(8,4),
    nn.Sigmoid()
)
print(model) 

loss_fn = nn.MSELoss() 
optimizer = optim.Adam(model.parameters(), lr=0.001)

for epoch in range(10000):
 
    Y = model(X) # 1공식, 순전파
    E = loss_fn(Y, YT) # 2공식, 오차계산
    optimizer.zero_grad()
    E.backward() # 6공식, 오차역전파
    optimizer.step() # 7공식, 학습

    if epoch%100 == 99:
        print(epoch, E.item())

Y = model(X)
Y = nn.functional.softmax(Y, dim=1)
print(Y.data)