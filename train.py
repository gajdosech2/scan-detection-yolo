import sys
sys.path.insert(0, './yolo')

from train import train

annotation_path = 'data/train/type1_annotations.txt'
classes_path = 'data/classes.txt'
anchors_path = 'data/anchors.txt'

train(annotation_path, classes_path, anchors_path)