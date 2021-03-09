import os
import sys
import numpy as np
import cv2
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.gridspec as gridspec
import random

FILE_SUFFIX = "_datamap.png"
DIM = 2
PROB = False

def visualize(path, save=False):
  images = os.listdir(path)
  #random.shuffle(images)
    
  plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0)
    
  j = 0
  for image_file in images:
    if FILE_SUFFIX not in image_file:
      continue
            
    if j > (DIM*DIM - 1):
      break
        
    name = image_file.split(".")[0]
    if "_" in image_file:
      name = "_".join(image_file.split("_")[:2])
            
    img = cv2.imread(path + "/" + image_file)
        
    ax = plt.subplot(DIM, DIM, j+1, autoscale_on=True, frame_on=False, xmargin=0, ymargin=0)
    ax.axis('off') 
    imgplot = plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    with open(path + "/" + name + ".txt", "r") as f:
      line = f.readline()
      while line:
        [x, y, w, h, clss] = [float(i) for i in line.split(",")]    
        clss = int(clss)
                    
        if clss != 2:
          color = ['g','r','b','0'][clss]
          rect = patches.Rectangle((x-w/2, y-h/2), w, h, linewidth=2, edgecolor=color, facecolor='none')
          ax.add_patch(rect)
                    
          if PROB:
            ax.text(x, y, "%0.2f" % (conf), color=color)
                    
        line = f.readline()
    j += 1

  if save:
    plt.savefig("vis.png", dpi=600)
  plt.show()

if __name__ == "__main__":
  if len(sys.argv) == 1:
    visualize('data/train/dataset0')
  elif len(sys.argv) == 2:
    visualize(sys.argv[1])





