#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class LinearClassifier
{
public:

    vector<double> sigmo(const vector<double> &a) 
    {
        vector<double> result(a.size(), 0);

        for (int i = 0; i < a.size(); ++i) 
        {
            result[i] = (1 / (1 + exp(a[i])));
        }

        return result;
    }

    vector<double> multi(const vector<vector <double>> &a, const vector<double> &b) 
    {
        double row = a.size();
        double col = a[0].size();
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
    LinearClassifier p = LinearClassifier();

    vector<double> input = {0.4, 0.2, 0.6, 0.5};
    
    vector<vector<double>> weight1 = 
    {
        {0.2, 0.6, 0.5, 0.3},
        {0.1, 0.8, 0.7, 0.2},
        {0.5, 0.3, 0.9, 0.7},
        {0.4, 0.6, 0.1, 0.8},
        {0.7, 0.9, 0.5, 0.6},
        {0.6, 0.3, 0.7, 0.2}
    };
    
    vector<vector<double>> weight2 = 
    {
        {0.6, 0.3, 0.7, 0.4, 0.2, 0.5},
        {0.7, 0.5, 0.8, 0.1, 0.9, 0.4},
        {0.3, 0.6, 0.2, 0.7, 0.8, 0.3},
        {0.4, 0.9, 0.5, 0.2, 0.1, 0.7},
        {0.5, 0.7, 0.8, 0.6, 0.5, 0.2}
    };

    vector<vector<double>> weight3 = 
    {
        {0.7, 0.6, 0.1, 0.5, 0.4},
        {0.8, 0.2, 0.3, 0.9, 0.1},
        {0.4, 0.9, 0.7, 0.5, 0.2}
    };

    input = p.sigmo(p.multi(weight1, input));
    input = p.sigmo(p.multi(weight2, input));
    input = p.sigmo(p.multi(weight3, input));
    
    cout << "[\n";
    for (double val : input) 
    {
        cout << "[" << val << "]" << endl;
    }
    cout << "]";

    system("pause");
}