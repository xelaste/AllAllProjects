let MinPriorityQueue = function () {
    //const pq = [];
    //const keys = new Map();
    //    let size = 0;
    //    let comparator = function (a, b) { return a > b };
    this.MinPriorityQueue = function (maxSize, comparator) {
        this.maxSize = maxSize;
        if (comparator) {
            this.comparator = comparator;
        }
        else {
            this.comparator = function (a, b) {
                if (a > b) return 1;
                if (a === b) return 0;
                if (a < b) return -1;
            };
        }
        this.pq = [];
        this.keys = new Map();
        this.index = new Map();
    }

    this.isEmpty = function () {
        return this.pq.length === 0;
    }
    this.size = function () {
        return this.pq.length;
    }
    this.contains = function (i) {
        return this.keys.contains(i);
    }


    this.delMin = function () {
        let n = this.size();
        if (n === 0) throw new Error("Priority queue underflow");
        let min = this.pq[0];
        exch(0, n - 1);
        this.pq.pop();
        this.keys.delete(min);
        this.index.delete(min);
        sink(0);
        return min;
    }

    this.insert = function (i, key) {
        if (this.pq.length === this.maxSize) {
            throw new Error("index >= capacity: " + i);
        }
        if (this.contains(i)) throw new Error("index is already in the priority queue" + i);
        this.pq.push(i);
        this.index.set(i, this.size() - 1);
        this.keys.set(i, key);
        swim(this.size() - 1);
    }


    this.decreaseKey = function (i, key) {
        if (!this.contains(i)) throw new Error("index is not in the priority queue");
        let value = this.keys.get(i);
        if (this.comparator(value, key) === 0)
            throw new Error("Calling decreaseKey() with a key equal to the key in the priority queue");
        if (this.comparator(value, key) < 0)
            throw new Error("Calling decreaseKey() with a key strictly greater than the key in the priority queue");
        this.keys.set(i, key);
        swim(this.qp[i]);
    }

    this.increaseKey = function (i, key) {
        if (!this.contains(i)) throw new Error("index is not in the priority queue " + i);
        let value = this.keys.get(i);
        if (this.comparator(value, key) === 0)
            throw new Error("Calling increaseKey() with a key equal to the key in the priority queue " + key);
        if (this.comparator(value, key) > 0)
            throw new Error("Calling increaseKey() with a key strictly less than the key in the priority queue " + key);
        this.keys.set(i, key);
        sink(this.index.get(i));
    }


    function greater(i, j) {
        return this.comparator(this.pq[i], this.pq[j]);
    }
    function exch(i, j) {
        let swap = this.pq[i];
        this.pq[i] = this.pq[j];
        this.pq[j] = swap;
        this.index.set(this.pq[i], i);
        this.index.set(this.pq[j], j);
    }
    function swim(k) {
        while (k > 1 && greater(k / 2, k)) {
            exch(k, k / 2);
            k = k / 2;
        }
    }
    function sink(k) {
        let n = this.size() - 1;
        while (2 * k <= n) {
            let j = 2 * k;
            if (j < n && greater(j, j + 1)) j++;
            if (!greater(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

}
export default MinPriorityQueue;