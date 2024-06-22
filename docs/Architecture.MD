# Pakatoo : Architectural Documentation

Author : RALAMBOARIVONY Ravaka \
Date : 19-06-2024

## I. Contextual information

Pakatoo is a third-party Recommendation system as a Service (RaaS). However, it also has to match the industry standards in terms of performance and user-experience ie. the inference has to be real time or at least quasi-real time.

Political and economical context also has to be put into consideration when architecturing the system. For instance, we need to make Pakatoo easily adaptable to new legal contexts in order to ensure Pakatoo's perennity and resilience against these changes (eg. RGPD). The EU's efforts are currently going for **data sovereignty** which could end up being an opportunity.

Our only competitor's (ReCombee) weakness is their "cold start". That is because in order for their collaborative filtering to start working, enough items were interacted with. Item-based filtering is then used as a starter. This weakness could be leveradged in order to compete.

## II. Architecture

### A. Constraints

- The microservice architecture is going to be used in order to have flexibility in the choice of wether the hardware is going to be handled internally or externally, to make development easier, to allow use of load balancing and containerisation.
- The inference needs to **scale** depending on the load and latency to load relationship must be constant.
- The amount of users and items should not affect inference time.
- The model needs to saved and retrieved easily in case of a crash or reboot.

### B. Decisions

In order to manage cold starts, just like our competitors ReCombee, we will use an item-based and collaborative filtering hybrid model. By initalizing the model with non-random values the system will be able to hopefully find a minima in less time than if it was initialized randomly.

Moreover, we will need to make use of cross-database enrichment contrario to our competitor Recombee while staying in line with Europe's legal context. The best way to implement this will be a model that is flexible and with the same attention mechanism as in the transformer architecture. The most fit neural architecture to achieve is a modified version of Hopfield Networks.

### B. Security

User-data must be unexploitable by advertisers and others, as well as to be difficult to use by attackers in case of potential breach. In order to do so, the database has to be :
- Encrypted in transit and at rest
- Implement **differential privacy** to avoid potential **inference attacks** or better if we can make it impossible.

## III. Techstack

Inference : Python, C++
Other : Docker, Linux
