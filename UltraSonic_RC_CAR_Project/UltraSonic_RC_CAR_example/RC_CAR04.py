import numpy as np
import torch
from mydata import I, T
 
np.set_printoptions(formatter={'float_kind': lambda x: "{0:6.4f}".format(x)})
 
x_train = I
 
x_train = x_train / 250
 
# 모델 클래스 없이 state_dict만 읽어 가중치를 꺼냄
# nn.Sequential 인덱스:
# 0=Linear, 1=ReLU, 2=Linear, 3=ReLU, 4=Linear, 5=Sigmoid
state = torch.load("model.pt", map_location="cpu", weights_only=True)
# nn.Linear weight는 (out, in) 형태 → Keras와 같은 (in, out)으로 전치
# 전치 덕분에 아래 flatten() 순서도 Keras 버전과 동일해짐
W1, b1 = state["0.weight"].numpy().T, state["0.bias"].numpy()
W2, b2 = state["2.weight"].numpy().T, state["2.bias"].numpy()
W3, b3 = state["4.weight"].numpy().T, state["4.bias"].numpy()

print(W1.shape, b1.shape)
print(W2.shape, b2.shape)
print(W3.shape, b3.shape)
 
xs = x_train
ys = []
for x in xs:
    x = np.array([x])       # x should be array
    h1 = x @ W1 + b1        # dense layer
    h1 = np.maximum(0, h1)  # ReLU
    h2 = h1 @ W2 + b2       # dense layer
    h2 = np.maximum(0, h2)  # ReLU
    h3 = h2 @ W3 + b3       # dense layer
    h3 = 1 / (1 + np.exp(-h3))
    ys.append(h3)

for y in ys[976:]:
    print(y)

names = ["WH", "BH", "WM", "BM", "WO", "BO"]
arrays = [W1, b1, W2, b2, W3, b3]

for name, array in zip(names, arrays):
    print("double %s[] = {" % name)
    print("   ", ", ".join([str(x) for x in array.flatten()]))
    print("};\n")
