import xml.etree.ElementTree as ET
import os
import sys
from glob import glob

DATA_ROOT = 'data/inference/'
SUFFIX_LENGTH = 14
CLASSES_PATH = 'data/classes.txt'

def convert(dataset):
    def get_classes(classes_path):
        with open(classes_path) as f:
            class_names = f.readlines()
        return [c.strip() for c in class_names]


    classes = get_classes(CLASSES_PATH)
    assert len(classes) > 0, 'no class names detected!'
    print(f'num classes: {len(classes)}')


    for path in glob(os.path.join(dataset, '*.xml')):
        in_file = open(path)

        tree = ET.parse(in_file)
        root = tree.getroot()

        file_name = root.find('filename').text
        print(file_name)
        out_file = open(path[:-SUFFIX_LENGTH] + ".txt", 'w')
        
        for obj in root.iter('object'):
            cls = obj.find('name').text 
            cls_id = classes.index(cls)
            xmlbox = obj.find('bndbox')
            b = (int(xmlbox.find('xmin').text), int(xmlbox.find('ymin').text), int(xmlbox.find('xmax').text), int(xmlbox.find('ymax').text))
            w, h = abs(b[2] - b[0]), abs(b[3] - b[1])
            b = [b[0]+w/2, b[1]+h/2, w, h]
            out_file.write(','.join([str(int(a)) for a in b]) + ',' + str(cls_id) + '\n')
        
        out_file.close()


if __name__ == "__main__":
    if len(sys.argv) == 1:
        convert(DATA_ROOT + 'various')
    elif len(sys.argv) == 2:
        convert(DATA_ROOT + sys.argv[1])