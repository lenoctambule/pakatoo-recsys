# Sparsely Activated Hopfield Network 

Author : RALAMBOARIVONY Ravaka \
Date : 19-06-2024

## Abstract

Most approaches in the design of deep learning architecture are layered and top-down, however Hopfield Networks are one of the rare cases, maybe the only one, where the design is bottom-up by taking inspiration from statistical physics. More importantly the system also seems to be functionning from the bottom-up as it does not require layer to layer algorithms such as backpropagation. This property is interesting computationally because it might allow us to design them such that they are sparsely activated which could  help optimize training and inference times for CPUs aswell as saving energy but could also allow for online training. That is only if we are able to make these networks to be sparsely activated during both training and inference by introducing local learning rules.

This paper introduces Sparsely Activated Hopfield Neural Network such that it is scalable with non-neuroconcrete or non-specialized and heterogenous hardware.

## Complex Systems Engineering

Local learning rules are both biologically plausible and desirable because of the scaling possibilities but it is difficult to achieve. And much of that difficulty stems from the fact that the approach is novel since it is not top-down but bottom-up and emergent. We are designing micro-scale properties of the system such that it will self-organize to operate as we want at a macro-scale ie. give the system intentional (and potentially unintentional) emergent properties.

Hopfield Networks have given insights in engineering systems this way by introducing a macro-scale energy function or hamiltonian $E$ and at a microscale introducing learning rules that respectively lowers this macro-measurement $E$ for desirable states of the system while ensuring that the update rule make the system converge to a lower-energy state.

However, they are fully connected network thus we can't exactly consider the learning and update rules to be local. 

## Problem formulation : a system of systems

First, we formalize a system $S$ as an ensemble of parts that as a whole exhibit abstract properties,
$$
S : \bigcup_{x \in S} \mu^x \rightarrow \omega^S
$$

Where $\mu^x$ is a concrete property associated to element $x$ of a system $S$ and $\omega^S$ is a abstract property of a system $S$. The goal is to define each $\mu^x$ such that the sum of these properties matches an abitrarily defined $\omega^S$ or define $\omega^S$ such that it is matched by $\sum_{x \in S}\mu^x$.

For instance, each one of a car's parts makes it drive, respond to our controls, be confortable, etc ... When engineering it, we consider its abstract properties first and work out the parts to be put together. When we reason about it, we consider its parts to figure out its abstract properties. However, a car does not self-assemble or self-organizes because we are doing that. What we want is tell our wishes to a machine so it can do the reasoning and the engineering for us.

This gives an interesting problem which is to find a system $S_{\text{meta}}$ whose abstract property is to efficiently be or make any system we ask. Which means that we are essentially creating a system of all systems.

$$
\bigcup_{x \in S} \mu^x \rightarrow \text{any } \omega
$$


## Energy-based Network


## Results



## Discussion