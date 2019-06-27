import cv2
import numpy as np

video = cv2.VideoCapture(0)

while True:
    (grabbed, frame) = video.read()
    #resize image
    #res = cv2.resize(frame,(2000,900))
    if not grabbed:
        break

    blur = cv2.GaussianBlur(frame, (21, 21), 0)
    hsv = cv2.cvtColor(blur, cv2.COLOR_BGR2HSV)
    
    #not using hsv
    #hsv = blur
    
    #finds orange/yellow but not red
    #lower = [18, 50, 50]
    #upper = [35, 255, 255]
    
    #can see most of the image
    lower = [0, 0, 0]
    upper = [255, 255, 255]  
    
    #sees red only
    #lower = [10,150,0]
    #upper = [180,255,255]
    
    #dark blue
    #lower = [100,150,0]
    #upper = [140,255,255]
    
    
    lower = np.array(lower, dtype="uint8")
    upper = np.array(upper, dtype="uint8")
    mask = cv2.inRange(hsv, lower, upper)


    #contour attempt
    output = cv2.bitwise_and(frame, hsv, mask=mask)
    #im_gray = cv2.imread(output, cv2.IMREAD_GRAYSCALE)
    #(thresh, im_bw) = cv2.threshold(im_gray, 128, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
    gray = cv2.cvtColor(output, cv2.COLOR_BGR2GRAY)
    ret,thresh1 = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)
    contours, hierarchy = cv2.findContours(thresh1,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    output = cv2.drawContours(gray, contours, -1, (100,100,100), 3)
    
    cv2.imshow("output", output)
    if cv2.waitKey(1000) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
video.release()