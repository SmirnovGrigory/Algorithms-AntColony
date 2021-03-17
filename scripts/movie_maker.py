import numpy as np
import cv2
import os

path = '/home/toliman/Projects/Algorithms-AntColony/tmp/frames/'
path_s = '/home/toliman/Projects/Algorithms-AntColony/scripts'

video_name = 'vis.avi'

images = []

dir = os.listdir(path)

frames_count = len(dir)

for i, image in enumerate(dir):
    images.append(cv2.imread(f'{path}frame_{i}.png'))

height, width, layers = images[0].shape

video = cv2.VideoWriter(os.path.join(path_s, video_name), 0, 30, (width, height))
for i in range(frames_count):
    video.write(images[i])

cv2.destroyAllWindows()

video.release()


def convert_avi_to_mp4(avi_file_path, output_name):
    os.popen(
        "ffmpeg -i '{input}' -ac 2 -b:v 2000k -c:a aac -c:v libx264 -b:a 160k "
        "-vprofile high -bf 0 -strict experimental -f mp4 '{output}.mp4'".format(
            input=avi_file_path, output=output_name))
    return True


convert_avi_to_mp4(os.path.join(path_s, video_name), 'vis')

# os.system('.' + os.path.join(path_s, video_name) + '.mp4')
