import numpy as np
import cv2
import matplotlib.pyplot as plt

image_color = cv2.imread('cube.png')
print('image_color.shape =', image_color.shape)
image = cv2.cvtColor(image_color, cv2.COLOR_BGR2GRAY)
print('image.shape =', image.shape)

filter = np.array([
    [1,1,1],
    [1,1,1],
    [1,1,1],
])/9

image_pad = np.pad(image,((1,1), (1,1)))
print('image_pad.shape =', image_pad.shape)

convolution = np.zeros_like(image)

for row in range(image.shape[0]):
    for col in range(image.shape[1]):
        window = image_pad[row:row+3, col:col+3]
        convolution[row, col] = np.clip(np.sum(window*filter), 0, 255)

images = [image, convolution]
labels = ['gray', 'convolution']

plt.figure(figsize=(10, 5))
for i in range(len(images)):
    plt.subplot(1,2,i+1)
    plt.xticks([])
    plt.yticks([])
    plt.imshow(images[i], cmap=plt.cm.gray)
    plt.xlabel(labels[i])
plt.show()