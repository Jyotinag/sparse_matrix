

Sparse Matrix VS. Dense Matrix: Designing an Eﬃcient Data

Structure

Jyotirmay Nag Setu

April 2022

Abstract

In numerical analysis and scientiﬁc computing, gaining eﬃciency regarding memory utilization and arith-

metic operations is a big challenge. In a real life scenario most of the data we work with tends to mainly

comprise of zero elements. That is why it is really ineﬃcient to store a large 2d matrix in a 2d array which

mostly comprise of zero values. We call this matrices sparse. There are several methods of storing a sparse

matrix that utilizes the memory properly. In this write up, we will go through one such implementation

called CSR representation. We will analyze, given a speciﬁc type of matrix, how much eﬃciently it works

and go over some other implementations that can be more useful and eﬃcient.

1 Introduction

We call a matrix sparse if most of its value is zero. In practice, we encounter data sets that contain mostly

zero values. We can deﬁne sparsity of a matrix as follows.

Number of Zero Elements

Sparsity =

T otal Element

Almost every real-world data can be viewed as a graph and a graph can be represented as a 2d matrix.

That is why it is very important to come up with an eﬃcient solution for storing this sparse matrix.

2 Related Work

Many researchers have worked to address the problem of eﬃciently processing and storing a sparse matrix

and have come up with many data structures to store a sparse matrix. In his paper, Y saad et al.[1] went

through some of the storage formats for a sparse matrix such as Dense Format, Linpack Banded Format,

Compressed Sparse Row Format, Coordinate Format, Variable Block Row Format etc. In his paper, S Toledo

et al. [2] addresses the memory system performance of sparse matrix vector multiplication.

3 Problem Statement

We are given a matrix A of size Rnd×nd, where each non-overlapping d d block of the matrix, Dij, is a

diagonal matrix. So the matrix consists of n2 such blocks. An example of such a matrix is shown below:

×





D11

D21

· · ·

D12 D13 · · · D1n





D22

· · ·

D

D23 · · ·

D



2n 

(1)





· · ·

· · ·

· · ·

· · ·

D

D

D

n1

n2

n3

nn

4 Solution

We are going to implement the CSR matrix format and going to use the map from c++. Maps are associative

containers that store elements in a mapped fashion. Each element has a key value and a mapped value. No

two mapped values can have the same key values. We are going to sparsify a dense format matrix and going

to take only the non-zero values and save them as a map where the key will be a pair of the row and column

and the value will be the non-zero value. The main focus is to not waste memory for storing the zero values.

The eﬃciency of this data structure depends on the sparsity of the matrix. As described previously sparsity

is the ratio of number of zero elements to the total elements. From the problem deﬁnition we can summarize

that the sparsity will depend on the value of n and d. We can see from our sparse implementation below

that we are disregarding the zero values and only saving the non-zero elements in our map.

1





std : : map<pair<int , int >, int> s p a r s i f y ( int dense matrix [ row ] [ column ] ) {

map<pair<int , int >,int> new matrix ;

for ( int i =0; i<row ; i ++){

for ( int j =0; j<column ; j ++){

i f ( dense matrix [ i ] [ j ]!=0){

new matrix [ make pair ( i , j )]= dense matrix [ i ] [ j ] ;

}

}

}

return new matrix ;

}

Operations on this map would look something like below. We will traverse through the map and access the

values as follows.

void print mapped matrix ( std : : map<pair<int , int >, int> new matrix ){

for (auto i = new matrix . begin ( ) ; i !=new matrix . end ( ) ; i ++){

cout<<” ( ”<<i−>f i r s t . f i r s t <<” , ”<<i−>f i r s t . second<<” ) : ”<<i−>second<<endl ;

}

}

Doing Matrix operation is a bit trickier when we are working with a data structure like this. Consider adding

two matrices. We will add two values if there row and column values matches. Otherwise we have to save

the smaller row and column values with the non-zero element.

map<pair<int , int >, int> add sparse matrix ( map<pair<int , int >, int> new matrix ,

map<pair<int , int >, int> new matrix2 ){

map<pair<int , int >, int> r e s u l t ;

cout<<”Debug” ;

int apos = 0 , bpos = 0 , len = new matrix . s i z e ( ) ;

for (auto i = new matrix . begin ( ) , j = new matrix2 . begin ( ) ;

i !=new matrix2 . end ( ) ; i ++, j ++){

/∗ i n t val = i−>second + j−>second ;

r e s u l t [ make pair ( i−>f i r s t . f i r s t , i−>f i r s t . second )]= val ; ∗/

i f ( i−>f i r s t . f i r s t > j−>f i r s t . f i r s t | | i−>f i r s t . f i r s t == j−>f i r s t . f i r s t

&& i−>f i r s t . second > j−>f i r s t . second ){

r e s u l t [ make pair ( j−>f i r s t . f i r s t , j−>f i r s t . second )]= j−>second ;

bpos++;

}

else i f ( i−>f i r s t . f i r s t < j−>f i r s t . f i r s t | | i−>f i r s t . f i r s t == j−>f i r s t . f i r s t

&& i−>f i r s t . second < j−>f i r s t . second ){

r e s u l t [ make pair ( i−>f i r s t . f i r s t , i−>f i r s t . second )]= i−>second ;

apos++;

}

else {

int val = i−>second + j−>second ;

i f ( val !=0){

r e s u l t [ make pair ( i−>f i r s t . f i r s t , i−>f i r s t . second )]= val ;

}

apos++;

bpos++;

}

while ( apos<len ){

apos++;

r e s u l t [ make pair ( i−>f i r s t . f i r s t , i−>f i r s t . second )]= i−>second ;

}

while ( bpos<len ){

bpos++;

r e s u l t [ make pair ( j−>f i r s t . f i r s t , j−>f i r s t . second )]= j−>second ;

}

}

return r e s u l t ;

}

