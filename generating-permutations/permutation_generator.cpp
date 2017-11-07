#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

struct result {
    int cc;
    double tt;
};

vector<int> ten2ascent(int num, int digit);    // 将十进制数转化为递增进位制数，递增进位制数长度为digit-1，即最高位逢digit进1
int ascent2ten(vector<int> asc, int digit);    // 将递增进位制数转化为十进制数，递增进位制数长度为digit-1，即最高位逢digit进1
vector<int> ten2descent(int num, int digit);    // 将十进制数转化为递减进位制数，递减进位制数长度为digit-1，即最低位逢digit进1
int descent2ten(vector<int> desc, int digit);    // 将递减进位制数转化为十进制数，递减进位制数长度为digit-1，即最低位逢digit进1
bool ascent_plus(vector<int> a, vector<int> b, vector<int> &c, int digit);
// 递增进位制数的加法运算，递增进位制数最高位逢digit进1，若a+b不能用digit-1位数表示，则返回false，否则返回true，c记录a+b的值
bool ascent_minus(vector<int> a, vector<int> b, vector<int> &c, int digit);
// 递增进位制数的减法运算，递增进位制数最高位逢digit进1，若a-b<0，则返回false，否则返回true，c记录a-b的值
bool descent_plus(vector<int> a, vector<int> b, vector<int> &c, int digit);
// 递减进位制数的加法运算，递减进位制数最低位逢digit进1，若a+b不能用digit-1位数表示，则返回false，否则返回true，c记录a+b的值
bool descent_minus(vector<int> a, vector<int> b, vector<int> &c, int digit);
// 递减进位制数的减法运算，递减进位制数最低位逢digit进1，若a-b<0，则返回false，否则返回true，c记录a-b的值
vector<int> lexic_permutation_to(vector<int> perm);    // 字典序下排列转化为中介数
vector<int> lexic_to_permutation(vector<int> lexic);    // 字典序下中介数转化为排列
bool lexic_next_permutation_by_def(vector<int> &perm);
// 字典序下根据定义生成当前排列的下一个排列，若已是最后一个，则返回false，否则返回true，perm记录下一个排列
bool lexic_relative_permutation(vector<int> &perm, int num);
// 字典序下相对当前排列的前第几个或者后第几个排列，若溢出，则返回false，否则返回true，perm记录相应的排列
vector<int> ascent_permutation_to(vector<int> perm);    // 递增进位制法下排列转化为中介数
vector<int> ascent_to_permutation(vector<int> asc);    // 递增进位制法下中介数转化为排列
bool ascent_relative_permutation(vector<int> &perm, int num);
// 递增进位制法下相对当前排列的前第几个或者后第几个排列，若溢出，则返回false，否则返回true，perm记录相应的排列
vector<int> descent_permutation_to(vector<int> perm);    // 递减进位制法下排列转化为中介数
vector<int> descent_to_permutation(vector<int> desc);    // 递减进位制法下中介数转化为排列
bool descent_relative_permutation(vector<int> &perm, int num);
// 递减进位制法下相对当前排列的前第几个或者后第几个排列，若溢出，则返回false，否则返回true，perm记录相应的排列
vector<int> sjt_permutation_to(vector<int> perm);    // 邻位对换法下排列转化为中介数
vector<int> sjt_to_permutation(vector<int> sjt);    // 邻位对换法下中介数转化为排列
bool sjt_next_permutation_by_def(vector<int> &perm, vector<int> &dir);
// 邻位对换法下根据当前排列和数字方向生成下一个排列和数字方向，若已是最后一个，返回false，否则返回true，perm和dir记录下一个排列及对应的数字方向
bool sjt_relative_permutation(vector<int> &perm, int num);
// 邻位对换法下相对当前排列的前第几个或者后第几个排列，若溢出，则返回false，否则返回true，perm记录相应的排列
void output(vector<int> &perm);    // 输出某个排列
void recursive_generate_permutation(vector<int> &array, int start, int end, int &count, bool out=false);    // 经典递归算法产生序列start到end部分的全排列，out控制输出，下同
void heap_generate_permutation(vector<int> &array, int n, int &count, bool out=false);    // Heap算法产生n个数的全排列
result recursive_generate_permutation_all(int n, bool out=false);    // 经典递归算法产生全排列
result heap_generate_permutation_all(int n, bool out=false);    // Heap算法产生全排列
result lexic_generate_permutation_by_def(int n, bool out=false);    // 基于相邻排列的字典序法产生全排列
result lexic_generate_permutation_by_tran(int n, bool out=false);    // 基于中介数的字典序法产生全排列
result ascent_generate_permutation(int n, bool out=false);    // 递增进位制法产生全排列
result descent_generate_permutation(int n, bool out=false);    // 递减进位制法产生全排列
result sjt_generate_permutation_by_def(int n, bool out=false);    // 基于相邻排列操作的邻位对换法产生全排列
result sjt_generate_permutation_by_tran(int n, bool out=false);    // 基于中介数的邻位对换法产生全排列
void method_select(int method_number, int n, bool out=false);    // 对长度为n的序列，用method_number对应的算法生成全排列

