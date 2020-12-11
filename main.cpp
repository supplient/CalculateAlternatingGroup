#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef vector<int> Cycle;
typedef vector<Cycle> Permutation;

ostream& operator<<(ostream& out, const Cycle& cycle) {
    out << "(";
    for(int i=0; i<cycle.size(); i++) {
        out << cycle[i]+1;
        if(i != cycle.size()-1)
            out << " ";
    }
    out << ")";
    return out;
}

ostream& operator<<(ostream& out, const Permutation& perm) {
    if(perm.size() == 0)
        out << "e";
    for(auto& cycle: perm)
        out << cycle;
    return out;
}

Permutation getCompressedPerm(const vector<int>& p) {
    int n = p.size();
    Permutation res;
    vector<bool> mark(n, false);
    for(int i=0; i<n; i++) {
        if(mark[i])
            continue;

        Cycle cycle;
        int now = i;
        while(!mark[now]) {
            mark[now] = true;
            cycle.push_back(now);

            now = p[now];
        }
        if(cycle.size() > 1)
            res.push_back(cycle);
    }
    return res;
}

Permutation getPerm(const vector<int>& p) {
    Permutation perm(0);

    vector<int> pos2bucket(p.size());
    vector<int> bucket2pos(p.size());
    for(int i=0; i<p.size(); i++) {
        pos2bucket[i] = i;
        bucket2pos[i] = i;
    }

    for(int i=0; i<p.size(); i++) {
        if(pos2bucket[i]==p[i])
            continue;

        // swap bucket pos2bucket[i] and p[i]
        {
            int bi = pos2bucket[i];
            int bj = p[i];
            int pi = i;
            int pj = bucket2pos[bj];

            pos2bucket[pi] = bj;
            pos2bucket[pj] = bi;
            bucket2pos[bi] = pj;
            bucket2pos[bj] = pi;

            perm.push_back({pi, pj});
        }
    }

    return perm;
}

vector<Permutation> getEvenPerms(int n) {
    vector<int> p(n);
    for(int i=0; i<n; i++)
        p[i] = i;

    vector<Permutation> evenPerms;
    do {
        auto perm = getPerm(p);
        if(perm.size() % 2 == 0)
            evenPerms.push_back(getCompressedPerm(p));
    } while(next_permutation(p.begin(), p.end()));

    return evenPerms;
}

int main() {
    int n;

    cin >> n;

    auto evenPerms = getEvenPerms(n);

    cout << "Total " << evenPerms.size() << ":" << endl;
    for(const auto& perm: evenPerms)
        cout << perm << endl;

    cout << endl;

    return 0;
}