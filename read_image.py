import cv2 as cv 
import sys

img = cv.imread("Gtav_auto.jpg", cv.IMREAD_UNCHANGED)

if img is None:
    sys.exit("Could not read the image")

cv.imshow("Display window", img)
k = cv.waitKey(0)

if k == ord("s"):
    cv.imwrite("gtav_auto.png", img)

scale_percent = 40 # percent of original size
width = int(img.shape[1]*scale_percent/100)
height = int(img.shape[0]*scale_percent/100)
dim = (width, height)

# resize image
resized = cv.resize(img, dim, interpolation = cv.INTER_AREA)

cv.imshow("Resize image", resized)
cv.waitKey(0)
cv.destroyAllWindows()