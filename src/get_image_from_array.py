from PIL import Image
import numpy as np
import os 

file = open('D:\AandP\PROJECT\src\decopmressed_image_in_arrayx.txt', 'r')
n, m = [int(i) for i in file.readline().split()]
array_of_pixels = np.zeros(n*m)
for i in range(n * m):
    pixel = int(file.readline())
    array_of_pixels[i] = pixel
array_of_pixels = array_of_pixels.reshape((n, m))
array_of_pixels = array_of_pixels.astype(np.uint8)
image = Image.fromarray(array_of_pixels)
image = image.convert('L')
image.save('decompressed_check\\new_rab_stol.png')
