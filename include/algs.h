int partition(long* array, int low, int high) {
    long pivot = array[low];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (array[i] < pivot);
        do {
            j--;
        } while (array[j] > pivot);
        if (i >= j)
            return j;
        std::swap(array[i], array[j]);
    }
}

void quicksort(long* array, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        quicksort(array, low, pivotIndex);
        quicksort(array, pivotIndex + 1, high);
    }
}

void function(long* array, int size) {
    // Example: Bubble sort
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }

    // Linear time algorithm:
    // for(int i = 0; i < size-1; i++){
        // array[i] = 2*array[i] + array[i+1]/276;
    // }

    // Linearithmic time algorithm:
    // quicksort(array, 0, size-1);
}
