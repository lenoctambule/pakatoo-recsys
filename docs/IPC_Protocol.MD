# IPC API

## Request

Header :

- Instance ID       (ushort)
- Command ID        (ushort)
- Message length    (unsigned long)

Body is arbitrary.

## Response

Header :
- Return code       (uchar)
- Message length    (unsigned long)

Body is arbitrary.