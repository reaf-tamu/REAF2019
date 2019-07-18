import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while(1):

    # _, frame = cap.read()
    # hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    _,frame = cap.read()
    imgHLS = cv2.cvtColor(frame, cv2.COLOR_BGR2HLS)
    Lchannel = imgHLS[:,:,1]
    #change 250 to lower numbers to include more values as "white"
    mask = cv2.inRange(Lchannel, 250, 255)
    res = cv2.bitwise_and(frame,frame, mask= mask)
    mask = cv2.inRange(imgHLS, np.array([0,250,0]), np.array([255,255,255]))
    # define range of white color in HSV
    # change it according to your need !
    # sensitivity = 15
    # lower_white = np.array([0,0,255-sensitivity])
    # upper_white = np.array([255,sensitivity,255])
    # # lower_white = np.array([0,0,0], dtype=np.uint8)
    # # upper_white = np.array([0,0,255], dtype=np.uint8)

    # # Threshold the HSV image to get only white colors
    # mask = cv2.inRange(hsv, lower_white, upper_white)
    # # Bitwise-AND mask and original image
    # res = cv2.bitwise_and(frame,frame, mask= mask)

    cv2.imshow('frame',frame)
    cv2.imshow('mask',mask)
    cv2.imshow('res',res)

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

cv2.destroyAllWindows()