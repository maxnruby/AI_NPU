import numpy as np
import torch
import torch.nn as nn
from torch.utils.data import TensorDataset, DataLoader
import matplotlib.pyplot as plt
from mydata import I, T
 
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
 
# ---------------- 데이터 준비 ---------------
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
 
# Keras fit() 기본값: batch_size=32, shuffle=True
train_loader = DataLoader(TensorDataset(x_train, y_train),
   batch_size=32, shuffle=True)
 
 # ---------------- 모델 정의 ---------------
model = nn.Sequential(
    nn.Linear(I.shape[2], 16),
    nn.ReLU(),
    nn.Linear(16, 16),
    nn.ReLU(),
    nn.Linear(16, T.shape[2]),
    nn.Sigmoid(),
)
 
# Keras Dense 기본 초기화(glorot_uniform, bias=0)와 맞춤
def init_keras_style(m):
    if isinstance(m, nn.Linear):
        nn.init.xavier_uniform_(m.weight)
        nn.init.zeros_(m.bias)
 
model.apply(init_keras_style)
model.to(device)
 
# Keras Adam 기본값: lr=0.001, epsilon=1e-7
optimizer = torch.optim.Adam(model.parameters(), lr=1e-3, eps=1e-7)
criterion = nn.MSELoss()
mae_fn = nn.L1Loss()
 
 
def evaluate(x, y):
    model.eval()
    with torch.no_grad():
        pred = model(x.to(device))
        y = y.to(device)
        return criterion(pred, y).item(), mae_fn(pred, y).item()

 
# ---------------- 학습 --------------
EPOCHS = 2000
history = {"loss": [], "val_loss": [], "mae": [], "val_mae": []}
 
for epoch in range(1, EPOCHS + 1):
    model.train()
    sum_loss, sum_mae, n = 0.0, 0.0, 0
    for xb, yb in train_loader:
        xb, yb = xb.to(device), yb.to(device)

        optimizer.zero_grad()
        pred = model(xb)
        loss = criterion(pred, yb)
        loss.backward()
        optimizer.step()
 
        bs = xb.size(0)
        sum_loss += loss.item() * bs
        sum_mae += mae_fn(pred, yb).item() * bs
        n += bs
 
 # 원본과 동일하게 validation_data=(x_train, y_train)
    val_loss, val_mae = evaluate(x_train, y_train)
 
    history["loss"].append(sum_loss / n)
    history["mae"].append(sum_mae / n)
    history["val_loss"].append(val_loss)
    history["val_mae"].append(val_mae)
 
    if epoch % 100 == 0 or epoch == 1:
        print(f"Epoch {epoch}/{EPOCHS}"
            f" - loss: {sum_loss / n:.4f} - mae: {sum_mae / n:.4f}"
            f" - val_loss: {val_loss:.4f} - val_mae: {val_mae:.4f}")
 
 # ---------------- 학습 곡선 ---------------
loss = history["loss"]
val_loss = history["val_loss"]
 
epochs = range(1, len(loss) + 1)

plt.plot(epochs, loss, 'g.', label='Training loss')
plt.plot(epochs, val_loss, 'b', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()
 
# ---------------- 평가 / 예측 ---------------
np.set_printoptions(formatter={'float_kind': lambda x: "{0:6.4f}".format(x)})
 
loss, mae = evaluate(x_train, y_train)
print(f"loss: {loss:.4f} - mae: {mae:.4f}")

model.eval()
with torch.no_grad():
    predictions = model(x_train.to(device)).cpu().numpy()
 
print(y_train[976:].numpy())
print(predictions[976:])
            
 # ---------------- 저장 ---------------
torch.save(model.state_dict(), "model.pt")