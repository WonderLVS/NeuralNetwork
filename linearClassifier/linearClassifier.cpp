#include <iostream>
using namespace std;

class LinearClassifier
{
public:
    double weight = 0;
    double learnRate = 0;

    double query(double input)
    {
        return weight * input;
    }

    string classify(int width, int weigth, int lenght) 
    {
        if( ( weight * width ) <= lenght ) 
        {
            return " caterpillar";
        } 
        else 
        {
            return " ladybug";
        }
    }

    void train(double width, double length)
    {
        double output = query(width);
        double error = length - output;
        double delta = learnRate * (error / width);
        weight += delta;
    }

    LinearClassifier(double u_weight, double u_learnRate)
    {
        weight = u_weight;
        learnRate = u_learnRate;
    }
};

int main()
{
    double widths[]  { 2, 9, 3, 10, 4, 11, 6,
                        12, 3, 11, 4, 12, 5, 12 };
    double lengths[] {12, 2, 10, 3, 11, 4, 12,
                        5, 8, 2, 9, 2, 10, 3};

    LinearClassifier p = LinearClassifier(0.05, 0.1);
    int sizeInp = size(widths);

    cout << "\nBugs classification before learning: \n" << p.weight << endl;

    for (int i = 0; i < sizeInp; i++)
    {
        cout << "Bug number " << i << " should be: " << p.classify( widths[i], p.weight, lengths[i] ) << endl;
    }

    for (int i = 0; i < sizeInp; i++)
    {
        p.train(widths[i], lengths[i]);
    }

    cout << "\nBugs classification after learning: \n" << p.weight << endl;

    for (int i = 0; i < sizeInp; i++)
    {
        cout << "Bug number " << i << " should be: " << p.classify( widths[i], p.weight, lengths[i] ) << endl;
    }
    
    system("pause");
}