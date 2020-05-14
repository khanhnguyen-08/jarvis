# import the necessary packages
from PyQt5.QtWidgets import *
from PyQt5 import uic
import sys
from threading import Thread
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
# initialize the camera and grab a reference to the raw camera capture
class camera:
    def __init__(self):
        self.camera = PiCamera()
        self.camera.resolution = (640, 480)
        self.camera.framerate = 32
        self.rawCapture = PiRGBArray(self.camera, size=(640, 480))
        # allow the camera to warmup
        time.sleep(0.1)
        
    # capture frames from the camera
    def run(self):
        for frame in self.camera.capture_continuous(self.rawCapture, format="bgr", use_video_port=True):
            # grab the raw NumPy array representing the image, then initialize the timestamp
            # and occupied/unoccupied text
            image = frame.array
            # show the frame
            cv2.imshow("Frame", image)
            key = cv2.waitKey(1) & 0xFF
            # clear the stream in preparation for the next frame
            self.rawCapture.truncate(0)
            # if the `q` key was pressed, break from the loop
            if key == ord("q"):
                break

class UI(QMainWindow):
    def __init__(self):
        super(UI, self).__init__()
        uic.loadUi("Start_camera_button.ui", self)
        
        self.Start = self.findChild(QPushButton, 'pushButtonStart')
        self.Start.clicked.connect(self.StartOnClicked)
        
        self.show()
    
    def StartOnClicked(self):
        doorCamera = camera()
        CameraThread = Thread(target=doorCamera.run())
        CameraThread.start()
    
if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = UI()
    app.exec_()
