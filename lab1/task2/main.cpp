#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
#include <numeric>

class Task2 {


private:
    struct location {
        int x;
        int y;
    };
    int find_max_in_matr(std::vector<std::vector<int> >& indexes)
    {
        int temp = 0;
        location l;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 1; j++) {

                if (temp < indexes[i][j]) {
                    temp = indexes[i][j];
                    l.x = i;
                    l.y = j;
                }
            }
        }

        return l.x;
    }
    int find_min_in_column(const std::vector<int>& col)
    {
        int minElement = *std::min_element(col.begin(), col.end());
        return minElement;
    }
    std::vector<int> extract_column(int col_n, const std::vector<std::vector<int> >& mat)
    {
        int i = col_n;
        int n = mat.size();
        std::vector<int> extracted_column;
        if (i > n) {
            std::cout << "No such row";
            std::exit(EXIT_FAILURE);
        }

        for (int j = 0; j < n; j++) {
            extracted_column.push_back(mat[j][i]);
        }
        return extracted_column;
    }
    void solve_sort(int sj, std::vector<std::vector<int> >& mat)
    {
        // method for sorting
        int n = mat[0].size();
        int k = sj;
        std::vector<int> temp;
        int l;
        for (int j = k + 1; j < n; j++) {
            temp.push_back(mat[k][j]);
        }
        sort(temp.begin(), temp.end(), std::greater<int>());
        l = 0;
        for (int j = k + 1; j < n; j++) {
            mat[k][j] = temp[l];
            //temp.push_back(mat[k][j]);
            l++;
        }
    }
    std::vector<int> find_zeros_in_row(std::vector<int>& row)
    {
        std::vector<int>::iterator row_i;

        std::vector<int> indexes;
        std::vector<int> max_index;
        for (row_i = row.begin(); row_i != row.end(); row_i++) {
            if (*row_i == 0) {
                indexes.push_back(distance(row.begin(), row_i));
            }
        }
        if (indexes.size() == 0) {
            max_index.push_back(-1);
        }
        else {
            int max = *std::max_element(indexes.begin(), indexes.end());
            max_index.push_back(max);
        }

        return max_index;
    }
    std::vector<std::vector<int> > find_zeros(std::vector<std::vector<int> >& mat)
    {
        std::vector<std::vector<int> >::iterator row;
        std::vector<std::vector<int> > res;
        std::vector<int>::iterator col;
        std::vector<std::vector<int> > indexes;
        int n = mat[0].size();
        for (int i = 0; i < n; i++) {
            res.push_back(find_zeros_in_row(mat[i]));
        }
        //std::cout << "len of indexes: "<<"(" << res.size() << ")";
        return res;
    }
    int find_sum_of_column(std::vector<int>& column){
        int sum_of_elems = std::accumulate(column.begin(), column.end(), 0);
        return sum_of_elems;
    }
    std::vector<int> get_vector_of_col_summs(std::vector<std::vector<int> >& mat){
        int len = mat.size();
        std::vector<int> summs;
        std::vector<int> col;
        int summ = 0;
        for (int i =0; i<len; i++){
            col = extract_column(i, mat);
            summ = find_sum_of_column(col);
            summs.push_back(summ);
        }
        return summs;
    }
    int get_col_with_min_summ( std::vector<int> summs){
        int minElementIndex = std::min_element(summs.begin(),summs.end()) - summs.begin();

        return minElementIndex;
    }
    void change_row_with_min_summ(std::vector<int>& row, int col){
        // we change the row by removing the element for the specific column
        row.erase(row.begin()+col);
    }
    int count_zeroes_in_matrix(std::vector<std::vector<int> >& mat)
    {
        int z_count = 0;
        std::vector<std::vector<int> >::iterator row;
        for (row = mat.begin(); row != mat.end(); row++) {
            z_count = z_count + count(row->begin(), row->end(), 0);
        }
        return z_count;
    }
    std::vector<int> extract_values_between(int a, int b, std::vector<int>& col)
    {
        std::vector<int>::iterator i;
        std::vector<int> result;
        for (i = col.begin(); i != col.end(); i += 1) {
            if (*i >= a && *i <= b) {
                result.push_back(*i);
                // std::cout << "value " << *i << std::endl;
            }
        }
        return result;
    }



