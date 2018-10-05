import cv2
import numpy as np
from matplotlib import pyplot as plt
import time

cap = cv2.VideoCapture(0)

while True:
	
	ret, frame = cap.read()
	
	edges = cv2.Canny(frame, 100, 200)
	
	cv2.imshow('Edges', edges)
	
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
	
	
# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()