int main()
{
    // 算法及其对应的选项数字
    cout << "-----------------Option----------------" << endl;
    cout << " ----------------------------- ------- " << endl;
    cout << "|           Methods           | Input |" << endl;
    cout << " ----------------------------- ------- " << endl;
    cout << "|          Recursive          |   1   |" << endl;
    cout << "|            HEAP             |   2   |" << endl;
    cout << "| Lexicographical(definition) |   3   |" << endl;
    cout << "|   Lexicographical(medium)   |   4   |" << endl;
    cout << "|           Ascent            |   5   |" << endl;
    cout << "|           Descent           |   6   |" << endl;
    cout << "|       SJT(definition)       |   7   |" << endl;
    cout << "|         SJT(medium)         |   8   |" << endl;

    int length;
    cout << "Please input the length of the permutation: ";
    cin >> length;    // 输入序列长度

    // int method_number;
    // cout << "Please input a number which represent the method: ";
    // cin >> method_number;    // 输入选项数字

    // 用所有算法对长度为length的序列进行全排列
    bool out = false;
    for(int i = 1; i <= 8; i++) {
        method_select(i, length, out);
    }
    return 0;
}

vector<int> ten2ascent(int num, int digit) {
    if(num < 0) {
        cout << "Number should be nonnegtive!" << endl;
        exit(1);
    }
    vector<int> asc(digit - 1);
    int fac = 1;
    for(int i = 2; i < digit; i++) {
        fac *= i;
    }
    if(num >= (fac * digit)) {
        cout << "Overflow!" << endl;    // 超过表示范围
        exit(1);
    }
    int temp = num;
    for(int i = 0; i < digit - 1; i++) {
        asc[i] = temp / fac;
        temp %= fac;
        fac /= (digit - 1 - i);
    }
    return asc;
}

int ascent2ten(vector<int> asc, int digit) {
    int num = 0;
    for(int i = 0; i < digit - 1; i++) {
        num = (num + asc[i]) * (digit - 1 - i);
    }
    return num;
}

vector<int> ten2descent(int num, int digit) {
    if(num < 0) {
        cout << "Number should be nonnegtive!" << endl;
        exit(1);
    }
    vector<int> desc;
    desc.push_back(num % digit);
    int temp = num / digit;
    int nn = digit - 1;
    while((temp != 0) && (nn >= 2)) {
        desc.push_back(temp % nn);
        temp /= nn;
        nn--;
    }
    if(temp != 0) {
        cout << "Overflow!" << endl;    // 超过表示范围
        exit(1);
    }
    int sz = desc.size();
    for(int i = 0; i < sz / 2; i++) {
        temp = desc[i];
        desc[i] = desc[sz - 1 - i];
        desc[sz - 1 - i] = temp;
    }
    desc.insert(desc.begin(), digit - 1 - sz, 0);
    return desc;
}

int descent2ten(vector<int> desc, int digit) {
    int num = 0;
    for(int i = 0; i < digit - 2; i++) {
        num = (num + desc[i]) * (i + 3);
    }
    num += desc[digit - 2];
    return num;
}

bool ascent_plus(vector<int> a, vector<int> b, vector<int> &c, int digit) {
    int dig = 2;
    int res = 0;    // 控制进位
    for(int i = digit - 2; i >= 0; i--) {
        c[i] = a[i] + b[i] + res;
        if(c[i] >= dig) {
            c[i] -= dig;    // 当前逢dig进1
            res = 1;
        } else {
            res = 0;
        }
        dig++;
    }
    if(res == 1) {
        return false;
    } else {
        return true;
    }
}

