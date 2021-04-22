import sys
sys.path.insert(0, './yolo')

from shutil import copyfile
import os
import time
from yolo import YOLO
from PIL import Image

os.environ["CUDA_VISIBLE_DEVICES"] = "-1"

RESULT_PATH = 'result/'
PROCESS_PATH = 'process/'
DATA_SUFFIX = '_datamap.png'
CLEAN_UP = False
SHOW = False
SCORE_THRESHOLD = 0.21


def input_files():
    files = os.listdir(PROCESS_PATH)
    for f in files:
        if '.cogs' in f:
            print("processing: " + f)
            if os.name == 'nt':
                os.system('"utils\WCC.exe"' + 
                          ' --boxes ' +
                          PROCESS_PATH + f + ' ' +
                          PROCESS_PATH)
            else:
                print('OS other than Windows is currently not supported.')


def inference():
    model = YOLO(score=SCORE_THRESHOLD)

    for f in os.listdir(PROCESS_PATH):
        if f.endswith(DATA_SUFFIX):
            image = Image.open(PROCESS_PATH + f)
            prediction, boxes = model.detect_image(image)
            if SHOW:
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
    
    
def clean_up():
    files = os.listdir(PROCESS_PATH)
    for f in files:
        if '.png' in f:
            os.remove(PROCESS_PATH + f)
 
 
if __name__ == '__main__':
    start = time.time()
    if not any('.png' in f for f in os.listdir(PROCESS_PATH)):
        input_files()
    inference()
    stop = time.time()
    if CLEAN_UP:
        clean_up()
    print(f'Total time: {stop - start} seconds')
    
 


