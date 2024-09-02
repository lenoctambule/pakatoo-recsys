# Pakatoo Recommendation System

A Real-time collaborative filtering system based on energy-based learning.

## Inner-workings

This is an energy-based model using simple correlation calculations inspired by Hopfield Networks. We base the calculations of probability on the simple postulate that either positive energy transitions are more likely than negative energy transitions or that negative energy transitions are more likely than positive energy transitions. The collaborative filtering is stored using an item-item interaction sparse matrix where we update the weights based on user rating history and calculate the probability of liking an item using the softmax function. Weights are regularized using a Dynamic Learning Rate in order to catter with interactions that are overrepresented within the data and to avoid breaking through floating point number limits.

The hamiltonian is the same as Hopfield Networks except that it is localized to a sequence or a subset of the graph $s$ where,

$$
E(s) = \sum_{ < i,j > } W_{ij} \cdot r_i \cdot r_j
$$

Where $r_i$ and $r_j$ are ratings between -1 and 1, in the same rating history or sequence. The learning rule is used to capture statistical correlation between nodes of the graph. Given a weight $W_{ij}$, the learning rule is

$$
dW_{ij} = DLR(W_{ij}) \cdot r_i \cdot r_j
$$

Where DLR is the dynamic learning rate function for which we've chosen,

$$
DLR(W_{ij}) = exp(-|x|)
$$

Now, in order to make inferences, we simply alter the state of the sequence and compute the energy of each of the resulting states to evaluate the probabilities of each state relative to each other. Thus, we have

$$
P(s_i)= {exp({s_i}) \over \sum_{s_j \in |A|} exp({s_j})}
$$

Where $s_i$ is one of the state of the user's rating history to be evaluated.

## Possible improvements

In order to save space complexity, I've chosen to store the matrix as sparse at the expense of time complexity and poor parallelizations possibilities. That is because I thought the "hard-limit" nature of memory would pose a problem given the fact that such a graph would be sparse in real world applications. There is also the possibility to introduce an interaction distance in order to make distant ratings in the sequence less important and focus on recent user activity.

## Results

MovieLens 100k
RMSE : 0.990