bool ascent_minus(vector<int> a, vector<int> b, vector<int> &c, int digit) {
    int dig = 2;
    int res = 0;
    for(int i = digit - 2; i >= 0; i--) {
        c[i] = a[i] - res - b[i];
        if(c[i] < 0) {
            c[i] += dig;
            res = 1;
        } else {
            res = 0;
        }
        dig++;
    }
    if(res == 1) {
        return false;
    } else {
        return true;
    }
}

bool descent_plus(vector<int> a, vector<int> b, vector<int> &c, int digit) {
    int dig = digit;
    int res = 0;
    for(int i = digit - 2; i >= 0; i--) {
        c[i] = a[i] + b[i] + res;
        if(c[i] >= dig) {
            c[i] -= dig;
            res = 1;
        } else {
            res = 0;
        }
        dig--;
    }
    if(res == 1) {
        return false;
    } else {
        return true;
    }
}

bool descent_minus(vector<int> a, vector<int> b, vector<int> &c, int digit) {
    int dig = digit;
    int res = 0;
    for(int i = digit - 2; i >= 0; i--) {
        c[i] = a[i] - res - b[i];
        if(c[i] < 0) {
            c[i] += dig;
            res = 1;
        } else {
            res = 0;
        }
        dig--;
    }
    if(res == 1) {
        return false;
    } else {
        return true;
    }
}

vector<int> lexic_permutation_to(vector<int> perm) {
    int sz = perm.size();
    vector<int> lexic(sz - 1, 0);
    for(int i = 0; i < sz - 1; i++) {
        for(int j = i + 1; j < sz; j++) {
            if(perm[j] < perm[i]) {
                lexic[i]++;    // lexic[i]表示perm[(i+1):]中比perm[i]小的数字个数
            }
        }
    }
    return lexic;
}

vector<int> lexic_to_permutation(vector<int> lexic) {
    int sz = lexic.size();
    vector<int> perm(sz + 1);
    int sum = 0;
    for(int i = 0; i < sz; i++) {
        perm[i] = lexic[i] + 1;
        int temp = perm[i];
        for(int j = 0; j < i; j++) {
            if(perm[j] <= perm[i]) {
                temp++;    // 之前序列已出现比perm[i]小的数字
            }
        }
        bool flag = (temp > perm[i])? true: false;
        perm[i] = temp;
        while(flag) {
            flag = false;
            for(int j = 0; j < i; j++) {
                if(perm[j] == perm[i]) {
                    flag = true;
                    perm[i]++;
                    break;
                }
            }
        }
        sum += perm[i];
    }
    perm[sz] = ((sz + 1) * (sz + 2)) / 2 - sum;
    return perm;
}

bool lexic_next_permutation_by_def(vector<int> &perm) {
    int sz = perm.size();
    int ind1 = -1;
    for(int i = 0; i < sz - 1; i++) {    // 寻找最大的递增索引，
        if(perm[i] < perm[i + 1]) {
            ind1 = i;
        }
    }
    if(ind1 == -1) {
        return false;
    } else {
        int ind2 = ind1 + 1;
        for(int j = ind1 + 2; j < sz; j++) {
            if(perm[j] > perm[ind1]) {
                ind2 = j;
            }
        }
        int temp = perm[ind1];    // 与右侧比当前数大的最小数交换
        perm[ind1] = perm[ind2];
        perm[ind2] = temp;
        for(int j = ind1 + 1; j < ((ind1 + 1 + sz) / 2); j++) {    // 翻转
            temp = perm[j];
            perm[j] = perm[ind1 + sz - j];
            perm[ind1 + sz - j] = temp;
        }
        return true;
    }
}

bool lexic_relative_permutation(vector<int> &perm, int num) {
    if(num == 0) {
        return true;
    } else {
        int sz = perm.size();
        vector<int> lexic = lexic_permutation_to(perm);    // 得到中介数
        vector<int> nn(sz - 1, 0);
        vector<int> relexic(sz - 1, 0);
        bool flag;
        if(num > 0) {
            nn = ten2ascent(num, sz);
            flag = ascent_plus(lexic, nn, relexic, sz);
        } else {
            nn = ten2ascent(-num, sz);
            flag = ascent_minus(lexic, nn, relexic, sz);
        }
        if(flag) {
            perm = lexic_to_permutation(relexic);    // 推出排列
        }
        return flag;
    }
}

vector<int> ascent_permutation_to(vector<int> perm) {
    int sz = perm.size();
    vector<int> asc(sz - 1, 0);
    for(int i = 0; i < sz; i++) {
        if(perm[i] != 1) {
            for(int j = i + 1; j < sz; j++) {
                if(perm[j] < perm[i]) {
                    asc[sz - perm[i]]++;    // 中介数定义
                }
            }
        }
    }
    return asc;
}

