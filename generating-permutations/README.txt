文件介绍:
permutation_generator.cpp
    项目代码，实现论文中提及的全排列生成算法，对{1,2,3,...,n}（n为序列长度），生成它所有可能的排列。具体地,
result recursive_generate_permutation_all(int n, bool out=false);    —— 经典递归算法
result heap_generate_permutation_all(int n, bool out=false);         —— Heap算法
result lexic_generate_permutation_by_def(int n, bool out=false);     —— 基于相邻排列的字典序法
result lexic_generate_permutation_by_tran(int n, bool out=false);    —— 基于中介数的字典序法
result ascent_generate_permutation(int n, bool out=false);           —— 递增进位制法
result descent_generate_permutation(int n, bool out=false);          —— 递减进位制法
result sjt_generate_permutation_by_def(int n, bool out=false);       —— 基于相邻排列操作的邻位对换法
result sjt_generate_permutation_by_tran(int n, bool out=false);      —— 基于中介数的邻位对换法
为了实现这些算法，该cpp文件编写了一些基本的函数，十进制数与递增进位制数、递减进位制数之间的相互转化函数，递增进位制数、递减进位制数的加减法函数，四类中介数与相应排列之间的相互转化函数。cpp文件的注释会有具体的说明。另外，该cpp文件还利用中介数的具体意义编写了由当前排列生成该排列在方法中前第几个或者后第几个排列的函数。
