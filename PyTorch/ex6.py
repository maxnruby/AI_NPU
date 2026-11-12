import torch
import torchvision
import torchvision.transforms as transforms

# 1. FashionMNIST 데이터셋 다운로드 및 로드
# 이미지 데이터를 PyTorch 텐서(Tensor) 형태로 변환합니다.
transform = transforms.ToTensor()

train_dataset = torchvision.datasets.FashionMNIST(
    root='./data', 
    train=True, 
    download=True, 
    transform=transform
)

# 2. 최초 데이터(첫 번째 샘플) 가져오기
image, label = train_dataset[0]

# 3. 28x28 형태의 픽셀값 출력
# ToTensor()로 가져온 이미지 차원은 (채널, 높이, 너비) 즉 (1, 28, 28) 형태입니다.
# 28x28 형태로 출력하기 위해 첫 번째 채널을 선택하거나 squeeze()를 사용합니다.
pixel_values = image.squeeze().numpy()

print("--- 최초 데이터의 28x28 픽셀값 ---")
for row in pixel_values:
    # 각 픽셀값(0~1 사이 소수점)을 한눈에 보기 쉽게 소수점 둘째 자리까지 출력합니다.
    print(" ".join(f"{pixel:.2f}" for pixel in row))

# 4. 해당 데이터의 라벨값 출력
# FashionMNIST의 라벨 번호를 사람이 읽을 수 있는 텍스트 클래스로 매핑합니다.
classes = [
    "T-shirt/top", "Trouser", "Pullover", "Dress", "Coat",
    "Sandal", "Shirt", "Sneaker", "Bag", "Ankle boot"
]

print("\n--- 해당 데이터의 라벨 정보 ---")
print(f"라벨 숫자값: {label}")
print(f"라벨 클래스명: {classes[label]}")