# import numpy as np
# import cv2

# cap = cv2.VideoCapture(0)

# while(True):
    # # Capture frame-by-frame
    # ret, frame = cap.read()

    # # Our operations on the frame come here
    # #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # # Display the resulting frame
    # cv2.imshow('frame',frame)
    # if cv2.waitKey(1) & 0xFF == ord('q'):
        # break

# # When everything done, release the capture
# cap.release()
# cv2.destroyAllWindows()


# #HI IT'S REMOTE NICOLE

import numpy as np
import cv2


cap = cv2.VideoCapture(0)
#cap2 = cv2.VideoCapture(1)
#cap3 = cv2.VideoCapture(2)

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    #ret2, frame2 = cap2.read()
    #ret3, frame3 = cap3.read()
    
    # Our operations on the frame come here
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Display the resulting frame
    cv2.imshow('frame',frame)
    #cv2.imshow('frame2', frame2)
    #cv2.imshow('frame3', frame3)
    
    #
    #Stereo test, need to download matplotlib to do disparity map
    #stereo = cv2.StereoBM_create(numDisparities=16, blockSize=15)
    #disparity = stereo.compute(frame2, frame3)
    #cv2.imshow('disparity', disparity)
    #
    #
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
#cap2.release()
#cap3.release()
cv2.destroyAllWindows()