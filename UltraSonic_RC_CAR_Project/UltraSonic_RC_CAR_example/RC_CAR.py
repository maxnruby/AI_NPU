import numpy as np
import torch
import matplotlib.pyplot as plt
from mydata import I, T

x_train = torch.from_numpy(I).float()
y_train = torch.from_numpy(T).float()

x_train = x_train / 250

print(I.shape)
print(T.shape)

print(I.shape[0], I.shape[1], I.shape[2])

x_train = x_train.reshape(I.shape[0], I.shape[2])
y_train = y_train.reshape(T.shape[0], T.shape[2])
 
print(x_train.shape)
print(y_train.shape)