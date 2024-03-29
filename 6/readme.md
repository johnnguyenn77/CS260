## Heap sort timings

|    Size |       Heap |
| ----- | --------- |
|       8 |     0.0000 |
|      16 |     0.0000 |
|      32 |     0.0000 |
|      64 |     0.0000 |
|     128 |     0.0000 |
|     256 |     0.0000 |
|     512 |     0.0000 |
|    1024 |     0.0000 |
|    2048 |     1.0000 |
|    4096 |     1.0000 |
|    8192 |     2.0000 |
|   16384 |     5.0000 |
|   32768 |    10.0000 |
|   65536 |    20.0000 |
|  131072 |    43.0000 |

## Testing 4 common sorting algorithms

|    Size |     Bubble |     Insert |      Merge |      Quick |
|---------|------------|------------|------------|------------|
|       8 |     0.0000 |     0.0000 |     0.0000 |     0.0000 |
|      16 |     0.0000 |     0.0000 |     0.0000 |     0.0000 |
|      32 |     0.0000 |     0.0000 |     0.0000 |     0.0000 |
|      64 |     0.0000 |     0.0000 |     0.0000 |     0.0000 |
|     128 |     0.0000 |     0.0000 |     0.0000 |     0.0000 |
|     256 |     0.0000 |     0.0000 |     0.0000 |     0.0000 |
|     512 |     0.0000 |     1.0000 |     0.0000 |     0.0000 |
|    1024 |     4.0000 |     4.0000 |     1.0000 |     0.0000 |
|    2048 |    17.0000 |    16.0000 |     0.0000 |     0.0000 |
|    4096 |    56.0000 |    57.0000 |     1.0000 |     1.0000 |
|    8192 |   214.0000 |   216.0000 |     2.0000 |     1.0000 |
|   16384 |   940.0000 |   857.0000 |     5.0000 |     3.0000 |
|   32768 |  4805.0000 |  3560.0000 |    10.0000 |     5.0000 |
|   65536 | 22972.0000 | 14545.0000 |    21.0000 |    14.0000 |
|  131072 | 99055.0000 | 59574.0000 |    41.0000 |    27.0000 |

- What was the fastest algorithm?\
Quicksort
- What was the slowest algorithm?\
Heap sort
- Did the timings match the analysis from class?\
Yes
- What was the hardest part of this assignment?\
None