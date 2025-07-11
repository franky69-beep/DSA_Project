#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int MAX_SIZE = 10000;
int originalList[MAX_SIZE], sortedList[MAX_SIZE];
bool dataGenerated = false;
bool isSorted = false;
int lstep = 0, bstep = 0, estep = 0;

void generateRandomNumbers(int arrOriginal[], int arrSorted[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        int val = rand() % 10000;
        arrOriginal[i] = val;
        arrSorted[i] = val;
    }
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int linearSearch(int arr[], int first, int last, int target) {
    for (int i = first; i <= last; i++) {
        lstep++;
        if (arr[i] == target) return i;
    }
    return -1;
}


int binarySearch(int arr[], int first, int last, int target) {
    if (first > last) return -1;
    int mid = (first + last) / 2;
    bstep++;
    if (arr[mid] == target) return mid;
    else if (target < arr[mid]) return binarySearch(arr, first, mid - 1, target);
    else return binarySearch(arr, mid + 1, last, target);
}



int exponentialSearch(int arr[], int size, int target) {
    if (arr[0] == target) {
        estep++;
        return 0;
    }
    int i = 1;
    while (i < size && arr[i] <= target) {
        estep++;
        i *= 2;
    }
    int left = i / 2;
    int right = min(i, size - 1);
    int localStepBefore = bstep;
    int result = binarySearch(arr, left, right, target);
    estep += (bstep - localStepBefore);
    return result;
}

void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";
}







int main() {
    int size;
    int choice, searchValue, index;

    cout << "===== ALGORITHM ANALYZER (FINAL PROJECT) =====\n";

    while (true) {
        cout << "\nChoose Operation:\n";
        cout << "1. Generate Random Numbers\n";
        cout << "2. Quick Sort\n";
        cout << "3. Merge Sort\n";
        cout << "4. Linear Search\n";
        cout << "5. Binary Search\n";
        cout << "6. Exponential Search\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
    cout << "Enter number of elements (max " << MAX_SIZE << "): ";
    cin >> size;
    if (size <= 0 || size > MAX_SIZE) {
        cout << "Invalid size!\n";
        break;
    }

    auto start = high_resolution_clock::now();
    generateRandomNumbers(originalList, sortedList, size);
    auto end = high_resolution_clock::now();

    auto duration_ms = duration_cast<milliseconds>(end - start);

    dataGenerated = true;
    isSorted = false;

    cout << "Random numbers generated in " << duration_ms.count() << " milliseconds.\n";
    cout << "Generated Numbers:\n";
    displayArray(originalList, size);
    break;
}


        case 2: {
            if (!dataGenerated) {
                cout << "Generate data first (Option 1).\n";
                break;
            }

            auto start = high_resolution_clock::now();
            quickSort(sortedList, 0, size - 1);
            auto end = high_resolution_clock::now();

            auto duration_ms = duration_cast<milliseconds>(end - start);
            isSorted = true;

            cout << "Quick Sort completed in " << duration_ms.count() << " milliseconds.\n";
            cout << "Sorted Array:\n";
            displayArray(sortedList, size);
            break;
        }

        case 3: {
            if (!dataGenerated) {
                cout << "Generate data first (Option 1).\n";
                break;
            }

            auto start = high_resolution_clock::now();
            mergeSort(sortedList, 0, size - 1);
            auto end = high_resolution_clock::now();

            auto duration_ms = duration_cast<milliseconds>(end - start);
            isSorted = true;

            cout << "Merge Sort completed in " << duration_ms.count() << " milliseconds.\n";
            cout << "Sorted Array:\n";
            displayArray(sortedList, size);
            break;
        }

        case 4: {
            if (!dataGenerated || !isSorted) {
                cout << "Generate and sort data first (Option 1 + 2/3).\n";
                break;
            }

            cout << "Enter value to search: ";
            cin >> searchValue;
            lstep = 0;

            auto start = high_resolution_clock::now();
            index = linearSearch(sortedList, 0, size - 1, searchValue);
            auto end = high_resolution_clock::now();

            auto duration_ms = duration_cast<milliseconds>(end - start);

            if (index != -1)
                cout << "Linear Search: Found at index " << index;
            else
                cout << "Linear Search: Not found";
            cout << " | Comparisons: " << lstep;
            cout << " | Time: " << duration_ms.count() << " milliseconds\n";
            break;
        }

        case 5: {
            if (!dataGenerated || !isSorted) {
                cout << "Generate and sort data first (Option 1 + 2/3).\n";
                break;
            }

            cout << "Enter value to search: ";
            cin >> searchValue;
            bstep = 0;

            auto start = high_resolution_clock::now();
            index = binarySearch(sortedList, 0, size - 1, searchValue);
            auto end = high_resolution_clock::now();

            auto duration_ms = duration_cast<milliseconds>(end - start);

            if (index != -1)
                cout << "Binary Search: Found at index " << index;
            else
                cout << "Binary Search: Not found";
            cout << " | Comparisons: " << bstep;
            cout << " | Time: " << duration_ms.count() << " milliseconds\n";
            break;
        }

        case 6: {
            if (!dataGenerated || !isSorted) {
                cout << "Generate and sort data first (Option 1 + 2/3).\n";
                break;
            }

            cout << "Enter value to search: ";
            cin >> searchValue;
            bstep = 0;
            estep = 0;

            auto start = high_resolution_clock::now();
            index = exponentialSearch(sortedList, size, searchValue);
            auto end = high_resolution_clock::now();

            auto duration_ms = duration_cast<milliseconds>(end - start);

            if (index != -1)
                cout << "Exponential Search: Found at index " << index;
            else
                cout << "Exponential Search: Not found";
            cout << " | Comparisons: " << estep;
            cout << " | Time: " << duration_ms.count() << " milliseconds\n";
            break;
        }

        case 7:
            cout << "Exiting program.\n";
            return 0;

        default:
            cout << "Invalid option! Try again.\n";
        }
    }

    return 0;
}
