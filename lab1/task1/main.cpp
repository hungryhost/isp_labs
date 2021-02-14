#include <iostream>
#include <vector>
#include <bits/stdc++.h>

std::vector<int> init_and_fill_vector(int size) {
   // initialize and fill the vector for the task 1
   std::vector<int> vect(size, 0);
   std::vector<int>::iterator i;
   for(i=vect.begin();i!=vect.end();i+=1){
        *i = rand() % 1000;
   }
   for(i=vect.begin();i!=vect.end();i+=2){
        *i = rand() % 1000 - 1500;
    }
   std::cout << "The elements of vector are:\n";
   // Print the values in the vector
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine e(seed);
   std::shuffle(vect.begin(), vect.end(), e);
   for(i=vect.begin();i!=vect.end();i++)
        std::cout<<*i<<" ";

   return vect;
}

std::vector<int> find_first_third_positive(std::vector<int> initial_vector){
    // result 2d vector with ndexes of first three posititve
    // numbers. The last one is the one we're looking for.
    std::vector<int> result_vector;
    std::vector<int>::iterator i = initial_vector.begin();
    // counter for the positive numbers
    int count = 0;

    while(i != initial_vector.end() && count < 3) {
        if (*i > 0) {
            result_vector.push_back(i-initial_vector.begin());
            ++i;
            count++;
        }
        else ++i;
    }
    return result_vector;


}

int get_third_element_index(std::vector<int> input_vector){
    std::vector<int> result = find_first_third_positive(input_vector);
    if (result.size() < 3){
        return -1;
    }
    return result.back();
}

void task1(bool bad){
    std::vector<int> myvect;
    if (bad == true) {
        myvect = {-1, -1, -333, -49, -1, -4, -129, -121, -11, -12,
                 -11, -11, -333, -491, -11, -4, -129, -121, -11, -12,
                 -21, -11, -3313, -439, -112, -4, -129, -121, -11, -12,
                 -1, -1, -3333, -149, -18, -48, -1299, -1421, -121, -11};
    }
    else {
        myvect = init_and_fill_vector(40);
    }
    int result = get_third_element_index(myvect);
    if (result == -1) {
        std::cout << '\n' << "Result of task 1: Array does not have 3 positive numbers"
                  << std::endl;
    }
    else{
        std::cout << '\n' << "Result of task 1: " << result << std::endl;
    }
}
int main()
{
    task1(false);
    task1(true);
    return 0;
}


