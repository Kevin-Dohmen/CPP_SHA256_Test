# C++ SHA256 Test

This is a small project of mine, to play around with C++.  
Its a working SHA256 Hashing algorithm.  
I also focussed on optimizing a lot.

> Note: in my initial version i tried not to use Copilot or any AI tools, but i did ask Copilot when i really didn't get it. (eg. Makefile or the padding caluclation)  
  I did use it for optimizing a lot, though i ended up reverting some stuff because i like creating memory leaks manually.

## Algorithms

### Base64

Used to turn any form of data (just bytes in this case) into "readable" characters `regex [A-Za-z0-9+/=]*`.

### SHA256

Turns any ammount of data into a fixed-length (256-bits) "hash".  
Any input will always result in the same hash, but you can't go back from hash to original data.  
Used in for example networking, to check if a file is transfered correctly.

## Results

### Time

> Note: this is in WSL(Ubuntu) and compiled with MinGW on a (slightly bloated) Win11 system with a `AMD Ryzen 5 2600` (3,4 GHz base clock)

|Input lenght (bytes)|Time MS|Clock Cycles (SHA-only)|
|:-------------------|:------|:-----------|
|0 B|0 ms|3978|
|12 B|0 ms|3910|
|64 B|0 ms|5746|
|72 B|0 ms|5814|
|6,3 MB|33,494 ms|113630211|

## Sources

- [Wikipedia - SHA-2](https://en.wikipedia.org/wiki/SHA-2) | For explaination an pseudo-code.
- Copilot | As a chat version of StackOverflow but it actually knows my problem, and optimizations.
