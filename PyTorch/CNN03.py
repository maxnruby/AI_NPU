import numpy as np

np.random.seed(1)

image = np.random.randint(5, size=(4,4))
print('image =\n', image)

filter = np.random.randint(5, size=(3,3))
print('filter =\n', filter)

image_pad = np.pad(image,((1,1), (1,1)))
print('image_pad =\n', image_pad)

convolution = np.zeros((4,4))
 
for row in range(4):
    for col in range(4):
        window = image_pad[row:row+3, col:col+3]
        convolution[row, col] = np.sum(window*filter)
        
print('convolution =\n', convolution)