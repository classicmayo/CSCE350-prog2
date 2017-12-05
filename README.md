Noemi Glaeser
3-Dec-2017

Assignment Synopsis adapted from Dr. Gabriel Terejanu

# Bitcoin Simulation Programming Assignment

Usage:
```
lastName_firstName_BTC blockchain.txt transaction.txt
```

## About the Input Files
### Blockchain File
ASCII file which contains headers of all the blocks in the blockchain. Example (`blockchain_1.txt`):
```
026765a1c8235d4ac23d2582cda3b9f5c062f805540320173eb9e9148c0dc518 704b42e4b11ca131b443c2b02a07ec0b45407f1b125027e3e68b86ace6924458 00000001
0b53181ae351f4508363cdc3e8fb3e819fb706c4ba98a3005a980a837561074a 06aa7a8cbda7ac4351c0cae116c589c2eb0ca96cb4c90844812945cb4ffe27c5 00000019
000000000000000000ad6e90c0790e83760a9d13728c23474352a2c8c7a6e0eb 2b12fcf1b09288fcaff797d71e950e71ae42b91e8bdb2304758dfcffc2b620e3 0000000f
```

Each line represents a block. The latest block is on the first line, followed by the block before it, etc. Each header has three fields, separated by spaces, and represented in hexadecimal:  
 Field | Size | Description   
 ----- | ---- | -----------   
 Previous Block Hash | 32 B | References the hash of the previous (parent) block in the chain   
 Merkle Root | 32 B | Hash of the root of the Merkle tree of this block's transactions   
 Nonce | 4 B | Counter for the proof-of-work algorithm   

#### Block Hash
The hash of a particular block is obtained by concatenating its three fields and taking the SHA-256 hash. 

#### Merkle Root
The transactions in the transaction file are given in order. The hash of a transaction can be obtained by taking the SHA-256 hash of the corresponding line of the text file.  
  
A Merkle tree is constructed as follows:  

To illustrate the concept, let us label the transactions in the transaction file in order as A, B, C, ... Take the example file `transactions_1.txt`:  

```
A - Bob Alice 5.0
B - Alice Bob 1.0
C - John Bill 2.4
D - Bill Alice 1.3
E - John Bill 2.7
F - Bob John 7.9
G - Tom Todd 4.5
H - Todd Bob 12.0
```

Now we compute the hash of each transaction. Next, concatenate the hashes of adjacent transactions and take the hash of this new string:  

```
H_AB = hash(hash(A)+hash(B))
H_CD = hash(hash(C)+hash(D))
H_EF = hash(hash(E)+hash(F))
H_GH = hash(hash(G)+hash(H))
```

Concatenate adjacent hashes once again and take the hash of these strings:  

```
H_ABCD = hash(H_AB + H_CD)
H_EFGH = hash(H_EF + H_GH)
```

This process continues until only one string remains, which is called the Merkle root:

```
H_ABCDEFGH = hash(H_ABCD + H_EFGH) 
``` 

As you can see, the subsequent hashing creates a binary tree known as the Merkle tree:  
```
          H_ABCDEFGH
          /        \
       H_ABCD      H_EFGH
       /    \      /    \ 
   H_AB    H_CD   H_EF   H_GH
  /   \    /  \   /   \   /   \
H_A  H_B H_C H_D H_E H_F H_G  H_H
```

### Transaction File
ASCII file containing N transactions, where N is a power of 2. Example (`transactions_1.txt`):
```
Bob Alice 5.0
Alice Bob 1.0
John Bill 2.4
Bill Alice 1.3
John Bill 2.7
Bob John 7.9
Tom Todd 4.5
Todd Bob 12.0 
``` 
Each line represents a transaction, with the first field being the sender, the second the recipient, and the third representing the amount transferred.

## Overview of the Code

1. First, the code checks that the given chain is valid (that is, every block in it is valid, and the chain is not broken).  
- A block is valid if its hash begins with four 0 bits (i.e., one 0 in hex).  
- A chain is unbroken if each block correctly points to the next block in the chain.
2. If the chain is invalid, we print the root of the Merkle tree corresponding to the transactions in the second input file (the transaction file).
- The Merkle root of the above example transaction file is `91fc3bf900a0558a6ead455c2f2c440302d0c33d17c408dd3ce384620d452c70`
3. If the chain is valid, we print out the fields of a new block to point to the latest block in the chain
- The block has the root of the Merkle tree created using the transaction file
- The nonce is mined to create a valid block (i.e., brute force all possible 4-byte combinations to create a block which has a hash beginning in four 0 bits)
- In this example case, the new block is `09ebbf28bacb7910d24dc1ea7a3a3480611a263e7c8163276a1a14f812d43ffd 91fc3bf900a0558a6ead455c2f2c440302d0c33d17c408dd3ce384620d452c70 0000000d`. Its hash is `03b93c10887c7f015dd9524d39f3d763a2f43872f7555724b552de94132e0f25` (note that it begins in a 0 hex character; thus it is valid).
