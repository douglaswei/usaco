/*
ID: weiguoz1
PROB: wormhole
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

const int MAX_WHOLE_NUMBER = 12;

int whole_number = 0;
int whole_pos[MAX_WHOLE_NUMBER][2];
int whole_mask[MAX_WHOLE_NUMBER];
int whole_conc[MAX_WHOLE_NUMBER];
int whole_next[MAX_WHOLE_NUMBER];

int modify(int pos, int beg_num) {
    // 1. if pos in conc[idx] (idx < pos), just set it
    for (int idx = 0; idx < pos; ++idx) {
        if (whole_conc[idx] == pos) {
            whole_conc[pos] = idx;
            whole_conc[idx] = pos;
            return 0;
        }
    }

    // 2. just increace it locally
    for (int value = beg_num; value < whole_number; ++value) {
        if (value == pos) {
            continue;
        }
        if (value == whole_conc[whole_conc[value]]
                && (value < pos || whole_conc[value] < pos)) {
            continue;
        }
        whole_conc[pos] = value;
        whole_conc[value] = pos;
        break;
    }
    return 0;
}

int adjust() {
    // 1. find the first place need to modify
    // start from the end of the list
    int pos = whole_number - 1;
    while (pos >= 0) {
        int valid = 0;
        int valid_pos = whole_conc[pos] + 0;
        while (valid_pos < whole_number) {
            if (whole_conc[valid_pos] > pos) {
                break;
            }
            ++valid_pos;
        }
        if (whole_conc[pos] < pos
                || whole_conc[pos] >= whole_number - 1
                || valid_pos == whole_number) {
            pos --;
            continue;
        }
        break;
    }
    if (pos < 0) {
        return -1;
    }

    int mod_pos = pos;
    // 2. modify the value from data[pos]
    while (mod_pos < whole_number) {
        if (mod_pos == pos) {
            modify(mod_pos, whole_conc[mod_pos] + 1);
        } else {
            modify(mod_pos, 0);
        }
        ++mod_pos;
    }
}

int search_from(int beg) {
    // init mask
    for (int idx = 0; idx < whole_number; ++idx) {
        whole_mask[idx] = 0;// 0 for unused
    }
    
    int cur = beg;
    while (true) {
        // travel through beg to next,
        // then next to conc[next],
        // then set cur to conc[next],
        int next = whole_next[cur];
        if (next == -1) {
            return 1;
        }
        cur = whole_conc[next];
        if (cur == beg) {
            return 0;
        }
    }
}

int find_path() {
    for (int idx = 0; idx < whole_number; ++idx) {
        int res = search_from(idx);
        if (res == 0) {
            printf("search from:[%d]\n", idx);
            return 0;
        }
    }
    return -1;
}

int main() {
    std::ofstream fout ("wormhole.out");
    std::ifstream fin ("wormhole.in");

    int res = 0;

    fin >> whole_number;

    for (int idx = 0; idx < whole_number; ++idx) {
        fin >> whole_pos[idx][0] >> whole_pos[idx][1];
        if (idx % 2 == 0) {
            whole_conc[idx] = idx + 1;
        } else {
            whole_conc[idx] = idx - 1;
        }
    }

    // init next[]
    for (int idx = 0; idx < whole_number; ++idx) {
        int least_dis = -1;
        int next = -1;
        for (int idy = 0; idy < whole_number; ++idy) {
            if (idx == idy) {
                continue;
            }
            if (whole_pos[idx][1] != whole_pos[idy][1]) {
                continue;
            }
            int dis = whole_pos[idy][0] - whole_pos[idx][0];
            if (dis < 0) {
                continue;
            }
            if (least_dis < 0 || least_dis > dis) {
                least_dis = dis;
                next = idy;
            }
        }

        whole_next[idx] = next;
        printf("next[%d] : [%d]\n", idx, next);
    }

    while (true) {
        for (int idx = 0; idx < whole_number; ++idx) {
            printf("%d:[%d] | ", idx, whole_conc[idx]);
        }
        printf("\n");

        if (find_path() == 0) {
            printf("*** find path ***\n");
            res++;
        }

        if (adjust() < 0) {
            break;
        }
    }

    fout << res << std::endl;
}

