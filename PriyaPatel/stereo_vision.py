import cv2
import numpy as np
from matplotlib import pyplot as plt
imgL = cv2.imread('left.jpg',0)
imgR = cv2.imread('right.jpg',0)
stereo = cv2.StereoBM_create(numDisparities=16, blockSize=15)
disparity = stereo.compute(imgL,imgR)
plt.imshow(disparity,'gray')
plt.show()