//binaryu search is used to find the partition point
//time complexity is O(log(min(m,n)))
//space complexity is O(1)

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {

    // Ensure nums1 is the smaller array
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int m = nums1Size;
    int n = nums2Size;
    int low = 0, high = m;

    while (low <= high) {
        int Px = low + (high - low) / 2;
        int Py = (m + n + 1) / 2 - Px;

        int x1 = (Px == 0) ? INT_MIN : nums1[Px - 1];
        int x2 = (Py == 0) ? INT_MIN : nums2[Py - 1];

        int x3 = (Px == m) ? INT_MAX : nums1[Px];
        int x4 = (Py == n) ? INT_MAX : nums2[Py];

        if (x1 <= x4 && x2 <= x3) {
            if ((m + n) % 2 == 1) {
                return (double)(x1 > x2 ? x1 : x2);
            } else {
                int maxLeft = (x1 > x2) ? x1 : x2;
                int minRight = (x3 < x4) ? x3 : x4;
                return (maxLeft + minRight) / 2.0;
            }
        } else if (x1 > x4) {
            high = Px - 1;
        } else {
            low = Px + 1;
        }
    }

    return -1.0; 
}