vector<int> ascent_to_permutation(vector<int> asc) {
    int sz = asc.size();
    vector<int> perm(sz + 1, 1);
    for(int i = 0; i < sz; i++) {
        int count = 0;
        for(int j = sz; j >= 0; j--) {
            if(perm[j] == 1) {    // 寻找空位
                if(count < asc[i]) {
                    count++;
                } else {
                    perm[j] = sz + 1 - i;
                    break;
                }
            }
        }
    }
    return perm;
}

bool ascent_relative_permutation(vector<int> &perm, int num) {
    if(num == 0) {
        return true;
    } else {
        int sz = perm.size();
        vector<int> asc = ascent_permutation_to(perm);
        vector<int> nn(sz - 1, 0);
        vector<int> reasc(sz - 1, 0);
        bool flag;
        if(num > 0) {
            nn = ten2ascent(num, sz);
            flag = ascent_plus(asc, nn, reasc, sz);
        } else {
            nn = ten2ascent(-num, sz);
            flag = ascent_minus(asc, nn, reasc, sz);
        }
        if(flag) {
            perm = ascent_to_permutation(reasc);
        }
        return flag;
    }
}

vector<int> descent_permutation_to(vector<int> perm) {
    int sz = perm.size();
    vector<int> desc(sz - 1, 0);
    for(int i = 0; i < sz; i++) {
        if(perm[i] != 1) {
            for(int j = i + 1; j < sz; j++) {
                if(perm[j] < perm[i]) {
                    desc[perm[i] - 2]++;    // 中介数定义
                }
            }
        }
    }
    return desc;
}

vector<int> descent_to_permutation(vector<int> desc) {
    int sz = desc.size();
    vector<int> perm(sz + 1, 1);
    for(int i = sz - 1; i >= 0; i--) {
        int count = 0;
        for(int j = sz; j >= 0; j--) {
            if(perm[j] == 1) {    // 寻找空位
                if(count < desc[i]) {
                    count++;
                } else {    // 右侧空位数满足条件
                    perm[j] = i + 2;
                    break;
                }
            }
        }
    }
    return perm;
}

bool descent_relative_permutation(vector<int> &perm, int num) {
    if(num == 0) {
        return true;
    } else {
        int sz = perm.size();
        vector<int> desc = descent_permutation_to(perm);
        vector<int> nn(sz - 1, 0);
        vector<int> redesc(sz - 1, 0);
        bool flag;
        if(num > 0) {
            nn = ten2descent(num, sz);
            flag = descent_plus(desc, nn, redesc, sz);
        } else {
            nn = ten2descent(-num, sz);
            flag = descent_minus(desc, nn, redesc, sz);
        }
        if(flag) {
            perm = descent_to_permutation(redesc);
        }
        return flag;
    }
}

vector<int> sjt_permutation_to(vector<int> perm) {
    int sz = perm.size();
    vector<int> left(sz - 1, 0);
    vector<int> right(sz - 1, 0);
    vector<int> sjt(sz - 1, 0);
    for(int i = 0; i < sz; i++) {
        if(perm[i] != 1) {
            for(int j = 0; j < i; j++) {
                if(perm[j] < perm[i]) {
                    left[perm[i] - 2]++;
                }
            }
            for(int j = i + 1; j < sz; j++) {
                if(perm[j] < perm[i]) {
                    right[perm[i] - 2]++;
                }
            }
        }
    }
    sjt[0] = right[0];
    for(int i = 3; i <= sz; i++) {
        int temp = (i % 2 == 1)? (sjt[i - 3]): (sjt[i - 3] + sjt[i - 4]);
        sjt[i - 2] = (temp % 2 == 1)? (left[i - 2]): (right[i - 2]);    // 中介数定义（奇向右偶向左）
    }
    return sjt;
}

