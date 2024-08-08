# PK2 File Structure

PK2 files are made to store sparse networks for Pakatoo.

## Structure

The header is 12 bytes and contains the magic header and the depth of the network.

- 4 bytes magic head : PK2\x00
- 8 bytes weight depth (unsigned int)

The network is stored as an adjacency list. Each adjancy list is stored linearly following this structure :
Header:
- 8 bytes self id (size_t)
- 8 bytes length of adjacency matrix (size_t)
Body :
- 8 bytes target id (size_t)
- N * 4 bytes weight vector (array of floats)
