#include <bits/stdc++.h>

using namespace std;

const int BLOCK_SIZE = 600;
const int QUERY_BUFFER = 600;
const int MOD = 998244353;

int Add(int&a, int b) {
    a += b;
    a -= a >= MOD ? MOD : 0;
    a += a < 0 ? MOD : 0;
    return a;
}

bool flag = false;
int Mul(int a, int b) { return 1ll * a * b % MOD; }

struct Block {
    long long sum;
    int sum2;
    int firstColor, lastColor;
    vector<long long> elements;

    Block() { sum = sum2 = 0; }

    int size() { return elements.size(); }

    void simplify() {
        vector<long long> newElements;
        int last = -1;
        int curColor = firstColor;
        for (int i = 0; i < elements.size(); ++i) {
            if (elements[i]) {
                if (last == -1) firstColor = curColor;
                if (last % 2 == i % 2 && last != -1) {
                    newElements.back() += elements[i]; 
                }
                else newElements.push_back(elements[i]);
                last = i;
            }
            curColor ^= 1;
        }
        sum2 = 0;
        sum = 0;
        swap(newElements, elements);
        curColor = firstColor;
        for (auto x : elements) {
                int xx = x % MOD;
                Add(sum2, Mul(xx, xx));
                sum += x;
                curColor ^= 1;
        }
        lastColor = curColor ^ 1;
    }

    void addBall(int color, long long position, long long amount) {
        // cerr << "add " << color << " " << position << " " << amount << '\n';
        if (elements.empty()) firstColor = color ^ 1;
        int pos = elements.size();
        int curColor = firstColor ^ 1;
        for (int i = 0; i < elements.size(); ++i) {
            curColor ^= 1;
            if (elements[i] < position) {
                position -= elements[i];
                continue;
            }
            if (curColor == color) {
                elements[i] += amount;
                simplify();
                return;
            }
            pos = i;
            break;
        }
        elements.push_back(0);
        elements.push_back(0);
        for (int i = elements.size() - 1; i > pos + 2; --i) {
            elements[i] = elements[i - 2];
        }
        if (pos + 2 < elements.size()) elements[pos + 2] = elements[pos] - position;
        elements[pos + 1] = amount;
        elements[pos] = position;
        simplify();
    }

    void removeBall(long long position, long long amount) {
        if (amount == sum) {
            elements.clear();
            sum = sum2 = 0;
            return;
        }
        int pos = elements.size();
        int curColor = firstColor ^ 1;
        for (int i = 0; i < elements.size(); ++i) {
            curColor ^= 1;
            if (elements[i] < position) {
                position -= elements[i];
                continue;
            }
            long long thisAmount = min(amount, elements[i] - position);
            elements[i] -= thisAmount;
            position = 0;
            amount -= thisAmount;
            if (amount == 0) break;
        }
        simplify();
    }

    void flipBall(long long position, long long amount) {
        if (amount == sum) {
            firstColor ^= 1;
            lastColor ^= 1;
            return;
        }
        int pos = elements.size();
        int curColor = firstColor ^ 1;
        vector<pair<int, long long>> needToInsert;

        for (int i = 0; i < elements.size(); ++i) {
            curColor ^= 1;
            if (elements[i] < position) {
                position -= elements[i];
                continue;
            }
            if (amount <= elements[i] - position) {
                needToInsert.push_back({i + 1, amount});
                needToInsert.push_back({i + 1, elements[i] - position - amount}); 
                elements[i] = position;
            
            } else {
                long long thisAmount = elements[i] - position;
                amount -= thisAmount;
                elements[i] = position;
                needToInsert.push_back({i + 1, thisAmount});
                for (int j = i + 1; j < elements.size(); ++j) {
                    if (elements[j] >= amount) {
                        needToInsert.push_back({j + 1, elements[j] - amount});
                        elements[j] = amount;
                        break;
                    }
                    amount -= elements[j];
                }
            }    
            break;
        }
        while (needToInsert.size()) {
            auto x = needToInsert.back();
            elements.insert(elements.begin() + x.first, x.second);
            needToInsert.pop_back();
        }
        simplify();
    }

    int query(long long position, long long amount) {
        if (amount == sum) return sum2;
        int res = 0;
        for (int i = 0; i < elements.size(); ++i) {
            if (elements[i] < position) {
                position -= elements[i];
                continue;
            }
            long long thisAmount = min(amount, elements[i] - position);
            int t = thisAmount % MOD;
            // if (flag) cerr << position << ' ' << amount << ' ' << thisAmount << '\n';
            Add(res, Mul(t, t));
            position = 0;
            amount -= thisAmount;
            if (amount == 0) break;
        }
        return res;
    }

    void print() {
        cerr << "First color: " << firstColor << ";Last color: " << lastColor << "; Sum: " << sum << "; SumSquare: " << sum2 << "\n";
        for (auto element : elements) cerr << element << " "; cerr << '\n';
    }
};

