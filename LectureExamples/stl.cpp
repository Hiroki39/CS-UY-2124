#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main() {
    char bjarne[] = "Bjarne Stroustrup";
    int len = 17;
    sort(bjarne, bjarne + len);  // Uses a half open range [start, stop

    vector<char> vc(bjarne, bjarne + len);
    // list<char> lc(&vc[0], &vc[vc.size()]);
    list<char> lc(vc.begin(),
                  vc.end());  // itialize a linked list based on the vector
    vector<char>::iterator loc =
        find(vc.begin(), vc.end(), 'S');  // return an Iterator!
    list<char>::iterator loc2 = find(lc.begin(), lc.end(), 'Q');
}
