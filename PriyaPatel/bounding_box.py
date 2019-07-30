import cv2
from imutils.video import WebcamVideoStream
import imutils
import json
import numpy as np
from networktables import NetworkTable
import time
import sys
__version__ = "0.0.1"
__description__ = """
An extremely light implementation of vision processing optimized for Arch. May be rewritten in C Plus Plus in the future.
Written by GowanR
TODO:
Get rid of wincap in get bounding funciton.
"""

vs = WebcamVideoStream( 0 ).start() # Initialize the camera object on a seperate I/O thread
limits = {}

try:
    fs = open( sys.argv[1] + ".json", "r" ) # open the file under a .json extention
    data = json.loads( fs.read() )
    limits.update( data )
    fs.close( ) # close the file
except Exception as e:
    print( e )
    print( "> No input json file given. Stop that. <" )
    raise
try:
    NetworkTable.setIPAddress( sys.argv[2] )
    NetworkTable.setClientMode( )
    NetworkTable.initialize( )
    smt_dash = NetworkTable.getTable( "SmartDashboard" )
except Exception as e:
    print( e )
    print( "> No ip given. Stop that. <" )

def get_bounding_rect( cap, win_cap, win, upper, lower):
    msk = cv2.dilate(cv2.erode( cv2.inRange( cv2.blur( cv2.cvtColor( cap, cv2.COLOR_BGR2HSV ), (5,5) ), np.array(lower), np.array(upper) ), None, iterations=3), None, iterations=3)
    im2, contours, hierarchy = cv2.findContours( msk, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE )
    if len(contours) > 0:
        areas = [cv2.contourArea(c) for c in contours] # get the area of each contour
        max_index = np.argmax(areas) # get the index of the largest contour by area
        cnts = contours[max_index] # get the largest contout by area
        cv2.drawContours(msk, [cnts], 0, (0,255,0), 3) # Draw the contours to the mask image
        x,y,w,h = cv2.boundingRect(cnts) #  get the bouding box information about the contour
        cv2.rectangle(win_cap,(x,y),(x+w,y+h),(255,255,255),2) # Draw rectangle on the image to represent the bounding box
        cv2.imshow( "debug.", win_cap )
        try:
            self.smt_dash.putNumber('vis_x', x)
            self.smt_dash.putNumber('vis_y', y)
            self.smt_dash.putNumber('vis_w', w)
            self.smt_dash.putNumber('vis_h', h)
        except Exception:
            pass

while True:
    for k, v in limits.items( ): # Cycle through each item in the limits
        get_bounding_rect( vs.read(), vs.read(), k, v[0], v[1] ) # Get the bounding rect of the capture with limits
    # Quit with the "q" key!
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
vs.stop()