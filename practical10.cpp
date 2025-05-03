#include <iostream>
#include <vector>
using namespace std;

// Swap function
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Max-Heapify
void maxHeapify(vector<int> &arr, int n, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// Min-Heapify
void minHeapify(vector<int> &arr, int n, int i) {
    int smallest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// Build Max-Heap
void buildMaxHeap(vector<int> &arr, int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

// Build Min-Heap
void buildMinHeap(vector<int> &arr, int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    vector<int> marks(n);
    cout << "Enter marks obtained in DSAL:\n";
    for (int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ": ";
        cin >> marks[i];
    }

    // Copy marks for separate heaps
    vector<int> maxHeap = marks;
    vector<int> minHeap = marks;

    // Build heaps
    buildMaxHeap(maxHeap, n);
    buildMinHeap(minHeap, n);

    // Top of heaps is max/min
    cout << "\nMaximum Marks: " << maxHeap[0];
    cout << "\nMinimum Marks: " << minHeap[0] << endl;

    return 0;
}
