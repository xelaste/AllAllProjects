let uniqueEdgeId = 0;
class Edge {
  id;
  source;
  target;
  data;
  attributes;
  constructor(source, target, data, attributes) {
    this.id = uniqueEdgeId++;
    this.source = source;
    this.target = target;
    this.data = data;
    this.attributes = attributes;
  }
  from() {
    return this.getSource();
  }
  to() {
    return this.getTarget();
  }
  getSource() {
    return this.source;
  }
  getTarget() {
    return this.target;
  }
  getId() {
    return this.id;
  }
  getData() {
    return this.data;
  }
  getAttributes() {
    return this.attributes;
  }
}
export default Edge;
