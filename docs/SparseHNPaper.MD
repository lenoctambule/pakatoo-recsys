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

## I. Problem formulation : a self-engineered system

First, we formalize a system $S$ as an ensemble of parts that as a whole exhibit abstract properties,
$$
S : \prod_{e \in S} P_e \rightarrow P_A
$$

Where $\mu^x$ is a concrete property associated to element $x$ of a system $S$ and $\omega^S$ is a abstract property of a system $S$. The goal is to define each $\mu^x$ such that the sum of these properties matches an abitrarily defined $\omega^S$ or define $\omega^S$ such that it is matched by $\prod_{e \in S} P_e $.

When engineering a system, abstract properties are considered first and then the parts are designed and assembled such that it satisfies that abstract property. When we reason about a system, we consider its parts to figure out its abstract properties. However, we want our system to be self-engineered or autonomously analyzed.

This gives an interesting problem which is to find a system $S_{\text{meta}}$ whose abstract property is to be adaptive. Achieving this would allow to create both systems that are resistant to perturbations but to create systems that improve without any human input.

## II. No need to be smarter, just smart enough

Through Cybernetics and thanks to Ross Ashby insights, we have a theoretical framework for adaptability which can be measured as the ratio between the variety of self-preserving responses of a system and the variety of perturbations of its environment or adversary.

Thus, in order for our system to be adaptable relative to its environment the ratio $r$ of response over perturbation complexity ratio needs to be 

$$ Q = {K(S) \over K(E)} \geq 1 $$

Where $K_S$ is the system's complexity of response and $K_E$ complexity of perturbations.
However, in certain games, simple mimicry (eg. Tit for Tat strategy in Rapoport's work) matches performance of any other strategy because mimicry matches any adversary's strategies in complexity of response just not temporally. In other games where temporality is important, mimic strategies will always underperform because no matter how good of a decision you make, it does not matter if it is too late. We, thus, also need to introduce temporal precedence as a constraint which means that $K(S, t) > K_E(E, t+\delta t)$.

However, in order, to ensure that temporality does not hinder performance and to save computation we'll instead state that,

$$
Q(t) = {K(S, t) \over K(E, t + \delta t)}\approx 1
$$

This gives us one fundamental mechanism of our system which is complexity acclimatation. This is especially crucial in games where complexity comes with a cost.

## III. Sparsely activated and self-organizing network

We can now have

## Results



## Discussion