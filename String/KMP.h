#include <string>
#include <vector>
using namespace std;

int KMP(string s, string p){
    // 预处理next数组
    int n = s.size();
    int m = p.size();
    vector<int> next(m, 0);
    int j = 0;
    for(int i = 1; i < m; ++i){
        while(j > 0 && p[i] != p[j])
            j = next[j - 1];
        if(p[i] == p[j])
            j++;
        next[i] = j;  
    }

    // 匹配过程
    j = 0;
    for(int i = 0; i < n; ++i){
        while(j > 0 && s[i] != p[j])
            j = next[j - 1];
        if(s[i] == p[j])
            j++;
        if(j == m)  return i - j + 1;
    }
    return -1;
}