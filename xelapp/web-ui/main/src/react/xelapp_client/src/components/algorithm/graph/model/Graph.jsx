import Edge from './Edge';
class Graph {
    // defining vertex array and
    // adjacent list
    constructor(noOfVertices) {
        this.noOfVertices = noOfVertices;
        this.adjList = new Map();
        this.vertices = new Set();
    }

    addVertex(v) {
        this.adjList.set(v.getId(), new Map());
        this.vertices.add(v);
    }


    addEdge(v, w, data, attributes) {
        if (!this.adjList.has(v.getId)) {
            this.addVertex(v);
        }
        if (!this.adjList.has(w.getId)) {
            this.addVertex(w);
        }
        this.adjList.get(v.getId()).set(w.getId(), new Edge(v, w, data, attributes));
    }

    getEdges() {
        return this.adjList;
    }
    getVertices() {
        return this.vertices;
    }

}
export default Graph;