import matplotlib.pyplot as plt
import numpy as np
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

# ----------------- Combine duplicate FENs ----------------------- #

chess_data = pd.read_csv(DATA)
chess_data = chess_data.iloc[:, :8]
chess_data = chess_data.sort_values(by=[FEN], ascending=False)

# merge duplicate FENs
chess_data = chess_data.groupby(FEN).mean().reset_index()

# save to csv
chess_data.to_csv(COMBINED_FILE, sep=',', index=False)

# ---------------------- Scatter plot --------------------------- #

# Need to do better, clean data and all

# FEN vs Depth Limit
plt.figure(figsize=(10, 10))
plt.scatter(chess_data[FEN], chess_data[MINMAXAB_DEPTH], label="MinMaxAlphaBeta Depth Limit")
plt.scatter(chess_data[FEN], chess_data[MINMAXSIMPLE_DEPTH], label="MinMaxSimple Depth Limit")
plt.legend(loc='upper left')
plt.title("FEN vs Depth Limit")
plt.xlabel("FEN")
plt.ylabel("Depth Limit")
plt.xticks(rotation=90)
plt.show()

