import os
import sys
import cv2
import matplotlib.pyplot as plt
import matplotlib.patches as patches

FILE_SUFFIX = '_datamap.png'
DIM = 2
SAVE = False

        
def visualize(path):
    images = os.listdir(path)
    #random.shuffle(images)
        
    plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0)
        
    j = 0
    for image_file in images:
        if FILE_SUFFIX not in image_file:
            continue
                        
        if j > (DIM*DIM - 1):
            break
                
        name = image_file.split('.')[0]
        if '_' in image_file:
            name = '_'.join(image_file.split('_')[:2])
                        
        img = cv2.imread(path + '/' + image_file)
                
        ax = plt.subplot(DIM, DIM, j+1, autoscale_on=True, frame_on=False, xmargin=0, ymargin=0)
        ax.axis('off') 
        plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        with open(path + '/' + name + '.txt', 'r') as f:
            line = f.readline()
            while line:
                x1, y1, x2, y2, clss = [int(i) for i in line.split(',')]        
                color = ['g', 'r', 'b', 'y', 'm'][clss]
                rect = patches.Rectangle((x1, y1), x2-x1, y2-y1, linewidth=1, edgecolor=color, facecolor='none')
                ax.add_patch(rect)                                        
                line = f.readline()
        j += 1

    if SAVE:
        plt.savefig('vis.png', dpi=600)
    plt.show()


if __name__ == '__main__':
    if len(sys.argv) == 1:
        visualize('data/train/dataset0')
    elif len(sys.argv) == 2:
        visualize(sys.argv[1])





