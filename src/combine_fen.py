import os
import pandas as pd

# ---------------------Global variables----------------------- #

# Data directory
DATA_PATH = os.path.join(os.path.dirname(__file__), '..', 'data')
# Results directory
RESULTS = os.path.join(os.path.dirname(__file__), '..', 'results')
# Data file to be used for plotting with duplicate FENs
DATA = os.path.join(DATA_PATH, 'all.csv')
# Combined data file to be used for plotting after merging duplicate FENs
COMBINED_FILE = os.path.join(RESULTS, 'combined.csv')
# Nodes File
NODES_FILE = os.path.join(DATA_PATH, 'nodes_at_depth.csv')
NODES = os.path.join(RESULTS, 'nodes.csv')

# Create results directory if it doesn't exist
if not os.path.exists(RESULTS):
    os.makedirs(RESULTS)

# ----------------- Column names ----------------------- #

# FEN	Evaluation	MinMaxAlphaBeta Depth Limit	MinMaxAlphaBeta Time	MinMaxAlphaBeta Nodes	MinMaxSimple Depth Limit	MinMaxSimple Time	Total Nodes

FEN = "FEN"
EVAL = "Evaluation"
MINMAXAB_DEPTH = "MinMaxAlphaBeta Depth Limit"
MINMAXAB_TIME = "MinMaxAlphaBeta Time"
MINMAXAB_NODES = "MinMaxAlphaBeta Nodes"
MINMAXSIMPLE_DEPTH = "MinMaxSimple Depth Limit"
MINMAXSIMPLE_TIME = "MinMaxSimple Time"
TOTAL_NODES = "Total Nodes"

D2 = "nodes_at_depth_2"
D4 = "nodes_at_depth_4"
D6 = "nodes_at_depth_6"
D8 = "nodes_at_depth_8"
D10 = "nodes_at_depth_10"
D12 = "nodes_at_depth_12"
D14 = "nodes_at_depth_14"
D16 = "nodes_at_depth_16"

# ----------------- Combine duplicate FENs ----------------------- #

# All data

chess_data = pd.read_csv(DATA)
chess_data = chess_data.iloc[:, :8]
chess_data = chess_data.sort_values(by=[FEN], ascending=False)

# merge duplicate FENs
chess_data = chess_data.groupby(FEN).mean().reset_index()

# save to csv
chess_data.to_csv(COMBINED_FILE, sep=',', index=False)

# Nodes at depth
nodes_data = pd.read_csv(NODES_FILE)
nodes_data = nodes_data.iloc[:, :9]
nodes_data = nodes_data.sort_values(by=[FEN], ascending=False)

# merge duplicate FENs
nodes_data = nodes_data.groupby(FEN).max().reset_index()

# fill NaN with 0
nodes_data = nodes_data.fillna(0)

# save to csv
nodes_data.to_csv(NODES, sep=',', index=False)