#include <functional>
#include <iostream>
#include <utility> // std::swap

// 函数别名用于简化函数指针的表达
using ValidateFuctionRaw = bool (*)(int, int);

// 使用 std::function 的方式
using ValidateFunction = std::function<bool(int, int)>;

// 注意用户自定义比较函数位于第三个参数
void selectionSort(int* array, int size, ValidateFuctionRaw comparisonFcn) {
  // 遍历数组中的每一个元素
  for (int startIndex{0}; startIndex < (size - 1); ++startIndex) {
    // 最小/大数值的索引
    int bestIndex{startIndex};

    // 查询数组中剩下元素的最小/大值
    for (int currentIndex{startIndex + 1}; currentIndex < size; ++currentIndex) {
      // 如果当前元素小于/大于之前找到的元素（由 startIndex + 1 开始）
      if (comparisonFcn(array[bestIndex], array[currentIndex])) // 比较在这里完成
      {
        // 本次遍历中最新的最小/大值
        bestIndex = currentIndex;
      }
    }

    // 交换起始元素与最小/大的元素
    std::swap(array[startIndex], array[bestIndex]);
  }
}

// 升序的比较函数
bool ascending(int x, int y) { return x > y; }

// 降序的比较函数
bool descending(int x, int y) { return x < y; }

// 用于打印元素
void printArray(int* array, int size) {
  for (int index{0}; index < size; ++index) {
    std::cout << array[index] << ' ';
  }

  std::cout << '\n';
}

int main() {
  int array[9]{3, 7, 9, 5, 6, 1, 8, 2, 4};

  // 根据 descending() 进行降序排序
  selectionSort(array, 9, descending);
  printArray(array, 9);

  // 根据 ascending() 进行升序排序
  selectionSort(array, 9, ascending);
  printArray(array, 9);

  return 0;
}
