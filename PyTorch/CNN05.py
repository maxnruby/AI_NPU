import numpy as np

np.random.seed(1)

image = np.random.randint(5, size=(4,4))
print('image =\n', image)

filter = np.random.randint(5, size=(3,3,2))
print('filter_0 =\n', filter[:,:,0])
print('filter_1 =\n', filter[:,:,1])

image_pad = np.pad(image,((1,1), (1,1)))
print('image_pad =\n', image_pad)

convolution = np.zeros((4,4,2))
 
for fn in range(2):
    for row in range(4):
        for col in range(4):
            window = image_pad[row:row+3, col:col+3]
            convolution[row, col, fn] = np.sum(window*filter[:,:,fn])
        
print('convolution_0 =\n', convolution[:,:,0])
print('convolution_1 =\n', convolution[:,:,1])
 
max_pooled = np.zeros((2,2,2))

for fn in range(2):
    for row in range(0, 2):
        for col in range(0, 2):
            window = convolution[2*row:2*row+2, 2*col:2*col+2, fn]
            max_pooled[row, col, fn] = np.max(window)

print('max_pooled_0 =\n', max_pooled[:,:,0])
print('max_pooled_1 =\n', max_pooled[:,:,1])