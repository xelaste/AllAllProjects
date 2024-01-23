import Graph from "../model/Graph";
import Vertex from "../model/Vertex";
export default function generateRandomGraph(n, k, w, props) {
    let g = new Graph(n);
    let p = k / (n - 1.0)
    for (let i = 0; i < n; i++) {
        let vertex = new Vertex('v' + i);
        g.addVertex(vertex);
    }
    // A for loop to randomly generate edges
    for (let i = 0; i < n; i++) {
        let order = 0;
        for (let j = 0; j < n; j++) {
            let adj = g.adj('v' + j)
            if (i === j || (adj && adj.get('v' + i))) {
                continue;
            }
            let weight = Math.floor(w * Math.random());
            let edgeProbability = Math.random();
            if (edgeProbability <= p) {
                g.addEdge(g.getVertex('v' + i), g.getVertex('v' + j), { weight: weight }, {});
                order++;
            }
        }
        if (order === 0) {
            while (order<k/2) {
                let j = Math.ceil(Math.random() * (n - 1));
                let adj = g.adj('v' + j)
                if (i === j || (adj && adj.get('v' + i))) {
                    continue;
                }
                let weight = Math.floor(w * Math.random());
                g.addEdge(g.getVertex('v' + i), g.getVertex('v' + j), { weight: weight }, {});
                order++;
                break;
            }
        }
    }
    return g;
}
