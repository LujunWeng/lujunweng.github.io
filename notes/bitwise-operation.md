# Bitwise Operation

## Operators

## Common Questions and Solutions

#### 1. Extracting the least-significant bit
`x & 1`

#### 2. Extracting the lowest set bit
`x & ~(x - 1)`

The effect of `(x - 1)` is interesting. It will divide `x` into two parts around the lowest set bit. The lowest set bit will become 0. The left part of the lowest set bit will remain the same. The right part of the lowest set will be all 1s instead of 0s. This makes it possible to extract and replace the lowest set bit of `x`.

#### 3. Replacing the lowest set bit with 0
`x & (x - 1)`

