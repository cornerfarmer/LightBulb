# Backpropagation xor

* The example is integrated into LightBulbExample and its code can be found in [BackpropagationXor](https://github.com/domin1101/LightBulb/tree/master/example/LightBulbExample/Examples/BackpropagationXor). *

A first basic example how to train a neural network to simulate a xor calculator. To achieve that a simple gradient descent algorithm is used.

## The network

The first thing to do is creating the neural network we want to train:

```c++
FeedForwardNetworkTopologyOptions networkTopologyOptions;
networkTopologyOptions.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
networkTopologyOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
networkTopologyOptions.neuronsPerLayerCount[0] = 2;
networkTopologyOptions.neuronsPerLayerCount[1] = 3;
networkTopologyOptions.neuronsPerLayerCount[2] = 1;

FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(networkTopologyOptions);

std::unique_ptr<NeuralNetwork> network(new NeuralNetwork(networkTopology));
```

At first we prepare the configuration of our feed forward network topology. (A network topology manages the structure information of a neural network)
We want to use the same activaton/netInput function for every neuron. So we use the SameNeuronDescriptionFactory with the WeightedSumFunction as net input and the FermiFunction as activation function.
The network should have three layers. The input layer with two, the hidden layer with 3 and the output layer with one neuron.

Now we are ready to create the network topology.
After creating the topology its easy to create the network.

Thats it, now we have our feed forward network and can go on train it.

## The trainer 

A trainer is necessary for all kind of supervised learning stuff. It tells the learning rule what the network should learning.
In our case this is just all four xor combinations:

```c++
std::unique_ptr<Teacher> teacher(new Teacher());
for (int i = 0; i < 2; i += 1)
{
    for (int l = 0; l < 2; l += 1)
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

Everyone of these combinations becomes an extra teaching lesson. A teaching lesson consists of a teaching pattern and a teaching input.
The teaching pattern contains the input for the neural network.
The teaching input contains the values the neural network should output.

# The learning rule

The learning rule manages the whole learning process.

```c++
SimpleGradientDescentOptions simpleGradientDescentOptions;
To be continued...
```