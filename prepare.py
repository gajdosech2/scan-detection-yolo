import os
import sys

FILE_SUFFIX = '_datamap.png'
CLS_NAME = 'wheel'
TYPE = 1
def join_labels(dataset_type):
    if TYPE == 1:
        join_labels1(dataset_type)
    elif TYPE == 2:
        join_labels2(dataset_type)
        

def join_labels1(dataset_type):
  path = 'data/' + dataset_type + '/'
  datasets = [dataset for dataset in os.listdir(path) if os.path.isdir(path + dataset)]
   
  with open(path + 'type1_annotations.txt', 'w') as labels:
    for dataset in datasets:
      dataset_path = path + '/' + dataset
      for file in os.listdir(dataset_path):
        if '.txt' in file:
          name = file.split('.')[0]
          print('processing: ' + name)
          print('data/' + dataset_type + '/' + dataset + '/' + name + FILE_SUFFIX, file=labels, end=' ')
          
          with open(dataset_path + '/' + file, 'r') as single_labels:
            space = False
            line = single_labels.readline()
            while line:
              coords = line.split(',')
              if len(coords) == 5:
                x_center, y_center, width, height, cls = [int(c) for c in coords]
                x_min = x_center - width // 2
                y_min = y_center - height // 2
                x_max = x_center + width // 2
                y_max = y_center + height // 2
                
                if space:
                  print(' ', file=labels, end='')
                space = True 
                print(f'{x_min},{y_min},{x_max},{y_max},{cls}', file=labels, end='')
                line = single_labels.readline()
            
          print('', file=labels)
        
        
def join_labels2(dataset_type):
  path = 'data/' + dataset_type + '/'
  datasets = [dataset for dataset in os.listdir(path) if os.path.isdir(path + dataset)]
   
  with open(path + '/' + 'type2_annotations.txt', 'w') as labels:
    for dataset in datasets:
      dataset_path = path + '/' + dataset
      for file in os.listdir(dataset_path):
        if '.txt' in file:
          name = file.split('.')[0]
          print('processing: ' + name)
          
          with open(dataset_path + '/' + file, 'r') as single_labels:
            line = single_labels.readline()
            while line:
              coords = line.split(',')
              if len(coords) == 5:
                x_center, y_center, width, height, cls = [int(c) for c in coords]
                x_min = x_center - width // 2
                y_min = y_center - height // 2
                x_max = x_center + width // 2
                y_max = y_center + height // 2
                
                print(dataset + '/' + name + FILE_SUFFIX, file=labels, end=' ')
                print('{},{},{},{},{}'.format(x_min, y_min, x_max, y_max, CLS_NAME), file=labels)
              line = single_labels.readline()     
            
    
def process(dataset_type):    
  path = 'data/_COGS/' + dataset_type + '/'
  datasets = os.listdir(path)
  
  for dataset in datasets:
    export_path = 'data/' + dataset_type + '/' + dataset + '/'
    if not os.path.exists(export_path):
      os.makedirs(export_path, exist_ok=True)
  
    dataset_path = path + dataset + '/'
    files = os.listdir(dataset_path)
  
    for file in files:
      if '.cogs' in file:  
        name = file.split('.')[0]
        print('processing: ' + name)
        if os.name == 'nt':
          os.system('"utils\WCC.exe"' + 
                    ' --boxes ' + 
                    dataset_path + file + ' ' + 
                    export_path + ' ' + 
                    dataset_path)
        else:
          pass



if __name__ == '__main__':
  if len(sys.argv) == 1:
    #process('train')
    join_labels('train')
  elif len(sys.argv) == 2:
    process(sys.argv[1])
    join_labels(sys.argv[1])

