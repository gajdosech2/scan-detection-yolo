import sys
sys.path.insert(0, './yolo')

import os
from yolo import YOLO
from PIL import Image

RESULT_PATH = 'result/'
PROCESS_PATH = 'process/'


model = YOLO()

for f in os.listdir(PROCESS_PATH):
    if f.endswith('.png'):
        image = Image.open(PROCESS_PATH + f)
        prediction, boxes = model.detect_image(image)
        
        rgb_prediction = Image.new('RGB', prediction.size, (0, 0, 0))
        rgb_prediction.paste(prediction)
        rgb_prediction.show()
        rgb_prediction.save(RESULT_PATH + f[:-4] + '_result.png')
        
        with open(RESULT_PATH + f[:-4] + '_boxes.txt', 'w') as output:
            for box in boxes:
                width = abs(box[2] - box[0])
                height = abs(box[3] - box[1])
                nbox = (box[0] + width//2, box[1] + height//2, width, height, box[4])
                print(','.join(str(i) for i in nbox), file=output)
    
model.close_session()
    
 


