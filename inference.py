import sys
sys.path.insert(0, './yolo')

from shutil import copyfile
import os
from yolo import YOLO
from PIL import Image

RESULT_PATH = 'result/'
PROCESS_PATH = 'process/'
DATA_SUFFIX = '_datamap.png'

model = YOLO()

for f in os.listdir(PROCESS_PATH):
    if f.endswith(DATA_SUFFIX):
        image = Image.open(PROCESS_PATH + f)
        prediction, boxes = model.detect_image(image)
        prediction.show()
        prediction.save(RESULT_PATH + f[:-len(DATA_SUFFIX)] + '_result.png')
        
        rgb_prediction = Image.new('RGB', prediction.size, (0, 0, 0))
        rgb_prediction.paste(prediction)
        rgb_prediction.save(RESULT_PATH + f[:-len(DATA_SUFFIX)] + '_rgb.png')
        
        copyfile(PROCESS_PATH + f[:-len(DATA_SUFFIX)] + '_zmap.png', RESULT_PATH + f[:-len(DATA_SUFFIX)] + '_zmap.png')
        
        with open(RESULT_PATH + f[:-len(DATA_SUFFIX)] + '.txt', 'w') as output:
            for box in boxes:
                print(','.join(str(i) for i in box), file=output)
    
model.close_session()
    
 


