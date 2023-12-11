import matplotlib.pyplot as plt
import numpy as np
import os
import pandas as pd

# ---------------------Global variables----------------------- #

# Data directory
DATA_PATH = os.path.join(os.path.dirname(__file__), '..', 'data')

# Results directory
RESULTS = os.path.join(os.path.dirname(__file__), '..', 'results')

# Combined data file to be used for plotting after merging duplicate FENs
COMBINED_FILE = os.path.join(RESULTS, 'combined.csv')
NODES = os.path.join(RESULTS, 'nodes.csv')

# Create results directory if it doesn't exist
if not os.path.exists(RESULTS):
    os.makedirs(RESULTS)

# ----------------- Column names ----------------------- #

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

# ---------------------- Plot --------------------------- #

nodes = pd.read_csv(NODES)
nodes[D2] = nodes[D2].astype(int)
nodes[D4] = nodes[D4].astype(int)
nodes[D6] = nodes[D6].astype(int)
nodes[D8] = nodes[D8].astype(int)
nodes[D10] = nodes[D10].astype(int)
nodes[D12] = nodes[D12].astype(int)
nodes[D14] = nodes[D14].astype(int)
nodes[D16] = nodes[D16].astype(int)

nodes[D4] = nodes[D4] + nodes[D2]
nodes[D6] = nodes[D6] + nodes[D4]
nodes[D8] = nodes[D8] + nodes[D6]
nodes[D10] = nodes[D10] + nodes[D8]
nodes[D12] = nodes[D12] + nodes[D10]
nodes[D14] = nodes[D14] + nodes[D12]
nodes[D16] = nodes[D16] + nodes[D14]

def plot_nodes_vs_depth(x, y_range, x_label, y_label, title, x_log, y_log, file_name):
    plt.figure(figsize=(10, 10), dpi=80)
    # plot for each FEN
    for i in y_range:
        y = nodes.iloc[i, 1:len(x)+1]
        plt.plot(x, y, label=nodes[FEN][i], marker='o', markersize=3, linewidth=1)

    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title(title)
    plt.legend()

    if x_log:
        plt.xscale('log')
    if y_log:
        plt.yscale('log')
    # plt.show()
    plt.savefig(os.path.join(RESULTS, file_name))

# ---------------------- Inc Row --------------------------- #

# 1 col
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12, 14, 16], range(23, 32), "Depth", "Nodes", "Log Nodes vs Depth", False, True, "1_col_kp_log_nodes_vs_depth.png")

# 2 col
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], range(0, 4), "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_kp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], range(4, 8), "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_kpp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], range(11, 14), "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_bk_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], range(14, 17), "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_bkpp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [32, 33], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_nk_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [34, 35, 36], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_nkpp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [43, 44, 45], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_qk_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [46, 47, 48], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_qkpp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [55, 56, 57], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_rk_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [58, 59, 60], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "2_col_rkpp_log_nodes_vs_depth.png")

# 3 col
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [8, 9], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_kp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [17, 18], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_bk_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [19, 20], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_bkpp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [21, 22], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_bkbppp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [37], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_nk_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [39, 40], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_nkpp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [41, 42], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_nknppp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [49, 50], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_qk_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [51, 52], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_qkpp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [53, 54], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_qkqppp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [61, 62], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_rk_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [63, 64], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_rkpp_log_nodes_vs_depth.png")
plot_nodes_vs_depth([2, 4, 6, 8, 10, 12], [65, 66], "Depth", "Nodes", "Log Nodes vs Depth", False, True, "3_col_rkrppp_log_nodes_vs_depth.png")

# ---------------------- Inc Col --------------------------- #