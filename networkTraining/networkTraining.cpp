#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

vector<double> operator-(const vector<double> &v1, const vector<double> &v2) 
{
    vector<double> res(v1.size());
    
    for(size_t i = 0; i < v1.size(); i++)
    {
        res[i] = v1[i] - v2[i];
    }
    return res;
}

vector<double> operator*(const vector<double> &v1, const vector<double> &v2) 
{
    vector<double> res(v1.size());
    
    for(size_t i = 0; i < v1.size(); i++)
    {
        res[i] = v1[i] * v2[i];
    }
    return res;
}

vector<double> operator*(double v1, const vector<double> &v2) 
{
    vector<double> res(v2.size());
    
    for(size_t i = 0; i < v2.size(); i++)
    {
        res[i] = v1 * v2[i];
    }
    return res;
}

vector<double> operator-(double v1, const vector<double> &v2) 
{
    vector<double> res(v2.size());
    
    for(size_t i = 0; i < v2.size(); i++)
    {
        res[i] = v1 - v2[i];
    }
    return res;
}

vector<vector <double>> operator+=(vector<vector <double>> &v1, const vector<vector <double>> v2) 
{
    int rows = v1.size();
    int cols = v1[0].size();

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            v1[i][j] += v2[i][j];
        }
    }

    return v1;
}

class neuralNetwork
{
private:

// Values of the weights

vector<vector<double>> weight12 = 
    {
        {0.3, 0.8, 0.7, 0.2},
        {0.6, 0.9, 0.1, 0.4},
        {0.4, 0.5, 0.6, 0.9},
        {0.8, 0.2, 0.3, 0.7},
        {0.5, 0.7, 0.8, 0.1}
    };
    
    vector<vector<double>> weight23 = 
    {
        {0.7, 0.3, 0.5, 0.4, 0.9}, 
        {0.5, 0.2, 0.8, 0.3, 0.1}, 
        {0.8, 0.6, 0.3, 0.5, 0.2}, 
        {0.3, 0.7, 0.4, 0.1, 0.9},
        {0.4, 0.8, 0.6, 0.2, 0.7},
        {0.9, 0.4, 0.2, 0.6, 0.1}
    };

    vector<vector<double>> weight34 = 
    {
        {0.5, 0.2, 0.7, 0.1, 0.8, 0.4}, 
        {0.7, 0.3, 0.8, 0.9, 0.1, 0.6}, 
        {0.4, 0.5, 0.2, 0.7, 0.9, 0.3}
    };

    double learningRate;

public:
    neuralNetwork(double lr = 1): learningRate(lr){} 

//  Matrix transpose

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

//  External vector multiplication
    
    vector<vector <double>> multimatr(const vector<double> &v1, const vector <double> &v2) 
    {
        int rows = v1.size();
        int cols = v2.size();

        vector<vector <double>> res(rows, vector <double>(cols));

        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                res[i][j] = v1[i] * v2[j];
            }
        }

        return res;
    }

//  Obtaining the sigmoid of a function

    vector<double> sigmo(const vector<double> &a) 
    {
        vector<double> result(a.size(), 0);

        for (int i = 0; i < a.size(); ++i) 
        {
            result[i] = (1 / (1 + exp(- a[i])));
        }

        return result;
    }

//  Multiplying a matrix with a vector

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

//  Signal transmission

    vector<double> query(const vector<double> &inp) 
    {
        vector<double> output1 = inp;

        vector<double> output2 = sigmo(multi(weight12, output1));
        vector<double> output3 = sigmo(multi(weight23, output2));
        vector<double> output4 = sigmo(multi(weight34, output3));

        return output4;
    }

//  Operator overloading

    friend vector<double> operator-(const vector<double> &v1, const vector<double> &v2);
    friend vector<double> operator-(double v1, const vector<double> &v2);
    friend vector<double> operator*(const vector<double> &v1, const vector<double> &v2);
    friend vector<double> operator*(double v1, const vector<double> &v2);
    friend vector<vector <double>> operator+=(const vector<vector <double>> &v1, const vector<vector <double>> &v2);
    
    

//  Neural network training

    void train(const vector<double> &inp, const vector<double> &tar) 
    {
        vector<double> output1 = inp;

        vector<double> output2 = sigmo(multi(weight12, output1));
        vector<double> output3 = sigmo(multi(weight23, output2));
        vector<double> output4 = sigmo(multi(weight34, output3));

        cout << "Output neural network signals before learn: [" ; 
        for (size_t i = 0; i < output4.size(); ++i) 
        {
            cout << output4[i];
            if (i != output4.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
        
        vector<double> e4 = tar - output4;
        vector<double> e3 = multi(trans(weight34), e4);
        vector<double> e2 = multi(trans(weight23), e3);

        weight12 += multimatr(learningRate * e2 * output2 * (1 - output2), output1);
        weight23 += multimatr(learningRate * e3 * output3 * (1 - output3), output2);
        weight34 += multimatr(learningRate * e4 * output4 * (1 - output4), output3);

        output1 = inp;
        
        output2 = sigmo(multi(weight12, output1));
        output3 = sigmo(multi(weight23, output2));
        output4 = sigmo(multi(weight34, output3));

        cout << "Output neural network signals after learn: [" ; 
        for (size_t i = 0; i < output4.size(); ++i) 
        {
            cout << output4[i];
            if (i != output4.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }


};



int main() 
{
    neuralNetwork n = neuralNetwork(1.5);

    vector<double> inp = {0.6, 0.2, 0.7, 0.4};
    vector<double> tar = {0.1, 0.9, 0.5};

    for (int i = 1; i < 40; i++)
    {
        n.train(inp, tar);
    }
    
    system("pause");
}