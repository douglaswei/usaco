/*
ID: weiguoz1
PROB: skidesign
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const int MAX_HILL_NUMBER = 1000;
const int MAX_HILL_HEIGHT = 101;
const int DIFF = 17;

int main() {
    std::ofstream fout ("skidesign.out");
    std::ifstream fin ("skidesign.in");

    int hill_number = 0;
    int hill_height_arr[MAX_HILL_HEIGHT];
    int max_height = 0;
    int min_height = MAX_HILL_HEIGHT;

    int res = -1;

    for (int idx = 0; idx < MAX_HILL_HEIGHT; ++idx) {
        hill_height_arr[idx] = 0;
    }

    fin >> hill_number;
    for (int idx = 0; idx < hill_number; ++idx) {
        int height = 0;
        fin >> height;
        hill_height_arr[height] += 1;

        if (height < min_height) {
            min_height = height;
        }
        if (height > max_height) {
            max_height = height;
        }
    }

    for (int idx = 0; idx < MAX_HILL_HEIGHT; ++idx) {
        printf("level:[%d] count[%d]\n", idx, hill_height_arr[idx]);
    }

    for (int lower_bound = min_height; lower_bound <= max_height - DIFF; ++lower_bound) {
        int upper_bound = lower_bound + DIFF;
        int res_try = 0;
        for (int idx = min_height; idx <= max_height ; ++idx) {
            if (hill_height_arr[idx] == 0 || (idx >= lower_bound && idx <= upper_bound)) {
                continue;
            }
            int diff = lower_bound - idx;
            if (diff < 0)  {
                diff = idx - upper_bound;
            }

            res_try += hill_height_arr[idx] * diff * diff;
        }
        printf("lower bound:[%d], upper_bound:[%d] res:[%d]\n", lower_bound, upper_bound, res_try);
        if (res_try < res || res < 0) {
            res = res_try;
        }
    }

    fout << res << std::endl;
    
    return 0;
}