Transposing a matrix is the easiest operation with this data structure. We can swap the values of row and

column to get a transposed matrix. The implementation is as follows.

std : : map<pair<int , int >, int>

transpose sparse matrix ( std : : map<pair<int , int >, int> new matrix ){

std : : map<pair<int , int >, int> transpose ;

for (auto i = new matrix . begin ( ) ; i !=new matrix . end ( ) ; i ++){

transpose [ make pair ( i−>f i r s t . second , i−>f i r s t . f i r s t )]= i−>second ;

}

return transpose ;

}

2





4.1 Complexity Analysis

Very large matrices require a lot of memory, and some very large matrices that we wish to work with are

sparse.The problem with representing these sparse matrices as dense matrices is that memory is required

and must be allocated for each 32-bit or even 64-bit zero value in the matrix.This is clearly a waste of

memory resources as those zero values do not contain any information. For the matrix given in the problem

statement we have n2d2 total elements and if we consider the sparse representation we will have to traverse

through n2d elements. It is unnecessary to waste processing power for the zero elements.

4.2 Analysing the Solution

From the deﬁnition of sparsity we get the following equation for our matrix.

(n2d

2 −

n2d)

d

−

1

sparsity =

\=

n2d2

d

We can clearly see that the sparsity of the given matrix depends on the value of d. For a constant value of

n, the sparsity will increase with the value of d. Consider the following value of n and d.

n = 2

d = 3

sparsity = 66.67%

If n stays the same and the value of d increases then:

n = 2

d = 9

sparsity = 88.89%

We can clearly see that the sparsity increases for a constant value of n and an increasing value of d. Figure

1 shows that the memory consumption in this case decreases for our designed data structure when the value

of d increases for a constant n.In ﬁgure 1 the x-axis represents the value of n and the y-axis represents the

value of memory consumption in bytes. The memory consumption of the two matrix format was calculated

Figure 1: Memory Consumption for Fixed Value of n

as follows.

3





int mem = sizeof ( new matrix ) +

new matrix . s i z e ()

sizeof ( decltype ( new matrix ) : : mapped type ) ) ;

cout<<mem<<endl ;

∗

( sizeof ( decltype ( new matrix ) : : key type ) +

cout<<sizeof ( dense matrix ) ;

But the scenario changes when the value of n increases.Let’s consider the following scenarios. For a ﬁxed

value of d the sparsity will stay the same and with a increasing n the memory consumption will be higher.

In ﬁgure 2 we can see that our data structure performs worse when the sparsity of the matrix is low.In ﬁgure

2 the x-axis represents the value of n and the y-axis represents the value of memory consumption in bytes.

Figure 2: Memory Consumption for Fixed Value of d

5 Future Work

We can try out diﬀerent format for sparse matrix such as Linpack Banded Format, Compressed Sparse

Row Format, Coordinate Format, Variable Block Row Format etc. to ﬁnd a more eﬃcient solution for the

problem.

6 Conclusion

Designing a data structure that is eﬃcient in both memory utilization and arithmetical operation is a big

challenge in modern day computer science. As the volume of data increases storing and processing data is

becoming more challenging. In our solution we used map to make a CSR format of sparse matrix. Doing

matrix operations on this kind of data structure is a bit diﬃcult. For better ﬂexibility we can represent

the matrix in the yale format by keeping three 1d vector array A, IA, JA where A will hold the value and

IA and JA will save the row and column value. It is more ﬂexible to work with. We can achieve the same

ﬂexibility with three 1d arrays, but vector is dynamic and more eﬃcient. The full implementation can be

found in the following link. https://github.com/Jyotinag/sparse\_matrix

Personal Webpage Link:https://jyotinag.github.io/

References

[1] Yousef Saad. Sparskit: a basic tool kit for sparse matrix computations, 1994.

[2] S. Toledo. Improving the memory-system performance of sparse-matrix vector multiplication. IBM

Journal of Research and Development, 41(6):711–725, 1997.

4

