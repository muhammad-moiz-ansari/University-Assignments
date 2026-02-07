#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: ./benchmark.sh t1 v1"
    exit 1
fi

TASK_ARG=$1     # t1 t2 t3
VER_ARG=$2      # v1 v2 v3

# Extract numbers
TASK_NUM=${TASK_ARG:1}
VER_NUM=${VER_ARG:1}

CPP_FILE="23i-0523-F-TASK${TASK_NUM}-V${VER_NUM}.cpp"
EXEC="$TASK_ARG"

# Compile
g++ "$CPP_FILE" -o "$EXEC" || exit 1

times=()
speedups=()

iter_count=8
echo "Executing Task-${TASK_NUM}(V${VER_NUM}) ${iter_count} times..."

# Run n times
for ((i=1; i<=iter_count; i++)); do
    echo "Execution ${i}"
    output=$(./"$EXEC")

    # Extract elapsed time in ms
    elapsed=$(echo "$output" | grep "ms" | grep -oE '[0-9]+\.[0-9]+' | head -n 1)

    # Extract speedup value (x)
    speedup=$(echo "$output" | grep " x" | grep -oE '[0-9]+\.[0-9]+' | head -n 1)

    echo "Exec Time: ${elapsed}"
    echo "Speedup: ${speedup}"
    echo ""
    times+=("$elapsed")
    speedups+=("$speedup")
done

# Sort elapsed times
sorted_times=($(printf "%s\n" "${times[@]}" | sort -n))
printf "Sorted Exec Times: ${sorted_times[*]}\n\n"

# Keep middle 5 (remove outliers)
if [[ "$VER_ARG" == "v1" ]]; then
    start=$((iter_count - 5))
    clean_times=("${sorted_times[@]:start:5}")
else 
    clean_times=("${sorted_times[@]:0:5}")
fi

min_time=${sorted_times[0]}
max_time=${sorted_times[iter_count-1]}

sum=0
for t in "${clean_times[@]}"; do
    sum=$(echo "$sum + $t" | bc)
done

avg_time=$(echo "scale=3; $sum / 5" | bc)

# Sort speedups
sorted_speedups=($(printf "%s\n" "${speedups[@]}" | sort -n))

min_speedup=${sorted_speedups[0]}
max_speedup=${sorted_speedups[iter_count-1]}

echo "========== BENCHMARK RESULTS =========="
echo "File           : $CPP_FILE"
echo "Used Times(ms) : ${clean_times[*]}"
echo "Min Time (ms)  : $min_time"
echo "Max Time (ms)  : $max_time"
echo "Avg Time (ms)  : $avg_time"

# Speedup only meaningful for v2 / v3
if [[ "$VER_ARG" != "v1" ]]; then
    echo "Min Speedup    : $min_speedup x"
    echo "Max Speedup    : $max_speedup x"
fi
