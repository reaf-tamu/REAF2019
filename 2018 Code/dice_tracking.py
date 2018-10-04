# USAGE
# python ball_tracking.py --video ball_tracking_example.mp4
# python ball_tracking.py

# import the necessary packages
from collections import deque
from imutils.video import VideoStream
import numpy as np
import argparse
import cv2
import imutils
import time

# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video",
	help="path to the (optional) video file")
ap.add_argument("-b", "--buffer", type=int, default=64,
	help="max buffer size")
args = vars(ap.parse_args())

# define the lower and upper boundaries of the "green"
# ball in the HSV color space, then initialize the
# list of tracked points
boundaries = [
	([200, 200, 200], [255, 255, 255]),
]
greenLower = (200, 200, 200)
greenUpper = (255, 255, 255)
pts = deque(maxlen=args["buffer"])

# if a video path was not supplied, grab the reference
# to the webcam
if not args.get("video", False):
	cap = VideoStream(src=0).start()

# otherwise, grab a reference to the video file
else:
	cap = cv2.VideoCapture(args["video"])

# allow the camera or video file to warm up
time.sleep(2.0)

# keep looping
while True:
	# Capture frame-by-frame
    ret, frame = cap.read()
    
    #edge = cv2.Canny(frame,200,100)
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    resized = imutils.resize(frame, width=500)
    frame2 = cv2.GaussianBlur(resized, (5, 5), 0)
    
    for (lower, upper) in boundaries:
	    # create NumPy arrays from the boundaries
	    lower = np.array(lower, dtype = "uint8")
	    upper = np.array(upper, dtype = "uint8")
     
	    # find the colors within the specified boundaries and apply
	    # the mask
	    mask = cv2.inRange(frame2, lower, upper)

		# find contours in the mask and initialize the current
		# (x, y) center of the ball
	    cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
	    cv2.CHAIN_APPROX_SIMPLE)
	    cnts = cnts[0] if imutils.is_cv2() else cnts[1]
	    center = None

	    # only proceed if at least one contour was found
	    if len(cnts) > 3:
		# find the largest contour in the mask, then use
		# it to compute the minimum enclosing circle and
		# centroid
	        c = max(cnts, key=cv2.contourArea)
	        ((x, y), radius) = cv2.minEnclosingCircle(c)
	        M = cv2.moments(c)
	        center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

	        # only proceed if the radius meets a minimum size
	        if radius > 10:
		        # draw the circle and centroid on the frame,
		        # then update the list of tracked points
		        cv2.circle(frame2, (int(x), int(y)), int(radius),
			        (0, 255, 255), 2)
		        cv2.circle(frame2, center, 5, (0, 0, 255), -1)

	# update the points queue
    pts.appendleft(center)

	# loop over the set of tracked points
    for i in range(1, len(pts)):
		# if either of the tracked points are None, ignore
		# them
	    if pts[i - 1] is None or pts[i] is None:
		    continue

		# otherwise, compute the thickness of the line and
		# draw the connecting lines
	    thickness = int(np.sqrt(args["buffer"] / float(i + 1)) * 2.5)
	    cv2.line(frame, pts[i - 1], pts[i], (0, 0, 255), thickness)

	# show the frame to our screen
    #cv2.imshow("Frame", frame)
    cv2.imshow("Frame2", frame2)
    cv2.imshow("Mask", mask)	
    key = cv2.waitKey(1) & 0xFF

	# if the 'q' key is pressed, stop the loop
    if key == ord("q"):
        break

# if we are not using a video file, stop the camera video stream
if not args.get("video", False):
	vs.stop()

# otherwise, release the camera
else:
	vs.release()

# close all windows
cv2.destroyAllWindows()