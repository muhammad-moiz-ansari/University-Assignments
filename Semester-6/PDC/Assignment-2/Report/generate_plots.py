"""
PDC Assignment 2 - Plot Generator
Run: python3 generate_plots.py
Outputs: plots/ directory with all figures
"""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np
import os

os.makedirs("plots", exist_ok=True)

# ── Color scheme ──────────────────────────────────────────────
COLORS = {
    "V1_Scalar":       "#555555",
    "V2_AVX2":         "#1f77b4",
    "V3_OMP_SIMD":     "#ff7f0e",
    "V4_OMP_Threads":  "#2ca02c",
    "V5_Hybrid_AVX2":  "#d62728",
    "V6_Hybrid_SIMD":  "#9467bd",
}

LABELS = {
    "V1_Scalar":       "V1: Scalar Baseline",
    "V2_AVX2":         "V2: AVX2 SIMD",
    "V3_OMP_SIMD":     "V3: OMP SIMD",
    "V4_OMP_Threads":  "V4: OMP Threads",
    "V5_Hybrid_AVX2":  "V5: Hybrid (OMP+AVX2)",
    "V6_Hybrid_SIMD":  "V6: Hybrid (OMP+SIMD)",
}

DATASETS = {
    "D1": "email-Eu-core\n(105K triangles)",
    "D2": "ego-Facebook\n(1.6M triangles)",
    "D3": "com-LiveJournal\n(177.8M triangles)",
}

# ─────────────────────────────────────────────────────────────
# FIGURE 1: Single-thread speedup comparison (V1-V3 + V4@1 + V5@1 + V6@1)
# ─────────────────────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(10, 5))

single_thread_speedups = {
    "V1_Scalar":      [1.0,       1.0,       1.0      ],
    "V2_AVX2":        [2.44891,   2.47782,   1.42836  ],
    "V3_OMP_SIMD":    [1.10343,   0.574036,  0.633321 ],
    "V4_OMP_Threads": [1.23207,   1.21644,   1.04265  ],
    "V5_Hybrid_AVX2": [2.32861,   1.09767,   1.36094  ],
    "V6_Hybrid_SIMD": [0.984726,  1.44458,   0.668247 ],
}

x = np.arange(3)
n = len(single_thread_speedups)
width = 0.13
offsets = np.linspace(-(n-1)/2, (n-1)/2, n) * width

for i, (ver, vals) in enumerate(single_thread_speedups.items()):
    bars = ax.bar(x + offsets[i], vals, width, label=LABELS[ver],
                  color=COLORS[ver], edgecolor='white', linewidth=0.5)

ax.axhline(y=1.0, color='black', linestyle='--', linewidth=1, alpha=0.5, label='Baseline (1x)')
ax.set_xticks(x)
ax.set_xticklabels([DATASETS[d] for d in ["D1","D2","D3"]], fontsize=10)
ax.set_ylabel("Speedup over Scalar Baseline", fontsize=11)
ax.set_title("Figure 1: Single-Thread Speedup Comparison Across All Versions", fontsize=12, fontweight='bold')
ax.legend(fontsize=8, loc='upper right')
ax.set_ylim(0, 3.2)
ax.grid(axis='y', alpha=0.3)
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
plt.tight_layout()
plt.savefig("plots/fig1_single_thread_speedup.png", dpi=150, bbox_inches='tight')
plt.close()
print("Saved fig1")

# ─────────────────────────────────────────────────────────────
# FIGURE 2: OMP Threads Scalability (V4, V5, V6) — all 3 datasets
# ─────────────────────────────────────────────────────────────
threads = [1, 2, 4, 8]

