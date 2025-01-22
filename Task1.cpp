#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void createRandomNumbers(int count, const string &fileName)
{
    ofstream outputFile(fileName);
    if (!outputFile)
    {
        cout << "Error: Unable to create the file!" << endl;
        return;
    }
    srand(time(0));
    for (int i = 0; i < count; ++i)
    {
        int randomValue = rand() % 100000 + 1;
        outputFile << randomValue << endl;
    }
    outputFile.close();
    cout << "Generated " << count << " random integers and saved to " << fileName << endl;
}

int main()
{
    int totalNumbers;
    cout << "Enter the number of random integers to generate (e.g., 100, 1000, etc.): ";
    cin >> totalNumbers;
    string outputFileName = "random_numbers.txt";
    createRandomNumbers(totalNumbers, outputFileName);
    return 0;
}