vector<Block> blocks;

void Print() {
    int i = 0;
    for (auto& block : blocks) {
        cerr << "Block " << ++i << ":\n";
        block.print();
    }
}
void Build() {
    vector<Block> newBlocks;
    newBlocks.push_back(Block());
    newBlocks[0].firstColor = blocks[0].firstColor;
    long long pos = 0;
    for (auto& block : blocks) {
        int currentColor = block.firstColor;
        for (auto element : block.elements) {
            if (newBlocks.back().size() == BLOCK_SIZE) { newBlocks.push_back(Block()); newBlocks.back().firstColor = currentColor; pos = 0; }
            newBlocks.back().elements.push_back(element);
            currentColor ^= 1;
        }
    }
    swap(newBlocks, blocks);
    for (auto& block: blocks) block.simplify();
}

void Simplify() {
    int n = blocks.size();
    int j = 0;
    for (int i = 0; i < n; ++i) 
        if (blocks[i].sum != 0) {
            swap(blocks[j], blocks[i]);
            ++j;
        }
    n = j;
    blocks.resize(n);
    for (int i = 1; i < n; ++i) {
        if (blocks[i].firstColor == blocks[i - 1].lastColor) {
            blocks[i].addBall(blocks[i - 1].lastColor, 0, blocks[i - 1].elements.back());
            blocks[i - 1].elements.pop_back();
            blocks[i - 1].simplify();
        }
    }
    if (blocks.empty()) blocks.push_back(Block());
}

void AddBall(int color, long long position, long long amount) {
    // cerr << "There are " << blocks.size() << " blocks\n";
    // cerr << "Add color " << color << " at " << position << " with " << amount << " elements\n";
    for (auto& block : blocks) {
        // cerr << "Block " << block.sum << ' ' << position << '\n';
        if (block.sum < position) {
            position -= block.sum;
            continue;
        }
        // do something with this block
        block.addBall(color, position, amount);
        break;
    }
    Simplify();
}

void RemoveBall(long long position, long long amount) {    
    // cerr << "Remove at " << position << " with " << amount << " elements\n";
    for (auto& block : blocks) {
        if (block.sum < position) {
            position -= block.sum;
            continue;
        }
        // do something with this block
        long long thisAmount = min(amount, block.sum - position);
        block.removeBall(position, thisAmount);
        position = 0;
        amount -= thisAmount;
        if (amount == 0) break;
    }
    Simplify();
}

void FlipBall(long long position, long long amount) {
    // cerr << "Flip at " << position << " with " << amount << " elements\n";
    for (auto& block : blocks) {
        if (block.sum < position) {
            position -= block.sum;
            continue;
        }
        // do something with this block
        long long thisAmount = min(amount, block.sum - position);
        block.flipBall(position, thisAmount);
        position = 0;
        amount -= thisAmount;
        if (amount == 0) break;
    }
    Simplify();
}

int Query(long long position, long long amount) {
    int ans = 0;
    for (auto& block : blocks) {
        if (block.sum < position) {
            position -= block.sum;
            continue;
        }
        // do something with this block
        long long thisAmount = min(amount, block.sum - position);
        // if (flag) {
        //     block.print();
        //     cerr << "This ans " << block.query(position, thisAmount) << '\n';
        // }
        Add(ans, block.query(position, thisAmount));
        position = 0;
        amount -= thisAmount;
        if (amount == 0) break;
    }
    return ans;
}


int main() {
    // freopen("input.txt","r",stdin);
    double stime = clock();
    
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    string st;
    cin >> st;
    int cnt = 1;
    st = st + '~';
    blocks.push_back(Block());
    blocks[0].firstColor = st[0] == 'B';
    for (int i = 1; i <= n; ++i) {
        if (st[i] != st[i - 1]) {
            blocks[0].elements.push_back(cnt);
            cnt = 1;
        } else ++cnt;
    }
    int nq = 0;
    for (int i = 0; i < q; ++i) {
        // Print();
        if (i % QUERY_BUFFER == 0) Build();
        // else Simplify();
        char type;
        long long x, k;
        cin >> type >> x >> k;
        --x;
        if (type == 'I') {
            char c; cin >> c;
            AddBall(c == 'B', x + 1, k);
        } else if (type == 'D') {
            RemoveBall(x, k);
        } else if (type == 'F') {
            FlipBall(x, k);
        } else {
            // type == Q
            // ++nq;
            // if (nq == 46) {
            //     cerr << "X = " << x << " K = " << k << '\n';
            //     flag = true;
            // } else flag = false;
            cout << Query(x, k) << '\n';
        }
    }

    cerr << "Time " << (clock() - stime) / CLOCKS_PER_SEC * 1000 << "ms.\n";
}