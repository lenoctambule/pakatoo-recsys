
# Variable Learning Rate Unrestricted Boltzmann Machine

## Energy based learning

Energy based learning is centered around the fundamental assumption that higher (or lower) energy states of a system are more probable than higher energy states ie.

$$
E(a) > E(b) \iff P(X=a) > P(X=b)
$$

Where $E(a)$ denotes the energy of a system in a state $a$ and $P(X=a)$ is the probability of a random variable X representing the system of being in state $a$. And for continuous states, this assumption would imply that for an hamiltonian $E(x)$ and a probability density function $P(X=x) = f_X(x)$,

$$
{dE(x) \over dx} > 0 \iff {df_X(x) \over dx} > 0
$$

Thus, we can "learn" the probability density function through the normalisation of the energy function $f_X(x)$ ie.

$$
\int_{x \in \Omega} \text{normalize}(E(x))dx = 1
$$

## Energy landscape

The most common way to compute an energy landscape is to take heavy inspiration from the Ising model and compute correlations between microstates of the systems giving us :

$$
E(x) = \sum_{ <i,j> } I_{ij} \cdot x_i \cdot x_j
$$