public:
    void multiply_rows_by_number_of_zeroes(std::vector<std::vector<int> >& mat)
    {
        int N = mat.size();
        int count = 0;
        int new_val;
        int zeroes = count_zeroes_in_matrix(mat);
        std::vector<std::vector<int> >::iterator row;
        std::vector<int>::iterator col;
        for (row = mat.begin(); row != mat.end(); row++) {
            for (col = row->begin(); col != row->end(); col++) {
                if (*col < 0) {
                    new_val = *col / zeroes;
                    replace(row->begin(), row->end(), *col, new_val);
                }
            }
        }
    }

    void add_row(int col, int a, int b, std::vector<std::vector<int> >& mat)
    {
        int len = mat[0].size();
        std::vector<int> extracted_col = extract_column(col, mat);
        std::vector<int> values = extract_values_between(a, b, extracted_col);
        std::vector<int> new_row;
        int min_value = find_min_in_column(values);
        // std::cout << "value " << min_value << std::endl;
        for (int i = 0; i < len; i++) {
            new_row.push_back(min_value);
        }
        mat.push_back(new_row);
    }


    void solve_remove_col(std::vector<std::vector<int>> &mat){
        std::vector<int> summs = get_vector_of_col_summs(mat);
        std::vector<std::vector<int>> res;
        int col = get_col_with_min_summ(summs);
        for (int i = 0; i < mat.size(); i++){
            change_row_with_min_summ(mat[i], col);
        }
    }


    std::vector<std::vector<int> > solve_remove_with_max_zero(std::vector<std::vector<int> >& mat)
    {
        std::vector<std::vector<int> > v1 = find_zeros(mat);

        std::vector<std::vector<int> > res;
        int row = find_max_in_matr(v1);

        if (row == mat.size()-1){
            std::vector<std::vector<int> >::iterator it = mat.begin() + row;
            copy(mat.begin(), it, back_inserter(res));
        }
        else if (row == 0){
             std::vector<std::vector<int> >::iterator it1 = mat.begin() + 1;
             copy(it1, mat.end(), back_inserter(res));
        }
        else{

            std::vector<std::vector<int> >::iterator it1 = mat.begin() + row;
            std::vector<std::vector<int> >::iterator it2 = it1 + 1;
            copy(mat.begin(), it1, back_inserter(res));
            res.insert(res.end(), it2, mat.end());
        }
        return res;
    }

    std::vector<std::vector<int> > sort_after_md(std::vector<std::vector<int> >& mat)
    {
        int n = mat[0].size();

        for (int j = 0; j < n; j++) {
            solve_sort(j, mat);
        }
        return mat;
    }

    void printElement(const std::vector<std::vector<int> >& arr)
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
    std::vector<std::vector<int> > v = { { 3, -32, 22, 1 }, { 2, 0, -8, -6 },
                                         { -28, 2, -8, -10 }, { 4, 5, -31, 1 } };
    Task2 task2;
    task2.printElement(v);
    std::cout << std::endl;
    std::vector<std::vector<int> > res = task2.sort_after_md(v);
    std::cout << std::endl;
    task2.printElement(res);
    std::cout << std::endl;
    task2.multiply_rows_by_number_of_zeroes(res);
    task2.printElement(res);
    std::cout << std::endl;
    //task2.add_row(2, -20, 20, res);
    task2.printElement(res);
    std::cout << std::endl;
    std::vector<std::vector<int> > v1 = task2.solve_remove_with_max_zero(res);
    std::cout << std::endl;
    task2.printElement(v1);
    std::cout << std::endl;
    task2.solve_remove_col(v);
     std::cout << std::endl;
     task2.printElement(v);
    return 0;
}
