import sys
sys.path.insert(0, './yolo')

import os
from yolo import YOLO
from PIL import Image

RESULT_PATH = 'result/'
PROCESS_PATH = 'process/'


model = YOLO()

for f in os.listdir(PROCESS_PATH):
    image = Image.open(PROCESS_PATH + f)
    prediction = model.detect_image(image)
    prediction.show()
    prediction.save(RESULT_PATH + f[:-4] + "_result.png")
    
model.close_session()
    
 


