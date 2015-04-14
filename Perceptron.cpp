#include "Perceptron.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

Perceptron::Perceptron(int epochs, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled)
    : inputLayer(labeled[0].first.size(), Node()),
      outputLayer(labeled[0].second.size(), Node())
{
    srand(time(NULL));

    weights = new double*[inputLayer.size()];
    for (unsigned int i = 0; i < inputLayer.size(); i++)
        weights[i] = new double[outputLayer.size()];

    for (unsigned int i = 0; i < inputLayer.size(); i++) {
        for (unsigned int j = 0; j < outputLayer.size(); j++) {

            // TODO wat code coot ?
            weights[i][j] = 2*(static_cast<double>(rand()) / RAND_MAX); - 1;
        }
    }

    train(epochs, labeled);
}

// NOTE assumes output is correct size
void Perceptron::evaluate(const std::vector<double>& input, std::vector<double>& output)
{
    for (unsigned int i = 0; i < inputLayer.size(); i++)
        // TODO ???
        inputLayer[i].evaluateNode(inputLayer[i]);

    for (unsigned int i = 0; i < outputLayer.size(); i++) {
        std::vector<double> inputs(inputLayer.size(), 0);

        for (unsigned int j = 0; j < inputLayer.size(); j++) {
            inputs[j] = weights[j][i]*inputLayer[j].getOutput();
        }

        output[i] = outputLayer[i].evaluateNode(inputs);
    }
}

void Perceptron::train(int epochs, const std::vector<std::pair<std::vector<double>, std::vector<double>>>& labeled)
{
    for (int i = 0; i < epochs; i++) {
        for (unsigned int j = 0; j < labeled.size(); j++) {
            std::vector<double> output(labeled[j].second.size(), 0);
            evaluate(labeled[j].first, output);

            double error = 0;
            for (unsigned int k = 0; k < output.size(); k++) {
                error += fabs(output[k] - labeled[j].second);
            }

            if (error != 0) {
                for (unsigned int m = 0; m < inputLayer.size(); m++) {
                    for (unsigned int n = 0; n < outputLayer.size(); n++) {
                        // TODO check weight update
                        weights[m][n] += Perceptron::learningRate * error * labeled[j].first[m];
                    }
                }
            }
        }
    }
}
