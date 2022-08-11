import Edge from './Edge';
class Graph {
    // defining vertex array and
    // adjacent list
    constructor(noOfVertices) {
        this.noOfVertices = noOfVertices;
        this.adjList = new Map();
        this.vertices = new Map();
    }

    addVertex(v) {
        this.adjList.set(v.getId(), new Map());
        this.vertices.set(v.getId(),v);
    }


    addEdge(v, w, data, attributes) {
        if (!this.adjList.has(v.getId())) {
            this.addVertex(v);
        }
        if (!this.adjList.has(w.getId())) {
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
    getVertex(v) {
        return this.vertices.get(v);
    }

}
export default Graph;