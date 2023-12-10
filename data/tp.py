import os

# Replace all \t with , in all.csv
# g = open(os.path.join(os.path.dirname(__file__), 'all_corrected.csv'), 'w+')

# #relpcae all \t with ,
# with open(os.path.join(os.path.dirname(__file__), 'all.csv'), 'r+') as f:
#     for line in f.readlines():
#         line = line.replace("\t", ",")
#         g.write(line)

# g.close()

# Extracts FENs from combined.csv for stuff
g = open(os.path.join(os.path.dirname(__file__), 'fen_list.txt'), 'w+')
with open(os.path.join(os.path.dirname(__file__), '..', 'results', 'combined.csv'), 'r+') as f:
    for line in f.readlines():
        line = '"' + line.split(',')[0] + '",\n'
        g.write(line)

g.close()