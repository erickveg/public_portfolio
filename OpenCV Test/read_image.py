import cv2 as cv 
import sys

# Read the image.
img = cv.imread("OpenCV Test/Gtav_auto.jpg", cv.IMREAD_UNCHANGED)

# Message if the image is not found.
if img is None:
    sys.exit("Could not read the image")

scale_percent = 40 # percent of original size
width = int(img.shape[1]*scale_percent/100)
height = int(img.shape[0]*scale_percent/100)
dim = (width, height)

# resize image
resized = cv.resize(img, dim, interpolation = cv.INTER_AREA)

cv.imshow("Resize image", resized)

# The time image will be displayed. "0": for undefined time
k = cv.waitKey(0)

# If the user press "s", a new resized image will be saved
if k == ord("s"):
    cv.imwrite("OpenCV Test/gtav_auto.png", img)

cv.destroyAllWindows()