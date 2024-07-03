# Sparsely Activated Hopfield Network 

Author : RALAMBOARIVONY Ravaka \
Date : 19-06-2024

## Abstract

Most approaches in the design of deep learning architecture are layered and top-down, however Hopfield Networks are one of the rare cases, maybe the only one, where the design is bottom-up by taking inspiration from statistical physics. More importantly the system also seems to be functionning from the bottom-up as it does not require layer to layer algorithms such as backpropagation. This property is interesting computationally because it might allow us to design them such that they are sparsely activated which could  help optimize training and inference times for CPUs aswell as saving energy but could also allow for online training. That is only if we are able to make these networks to be sparsely activated during both training and inference.

This paper introduces Sparsely Activated Hopfield Neural Network such that it is scalable with non-neuromorphic or non-specialized hardware.

## Model

Local learning rules are both biologically plausible and desirable because of the scaling possibilities but it is difficult to achieve. Much of the difficulty stems from the fact that the approach is not top-down but bottom-up and emergent. Instead of designing a network, we are designing microscale properties of the system such that it will operate as we want at a macro-scale ie. give the system intentional emergent properties.

Hopfield Networks have given insights in how to engineer such systems by introducing a macro energy function or hamiltonian $E$ and at a microscale introducing learning rules and update rules that lowers $E$ for desirable states. This approach is fundational in both AI and the relatively new field of complex systems engineering.

## Results

## Discussion