1️⃣ What is Average Case Scenario?
The average case scenario describes the expected performance of an algorithm under typical inputs, not the best or worst.
It’s based on probability of different inputs.
Usually expressed in terms of time complexity or number of operations.


2️⃣ x is somewhere in the middle → on average n/2 comparisons
[ 3  x  7  9  1 ]   2 comparisons
[ 3  5  x  9  1 ]   3 comparisons
Average = (1 + 2 + 3 + ... + n)/n ≈ n/2


Diagram: Linear Search Average Case
Array: [ A1  A2  A3  ...  An ]
Search x:
Probability of finding x at Ai = 1/n
Number of comparisons at Ai = i
Average comparisons = (1 + 2 + 3 + ... + n)/n = (n+1)/2 ≈ n/2


3️⃣ Visualization: Average Case Comparisons
Comparisons
|
|        *
|      *  
|    *
|  *
|*_________________ Index in array
