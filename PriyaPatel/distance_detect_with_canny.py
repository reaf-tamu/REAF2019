import cv2
import numpy as np
from matplotlib import pyplot as plt
import time

cap = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_COMPLEX
while True:
    _, frame = cap.read()	
    #define marker - first edge detection
    edges = cv2.Canny(frame, 100, 200)
    #step 2 = find contours
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    ret,thresh1 = cv2.threshold(edges, 127,255,cv2.THRESH_BINARY)
    contours, hierarchy = cv2.findContours(thresh1, cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    for cnt in contours:
        area = cv2.contourArea(cnt)
        approx = cv2.approxPolyDP(cnt,0.02*cv2.arcLength(cnt,True),True)
        x = approx.ravel()[0]
        y = approx.ravel()[1]
        if area > 400:
            cv2.drawContours(frame,[approx],0,(0,0,0),5)
            if len(approx) == 4:
                cv2.putText(frame,"GATE!",(x,y),font,1,(0,0,0))

    output = cv2.drawContours(gray,contours,-1,(100,100,100),3)
    cv2.imshow("Thresh1",thresh1)
    cv2.imshow("output",output)
    cv2.imshow('Edges', edges)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
	
	
# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()





