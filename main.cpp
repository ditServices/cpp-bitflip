#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

int main() {
    char block[2048];
    char flipped[2048];

    FILE *f = fopen("/dev/sdb", "rb+");
    if(f == NULL) {
        cout << "Error opening the external drive." << endl;
        return 0;
    }

    fseek(f, 0x1BE, SEEK_SET);

    fread(block, 1, sizeof(block), f);

    for(int x=0; x<sizeof(block); x++) {
        printf("%.2X  ", block[x]);
        flipped[x] = ~block[x];
    }
    cout << endl;
    cout << "FLIPPED" << endl;

    for(int x=0; x<sizeof(flipped); x++) {
        printf("%.2X  ", flipped[x]);
    }

    fseek(f, 0x1BE, SEEK_SET);
    fwrite(flipped, 1, sizeof(flipped), f);

    fclose(f);
    return 0;
}
