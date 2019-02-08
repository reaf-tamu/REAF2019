import cv2
import numpy as np

video_file = "GOPR4571.MP4"
video = cv2.VideoCapture(video_file)

while True:
    (grabbed, frame) = video.read()
    if not grabbed:
        break

    blur = cv2.GaussianBlur(frame, (21, 21), 0)
    hsv = cv2.cvtColor(blur, cv2.COLOR_BGR2HSV)
    
    #finds orange/yellow but not red
    #lower = [18, 50, 50]
    #upper = [35, 255, 255]
    
    #can see most of the image
    #lower = [0, 0, 0]
    #upper = [255, 255, 255]  
    
    #sees red only
    lower = [150,150,0]
    upper = [180,255,255]
    
    
    lower = np.array(lower, dtype="uint8")
    upper = np.array(upper, dtype="uint8")
    mask = cv2.inRange(hsv, lower, upper)


    output = cv2.bitwise_and(frame, hsv, mask=mask)
    cv2.imshow("output", output)
    if cv2.waitKey(1000) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
video.release()