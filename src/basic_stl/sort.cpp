#include<bits/stdc++.h>

// 合并两个有序数组
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; ++i) {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// 归并排序的递归实现
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}




// 分区函数
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// 快速排序的递归实现
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main() 
{
    std::vector<int> nums1 = {12, 11, 13, 5, 6, 7};
    std::cout << "Before merge sort: " << std::endl;
    for (auto& n : nums1)
        std::cout << n << " ";
    std::cout << std::endl;
    mergeSort(nums1, 0, nums1.size() - 1);
    std::cout << "After merge sort: " << std::endl;
    for (auto& n : nums1)
        std::cout << n << " ";
    std::cout << std::endl;

    std::vector<int> nums2 = {10, 7, 8, 9, 1, 5};
    std::cout << "Before quick sort: " << std::endl;
    for (auto& n : nums2)
        std::cout << n << " ";
    std::cout << std::endl;
    quickSort(nums2, 0, nums2.size() - 1);
    std::cout << "After quick sort: " << std::endl;
    for (auto& n : nums2)
        std::cout << n << " ";
    std::cout << std::endl;

    std::vector<int> tmp(nums2.size());
    // std::function<void(std::vector<int>&, int, int)> mergeSort2 = [&](std::vector<int>& num, int l, int r) -> void {
    auto mergeSort2 = [&](auto&&mergeSort2, std::vector<int>& num, int l, int r) -> void {
        if (l >= r)
            return;
        int mid = l + (r - l) / 2;
        mergeSort2(mergeSort2, num, l, mid);
        mergeSort2(mergeSort2, num, mid + 1, r);
        int i = l, j = mid + 1, k = 0;
        while (i <= mid && j <= r) {
            if (num[i] <= num[j]) 
                tmp[k++] = num[i++];
            else
                tmp[k++] = num[j++];
        }
        while (i <= mid)
            tmp[k++] = num[i++];
        while (j <= r)
            tmp[k++] = num[j++];
        
        for (int st = l, cp = 0; st <= r; st++, cp++)
            num[st] = tmp[cp];
    };
    std::cout << "Before merge sort2: " << std::endl;
    std::vector<int> nums3 = {1, 70, 18, 49, 1, 5};
    for (auto& n : nums3)
        std::cout << n << " ";
    std::cout << std::endl;
    mergeSort2(mergeSort2, nums3, 0, nums3.size() - 1);
    std::cout << "After merge sort2: " << std::endl;
    for (auto& n : nums3)
        std::cout << n << " ";
    std::cout << std::endl;

    std::function<void(std::vector<int>&, int, int)> quickSort2 = [&](std::vector<int>& num, int l, int r) -> void {
        if (l >= r)
            return;
        int i = l - 1, j = r + 1;
        int mid = num[(l + (r - l) / 2)];
        while (i < j) {
            // do i++; while (num[i] < mid);
            // do j--; while (num[j] > mid);
            while (num[++i] < mid);
            while (num[--j] > mid);
            if (i < j)
                std::swap(num[i], num[j]);
        }
        quickSort2(num, l, j);
        quickSort2(num, j + 1, r);
    };

    std::vector<int> nums4 = {10, 701, 108, 49, 11, 5};
    std::cout << "Before quick sort2: " << std::endl;
    for (auto& n : nums4)
        std::cout << n << " ";
    std::cout << std::endl;
    quickSort2(nums4, 0, nums4.size() - 1);
    std::cout << "After quick sort2: " << std::endl;
    for (auto& n : nums4)
        std::cout << n << " ";
    std::cout << std::endl;

    std::vector<int> nums5 = {11, 3, 7, 5, 9, 1};
    std::cout << "Before quick choose: " << std::endl;
    for (auto& n : nums5)
        std::cout << n << " ";
    std::cout << std::endl;
    std::function<int(std::vector<int>&, int, int, int)> quickSort3 = [&](std::vector<int>& num, int l, int r, int k) -> int {
        if (l >= r)
            return num[l];
            // return num[k];
        int i = l - 1, j = r + 1;
        int mid = num[(l + (r - l) / 2)];
        while (i < j) {
            do i++; while (num[i] < mid);
            do j--; while (num[j] > mid);
            // while (num[++i] < mid);
            // while (num[--j] > mid);
            if (i < j)
                std::swap(num[i], num[j]);
        }
        if (k <= j - l + 1)
            return quickSort3(num, l, j, k);
        else
            return quickSort3(num, j + 1, r, k - j + l - 1);
            // return quickSort3(num, j + 1, r, k);
    };
    int k = 6;
    int res = quickSort3(nums5, 0, nums5.size() - 1, k);
    std::cout << "After quick choose, " << k << "th num is: " << res << std::endl;

    return 0;
}
