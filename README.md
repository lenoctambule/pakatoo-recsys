# Pakatoo Recommendation System

A Real-time collaborative filtering system based on energy-based learning.

## Usage

```text
>$ make
>$ python3 py/ipc/benchmark.py
>$ python3 py/ipc/benchmark-1m.py
```

## Possible improvements

In order to save space complexity, I've chosen to store the matrix as sparse at the expense of time complexity and poor parallelizations possibilities. That is because I thought the "hard-limit" nature of memory would pose a problem given the fact that such a graph would be sparse in real world applications. There is also the possibility to introduce an interaction distance in order to make distant ratings in the sequence less important and focus on recent user activity.

## Results

MovieLens 100k
RMSE : 0.990

MovieLens 1M
RMSE : 0.941
