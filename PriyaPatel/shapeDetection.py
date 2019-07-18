import numpy as np
import cv2

cap = cv2.VideoCapture(0)


while(True):
    if cv2.waitKey(1) == 27:
        break
    ret,frame = cap.read()
    grayFrame = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    cv2.imshow('video gray',grayFrame)

    cv2.imshow('og',frame)

# gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# ret,thresh = cv2.threshold(gray,127,255,1)

# contours,h = cv2.findContours(thresh,1,2)

# for cnt in contours:
#     approx = cv2.approxPolyDP(cnt,0.01*cv2.arcLength(cnt,True),True)
#     print(len(approx))
#     # if len(approx)==5:
#     #     print("pentagon")
#     #     cv2.drawContours(img,[cnt],0,255,-1)
#     # elif len(approx)==3:
#     #     print("triangle")
#     #     cv2.drawContours(img,[cnt],0,(0,255,0),-1)
#     if len(approx)==4:
#         print("square")
#         cv2.drawContours(img,[cnt],0,(0,0,255),-1)
cap.release()
cv2.destroyAllWindows()