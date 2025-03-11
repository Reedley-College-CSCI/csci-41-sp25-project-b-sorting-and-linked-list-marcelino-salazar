#ifndef SORTTRACKER_H
#define SORTTRACKER_H

#include <iostream>
#include <string>

// SortTrack tracks comparison and swap operations peformed by a sorting
// algorithm
class SortTracker {
private:
   int comparisonCount;
   int swapCount;
   
public:
   SortTracker() {
      comparisonCount = 0;
      swapCount = 0;
   }
   
   int GetComparisonCount() const {
      return comparisonCount;
   }
   
   int GetSwapCount() const {
      return swapCount;
   }
   
   // Returns true if the array element at index 1 is less than the array
   // element at index 2, false otherwise. Increments the comparison count.
   bool IsFirstLTSecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] < array[index2];
   }
   
   // Returns true if element1 is less than element2, false otherwise.
   // Increments the comparison count.
   bool IsLT(int element1, int element2) {
      comparisonCount++;
      return element1 < element2;
   }
   
   // Returns true if the array element at index 1 is less or equal to the
   // array element at index 2, false otherwise. Increments the comparison
   // count.
   bool IsFirstLTESecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] <= array[index2];
   }
   
   // Utility function to print an integer array's contents
   void PrintArray(const int* array, int arrayLength,
      std::ostream& output = std::cout, std::string delimiter = ", ",
      std::string prefix = "", std::string suffix = "") {
      // Print the prefix first
      output << prefix;
      
      // If the array is not empty, print the first element
      if (arrayLength > 0) {
         output << array[0];
      }
      
      // Print each remaining element, preceded by the delimiter
      for (int i = 1; i < arrayLength; i++) {
         output << delimiter << array[i];
      }
      
      // End with the suffix
      output << suffix;
   }
   
   // Swaps array elements at index 1 and index 2. Increments the swap count.
   void Swap(int* array, int index1, int index2) {
      // Increment the swap counter
      swapCount++;
      
      // Swap elements
      int temp = array[index1];
      array[index1] = array[index2];
      array[index2] = temp;
   }
};

#endif