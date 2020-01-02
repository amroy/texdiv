# texdiv
Texdiv is a small python code for fast kullback-Leibller divergence computation between two statistical models. I used this program for my research work during my PhD thesis to benchmark different statistical models when I had needed to avoid waiting hours or days to get a retrieval rate when using a large dataset. Texdiv uses OpenCL in the background to perform the parallel divergence computation.