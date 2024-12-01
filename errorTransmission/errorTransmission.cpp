#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class neuralNetwork
{
public:

    vector<vector <double>> trans(const vector<vector <double>> &a) 
    {
        int rows = a.size();
        int cols = a[0].size();
        vector<vector <double>> transed(cols, vector <double>(rows));

        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                transed[j][i] = a[i][j];
            }
        }

        return transed;
    }

    vector<double> sigmo(const vector<double> &a) 
    {
        vector<double> result(a.size(), 0);

        for (int i = 0; i < a.size(); ++i) 
        {
            result[i] = (1 / (1 + exp(- a[i])));
        }

        return result;
    }

    vector<double> multi(const vector<vector <double>> &a, const vector<double> &b) 
    {
        int row = a.size();
        int col = a[0].size();
        vector<double> result(row, 0);

        for (int i = 0; i < row; ++i) 
        {
            for (int j = 0; j < col; ++j) 
            {
                result[i] += a[i][j] * b[j];
            }
        }

        return result;
    }

};

int main()
{
    neuralNetwork p = neuralNetwork();

    vector<double> output = {0.2, 0.5, 0.3};

    vector<double> trueVal = {0.6, 0.2, 0.4};
    
    vector<vector<double>> weight1 = 
    {
        {0.3, 0.7, 0.4, 0.2, 0.1, 0.8},
        {0.9, 0.1, 0.6, 0.5, 0.2, 0.7},
        {0.2, 0.3, 0.8, 0.4, 0.3, 0.5},
        {0.7, 0.6, 0.9, 0.1, 0.8, 0.6},
        {0.1, 0.5, 0.4, 0.3, 0.7, 0.5}
    };
    
    vector<vector<double>> weight2 = 
    {
        {0.5, 0.3, 0.2, 0.7, 0.9},
        {0.7, 0.1, 0.8, 0.2, 0.6},
        {0.3, 0.8, 0.7, 0.1, 0.5},
        {0.9, 0.2, 0.6, 0.7, 0.3}
    };

    vector<vector<double>> weight3 = 
    {
        {0.4, 0.1, 0.6, 0.7},
        {0.3, 0.5, 0.8, 0.9},
        {0.6, 0.4, 0.1, 0.2}
    };

    vector<double> temp_err(output.size());
    
    for (int i = 0; i < output.size(); i++) 
    {
        temp_err[i] = trueVal[i] - output[i];
    }

    temp_err = p.multi(p.trans(weight3), temp_err);
    temp_err = p.multi(p.trans(weight2), temp_err);
    temp_err = p.multi(p.trans(weight1), temp_err);

    vector<double> err = temp_err;
    
    cout << "[";
    for (size_t i = 0; i < err.size(); ++i) 
    {
        cout << err[i];
        if (i != err.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    system("pause");
}