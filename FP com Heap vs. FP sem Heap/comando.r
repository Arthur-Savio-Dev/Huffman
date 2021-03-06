chama a função library(ggplot2) depois que importar o arquivo

------------------PQ--------------------------

 ggplot(data=tablepq, aes(x=size, y=comparisons)) +
 theme(legend.title=element_blank()) +
 geom_point(color='orange') +
 stat_function(fun=function(x)x, geom="line", aes(colour="O(n)")) +
 xlab("Size") +
 ylab("Comparisons") +
 ggtitle("Priority Queue Graph")
 
-----------------HEAP--------------------------

 ggplot(data=tableheap, aes(x=size, y=comparisons)) +
 theme(legend.title=element_blank()) +
 geom_point(color='green') +
 stat_function(fun=function(x)log2(x), geom="line", aes(colour="O(Log(n)")) +
 xlab("Size") +
 ylab("Comparisons") +
 ggtitle("Heap Graph") +
 xlim(0,500) +
 ylim(0,10)



