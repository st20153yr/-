#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void PrintRod(int n, int price[]) {
    for(int i=0; i<=n; i++) {
        cout << right << setw(3) << i;
    }
    cout << endl;
    for(int i=0; i<=n; i++) {
        cout << right << setw(3) << price[i];
    }
    cout << endl;
}
void BottomUpCutRod(int n, int price[], int length[]) {
    int r[n+1], tmp;
    r[0] = 0;

    for(int i=1; i<n+1; i++) {
        tmp = 0;
        for(int j=1; j<=i; j++) {
            tmp = max({tmp, price[j]+r[i-j]});
        }
        r[i] = tmp;
    }
    
    PrintRod(n, r);
}

int main() {
    int n;
    cout << "ロッドの長さ: ";
    cin >> n;

    int length[n+1];
    int price[n+1];
    
    length[0] = 0;
    price[0] = 0;
    cout << "価格を入力してください" << endl;
    for(int i=1; i<n+1; i++) {
        cout << i << "個目: ";
        length[i] = i;
        cin >> price[i];
    }

    BottomUpCutRod(n, price, length);
    return 0;
}