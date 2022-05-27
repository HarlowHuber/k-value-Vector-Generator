# k-valued--Vector--Generator
This generates all possible k-valued vectors for a given vector of k-values, where k = (k1, k2, k3, kn, kn+1, ...). 

For example, if k = (2, 2, 2), there will be 8 binary vectors generated, ordered by there Hamming norm, and sorted by the value of the vector: 

   Hamming norm = 3<br />
   (1, 1, 1)

   Hamming norm = 2<br />
   (1, 1, 0), (1, 0, 1), (0, 1, 1)

   Hamming norm = 1<br />
   (1, 0, 0), (0, 1, 0), (0, 0, 1)

   Hamming norm = 0<br />
   (0, 0, 0)
