import sys
import cv2
import os
import numpy as np
import plotly.graph_objs as go
import random

FILE_SUFFIX = '_zmap.png'
BOXES_SUFFIX = '.txt'


def depth_limits(depthmap, x1, y1, x2, y2):
    minz, maxz = 255, 0
    for x in range(x1, x2):
        for y in range(y1, y2):
            depth = depthmap[y][x]
            if depth != 0:
                minz = min(minz, depth)
                maxz = max(maxz, depth)             
    return minz, maxz
    
    
def load_boxes(path):
    boxes = []
    with open(path) as boxes_file:
        line = boxes_file.readline().strip()
        while line:
            box = [int(c)//4 for c in line.split(',')]
            boxes.append(box[:-1])
            line = boxes_file.readline().strip()
            
    return boxes
    

def load_depthmap(path):
    image = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
    print(path)
    image = cv2.resize(image, (0, 0), fx=0.25, fy=0.25, interpolation=cv2.INTER_NEAREST)
    return image
    
    
def get_points(depthmap):
    height, width = depthmap.shape
    points = []
    for y in range(0, height):
        for x in range(0, width):
            depth = depthmap[y][x]
            if depth != 0:
                points.append([x, y, depth])
            
    return np.array(points)
    
    
def plot_depthmap(data_path):  
    depthmap_path = data_path + FILE_SUFFIX
    
    boxes_path = data_path + BOXES_SUFFIX
    
    depthmap = load_depthmap(depthmap_path)
    points = get_points(depthmap)
    scan = go.Scatter3d(x=points[:, 0], y=points[:, 1], z=points[:, 2], mode='markers', 
                        marker=dict(size=2, color=points[:, 2], colorscale='gray'))                   
    data = [scan] 
    
    boxes = load_boxes(boxes_path) 
    for b in boxes:
        minz, maxz = depth_limits(depthmap, *b)
        objects = bounding_box(minz, maxz, *b)
        for o in objects:
            data.append(o)
            
    proj = go.layout.scene.camera.Projection(type='orthographic')
    cam = go.layout.scene.Camera(projection=proj)
    scene = go.layout.Scene(camera=cam)
    layout = go.Layout(autosize=True, scene=scene, title="Bin Scan", showlegend=False)
    fig = go.Figure(data=data, layout=layout)
    fig.show()
    
    
def bounding_box(minz, maxz, x1, y1, x2, y2):
    objects = []
    line = go.scatter3d.Line(width=5, color='#ff0000')
    objects.append(go.Scatter3d(x=[x1, x2, x2, x1, x1], 
                                y=[y1, y1, y2, y2, y1], 
                                z=[minz]*5, 
                                mode="lines", line=line))
                                
    objects.append(go.Scatter3d(x=[x1, x2, x2, x1, x1], 
                                y=[y1, y1, y2, y2, y1], 
                                z=[maxz]*5, 
                                mode="lines", line=line))

    objects.append(go.Scatter3d(x=[x1, x1], 
                                y=[y1, y1], 
                                z=[minz, maxz], 
                                mode="lines", line=line))
                                
    objects.append(go.Scatter3d(x=[x2, x2], 
                                y=[y1, y1], 
                                z=[minz, maxz], 
                                mode="lines", line=line))
                                
    objects.append(go.Scatter3d(x=[x2, x2], 
                                y=[y2, y2], 
                                z=[minz, maxz], 
                                mode="lines", line=line))
                                
    objects.append(go.Scatter3d(x=[x1, x1], 
                                y=[y2, y2], 
                                z=[minz, maxz], 
                                mode="lines", line=line))
                                
    return objects


def pick_name():
    files = os.listdir('result/')
    random.shuffle(files)
    for f in files:
        without_suffix = f.split('.')[0]
        return '_'.join(without_suffix.split('_')[:2])
    return ''


if __name__ == "__main__":
    if len(sys.argv) == 1:
        name = pick_name()
        if name == '':
            print('There are no result files!')
        else:
            print(f'visualizing: {name}')
            plot_depthmap('result/' + name)
    else:
        plot_depthmap(sys.argv[1])
