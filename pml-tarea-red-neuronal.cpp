#include <iostream>
using namespace std;

struct Node {
    int code;
    Node **next;
    int nextCount;
};

struct Layer {
    int count;
    Node *nodes;
};

struct NeuralNetwork {
    int numLayers;
    Layer *layers;
};

void createNeuralNetwork(NeuralNetwork &net, int e, int m, int n, int s) {
    net.numLayers = 1 + n + 1;
    net.layers = new Layer[net.numLayers];
    //CreaCapaEntrada

    //CreaCapasOcultas
    //input layer
    net.layers[0].count = e;
    net.layers[0].nodes = new Node[e];

    //CreaCapaSalida
    //hidden layer
    for (int i = 1; i <= n; ++i) {
        net.layers[i].count = m;
        net.layers[i].nodes = new Node[m];
    }

    int outputIndex = n + 1;
    net.layers[outputIndex].count = s;
    net.layers[outputIndex].nodes = new Node[s];

    //CreaNodo - inicializa
    for (int layerIndex = 0; layerIndex < net.numLayers; ++layerIndex) {
        Layer &layer = net.layers[layerIndex];
        for (int j = 0; j < layer.count; ++j) {
            layer.nodes[j].code = j + 1;
            layer.nodes[j].next = nullptr;
            layer.nodes[j].nextCount = 0;
        }
    }

}

void connectLayers(NeuralNetwork &net) {
    for (int layerIndex = 0; layerIndex < net.numLayers; layerIndex++) {
        Layer &currenLayer = net.layers[layerIndex];
        Layer &nextLayer = net.layers[layerIndex + 1];

        int currentCount = currenLayer.count;
        int nextCount = nextLayer.count;

        for (int currentNodeIndex =0; currentNodeIndex < currentCount; ++currentNodeIndex) {
            Node &currentNode = currenLayer.nodes[currentNodeIndex];
            currentNode.nextCount = nextCount;
            currentNode.next = new Node *[nextCount];

            for (int nextNodeIndex = 0; nextNodeIndex < nextCount; ++nextNodeIndex) {
                currentNode.next[nextNodeIndex] = &nextLayer.nodes[nextNodeIndex];
            }
        }
    }
}

void freeNetwork(NeuralNetwork &net) {
    for (int layerIndex = 0; layerIndex < net.numLayers - 1; ++layerIndex) {
        Layer &layer = net.layers[layerIndex];

        for (int j = 0; j < layer.count; ++j) {
            Node &node = layer.nodes[j];
            delete[] node.next;        // safe even if node.next == nullptr
            node.next = nullptr;
            node.nextCount = 0;
        }
    }

    for (int layerIndex = 0; layerIndex < net.numLayers; ++layerIndex) {
        delete[] net.layers[layerIndex].nodes;
        net.layers[layerIndex].nodes = nullptr;
        net.layers[layerIndex].count = 0;
    }

    delete[] net.layers;
    net.layers = nullptr;
    net.numLayers = 0;
}

void printNetworkDiagram(const NeuralNetwork &net) {
    cout << "\nNeural network structure (layers and connections):\n\n";

    for (int layerIndex = 0; layerIndex < net.numLayers; ++layerIndex) {
        const Layer &layer = net.layers[layerIndex];

        // Layer header
        cout << "Layer " << layerIndex;
        if (layerIndex == 0) {
            cout << " (input)";
        } else if (layerIndex == net.numLayers - 1) {
            cout << " (output)";
        } else {
            cout << " (hidden)";
        }
        cout << " - nodes: " << layer.count << "\n";

        // List of nodes in this layer
        cout << "  Nodes: ";
        for (int j = 0; j < layer.count; ++j) {
            cout << "[L" << layerIndex << ".N" << j << "]";
            if (j < layer.count - 1) {
                cout << "  ";
            }
        }
        cout << "\n";

        // Connections from this layer to the next one
        if (layerIndex < net.numLayers - 1) {
            cout << "  Connections:\n";

            for (int j = 0; j < layer.count; ++j) {
                const Node &node = layer.nodes[j];

                cout << "    [L" << layerIndex << ".N" << j << "] -> ";

                for (int k = 0; k < node.nextCount; ++k) {
                    // Each next[k] points to a node in layerIndex+1
                    cout << "[L" << (layerIndex + 1) << ".N" << k << "]";
                    if (k < node.nextCount - 1) {
                        cout << ", ";
                    }
                }
                cout << "\n";
            }
        }

        cout << "\n";
    }
}


int main() {
    int e, m, n, s;
    cin >> e >> m >> n >> s;

    long product = e * m * n * s;
    cout << product << endl;  // lo que pide el problema base

    NeuralNetwork net;

    //CreaCapaEntrada
    //CreaCapasOcultas
    //CreaCapaSalida
    createNeuralNetwork(net, e, m, n, s);

    //CreaNodo - enlaza
    connectLayers(net);

    printNetworkDiagram(net);

    freeNetwork(net);
    return 0;

}

