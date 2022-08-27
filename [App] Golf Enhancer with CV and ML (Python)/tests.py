import process_video as processor
import golferClass as Golfer
import cv2 as cv

video_processor = processor.Video_Processor("swing01_Trim.mp4", True)

video_processor.read_video()

golfer = Golfer.Golfer(video_processor.points_frames)

new_video_processor = processor.Video_Processor("generatedVideos/output_trimmed.avi")

frames = new_video_processor.slice_video()

cv.circle(frames[7], golfer.get_point(0, 7), 8, (255,255,0), thickness=-1)

#cv.imshow("Frame 7", frames[7])

def split_video_for_setup(frames, golfer, start_frame=0):
    for frame_number in range(start_frame, len(frames)):
        if golfer.get_point(4, frame_number) and golfer.get_point(1, frame_number):
            if golfer.get_point(4, frame_number)[1] < golfer.get_point(14, frame_number)[1] - 10:
                return frames[start_frame : frame_number], frame_number

def split_video_for_backswing(frames, golfer, start_frame):
    prev_y = golfer.get_point(4, start_frame)[1]
    for frame_number in range(start_frame, len(frames)):
        if golfer.get_point(4, frame_number):
            print(golfer.get_point(4, frame_number)[1])
            if golfer.get_point(4, frame_number)[1] > prev_y + 20:
                return frames[start_frame : frame_number], frame_number
            else:
                prev_y = golfer.get_point(4, frame_number)[1]

setup, setup_frame_number = split_video_for_setup(frames, golfer)


out = cv.VideoWriter('generatedVideos/setup.avi', cv.VideoWriter_fourcc(*'DIVX'), 15, ((frames[0].shape[1],frames[0].shape[0])))

for frame in setup:
    out.write(frame)

out.release()

backswing, backswing_frame_number = split_video_for_backswing(frames, golfer, setup_frame_number + 1)

out = cv.VideoWriter('generatedVideos/backswing.avi', cv.VideoWriter_fourcc(*'DIVX'), 15, ((frames[0].shape[1],frames[0].shape[0])))

for frame in backswing:
    out.write(frame)

out.release()

out = cv.VideoWriter('generatedVideos/swing.avi', cv.VideoWriter_fourcc(*'DIVX'), 15, ((frames[0].shape[1],frames[0].shape[0])))

for frame in frames[backswing_frame_number + 1 :]:
    out.write(frame)

#cv.waitKey(0)




