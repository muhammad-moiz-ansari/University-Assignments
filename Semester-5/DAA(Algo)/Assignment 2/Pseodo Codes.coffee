// Q-1
PARTITION_A(A, p, q)
    x = A[p]
    i = p
    count = p
    for j = p + 1 to q
        do if A[j] < x
            then i = i + 1
                exchange A[i] <-> A[j]
                count = count + 1
    exchange A[p] <-> A[i]
    if count = p then
        return count
    else
        return count - 1

PARTITION_B(A, p, q)
    x = A[q]
    i = p - 1
    for j = p to q - 1
        do if A[j] < x
            then i = i + 1
                exchange A[i] <-> A[j]
    exchange A[i + 1] <-> A[q]
    return i + 1

QUICKSORT_A(A, p, r)
if p < r then
    q ← PARTITION_A(A, p, r)
    QUICKSORT_A(A, p, q)       // left side (≤ q)
    QUICKSORT_A(A, q + 1, r)   // right side (> q)


// Q-5
HEAP-EXTRACT-MAX(A)
    if A.heap-size < 1
        error "heap underflow"
    max = A[1]
    A[1]= A[A.heap-size]
    A.heap-size = A.heap-size -1
    MAX-HEAPIFY(A,1)
    return max

// Q-6
STABLE-MAX-HEAPIFY(A, I, i, n)
    l ← LEFT(i)
    r ← RIGHT(i)

    largest ← i

    // Compare left child
    if l ≤ n then
        if A[l] > A[largest] then
            largest ← l
        else if A[l] = A[largest] and I[l] > I[largest] then
            largest ← l

    // Compare right child
    if r ≤ n then
        if A[r] > A[largest] then
            largest ← r
        else if A[r] = A[largest] and I[r] > I[largest] then
            largest ← r

    if largest ≠ i then
        exchange A[i] ↔ A[largest]
        exchange I[i] ↔ I[largest]
        STABLE-MAX-HEAPIFY(A, I, largest, n)


### Q-7 ###
DUALHEAPSORT(A, p, r)
    if (r - p) ≤ 1 then
        return

    mid ← ⌊(p + r) / 2⌋
    BUILD-MIN-HEAP(A, p, mid)
    BUILD-MAX-HEAP(A, mid+1, r)

    TREESWAP(A, p, mid, r)   // ensure partition correctness

    DUALHEAPSORT(A, p, mid)  // recursively sort left (small side)
    DUALHEAPSORT(A, mid+1, r)// recursively sort right (large side)


TREESWAP(A, root_min, root_max, n_min, n_max)
    if A[root_min] > A[root_max] then
        exchange A[root_min] ↔ A[root_max]

        MIN-HEAPIFY(A, root_min, n_min)
        MAX-HEAPIFY(A, root_max, n_max)

        for each child_min of root_min do
            for each child_max of root_max do
                TREESWAP(A, child_min, child_max, n_min, n_max)




### Q-9 ###

RADIX_SORT_STRINGS(strings[], num_strings)
    maxLen = 0
    for each string in strings
        if length(string) > maxLen
            maxLen = length(string)
    
    for position = maxLen - 1 down to 0
        COUNTING_SORT_BY_POSITION(strings, num_strings, position)
    
    return strings


COUNTING_SORT_BY_POSITION(strings, n, position)
    k = 27              // 0 for empty, 1-26 for 'a'-'z'
    C[0..k]             // count array
    B[1..n]             // output array for strings
    
    // Initialize counts
    for i = 0 to k
        C[i] = 0
    
    // Count occurrences of each character at position
    for j = 1 to n
        index = GET_CHAR_INDEX(strings[j], position)
        C[index] = C[index] + 1
    
    // Compute cumulative counts
    for i = 1 to k
        C[i] = C[i] + C[i-1]
    
    // Place strings in output array (backwards for stability)
    for j = n down to 1
        index = GET_CHAR_INDEX(strings[j], position)
        B[C[index]] = strings[j]           // Store entire string!
        C[index] = C[index] - 1
    
    // Copy back to original array
    for j = 1 to n
        strings[j] = B[j]


// Helper function to get character index
GET_CHAR_INDEX(string, position)
    if position >= length(string)
        return 0                    // Empty character (comes first)
    else
        char = string[position]
        return (char - 'a' + 1)    // 'a'=1, 'b'=2, ..., 'z'=26


### Example:
```
Input: ["b", "ab", "a", "abc", "aa"]
Total chars n = 2 + 3 + 1 + 3 + 2 = 11

maxLen = 3

Pass 1 (position 2, rightmost):
  "b"   → _ (empty)
  "ab"  → _ (empty)
  "a"   → _ (empty)
  "abc" → 'c'
  "aa"  → _ (empty)
  
After sort: ["b", "ab", "a", "aa", "abc"]

Pass 2 (position 1, middle):
  "b"   → _ (empty)
  "ab"  → 'b'
  "a"   → _ (empty)
  "aa"  → 'a'
  "abc" → 'b'
  
After sort: ["b", "a", "aa", "ab", "abc"]

Pass 3 (position 0, leftmost):
  "b"   → 'b'
  "a"   → 'a'
  "aa"  → 'a'
  "ab"  → 'a'
  "abc" → 'a'
  
After sort: ["a", "aa", "ab", "abc", "b"]
###