import numpy as np

np.random.seed(1)

image = np.random.randint(5, size=(4,4))
print('image =\n', image)

filter = np.random.randint(5, size=(3,3))
print('filter =\n', filter)

convolution = np.zeros((2,2))
 
for row in range(2):
    for col in range(2):
        window = image[row:row+3, col:col+3]
        print('window(%d, %d) =\n' %(row, col), window)
        print('window(%d, %d)*filter =\n' %(row, col), window*filter)
        convolution[row, col] = np.sum(window*filter)
        
print('convolution =\n', convolution)