import os


process = 'process/'
result = 'result/'
IoU_threshold = 0.45


def area(b):
    return abs(b[2] - b[0]) * abs(b[3] - b[1]) 


def intersection(b1, b2):
    dx = min(b1[2], b2[2]) - max(b1[0], b2[0])
    dy = min(b1[3], b2[3]) - max(b1[1], b2[1])
    if (dx>=0) and (dy>=0):
        return dx * dy
    else:
        return 0
    
    
def iou(b1, b2):
    i = intersection(b1, b2)
    u = area(b1) + area(b2) - i
    return i / u
    
    
def load_boxes(path):
    boxes = []
    with open(path) as boxes_file:
        line = boxes_file.readline().strip()
        while line:
            box = [int(c) for c in line.split(',')]
            boxes.append(box[:-1])
            line = boxes_file.readline().strip()
            
    return boxes  
    
    
def calculate(true_boxes, found_boxes):
    matched_boxes = []
    
    total_iou = 0
    min_iou = 0
    max_iou = 0
    while True:
        best_pair = []
        best_iou = 0
        
        for b1 in true_boxes:
            for b2 in found_boxes:
                current_iou = iou(b1, b2)
                if current_iou > best_iou:
                    best_pair = [b1, b2]
                    best_iou = current_iou
                    
        
        if best_iou > IoU_threshold:
            matched_boxes.append(best_pair)
            true_boxes.remove(best_pair[0])
            found_boxes.remove(best_pair[1])
            total_iou += best_iou
            min_iou = min(1 if not min_iou else min_iou, best_iou)
            max_iou = max(max_iou, best_iou)
        else:
            break
            
    true_positives = len(matched_boxes)
    false_positives = len(found_boxes)
    false_negatives = len(true_boxes)
    precision, recall, avg_iou = 1, 0, 0
    if true_positives:   
        avg_iou = total_iou / true_positives
    if true_positives + false_positives:
        precision = true_positives / (true_positives + false_positives)
    if true_positives + false_negatives:
        recall = true_positives / (true_positives + false_negatives)
     
    print(f'TP={true_positives}, FP={false_positives}, FN={false_negatives}')
    print(f'min_iou={min_iou:.3f}, max_iou={max_iou:.3f}, avg_iou={avg_iou:.3f}')
    
    f1 = 0
    if (precision + recall) > 0:
        f1 = 2 * (precision * recall) / (precision + recall)
    print(f'precision={precision:.3f}, recall={recall:.3f}, f1={f1:.3f}\n')
    
    
def evaluate():
    files = os.listdir(result)
    for f in files:
        if '.txt' in f: 
            true_boxes = load_boxes(process + f)
            found_boxes = load_boxes(result + f)
            print(f'=== {f[:-4]} EVALUATION ===')
            print(f'true boxes={len(true_boxes)}, found boxes={len(found_boxes)}')
            calculate(true_boxes[:], found_boxes[:])
            
            
if __name__ == '__main__':
    evaluate()
            
    
    