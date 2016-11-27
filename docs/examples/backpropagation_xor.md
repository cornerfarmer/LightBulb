# Backpropagation xor

*The example is integrated into LightBulbExample and its code can be found in [BackpropagationXor](https://github.com/domin1101/LightBulb/tree/master/example/LightBulbExample/Examples/BackpropagationXor).*

A first basic example how to train a neural network to simulate a xor calculator. To achieve that a simple gradient descent algorithm is used.

## The network

The first thing to do is creating the neural network we want to train:

```cpp
FeedForwardNetworkTopologyOptions networkTopologyOptions;
networkTopologyOptions.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
networkTopologyOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
networkTopologyOptions.neuronsPerLayerCount[0] = 2;
networkTopologyOptions.neuronsPerLayerCount[1] = 3;
networkTopologyOptions.neuronsPerLayerCount[2] = 1;

FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(networkTopologyOptions);

NeuralNetwork network(networkTopology);
```

At first we prepare the configuration of our feed forward network topology. (A network topology manages the structure information of a neural network)
We want to use the same activaton/netInput function for every neuron. So we use the SameNeuronDescriptionFactory with the WeightedSumFunction as net input and the FermiFunction as activation function.
The network should have three layers. The input layer with two, the hidden layer with 3 and the output layer with one neuron.

Now we are ready to create the network topology.
After creating the topology its easy to create the network.

Thats it, now we have our feed forward network and can go on and train it.

## The trainer 

A trainer is necessary for all kind of supervised learning stuff. It tells the learning rule what the network should learn.
In our case that's just all four xor combinations:

```cpp
std::unique_ptr<Teacher> teacher(new Teacher());
for (int i = 0; i < 2; i++)
{
    for (int l = 0; l < 2; l++)
    {
        std::vector<double> teachingPattern(2);
        TeachingInput<bool>* teachingInput = new TeachingInput<bool>(1);

        teachingPattern[0] = i;
        teachingPattern[1] = l;
        (*teachingInput).set(0, (i != l));
        teacher->addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
    }
}
```

Every of these combinations becomes an extra teaching lesson. A teaching lesson consists of a teaching pattern and a teaching input.
The teaching pattern contains the input for the neural network.
The teaching input contains the values the neural network should output.

## The learning rule

The learning rule manages the whole learning process.
For supervised learning we use the GradientDescentLearningRule which consists of two parts:
* The gradient calculation algorithm
* The gradient descent algorithm

The first one calculates the gradient of the neural network (e.q. with Backpropagation) and the second one executes the gradient descent and changes the weights of the network depending on the calculated gradient.

So lets create the gradient calculation algorithm.
```cpp
Backpropagation* backpropagation = new Backpropagation();
```

Now the gradient descent algorithm: Here we use just a very basic version: simple gradient descent with momentum.
```cpp
SimpleGradientDescentOptions simpleGradientDescentOptions;
SimpleGradientDescent* simpleGradientDescent = new SimpleGradientDescent(simpleGradientDescentOptions);
```

After that we can assemble our gradient descent learning rule:
```cpp
GradientDescentLearningRuleOptions options;
options.gradientCalculation = backpropagation;
options.gradientDescentAlgorithm = simpleGradientDescent;
options.neuralNetwork = &network;
GradientDescentLearningRule learningRule(options);
```

## Run it!

Now we are ready to start!
```cpp
std::unique_ptr<AbstractLearningResult> result(learningRule.start());
```

Check the result:
```cpp
if (result->succeeded)
    std::cout << "Learning has been successful" << std::endl;
```

Now lets try our trained network:
```cpp
std::vector<double> input(2);
input[0] = 0;
input[1] = 1;
std::vector<double> output = network.calculate(input);
std::cout << "0 and 1 => " << std::to_string(output[0]) << std::endl;

input[0] = 1;
output = network.calculate(input);
std::cout << "1 and 1 => " <<  std::to_string(output[0]) << std::endl;
```

When running the program, the output should now look like:
```
Learning has been successful
0 and 1 => 0.9643
1 and 1 => 0.0235
```

That was the very first example how to use LightBulb! :smile:

## Bonus

Now you can play a little bit with your code and try out other parameters:

For example you could change the learning rate:
```cpp
simpleGradientDescentOptions.learningRate = 0.9;
```
Or disable momentum:
```cpp
simpleGradientDescentOptions.momentum = 0;
```
Or maybe you want to try a completely different gradient descent algorithm like ResilientLearningRate:
```cpp
ResilientLearningRateOptions resilientLearningRateOptions;
ResilientLearningRate* resilientLearningRate = new ResilientLearningRate(resilientLearningRateOptions);
...
options.gradientDescentAlgorithm = resilientLearningRate;
```

Now you are ready for the [next Tutorial](function_evolution.md)!

TODO: List the whole code
