#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
class Task2 {

    public:

    int count_zeroes_in_matrix(std::vector<std::vector<int>> &mat){
        int z_count = 0;
        std::vector<std::vector<int>>::iterator row;
        for (row = mat.begin(); row != mat.end(); row++) {
            z_count = z_count + count(row->begin(), row->end(), 0);
        }
        return z_count;

    }
    void multiply_rows_by_number_of_zeroes(std::vector<std::vector<int>> &mat){
        int N = mat.size();
        int count = 0;
        int new_val;
        int zeroes = count_zeroes_in_matrix(mat);
        std::vector<std::vector<int> >::iterator row;
        std::vector<int>::iterator col;
        for (row = mat.begin(); row != mat.end(); row++) {
            for (col = row->begin(); col != row->end(); col++) {
                if (*col < 0){
                    new_val = *col/zeroes;
                    replace(row->begin(), row->end(), *col, new_val);
                }

            }
        }
    }

    void solve_sort(int sj, std::vector<std::vector<int>> &mat){
       // method for sorting
        int n = mat.size();
        int k = sj;
        std::vector<int> temp;
        int l;
        for(int j = k+1; j < n; j++){
            temp.push_back(mat[k][j]);

        }
        sort(temp.begin(), temp.end(),  std::greater<int>());
        l = 0;
        for(int j = k+1; j < n; j++){
            mat[k][j] = temp[l];
            //temp.push_back(mat[k][j]);
            l++;
        }

    }


    std::vector<std::vector<int>> diagonalSort(std::vector<std::vector<int>>& mat) {
          int n = mat.size();

          for(int j = 0; j < n; j++){
            solve_sort(j, mat);
          }
          return mat;
       }

    void printElement(std::vector<std::vector<int>>& arr)
       {

           // Traverse the 2D vector
           for (int i = 0; i < arr.size(); i++) {
               for (int j = 0; j < arr[0].size(); j++) {
                   std::cout << arr[i][j] << ' ';
               }
               std::cout << std::endl;
           }
       }
};

int main()
{
    std::vector<std::vector<int>> v = {{3,-32,22,21},{2,10,0,9},{-28,2,-8,0},{4,5,-31,-8}};
    Task2 task2;
    task2.printElement(v);
     std::cout << std::endl;
    std::vector<std::vector<int>> res = task2.diagonalSort(v);
     std::cout << std::endl;
    task2.printElement(res);
     std::cout << std::endl;
    int i = task2.count_zeroes_in_matrix(res);


    std::cout << "Number of zeroes: " << i << ' ' << std::endl;
    task2.multiply_rows_by_number_of_zeroes(res);
    task2.printElement(res);
    return 0;
}