vector<int> sjt_to_permutation(vector<int> sjt) {
    int sz = sjt.size();
    vector<int> dir(sz, 0);
    vector<int> perm(sz + 1, 1);
    for(int i = 1; i < sz; i++) {
        int temp = (i % 2 == 1)? (sjt[i - 1]): (sjt[i - 1] + sjt[i - 2]);
        dir[i] = (temp % 2 == 1)? 1: 0;    // 先得到方向
    }
    for(int i = sz - 1; i >= 0; i--) {
        int count = 0;
        if(dir[i] == 0) {
            for(int j = sz; j >= 0; j--) {    // 与方向相反
                if(perm[j] == 1) {    // 寻找空位
                    if(count < sjt[i]) {
                        count++;
                    } else {
                        perm[j] = i + 2;
                        break;
                    }
                }
            }
        } else {
            for(int j = 0; j <= sz; j++) {
                if(perm[j] == 1) {
                    if(count < sjt[i]) {
                        count++;
                    } else {
                        perm[j] = i + 2;
                        break;
                    }
                }
            }
        }
    }
    return perm;
}

bool sjt_next_permutation_by_def(vector<int> &perm, vector<int> &dir) {
    int sz = perm.size();
    int ind = -1;
    int maxmob = 0;
    // 寻找最大的可移动数
    if((dir[0] == 1) && (perm[0] > perm[1])) {
        ind = 0;
        maxmob = perm[0];
    }
    for(int i = 1; i < sz - 1; i++) {
        if(perm[i] > perm[i + dir[i]]) {
            if(perm[i] > maxmob) {
                maxmob = perm[i];
                ind = i;
            }
        }
    }
    if((dir[sz - 1] == -1) && (perm[sz - 1] > perm[sz - 2])) {
        if(maxmob < perm[sz - 1]) {
            maxmob = perm[sz - 1];
            ind = sz - 1;
        }
    }
    if(ind == -1) {
        return false;
    } else {
        // 交换
        int temp1 = perm[ind];
        int temp2 = dir[ind];    // 很重要，防止错位
        perm[ind] = perm[ind + temp2];
        perm[ind + temp2] = temp1;
        dir[ind] = dir[ind + temp2];
        dir[ind + temp2] = temp2;
        for(int i = 0; i < sz; i++) {
            if(perm[i] > maxmob) {
                dir[i] = -dir[i];    // 超过最大可移动数的数的方向改变
            }
        }
        return true;
    }
}

bool sjt_relative_permutation(vector<int> &perm, int num) {
    if(num == 0) {
        return true;
    } else {
        int sz = perm.size();
        vector<int> sjt = sjt_permutation_to(perm);
        vector<int> nn(sz - 1, 0);
        vector<int> resjt(sz - 1, 0);
        bool flag;
        if(num > 0) {
            nn = ten2descent(num, sz);
            flag = descent_plus(sjt, nn, resjt, sz);
        } else {
            nn = ten2descent(-num, sz);
            flag = descent_minus(sjt, nn, resjt, sz);
        }
        if(flag) {
            perm = sjt_to_permutation(resjt);
        }
        return flag;
    }
}

void output(vector<int> &perm) {
    for(int i = 0; i < perm.size(); i++) {
        cout << perm[i] << " ";
    }
    cout << endl;
}

void recursive_generate_permutation(vector<int> &array, int start, int end, int &count, bool out) {
    if(start == end) {
        count++;
        if(out) {
            output(array);
        }
    } else {
        recursive_generate_permutation(array, start + 1, end, count, out);
        for(int i = start + 1; i <= end; i++) {
            int temp = array[i];
            array[i] = array[start];
            array[start] = temp;
            recursive_generate_permutation(array, start + 1, end, count, out);
            array[start] = array[i];
            array[i] = temp;
        }
    }
}

void heap_generate_permutation(vector<int> &array, int n, int &count, bool out) {
    if(n == 1) {
        count++;
        if(out) {
            output(array);
        }
    } else {
        for(int i = 0; i < n - 1; i++) {
            heap_generate_permutation(array, n - 1, count, out);
            if(n % 2 == 0) {
                int temp = array[i];
                array[i] = array[n - 1];
                array[n - 1] = temp;
            } else {
                int temp = array[0];
                array[0] = array[n - 1];
                array[n - 1] = temp;
            }
        }
        heap_generate_permutation(array, n - 1, count, out);
    }
}

