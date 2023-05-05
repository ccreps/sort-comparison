// sortComparison.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include<math.h>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

//implementing the insertion sort function based heavily off of zybook Figure 4.5.1
void insertionSort(std::vector<int>& numbers) {
    int i,j,temp = 0;

    for (i = 1; i < numbers.size(); ++i) {
        j = i;
        while (j > 0 && numbers[j] < numbers[j - 1]) {
            temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            --j;
        }
    }
}

//implementing the bucket sort function based heavily off of zybook figure 4.15.1
void bucketSort(std::vector<int>& numbers, int numBuckets) {

    int maxValue = numbers[0];
    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] > maxValue) {
            maxValue = numbers[i];
        }
    }

    int nestedBucketSize = (maxValue + 1) / numBuckets;

    vector<vector<int>> buckets(numBuckets);
    for (vector<int> bucket : buckets) {
        bucket.resize(nestedBucketSize);
    }

    for (int number : numbers) {
        int index = floor(number * numBuckets / (maxValue + 1));
        buckets[index].push_back(number);
    }

    for (vector<int> &bucket : buckets) {
        insertionSort(bucket);
    }
    
    numbers.clear();

    for (int j = 0; j < buckets.size(); j++) {
        for (int k = 0; k < buckets[j].size(); k++) {
            numbers.push_back(buckets[j][k]);
        }
    }
}

//taken from zybook Figure 4.16.1
int RadixGetLength(int value){
    if (value == 0)
        return 1;

    int digits = 0;
    while (value != 0) {
        digits += 1;
        value = value / 10;
    }
    return digits;
}

//taken from zybook Figure 4.16.1
int RadixGetMaxLength(vector<int> vect, int vectSize) {
    int maxDigits = 0;
    for (int i = 0; i < vectSize; i++) {
        int digitCount = RadixGetLength(vect.at(i));
            if (digitCount > maxDigits) {
                maxDigits = digitCount;
            }
    }
    return maxDigits;
}

//implementing the radix sort function based heavily off zybook Participation Activity 4.16.6
void radixSort(std::vector<int>& numbers) {
    vector<vector<int>> buckets(10);

    int maxDigits = RadixGetMaxLength(numbers, numbers.size());
    
    int pow10 = 1;
    for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
        for (int i = 0; i < numbers.size(); i++) {
            int bucketIndex = abs(numbers.at(i) / pow10) % 10;
            buckets[bucketIndex].push_back(numbers.at(i));
        }
        int vectIndex = 0;
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < buckets[j].size(); k++) {
                numbers.at(vectIndex++) = buckets[j][k];
            }
        }
        pow10 = 10 * pow10;
        for (int i = 0; i < 10; i++) {
            buckets.at(i).clear();
        }
    }
}

int main() {
    srand(time(NULL));
    vector<int> randomVector1 (10000), randomVector2(10000), randomVector3(10000);

    generate(randomVector1.begin(), randomVector1.end(), rand);

    for (auto value : randomVector1)
        randomVector2.push_back(value);

    for (auto value : randomVector1)
        randomVector3.push_back(value);

    auto insertionStart = high_resolution_clock::now();
    insertionSort(randomVector1);
    auto insertionStop = high_resolution_clock::now();
    auto insertionDuration = duration_cast<milliseconds>(insertionStop - insertionStart); 

    auto bucketStart = high_resolution_clock::now();
    bucketSort(randomVector2, randomVector2.size());
    auto bucketStop = high_resolution_clock::now();
    auto bucketDuration = duration_cast<milliseconds>(bucketStop - bucketStart);

    auto radixStart = high_resolution_clock::now();
    radixSort(randomVector3);
    auto radixStop = high_resolution_clock::now();
    auto radixDuration = duration_cast<milliseconds>(radixStop - radixStart);

    cout << "Insertion Sort runtime was: " << insertionDuration.count() << " milliseconds." << endl;
    cout << "Bucket Sort runtime was: " << bucketDuration.count() << " milliseconds." << endl;
    cout << "Radix Sort runtime was:  " << radixDuration.count() << " milliseconds." << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
