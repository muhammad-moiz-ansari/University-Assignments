import pandas as pd
import matplotlib.pyplot as plt

# === Load CSV ===
csv_file = "results_hpc_2d.csv"   # change if needed
df = pd.read_csv(csv_file)

# Ensure numeric conversion
for col in df.columns:
    if col != "size":
        df[col] = pd.to_numeric(df[col], errors="coerce")

df["size"] = df["size"].astype(int)

print("\nAverages table loaded:")
print(df)

# === 1. Kernel execution time vs matrix size ===
plt.figure(figsize=(7,5))
plt.plot(df["size"], df["avg_kernel"], marker="o", label="Kernel time")
plt.xlabel("Matrix Size (N x N)")
plt.ylabel("Kernel Execution Time (ms)")
plt.title("Kernel Execution Time vs Matrix Size")
plt.grid(True)
plt.legend()
plt.savefig("kernel_vs_size.png", dpi=300)
plt.show()

# === 2. Total execution time vs matrix size ===
plt.figure(figsize=(7,5))
plt.plot(df["size"], df["avg_total"], marker="o", color="green", label="Total GPU time")
plt.plot(df["size"], df["avg_cpu"], marker="s", color="red", label="CPU time")
plt.xlabel("Matrix Size (N x N)")
plt.ylabel("Execution Time (ms)")
plt.title("Total Execution Time vs Matrix Size")
plt.grid(True)
plt.legend()
plt.savefig("total_vs_size.png", dpi=300)
plt.show()

# === 3. Speedup vs matrix size ===
plt.figure(figsize=(7,5))
plt.plot(df["size"], df["speedup_kernel"], marker="o", label="Speedup (Kernel)")
plt.plot(df["size"], df["speedup_total"], marker="s", label="Speedup (Total)")
plt.xlabel("Matrix Size (N x N)")
plt.ylabel("Speedup (CPU / GPU)")
plt.title("Speedup vs Matrix Size")
plt.grid(True)
plt.legend()
plt.savefig("speedup_vs_size.png", dpi=300)
plt.show()
