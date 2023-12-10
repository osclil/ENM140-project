import os

#create a new file called all.csv
g = open(os.path.join(os.path.dirname(__file__), 'all_corrected.csv'), 'w+')

#relpcae all \t with ,
with open(os.path.join(os.path.dirname(__file__), 'all.csv'), 'r+') as f:
    for line in f.readlines():
        line = line.replace("\t", ",")
        g.write(line)