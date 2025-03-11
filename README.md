# 190-final

Exploring the parallelizability of matrix multiplication.


### Matrix Size and Hypothesis 

![image](https://github.com/user-attachments/assets/7e34ed63-23c3-4896-9bf3-4d3f0e4b0885)

**Cache sizes**

Our machine is a 64 bit machine, meaning every integer takes up 8 bytes.

We see that our L1 cache has `128 KB = 1024 * 128` bytes, split among 8 cores. Assuming integer matricies, each entry of the matrix would take up 8 bytes. 

Therefore, our L1 cache can hold up to `(1024 * 128) / 8 = 16384` entries. The max dimension of our matrix should be `128 x 128` if we want all of it to fit in our L1 cache.

We see that our L2 cache has `2 MB = 1024 * 1024 * 2 bytes`, split among 8 cores.

Therefore, our L2 cache can hold up to `(1024 * 1024 * 2) / 8 = 262144` entries. The max dimension of our matrix should be `sqrt(262144) + 128 =>  640 x 640` if we want all of it to fit in our L2 cache.

We see that our L3 cache has `16 MB = (1024 * 1024 * 16) bytes`, split among 8 cores. 

Therefore, our L3 cache can hold up to `(1024 * 1024 * 16) / 8 = 2097152` entries. The max dimension of our matrix should be `floor (sqrt(2097152)) + 512 + 128 => 2088 x 2088` if we want all of it to fit in our L3 cache.