result recursive_generate_permutation_all(int n, bool out) {
    clock_t start, finish;
    int count = 0;
    vector<int> array(n, 0);
    for(int i = 0; i < n; i++) {
        array[i] = i + 1;
    }
    start = clock();
    recursive_generate_permutation(array, 0, n - 1, count, out);
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result heap_generate_permutation_all(int n, bool out) {
    clock_t start, finish;
    int count = 0;
    vector<int> array(n, 0);
    for(int i = 0; i < n; i++) {
        array[i] = i + 1;
    }
    start = clock();
    heap_generate_permutation(array, n, count, out);
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result lexic_generate_permutation_by_def(int n, bool out) {
    clock_t start, finish;
    int count = 1;
    vector<int> perm(n, 0);
    for(int i = 0; i < n; i++) {
        perm[i] = i + 1;
    }
    if(out) {
        output(perm);
    }
    start = clock();
    while(lexic_next_permutation_by_def(perm)) {
        count++;
        if(out) {
            output(perm);
        }
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result lexic_generate_permutation_by_tran(int n, bool out) {
    clock_t start, finish;
    int count = 1;
    vector<int> iter(n - 1, 0);
    vector<int> perm = lexic_to_permutation(iter);
    if(out) {
        output(perm);
    }
    vector<int> one = ten2ascent(1, n);
    vector<int> nextiter(n - 1, 0);
    start = clock();
    while(ascent_plus(iter, one, nextiter, n)) {
        count++;
        iter = nextiter;
        perm = lexic_to_permutation(iter);
        if(out) {
            output(perm);
        }
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result ascent_generate_permutation(int n, bool out) {
    clock_t start, finish;
    int count = 1;
    vector<int> iter(n - 1, 0);
    vector<int> perm = ascent_to_permutation(iter);
    if(out) {
        output(perm);
    }
    vector<int> one = ten2ascent(1, n);
    vector<int> nextiter(n - 1, 0);
    start = clock();
    while(ascent_plus(iter, one, nextiter, n)) {
        count++;
        iter = nextiter;
        perm = ascent_to_permutation(iter);
        if(out) {
            output(perm);
        }
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result descent_generate_permutation(int n, bool out) {
    clock_t start, finish;
    int count = 1;
    vector<int> iter(n - 1, 0);
    vector<int> perm = descent_to_permutation(iter);
    if(out) {
        output(perm);
    }
    vector<int> one = ten2descent(1, n);
    vector<int> nextiter(n - 1, 0);
    start = clock();
    while(descent_plus(iter, one, nextiter, n)) {
        count++;
        iter = nextiter;
        perm = descent_to_permutation(iter);
        if(out) {
            output(perm);
        }
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result sjt_generate_permutation_by_def(int n, bool out) {
    clock_t start, finish;
    int count = 1;
    vector<int> perm(n);
    vector<int> dir(n);
    for(int i = 0; i < n; i++) {
        perm[i] = i + 1;
        dir[i] = -1;
    }
    if(out) {
        output(perm);
    }
    start = clock();
    while(sjt_next_permutation_by_def(perm, dir)) {
        count++;
        if(out) {
            output(perm);
        }
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result sjt_generate_permutation_by_tran(int n, bool out) {
    clock_t start, finish;
    int count = 1;
    vector<int> iter(n - 1, 0);
    vector<int> perm = sjt_to_permutation(iter);
    if(out) {
        output(perm);
    }
    vector<int> one = ten2descent(1, n);
    vector<int> nextiter(n - 1, 0);
    start = clock();
    while(descent_plus(iter, one, nextiter, n)) {
        count++;
        iter = nextiter;
        perm = sjt_to_permutation(iter);
        if(out) {
            output(perm);
        }
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

void method_select(int method_number, int length, bool out) {
    result res;
    switch(method_number) {
        case 1:
            cout << "Method Recursive:" << endl;
            res = recursive_generate_permutation_all(length, out);
            break;
        case 2:
            cout << "Method Heap: " << endl;
            res = heap_generate_permutation_all(length, out);
            break;
        case 3:
            cout << "Method Lexicographical(definition): " << endl;
            res = lexic_generate_permutation_by_def(length, out);
            break;
        case 4:
            cout << "Method Lexicographical(medium): " << endl;
            res = lexic_generate_permutation_by_tran(length, out);
            break;
        case 5:
            cout << "Method Ascent: " << endl;
            res = ascent_generate_permutation(length, out);
            break;
        case 6:
            cout << "Method Descent: " << endl;
            res = descent_generate_permutation(length, out);
            break;
        case 7:
            cout << "Method SJT(definition): " << endl;
            res = sjt_generate_permutation_by_def(length, out);
            break;
        case 8:
            cout << "Method SJT(medium): " << endl;
            res = sjt_generate_permutation_by_tran(length, out);
            break;
    }
    cout << "Total permutations: " << res.cc << "   | Time consuming: " << res.tt << endl;
}
