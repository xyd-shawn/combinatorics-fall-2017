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

vector<int> ten2ascent(int num, int digit);
int ascent2ten(vector<int> asc, int digit);
vector<int> ten2descent(int num, int digit);
int descent2ten(vector<int> desc, int digit);
bool ascent_plus(vector<int> a, vector<int> b, vector<int> &c, int digit);
bool ascent_minus(vector<int> a, vector<int> b, vector<int> &c, int digit);
bool descent_plus(vector<int> a, vector<int> b, vector<int> &c, int digit);
bool descent_minus(vector<int> a, vector<int> b, vector<int> &c, int digit);
vector<int> lexic_permutation_to(vector<int> perm);
vector<int> lexic_to_permutation(vector<int> lexic);
bool lexic_next_permutation_by_def(vector<int> &perm);
bool lexic_relative_permutation(vector<int> &perm, int num);
vector<int> ascent_permutation_to(vector<int> perm);
vector<int> ascent_to_permutation(vector<int> asc);
bool ascent_relative_permutation(vector<int> &perm, int num);
vector<int> descent_permutation_to(vector<int> perm);
vector<int> descent_to_permutation(vector<int> desc);
bool descent_relative_permutation(vector<int> &perm, int num);
vector<int> sjt_permutation_to(vector<int> perm);
vector<int> sjt_to_permutation(vector<int> sjt);
bool sjt_next_permutation_by_def(vector<int> &perm, vector<int> &dir);
bool sjt_relative_permutation(vector<int> &perm, int num);
void recursive_generate_permutation(vector<int> &array, int start, int end, int &count);
void heap_generate_permutation(vector<int> &array, int n, int &count);
result recursive_generate_permutation_all(int n);
result heap_generate_permutation_all(int n);
result lexic_generate_permutation_by_def(int n);
result lexic_generate_permutation_by_tran(int n);
result ascent_generate_permutation(int n);
result descent_generate_permutation(int n);
result sjt_generate_permutation_by_def(int n);
result sjt_generate_permutation_by_tran(int n);
void method_select(int method_number, int n);

int main()
{
    int length;
    cout << "Please input the length of the permutation: ";
    cin >> length;

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

    // int method_number;
    // cout << "Please input a number which represent the method: ";
    // cin >> method_number;
    for(int i = 1; i <= 8; i++) {
        method_select(i, length);
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
        cout << "Overflow!" << endl;
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
        cout << "Overflow!" << endl;
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
    int res = 0;
    for(int i = digit - 2; i >= 0; i--) {
        c[i] = a[i] + b[i] + res;
        if(c[i] >= dig) {
            c[i] -= dig;
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
                lexic[i]++;
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
                temp++;
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
    for(int i = 0; i < sz - 1; i++) {
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
        int temp = perm[ind1];
        perm[ind1] = perm[ind2];
        perm[ind2] = temp;
        for(int j = ind1 + 1; j < ((ind1 + 1 + sz) / 2); j++) {
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
        vector<int> lexic = lexic_permutation_to(perm);
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
            perm = lexic_to_permutation(relexic);
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
                    asc[sz - perm[i]]++;
                }
            }
        }
    }
    return asc;
}

vector<int> ascent_to_permutation(vector<int> asc) {
    int sz = asc.size();
    vector<int> perm(sz + 1, 0);
    for(int i = 0; i < sz; i++) {
        int count = 0;
        for(int j = sz; j >= 0; j--) {
            if(perm[j] == 0) {
                if(count < asc[i]) {
                    count++;
                } else {
                    perm[j] = sz + 1 - i;
                    break;
                }
            }
        }
    }
    for(int i = 0; i <= sz; i++) {
        if(perm[i] == 0) {
            perm[i] = 1;
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
                    desc[perm[i] - 2]++;
                }
            }
        }
    }
    return desc;
}

