import cv2
import numpy as np

video_file = "GOPR4571.MP4"
video = cv2.VideoCapture(video_file)

while True:
    (grabbed, frame) = video.read()
    #resize image
    #res = cv2.resize(frame,(2000,900))
    if not grabbed:
        break

    blur = cv2.GaussianBlur(frame, (5, 5), 0)
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

    #contours
    _, contours, _ =cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)
    cv2.drawContours(frame, contours, -1, (255,255,255), 1000)

    #outputing video
    output = cv2.bitwise_and(frame, hsv, mask=mask)
    cv2.imshow("output", output)
    if cv2.waitKey(1000) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
video.release()