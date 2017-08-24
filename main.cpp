// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php.

#include <iostream>
#include "src/Sketch.h"

using namespace std;

int main() {
    auto sketch = new Sketch(10,10);

    string s1 = "abcd";
    string s2 = "efgh";
    string s3 = "ijkl";
    string s4 = "mnop";

    auto h1 = sketch->get_hash((uint8_t *) s1.c_str(), s1.size() );
    sketch->increment(h1);
    auto h2 = sketch->get_hash((uint8_t *) s2.c_str(), s2.size() );
    sketch->increment(h2);
    sketch->increment(h2);
    sketch->increment(h2);

    cout << s1 << " " << sketch->query(h1) << endl;
    cout << s2 << " " << sketch->query(h2) << endl;


    delete sketch;
    return 0;
}