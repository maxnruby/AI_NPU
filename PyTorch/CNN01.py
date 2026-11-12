import numpy as np

np.random.seed(1)

image = np.random.randint(5, size=(3,3))
print('image =\n', image)

filter = np.random.randint(5, size=(3,3))
print('filter =\n', filter)

image_x_filter = image * filter
print('image_x_filter =\n', image_x_filter)

convolution = np.sum(image_x_filter)
print('convolution =\n', convolution)
