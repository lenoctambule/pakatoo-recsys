
# Variable Learning Rate Unrestricted Boltzmann Machine

## Energy based learning

Energy based learning is centered around the fundamental assumption that higher (or lower) energy states of a system are more probable than higher energy states ie.

$$
E(a) > E(b) \iff P(X=a) > P(X=b)
$$

Where $E(a)$ denotes the energy of a system in a state $a$ and $P(X=a)$ is the probability of a random variable X representing the system of being in state $a$. And for continuous states, this assumption would imply that for an hamiltonian $E(x)$ and a probability density function $P(X=x) = f_X(x)$,

$$
sign({dE(x) \over dx}) = sign({df_X(x) \over dx})
$$

Thus, we can "learn" the probability density function through the normalisation of the energy function $f_X(x)$ ie.

$$
\int_{x \in \Omega} \text{normalize}(E(x))dx = 1
$$

Or, in the most practical case, we can approximate the probability of a state relative to other states.

## Energy landscape

The most common way to generate an energy landscape from a set of training data is to take heavy inspiration from the Ising model and compute correlations between microstates of the systems and storing them as an weight matrix I giving us :

$$
E(x) = \sum_{<ij>} I_{ij} \cdot x_i \cdot x_j
$$

## Time dependent Hamiltonian

In order to compute a time dependent hamiltonian, we need 