scalability_data = {
    "D1": {
        "V4_OMP_Threads":  [1.23207,  2.42935,  4.92846,  7.27276 ],
        "V5_Hybrid_AVX2":  [2.32861,  4.33653,  8.02654,  13.7789 ],
        "V6_Hybrid_SIMD":  [0.984726, 1.70941,  2.63802,  4.95994 ],
    },
    "D2": {
        "V4_OMP_Threads":  [1.21644,  2.50011,  3.96816,  6.58167 ],
        "V5_Hybrid_AVX2":  [1.09767,  1.58147,  2.77888,  5.72754 ],
        "V6_Hybrid_SIMD":  [1.44458,  2.5621,   4.02537,  6.05096 ],
    },
    "D3": {
        "V4_OMP_Threads":  [1.04265,  1.81433,  2.81796,  4.38559 ],
        "V5_Hybrid_AVX2":  [1.36094,  2.51264,  3.97957,  5.42367 ],
        "V6_Hybrid_SIMD":  [0.668247, 1.24574,  2.0246,   2.84031 ],
    },
}

fig, axes = plt.subplots(1, 3, figsize=(15, 5), sharey=False)
dataset_keys = ["D1", "D2", "D3"]
dataset_names = ["email-Eu-core", "ego-Facebook", "com-LiveJournal"]

for idx, (dk, dname) in enumerate(zip(dataset_keys, dataset_names)):
    ax = axes[idx]
    for ver in ["V4_OMP_Threads", "V5_Hybrid_AVX2", "V6_Hybrid_SIMD"]:
        ax.plot(threads, scalability_data[dk][ver],
                marker='o', linewidth=2, markersize=7,
                color=COLORS[ver], label=LABELS[ver])
    # Ideal scaling line
    ideal = [scalability_data[dk]["V4_OMP_Threads"][0] * t for t in threads]
    ax.plot(threads, ideal, 'k--', linewidth=1, alpha=0.4, label='Ideal scaling')
    ax.set_title(f"{dname}", fontsize=11, fontweight='bold')
    ax.set_xlabel("Number of Threads", fontsize=10)
    ax.set_ylabel("Speedup over Scalar Baseline" if idx == 0 else "", fontsize=10)
    ax.set_xticks(threads)
    ax.legend(fontsize=7)
    ax.grid(alpha=0.3)
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

fig.suptitle("Figure 2: Thread Scalability — V4, V5, V6 (Dynamic Scheduling, chunk=16)", 
             fontsize=12, fontweight='bold', y=1.02)
plt.tight_layout()
plt.savefig("plots/fig2_scalability.png", dpi=150, bbox_inches='tight')
plt.close()
print("Saved fig2")

# ─────────────────────────────────────────────────────────────
# FIGURE 3: Best speedup per version at 8 threads
# ─────────────────────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(11, 5))

best_8thread = {
    "D1": {
        "V1_Scalar":       1.0,
        "V2_AVX2":         2.44891,
        "V3_OMP_SIMD":     1.10343,
        "V4_OMP_Threads":  7.27276,
        "V5_Hybrid_AVX2":  13.7789,
        "V6_Hybrid_SIMD":  4.95994,
    },
    "D2": {
        "V1_Scalar":       1.0,
        "V2_AVX2":         2.47782,
        "V3_OMP_SIMD":     0.574036,
        "V4_OMP_Threads":  6.58167,
        "V5_Hybrid_AVX2":  5.72754,
        "V6_Hybrid_SIMD":  6.05096,
    },
    "D3": {
        "V1_Scalar":       1.0,
        "V2_AVX2":         1.42836,
        "V3_OMP_SIMD":     0.633321,
        "V4_OMP_Threads":  4.38559,
        "V5_Hybrid_AVX2":  5.42367,
        "V6_Hybrid_SIMD":  2.84031,
    },
}

versions = ["V1_Scalar","V2_AVX2","V3_OMP_SIMD","V4_OMP_Threads","V5_Hybrid_AVX2","V6_Hybrid_SIMD"]
x = np.arange(len(versions))
width = 0.25
ds_colors = ["#4BACC6", "#70AD47", "#ED7D31"]

