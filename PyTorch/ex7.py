import matplotlib.pyplot as plt
import torch
import torchvision
import torchvision.transforms as transforms

# 1. FashionMNIST 데이터셋 다운로드 및 로드
transform = transforms.ToTensor()

train_dataset = torchvision.datasets.FashionMNIST(
    root='./data', 
    train=True, 
    download=True, 
    transform=transform
)

# 2. 최초 데이터(첫 번째 샘플) 가져오기 [수정된 부분]
image, label = train_dataset[0]

# 3. 1채널 차원을 28x28 형태로 변환
image_squeezed = image.squeeze(0)

# 4. 클래스 이름 정의
classes = [
    "T-shirt/top", "Trouser", "Pullover", "Dress", "Coat",
    "Sandal", "Shirt", "Sneaker", "Bag", "Ankle boot"
]

# 5. Matplotlib로 이미지 시각화
plt.figure(figsize=(4, 4))
plt.imshow(image_squeezed, cmap='gray')
plt.title(f"Label: {label} ({classes[label]})")
plt.axis('off')
plt.show()