vector<int> descent_to_permutation(vector<int> desc) {
    int sz = desc.size();
    vector<int> perm(sz + 1, 0);
    for(int i = sz - 1; i >= 0; i--) {
        int count = 0;
        for(int j = sz; j >= 0; j--) {
            if(perm[j] == 0) {
                if(count < desc[i]) {
                    count++;
                } else {
                    perm[j] = i + 2;
                    break;
                }
            }
        }
    }
    for(int i = 0; i <= sz; i++) {
        if(perm[i] == 0) {
            perm[i] = 1;
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
        sjt[i - 2] = (temp % 2 == 1)? (left[i - 2]): (right[i - 2]);
    }
    return sjt;
}

vector<int> sjt_to_permutation(vector<int> sjt) {
    int sz = sjt.size();
    vector<int> dir(sz, 0);
    vector<int> perm(sz + 1, 0);
    for(int i = 1; i < sz; i++) {
        int temp = (i % 2 == 1)? (sjt[i - 1]): (sjt[i - 1] + sjt[i - 2]);
        dir[i] = (temp % 2 == 1)? 1: 0;
    }
    for(int i = sz - 1; i >= 0; i--) {
        int count = 0;
        if(dir[i] == 0) {
            for(int j = sz; j >= 0; j--) {
                if(perm[j] == 0) {
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
                if(perm[j] == 0) {
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
    for(int i = 0; i <= sz; i++) {
        if(perm[i] == 0) {
            perm[i] = 1;
        }
    }
    return perm;
}

bool sjt_next_permutation_by_def(vector<int> &perm, vector<int> &dir) {
    int sz = perm.size();
    int ind = -1;
    int maxmob = 0;
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
        int temp1 = perm[ind];
        int temp2 = dir[ind];
        perm[ind] = perm[ind + temp2];
        perm[ind + temp2] = temp1;
        dir[ind] = dir[ind + temp2];
        dir[ind + temp2] = temp2;
        for(int i = 0; i < sz; i++) {
            if(perm[i] > maxmob) {
                dir[i] = -dir[i];
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

void recursive_generate_permutation(vector<int> &array, int start, int end, int &count) {
    if(start == end) {
        count++;
    } else {
        recursive_generate_permutation(array, start + 1, end, count);
        for(int i = start + 1; i <= end; i++) {
            int temp = array[i];
            array[i] = array[start];
            array[start] = temp;
            recursive_generate_permutation(array, start + 1, end, count);
            array[start] = array[i];
            array[i] = temp;
        }
    }
}

void heap_generate_permutation(vector<int> &array, int n, int &count) {
    if(n == 1) {
        count++;
    } else {
        for(int i = 0; i < n - 1; i++) {
            heap_generate_permutation(array, n - 1, count);
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
        heap_generate_permutation(array, n - 1, count);
    }
}

result recursive_generate_permutation_all(int n) {
    clock_t start, finish;
    int count = 0;
    vector<int> array(n, 0);
    for(int i = 0; i < n; i++) {
        array[i] = i + 1;
    }
    start = clock();
    recursive_generate_permutation(array, 0, n - 1, count);
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result heap_generate_permutation_all(int n) {
    clock_t start, finish;
    int count = 0;
    vector<int> array(n, 0);
    for(int i = 0; i < n; i++) {
        array[i] = i + 1;
    }
    start = clock();
    heap_generate_permutation(array, n, count);
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result lexic_generate_permutation_by_def(int n) {
    clock_t start, finish;
    int count = 1;
    vector<int> perm(n, 0);
    for(int i = 0; i < n; i++) {
        perm[i] = i + 1;
    }
    start = clock();
    while(lexic_next_permutation_by_def(perm)) {
        count++;
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result lexic_generate_permutation_by_tran(int n) {
    clock_t start, finish;
    int count = 1;
    vector<int> iter(n - 1, 0);
    vector<int> perm = lexic_to_permutation(iter);
    vector<int> one = ten2ascent(1, n);
    vector<int> nextiter(n - 1, 0);
    start = clock();
    while(ascent_plus(iter, one, nextiter, n)) {
        count++;
        iter = nextiter;
        perm = lexic_to_permutation(iter);
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result ascent_generate_permutation(int n) {
    clock_t start, finish;
    int count = 1;
    vector<int> iter(n - 1, 0);
    vector<int> perm = ascent_to_permutation(iter);
    vector<int> one = ten2ascent(1, n);
    vector<int> nextiter(n - 1, 0);
    start = clock();
    while(ascent_plus(iter, one, nextiter, n)) {
        count++;
        iter = nextiter;
        perm = ascent_to_permutation(iter);
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result descent_generate_permutation(int n) {
    clock_t start, finish;
    int count = 1;
    vector<int> iter(n - 1, 0);
    vector<int> perm = descent_to_permutation(iter);
    vector<int> one = ten2descent(1, n);
    vector<int> nextiter(n - 1, 0);
    start = clock();
    while(descent_plus(iter, one, nextiter, n)) {
        count++;
        iter = nextiter;
        perm = descent_to_permutation(iter);
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result sjt_generate_permutation_by_def(int n) {
    clock_t start, finish;
    int count = 1;
    vector<int> perm(n);
    vector<int> dir(n);
    for(int i = 0; i < n; i++) {
        perm[i] = i + 1;
        dir[i] = -1;
    }
    start = clock();
    while(sjt_next_permutation_by_def(perm, dir)) {
        count++;
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

result sjt_generate_permutation_by_tran(int n) {
    clock_t start, finish;
    int count = 1;
    vector<int> iter(n - 1, 0);
    vector<int> perm = sjt_to_permutation(iter);
    vector<int> one = ten2descent(1, n);
    vector<int> nextiter(n - 1, 0);
    start = clock();
    while(descent_plus(iter, one, nextiter, n)) {
        count++;
        iter = nextiter;
        perm = sjt_to_permutation(iter);
    }
    finish = clock();
    result res;
    res.cc = count;
    res.tt = (double)(finish - start) / CLOCKS_PER_SEC;
    return res;
}

void method_select(int method_number, int length) {
    result res;
    switch(method_number) {
        case 1:
            res = recursive_generate_permutation_all(length);
            cout << "Method Recursive:" << endl;
            cout << "Total permutations: " << res.cc << endl;
            cout << "Time consuming(s): " << res.tt << endl;
            break;
        case 2:
            res = heap_generate_permutation_all(length);
            cout << "Method Heap: " << endl;
            cout << "Total permutations: " << res.cc << endl;
            cout << "Time consuming(s): " << res.tt << endl;
            break;
        case 3:
            res = lexic_generate_permutation_by_def(length);
            cout << "Method Lexicographical(definition): " << endl;
            cout << "Total permutations: " << res.cc << endl;
            cout << "Time consuming(s): " << res.tt << endl;
            break;
        case 4:
            res = lexic_generate_permutation_by_tran(length);
            cout << "Method Lexicographical(medium): " << endl;
            cout << "Total permutations: " << res.cc << endl;
            cout << "Time consuming(s): " << res.tt << endl;
            break;
        case 5:
            res = ascent_generate_permutation(length);
            cout << "Method Ascent: " << endl;
            cout << "Total permutations: " << res.cc << endl;
            cout << "Time consuming(s): " << res.tt << endl;
            break;
        case 6:
            res = descent_generate_permutation(length);
            cout << "Method Descent: " << endl;
            cout << "Total permutations: " << res.cc << endl;
            cout << "Time consuming(s): " << res.tt << endl;
            break;
        case 7:
            res = sjt_generate_permutation_by_def(length);
            cout << "Method SJT(definition): " << endl;
            cout << "Total permutations: " << res.cc << endl;
            cout << "Time consuming(s): " << res.tt << endl;
            break;
        case 8:
            res = sjt_generate_permutation_by_tran(length);
            cout << "Method SJT(medium): " << endl;
            cout << "Total permutations: " << res.cc << endl;
            cout << "Time consuming(s): " << res.tt << endl;
            break;
    }
}
