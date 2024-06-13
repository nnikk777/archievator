from PIL import Image
import numpy as np

image = Image.open('data\\rabstol_net_program_brands_29.png')
image = image.convert('L')
image_in_array = np.array(image)
n, m = image_in_array.shape[0], image_in_array.shape[1]
file = open('src/image_in_array.txt', 'w')
file.write(str(n) + ' ' + str(m) + '\n')
for i in range(n):
    for j in range(m):
        s = ''
        s += str(image_in_array[i,j]) + '\n'
        file.write(s)
file.close()
print()
