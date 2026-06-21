#!/usr/bin/env python3
import subprocess, re, csv, sys, os
import numpy as np
import matplotlib.pyplot as plt

# ------------------ CONFIG ------------------
cuda_src = "drive/MyDrive/HPC/mm_bench.cu"      # your CUDA file
exe_name = "mm_bench"         # compiled binary name
arch = "sm_75"                # GPU arch (Tesla T4 is sm_75)
sizes = [256, 512, 1024, 2048]  # matrix sizes to test
num_runs = 10                 # runs per size
#kernel_mode = "2d"            # "1d" or "2d"
out_dir = "drive/MyDrive/HPC" # save location
# --------------------------------------------

if len(sys.argv) > 1:
    kernel_mode = sys.argv[1]
else:
    kernel_mode = "2d"  # default
if kernel_mode not in ["1d", "2d"]:
    print("Invalid kernel mode. Use '1d' or '2d'.")
    sys.exit(1)

# Label for files
system = "colab"
label = f"{system}_{kernel_mode}"

os.makedirs(out_dir, exist_ok=True)
csv_path = os.path.join(out_dir, f"results_{label}.csv")
plot_path = os.path.join(out_dir, f"plots_{label}.png")

# Compile
print("Compiling CUDA program...")
subprocess.run(["nvcc", "-arch=" + arch, cuda_src, "-o", exe_name], check=True)
print("Compiled.")

# Regex to parse output line
pattern = re.compile(
    r"SIZE,(\d+),MODE,([^,]+),CPU,([\d.]+),H2D,([\d.]+),KERNEL,([\d.]+),D2H,([\d.]+),TOTAL_GPU,([\d.]+),VERIFIED,([01])"
)

rows = []
temp_bool = True

for size in sizes:
    if size >= 1024 and temp_bool:
        num_runs = num_runs // 2
        temp_bool = False

    print(f"\n=== Running size {size} ===")
    for run in range(1, num_runs + 1):
        cmd = ["./" + exe_name, str(size), kernel_mode]
        proc = subprocess.run(cmd, capture_output=True, text=True)
        out = proc.stdout.strip()
        m = pattern.search(out)
        if not m:
            print("Unexpected output:\n", out)
            sys.exit(1)
        row = {
            "size": int(m.group(1)),
            "mode": m.group(2),
            "cpu": float(m.group(3)),
            "h2d": float(m.group(4)),
            "kernel": float(m.group(5)),
            "d2h": float(m.group(6)),
            "total": float(m.group(7)),
            "verified": int(m.group(8)),
            "run": run,
        }
        rows.append(row)
        print(
            f"Run {run}: CPU={row['cpu']:.3f} ms | H2D={row['h2d']:.3f} | "
            f"Kernel={row['kernel']:.3f} | D2H={row['d2h']:.3f} | Total={row['total']:.3f}"
        )

# Helper: remove outliers
def iqr_filter(arr):
    if len(arr) == 0:
        return arr
    q1, q3 = np.percentile(arr, [25, 75])
    iqr = q3 - q1
    lb, ub = q1 - 1.5 * iqr, q3 + 1.5 * iqr
    return arr[(arr >= lb) & (arr <= ub)]

# Write raw + averages to CSV
with open(csv_path, "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(
        ["size", "run", "cpu_ms", "h2d_ms", "kernel_ms", "d2h_ms", "total_gpu_ms", "verified"]
    )
    for r in rows:
        writer.writerow(
            [r["size"], r["run"], r["cpu"], r["h2d"], r["kernel"], r["d2h"], r["total"], r["verified"]]
        )
    writer.writerow([])

    writer.writerow(
        ["size", "avg_cpu", "avg_h2d", "avg_kernel", "avg_d2h", "avg_total", "speedup_kernel", "speedup_total"]
    )
    for size in sizes:
        subset = [r for r in rows if r["size"] == size]
        cpu_clean = iqr_filter(np.array([r["cpu"] for r in subset]))
        h2d_clean = iqr_filter(np.array([r["h2d"] for r in subset]))
        kernel_clean = iqr_filter(np.array([r["kernel"] for r in subset]))
        d2h_clean = iqr_filter(np.array([r["d2h"] for r in subset]))
        total_clean = iqr_filter(np.array([r["total"] for r in subset]))

        avg_cpu = cpu_clean.mean()
        avg_h2d = h2d_clean.mean()
        avg_kernel = kernel_clean.mean()
        avg_d2h = d2h_clean.mean()
        avg_total = total_clean.mean()

        speedup_kernel = avg_cpu / avg_kernel if avg_kernel > 0 else float("nan")
        speedup_total = avg_cpu / avg_total if avg_total > 0 else float("nan")

        writer.writerow(
            [size, avg_cpu, avg_h2d, avg_kernel, avg_d2h, avg_total, speedup_kernel, speedup_total]
        )

print(f"\nResults saved to {csv_path}")

# Build plots
sizes_plot = sizes
avg_cpu_plot, avg_kernel_plot, avg_total_plot = [], [], []
speedup_kernel_plot, speedup_total_plot = [], []

for size in sizes:
    subset = [r for r in rows if r["size"] == size]
    avg_cpu_plot.append(np.mean(iqr_filter(np.array([r["cpu"] for r in subset]))))
    avg_kernel_plot.append(np.mean(iqr_filter(np.array([r["kernel"] for r in subset]))))
    avg_total_plot.append(np.mean(iqr_filter(np.array([r["total"] for r in subset]))))

    speedup_kernel_plot.append(avg_cpu_plot[-1] / avg_kernel_plot[-1])
    speedup_total_plot.append(avg_cpu_plot[-1] / avg_total_plot[-1])

plt.figure(figsize=(12, 8))

plt.subplot(2, 2, 1)
plt.plot(sizes_plot, avg_kernel_plot, marker="o")
plt.xlabel("Matrix size (N)")
plt.ylabel("Kernel time (ms)")
plt.title("Kernel execution time vs matrix size")
plt.grid(True)

plt.subplot(2, 2, 2)
plt.plot(sizes_plot, avg_total_plot, marker="o")
plt.xlabel("Matrix size (N)")
plt.ylabel("Total GPU time (ms)")
plt.title("Total GPU execution time vs matrix size")
plt.grid(True)

plt.subplot(2, 2, 3)
plt.plot(sizes_plot, speedup_kernel_plot, marker="o", label="CPU/Kernel")
plt.plot(sizes_plot, speedup_total_plot, marker="o", label="CPU/Total")
plt.xlabel("Matrix size (N)")
plt.ylabel("Speedup")
plt.title("Speedup vs matrix size")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig(plot_path)
plt.show()

print(f"Plot saved to {plot_path}")
