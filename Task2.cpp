#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

void createRandomFile(int count, const string &fileName)
{
    ofstream file(fileName);
    if (!file)
    {
        cout << "Error: Unable to create file!" << endl;
        return;
    }
    srand(time(0));
    for (int i = 0; i < count; ++i)
    {
        int randomValue = rand() % 100000 + 1;
        file << randomValue << endl;
    }
    file.close();
    cout << "Generated " << count << " random integers and saved to " << fileName << endl;
}

void sortUsingInsertion(vector<int> &data)
{
    int size = data.size();
    for (int i = 1; i < size; ++i)
    {
        int current = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > current)
        {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = current;
    }
}

vector<int> loadFromFile(const string &fileName)
{
    ifstream file(fileName);
    vector<int> values;
    int number;

    if (!file)
    {
        cout << "Error: Unable to open file " << fileName << endl;
        return values;
    }
    while (file >> number)
    {
        values.push_back(number);
    }
    file.close();
    return values;
}

void saveToFile(const string &fileName, const vector<int> &data)
{
    ofstream file(fileName);
    if (!file)
    {
        cout << "Error: Unable to create file " << fileName << endl;
        return;
    }
    for (int number : data)
    {
        file << number << endl;
    }
    file.close();
}

int main()
{
    int numberOfValues;
    cout << "Enter the number of random integers to generate and sort (e.g., 100, 1000, etc.): ";
    cin >> numberOfValues;

    string inputFileName = "random_input.txt";
    string outputFileName = "sorted_output.txt";

    createRandomFile(numberOfValues, inputFileName);

    vector<int> data = loadFromFile(inputFileName);
    if (data.empty())
    {
        cout << "Error: No data to sort. Exiting..." << endl;
        return 1;
    }
    cout << "Loaded " << data.size() << " integers from " << inputFileName << endl;

    auto startTime = high_resolution_clock::now();
    sortUsingInsertion(data);
    auto endTime = high_resolution_clock::now();

    auto elapsedTime = duration_cast<milliseconds>(endTime - startTime).count();
    cout << "Sorting completed using insertion sort in " << elapsedTime << " ms." << endl;

    saveToFile(outputFileName, data);
    cout << "Sorted integers saved to " << outputFileName << endl;

    ofstream timingFile("timing_log.csv", ios::app);
    if (!timingFile)
    {
        cout << "Error: Unable to open timing_log.csv!" << endl;
        return 1;
    }
    timingFile << numberOfValues << "," << elapsedTime << endl;
    timingFile.close();
    cout << "Timing result saved to timing_log.csv." << endl;

    return 0;
}
