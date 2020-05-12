"use strict";
export default class AutoPlay {
    constructor() {
        this.initialSet = [];
        for (let i = 1; i < 10; i++) {
            for (let j = 1; j < 10; j++) {
                for (let k = 1; k < 10; k++) {
                    for (let l = 1; l < 10; l++) {
                        if (i != j && i != k && i != l && j != k && j != l && k != l) {
                            this.initialSet.push([i, j, k, l]);
                        }
                    }
                }
            }
        }
    }
    getInitialSet() {
        return this.initialSet;
    }
    calculate(secret, guess) {
        let exist = 0;
        let matches = 0
        for (let i = 0; i < guess.length; i++) {
            for (let j = 0; j < secret.length; j++) {
                if (secret[j] === guess[i]) {
                    if (i === j) {
                        matches++;
                    }
                    else {
                        exist++;
                    }
                }
            }
        }
        return { matches: matches, exist: exist };
    }
    prune(heap, filter, guess) {
        let result = [];
        for (let i = 0; i < heap.length; i++) {
            let num =[...heap[i]];
            let response = this.calculate(num, guess);
            if (response.matches === filter.matches && response.exist === filter.exist) {
                result.push(num);
            }
        }
        return result;
    }

    game(secret) {
        let heap = this.getInitialSet();
        let i = 0;
        while (heap.length > 1) {
            let num = heap[Math.floor(Math.random() * heap.length)];
            let filter = this.calculate(secret, num)
            heap = this.prune(heap, filter, num);
            i++;
        }
    }
}

