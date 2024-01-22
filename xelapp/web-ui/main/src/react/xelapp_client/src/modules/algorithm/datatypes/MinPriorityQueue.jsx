function MinPriorityQueue (maxSize, comparator) {
  const pq = [];
  const keys = new Map();
  const index = new Map();

  if (!comparator) {
    comparator = (a, b) => {
      if (a > b) return 1;
      if (a === b) return 0;
      if (a < b) return -1;
    };
  }
  this.getEntireQueue = function () {
    return [...pq];
  };
  this.capacity = () => {
    return maxSize;
  };
  this.comparator = comparator;
  this.isEmpty = function () {
    return pq.length === 0;
  };
  this.size = function () {
    return pq.length;
  };
  this.contains = function (i) {
    return keys.has(i);
  };

  this.delMin = function () {
    let n = this.size();
    if (n === 0) throw new Error("Priority queue underflow");
    let min = pq[0];
    exch(0, n - 1);
    pq.pop();
    keys.delete(min);
    index.delete(min);
    sink(0);
    return min;
  };

  this.insert = function (i, key) {
    if (pq.length === this.capacity()) {
      throw new Error("index >= capacity: " + i);
    }
    if (this.contains(i))
      throw new Error("index is already in the priority queue" + i);
    pq.push(i);
    index.set(i, this.size() - 1);
    keys.set(i, key);
    swim(this.size() - 1);
  };

  this.decreaseKey = function (i, key) {
    if (!this.contains(i))
      throw new Error("index is not in the priority queue");
    let value = keys.get(i);
    if (comparator(value, key) === 0)
      throw new Error(
        "Calling decreaseKey() with a key equal to the key in the priority queue"
      );
    if (comparator(value, key) < 0)
      throw new Error(
        "Calling decreaseKey() with a key strictly greater than the key in the priority queue"
      );
    keys.set(i, key);
    swim(index.get(i));
  };

  this.increaseKey = function (i, key) {
    if (!this.contains(i))
      throw new Error("index is not in the priority queue " + i);
    let value = keys.get(i);
    if (comparator(value, key) === 0)
      throw new Error(
        "Calling increaseKey() with a key equal to the key in the priority queue " +
          key
      );
    if (comparator(value, key) > 0)
      throw new Error(
        "Calling increaseKey() with a key strictly less than the key in the priority queue " +
          key
      );
    keys.set(i, key);
    sink(index.get(i));
  };

  const greater = (i, j) => {
    return comparator(pq[i], pq[j]);
  };
  const exch = (i, j) => {
    let swap = pq[i];
    pq[i] = pq[j];
    pq[j] = swap;
    index.set(pq[i], i);
    index.set(pq[j], j);
  };
  const swim = (k) => {
    while (k > 0 && greater(nodeParent(k), k)) {
      let parent = nodeParent(k);
      exch(k, parent);
      k = parent;
    }
  };
  const sink = (k) => {
    let n = this.size() - 1;
    while (leftChidIdx(k) <= n) {
      let j = leftChidIdx(k);
      if (j < n && greater(j, j + 1)) j++;
      if (!greater(k, j)) break;
      exch(k, j);
      k = j;
    }
  };
  const leftChidIdx = (parent) => {
    return 2 * parent + 1;
  };
  const nodeParent = (child) => {
    return Math.floor((child - 1) / 2);
  };
};
export default MinPriorityQueue;
