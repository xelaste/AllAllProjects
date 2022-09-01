import Graph from "../model/Graph";
import Vertex from "../model/Vertex";
export default function generateRandomGraph(n, k, w, props) {
    let g = new Graph(n);
    let p = 2 * k / (n - 1.0)
    let edges = new Map();
    for (let i = 0; i < n; i++) {
        let vertex = new Vertex('v' + i);
        g.addVertex(vertex);
    }
    // A for loop to randomly generate edges
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            // edgeProbability is a random number
            // between 0.0 and 1.0
            // If the randomly chosen number
            // edgeProbability is less than
            // the probability of an edge p,
            // say, edgeProbability = 0.2 which is less
            // than p = 0.4, then add an edge between the
            // vertex i and the vertex j
            if (i === j || edges.get(j)) {
                continue;
            }
            let weight = Math.floor(w * Math.random());
            let edgeProbability = Math.random();
            if (edgeProbability < p) {
                g.addEdge(g.getVertex('v' + i), g.getVertex('v' + j), { weight: weight }, {});
                edges.set(i, j);
            }
        }
    }
    return g;
}
