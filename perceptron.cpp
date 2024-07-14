#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

template <class T, class S> 
double dot(vector<T> v, vector<S> w){
    /* Dot product of two vectors v and w  */
    double result = 0.0;
    try{
        if (v.size() == w.size())
             for (int i=0; i < (int)(v.size()); ++i )
                result +=  v.at(i) * w.at(i);
            
        else
            throw out_of_range("Vectors must be same size");
    }

    catch(exception& e){
        std::cout << "Input Error: " << e.what() << endl;
    }
    return result;
}

bool checkBinary(vector<int> v){
    for (auto element: v )
        if (element != 0 && element != 1)
            return false;
        
    return true;
}

class Perceptron {
    /*
    A class for representing a Perceptron with multiple binary inputs
    and a single binary output.

    Class Variables:
    - weights: A vector of predefined size whose elements are initially set to
        doubles.
    - bias: A single double valued number
    - size: An integer defining the number of inputs the perceptron takes.  */

    private:
        vector<double> weights;
        vector<int> inputs;
        double bias;
        int size;
        

    public:
        int output;
        double z;

        Perceptron(int size){
        /*  Constructor for Perceptron. Takes as input the number of inputs  */

            for (int i = 0; i < size; ++i)
                this->weights.push_back( 1.0 / size );
            
            this->size = size;
            this->bias = 0.0;
        }

        // Returns input vector
        vector<int> Inputs(){ return this->inputs; }

        // Returns weight vector
        vector<double> Weights(){ return this->weights; }

        // Returns bias 
        double Bias(){ return this->bias; }

        // Returns number of inputs/weights
        double Size(){ return this->size; }

        // Returns most recent output
        int Output(){ return this->output; }

        // Set value of weight at specific index
        void setWeight(int index, double w){
            this->weights.at(index) = w;
            this->z = dot(this->weights, this->inputs) + this->bias;

        }

        //Add to weight at specific index
        void addWeight(int index, double delta){
            setWeight(index, this->weights.at(index) + delta) ;
        }

        // Set value of bias
        void setBias(double b){
            this->bias = b;
            this->z = dot(this->weights, this->inputs) + this->bias;

        }

        //Add to bias
        void addBias(double delta){
            setBias(this->bias + delta) ;
        }

        // Forward Pass
        int forward(vector<int> x){
            try{
                if ( x.size() == this->size && checkBinary(x)){
                    this->inputs = x;
                    this->z = dot(this->weights, x) + this->bias;
                    if (this->z > 0)
                        this->output = 1;
                    else
                        this->output = 0;
                    return this->output;
                }

                else{
                    if (x.size()!= this->size)
                        throw out_of_range("Wrong input size.");
                    else
                        throw invalid_argument("Must be vector of binary digits.");
                }
            }

            catch(const exception& e){
                cout << "Input Exception: " << e.what() << endl;
            }
            return -1;
        }

};


int main(){

    Perceptron p1 = Perceptron(3);
    Perceptron p2 = Perceptron(3);

    vector<int> X = {0,0,1};
    p1.forward(X);
    cout << "Inputs: ";
    for (int in : p1.Inputs())
        cout << in << " ";
    
    p1.addBias(0.5);
    cout << endl << "Bias: " << p1.Bias() << endl << "Weights: ";
    for (double w : p1.Weights())
        cout << w << " ";
    
    cout << endl << "z: " << p1.z;
    cout << endl << "Output: " << p1.Output() << endl;
}
