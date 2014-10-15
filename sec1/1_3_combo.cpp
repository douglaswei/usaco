/*
ID: weiguoz1
PROB: combo
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

const int PASSWD_LEN = 3;

int main() {
    std::ofstream fout ("combo.out");
    std::ifstream fin ("combo.in");
    int circle_number = 0;
    int passwd_farmer[PASSWD_LEN];
    int passwd_master[PASSWD_LEN];
    
    fin >> circle_number;
    for (int passwd_index = 0; passwd_index < PASSWD_LEN; ++passwd_index) {
        fin >> passwd_farmer[passwd_index];
    }
    for (int passwd_index = 0; passwd_index < PASSWD_LEN; ++passwd_index) {
        fin >> passwd_master[passwd_index];
    }

    int valid_number = 5;

    if (circle_number < valid_number) {
        valid_number = circle_number;
    }

    int result = valid_number * valid_number * valid_number * 2;

    // compute cross number
    int cross_number = 1;
    for (int passwd_idx = 0; passwd_idx < PASSWD_LEN; ++passwd_idx) {
        int pwd_farmer = passwd_farmer[passwd_idx];
        int pwd_master = passwd_master[passwd_idx];
        int cur_cross = pwd_farmer - pwd_master;
        if (cur_cross < 0) {
            cur_cross = -cur_cross;
        }
        
        if (circle_number - cur_cross < cur_cross) {
            cur_cross = circle_number - cur_cross;
        }
        // now cur_cross is the smaller plus distance
        cur_cross = valid_number - cur_cross;
        if (valid_number < 5) {
            cur_cross = valid_number;
        }
        if (cur_cross < 0) {
            cross_number = 0;
            break;
        }
        cross_number = cross_number * cur_cross;
    }
    result = result - cross_number;

    fout << result << std::endl;

    return 0;
}

