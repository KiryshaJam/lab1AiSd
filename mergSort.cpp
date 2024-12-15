void merge(int arr[], int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;

    // Создаем временные массивы для левой и правой частей
    int leftArr[len1], rightArr[len2];

    // Копируем данные в временные массивы leftArr и rightArr
    for (int i = 0; i < len1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    // Объединяем временные массивы обратно в arr[left...right]
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы leftArr, если есть
    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы rightArr, если есть
    while (j < len2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}
