# Pakatoo : Architectural Documentation

Author : RALAMBOARIVONY Ravaka \
Date : 19-06-2024

## I. Contextual information

Pakatoo is a third-party Recommendation system as a Service (RaaS). However, it also has to match the industry standards in terms of performance and user-experience ie. the inference has to be real time or at least quasi-real time.

Political and economical context also has to be put into consideration when architecturing the system. For instance, we need to make Pakatoo easily adaptable to new legal contexts in order to ensure Pakatoo's perennity and resilience against these changes (eg. RGPD). The EU's efforts are currently going for **data sovereignty** which could end up being an opportunity.

Our only competitor's (ReCombee) weakness is their "cold start". That is because in order for their collaborative filtering to start working, enough items were interacted with. Item-based filtering is then used as a starter. This weakness could be leveradged in order to compete.

## II. Architecture

### A. Decisions

The microservice architecture is going to be used in order to have flexibility in the choice of wether the hardware is going to be handled internally or externally.

The inference needs to **scale** depending on the load and latency to load relationship must be constant.

### B. Security

User-data must be unexploitable by advertisers and others, as well as to be difficult to use by attackers in case of potential breach. In order to do so, the database has to be :
- Encrypted in transit and at rest
- Implement **differential privacy** to avoid potential **inference attacks**

## III. Techstack

Inference : Python, C++
