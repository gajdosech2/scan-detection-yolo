import sys
import tensorflow as tf
sys.path.insert(0, './yolo')

from train import train


def setup_gpu():
    gpus = tf.config.list_physical_devices('GPU')
    if gpus:
        try:
            for gpu in gpus:
                tf.config.experimental.set_memory_growth(gpu, True)
        except RuntimeError as e:
            print(e)

annotation_path = 'data/train/type1_annotations.txt'
classes_path = 'data/classes.txt'
anchors_path = 'data/anchors.txt'

#setup_gpu()
train(annotation_path, classes_path, anchors_path)