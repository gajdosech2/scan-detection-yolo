import sys
sys.path.insert(0, './yolo')

from train import train

train('data/train/annotations.txt', 'data/classes.txt', 'data/anchors.txt')
