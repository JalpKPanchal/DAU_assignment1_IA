#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

void mergeHelper(vector<int> &numbers, int leftIndex, int rightIndex)
{
    if (leftIndex >= rightIndex)
        return;
    int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
    mergeHelper(numbers, leftIndex, middleIndex);
    mergeHelper(numbers, middleIndex + 1, rightIndex);

    vector<int> merged;
    int i = leftIndex, j = middleIndex + 1;
    while (i <= middleIndex && j <= rightIndex)
    {
        if (numbers[i] <= numbers[j])
        {
            merged.push_back(numbers[i++]);
        }
        else
        {
            merged.push_back(numbers[j++]);
        }
    }
    while (i <= middleIndex)
        merged.push_back(numbers[i++]);
    while (j <= rightIndex)
        merged.push_back(numbers[j++]);

    for (int k = 0; k < merged.size(); ++k)
    {
        numbers[leftIndex + k] = merged[k];
    }
}

void sortWithMerge(vector<int> &numbers)
{
    mergeHelper(numbers, 0, numbers.size() - 1);
}

void createFileWithRandoms(int totalNumbers, const string &filename)
{
    ofstream outputFile(filename);
    if (outputFile)
    {
        srand(time(0));
        for (int i = 0; i < totalNumbers; ++i)
        {
            outputFile << (rand() % 100000 + 1) << endl;
        }
        outputFile.close();
        cout << "Generated " << totalNumbers << " random integers in file " << filename << endl;
    }
    else
    {
        cout << "Error creating file: " << filename << endl;
    }
}

vector<int> loadNumbers(const string &filename)
{
    ifstream inputFile(filename);
    vector<int> numbers;
    int number;
    if (inputFile)
    {
        while (inputFile >> number)
        {
            numbers.push_back(number);
        }
        inputFile.close();
    }
    else
    {
        cout << "Error opening file: " << filename << endl;
    }
    return numbers;
}

void saveNumbers(const string &filename, const vector<int> &numbers)
{
    ofstream outputFile(filename);
    if (outputFile)
    {
        for (const int &number : numbers)
        {
            outputFile << number << endl;
        }
        outputFile.close();
    }
    else
    {
        cout << "Error creating file: " << filename << endl;
    }
}

int main()
{
    int count;
    cout << "Enter the number of random integers to generate and sort: ";
    cin >> count;

    string randomNumbersFile = "random_numbers_data.txt";
    string sortedNumbersFile = "sorted_numbers_data.txt";

    createFileWithRandoms(count, randomNumbersFile);
    vector<int> data = loadNumbers(randomNumbersFile);
    if (!data.empty())
    {
        cout << "Loaded " << data.size() << " integers from file " << randomNumbersFile << endl;

        auto start = high_resolution_clock::now();
        sortWithMerge(data);
        auto end = high_resolution_clock::now();

        long long duration = duration_cast<milliseconds>(end - start).count();
        cout << "Sorting completed in " << duration << " ms." << endl;

        saveNumbers(sortedNumbersFile, data);
        cout << "Sorted data saved in file " << sortedNumbersFile << endl;

        ofstream timingLog("merge_sort_timings.csv", ios::app);
        if (timingLog)
        {
            timingLog << count << "," << duration << endl;
            timingLog.close();
            cout << "Timing data saved in file merge_sort_timings.csv." << endl;
        }
        else
        {
            cout << "Error creating timing log file." << endl;
        }
    }

    return 0;
}
