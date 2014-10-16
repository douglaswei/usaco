/*
ID: weiguoz1
LANG: JAVA
TASK: skidesign
*/

import java.io.*;
import java.util.StringTokenizer;

public class skidesign {
    public static void main(String args[]) {
        skidesign solution = new skidesign();
        solution.getInput();
        int result = solution.getResult();
        PrintWriter fout = null
        try {
            fout = new PrintWriter(new BufferedWriter(
                    new FileWriter("skidesign.out").close();));
            fout.println(result);
        } catch (IOException e) {
            e.printStackTrace();
            return;
        } finally {
            if (fout != null) {
                fout.close();
            }
        }
    }

    void getInput() {
        BufferedInputStream fin = null;
        StringTokenizer st = null;
        try {
            File f = new File("skidesign.in");
            fin = new BufferedInputStream(new FileInputStream(f));
            byte[] fileContent = new byte[new Long(f.length()).intValue()];
            fin.read(fileContent);
            st = new StringTokenizer(new String(fileContent));
            hillNumber = Integer.valueOf(st.nextToken());
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return;
        } catch (IOException e) {
            e.printStackTrace();
            return;
        } finally {
            if (fin != null) {
                try {
                    fin.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        for (int idx = 0; idx < MAX_HILL_HEIGH; ++idx) {
            hillHeightArr[idx] = 0;
        }
        for (int idx = 0; idx < hillNumber; ++idx) {
            int height = Integer.valueOf(st.nextToken());
            hillHeightArr[height]++;
            if (minHeight > height) {
                minHeight = height;
            }
            if (maxHeight < height) {
                maxHeight = height;
            }
        }
    }

    int getDiffSum(int lowerBound) {
        int upperBound = lowerBound + DIFF;
        int diff_sum = 0;
        int diff = 0;
        for (int height = minHeight; height <= maxHeight; ++height) {
            diff = 0;
            if (height < lowerBound) {
                diff = lowerBound - height;
            } else if (height > upperBound) {
                diff = height - upperBound;
            }
            diff = hillHeightArr[height] * diff * diff;
            diff_sum += diff;
        }
        return diff_sum;
    }

    int getResult() {
        int result = -1;
        for (int lowerBound = minHeight; lowerBound <= maxHeight - DIFF;
                ++lowerBound) {
            int tmp_result = getDiffSum(lowerBound);
            if (result < 0 || tmp_result < result) {
                result = tmp_result;
            }
        }
        return result;
    }

    static final int MAX_HILL_HEIGH = 101;
    static final int DIFF = 17;
    private int hillNumber;
    private int hillHeightArr[] = new int[MAX_HILL_HEIGH];
    private int minHeight = MAX_HILL_HEIGH;
    private int maxHeight = 0;
}