for di, (dk, dc) in enumerate(zip(["D1","D2","D3"], ds_colors)):
    vals = [best_8thread[dk][v] for v in versions]
    offset = (di - 1) * width
    bars = ax.bar(x + offset, vals, width, label=list(DATASETS.values())[di].replace('\n',' '),
                  color=dc, edgecolor='white', linewidth=0.5, alpha=0.9)
    for bar, val in zip(bars, vals):
        if val > 0.5:
            ax.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 0.1,
                    f'{val:.1f}x', ha='center', va='bottom', fontsize=7, fontweight='bold')

ax.axhline(y=1.0, color='black', linestyle='--', linewidth=1, alpha=0.5)
ax.set_xticks(x)
ax.set_xticklabels([LABELS[v].replace("V1: ","").replace("V2: ","").replace("V3: ","")
                    .replace("V4: ","").replace("V5: ","").replace("V6: ","")
                    for v in versions], fontsize=9, rotation=15, ha='right')
ax.set_ylabel("Speedup over Scalar Baseline", fontsize=11)
ax.set_title("Figure 3: Best Speedup per Version (8 Threads) Across Datasets", 
             fontsize=12, fontweight='bold')
ax.legend(fontsize=9)
ax.set_ylim(0, 17)
ax.grid(axis='y', alpha=0.3)
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
plt.tight_layout()
plt.savefig("plots/fig3_best_speedup_8threads.png", dpi=150, bbox_inches='tight')
plt.close()
print("Saved fig3")

# ─────────────────────────────────────────────────────────────
# FIGURE 4: Execution time comparison (ms) — log scale
# ─────────────────────────────────────────────────────────────
fig, axes = plt.subplots(1, 3, figsize=(15, 5))

exec_times = {
    "D1": {"V1":2.19481, "V2":0.89624, "V3":1.98907, "V4_8t":0.301785, "V5_8t":0.159288, "V6_8t":0.442507},
    "D2": {"V1":12.3207, "V2":4.9724,  "V3":21.4633, "V4_8t":1.87197,  "V5_8t":2.15113,  "V6_8t":5.75664},
    "D3": {"V1":7477.61, "V2":5235.09, "V3":11807.0, "V4_8t":1705.04,  "V5_8t":1378.7,   "V6_8t":2632.67},
}

ver_labels = ["V1\nScalar", "V2\nAVX2", "V3\nOMP\nSIMD", "V4\nOMP\n8T", "V5\nHybrid\nAVX2\n8T", "V6\nHybrid\nSIMD\n8T"]
ver_colors = [COLORS["V1_Scalar"], COLORS["V2_AVX2"], COLORS["V3_OMP_SIMD"],
              COLORS["V4_OMP_Threads"], COLORS["V5_Hybrid_AVX2"], COLORS["V6_Hybrid_SIMD"]]

for idx, (dk, dname) in enumerate(zip(["D1","D2","D3"], dataset_names)):
    ax = axes[idx]
    vals = list(exec_times[dk].values())
    bars = ax.bar(range(len(vals)), vals, color=ver_colors, edgecolor='white', linewidth=0.5)
    ax.set_yscale('log')
    ax.set_xticks(range(len(ver_labels)))
    ax.set_xticklabels(ver_labels, fontsize=8)
    ax.set_title(dname, fontsize=11, fontweight='bold')
    ax.set_ylabel("Execution Time (ms, log scale)" if idx == 0 else "", fontsize=9)
    ax.grid(axis='y', alpha=0.3)
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

fig.suptitle("Figure 4: Execution Time Comparison (Log Scale) — Best Config per Version",
             fontsize=12, fontweight='bold', y=1.02)
plt.tight_layout()
plt.savefig("plots/fig4_execution_times.png", dpi=150, bbox_inches='tight')
plt.close()
print("Saved fig4")

print("\nAll plots saved to plots/ directory")
print("Files:", os.listdir("plots"))
