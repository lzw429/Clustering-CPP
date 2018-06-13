#include <iostream>
#include <fstream>

using namespace std;

int main() {
    char inFileName[255] = "KMeansInput.txt";
    char outFileName[255] = "KMeansOutput.txt";
    cout << "Input file name: (default \"KMeansInput.txt\")";
    cin >> inFileName;
    cout << "Output file name: (default \"KMeansOutput.txt\")";
    cin >> outFileName;
    ifstream ifs(inFileName);
    ofstream ofs(outFileName);
    if (!ifs) {
        cout << "[Error] cannot open the file " << inFileName << " ." << endl;
        return 0;
    }
    return 0;
}