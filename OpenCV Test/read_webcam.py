import cv2 as cv 

# Choose a video file to read or provide and integer. "0" for webcam, 
# "1" for the next cam, "2" for the next one and so on.
capture = cv.VideoCapture(0)

while True:
    isTrue, frame = capture.read()
    cv.imshow("Video", frame)

    if cv.waitKey(20) & 0xFF==ord("d"):
        break

capture.release()
cv.destroyAllWindows()
