import React from 'react';
import '../../../../css/App.css';
import GraphLogicalView from '../view/GraphLogicalView';
import generateRandomGraph from '../util/RandomGraphGenerator'
import MinPriorityQueue from '../../datatypes/MinPriorityQueue';
import { useState } from 'react';

const shortPath = (G, s, props) => {

  const distTo = new Map();
  const edgeTo = new Map();
  let vertices = G.getVertices().keys();
  let pq = new MinPriorityQueue(vertices.length);
  const relax = (edge) => {
    let v = edge.from().getId();
    let w = edge.to().getId();
    if (distTo.get(w) > distTo.get(v) + edge.getData().weight) {
      distTo.set(w, distTo[v] + edge.getData().weight);
      if (edgeTo.get(w)) {
        edgeTo.get(w).getAttributes().selected = false;
      }
      edgeTo.set(w, edge);
      edge.getAttributes().selected = true;
      if (pq.contains(w)) {
        pq.decreaseKey(w, distTo.get(w));
      }
      else {
        pq.insert(w, distTo[w]);
        G.getVertex(w).getAttributes().inqueue = true;
      }
    }
  }
  for (const vertex of vertices) {
    distTo.set(vertex, Number.POSITIVE_INFINITY);
  }
  distTo.set(s, 0.0);

  pq.insert(s, distTo.get(s));
  const asyncNextNodeCheck = () => {
    if (!pq.isEmpty()) {
      let v = pq.delMin();
      let adj = G.adj(v);
      for (let edge of adj.values()) {
        relax(edge);
      }
    }
    setTimeout(asyncNextNodeCheck, props.timeout);
  }
  if (props.timeout) {
    setTimeout(asyncNextNodeCheck, props.timeout);
  }
  else {
    while (!pq.isEmpty()) {
      let min = pq.delMin();
      let v = G.getVertex(min)
      v.getAttributes().done = true;
      props.setVertex(min, "done");
      let adj = G.adj(min);
      for (let edge of adj.values()) {
        relax(edge);
      }
    }
  }
}



export default function Dijkstra(props) {
  const [graph, setGraph] = useState({});
  const [vertex, setVertex] = useState({});
  function init() {
    let numberOfNodes = document.getElementById("numberOfNodes").value;
    if (!numberOfNodes) {
      numberOfNodes = document.getElementById("numberOfNodes").placeholder;
      document.getElementById("numberOfNodes").value = numberOfNodes;
    }
    let nodeDegree = document.getElementById("nodeDegree").value;
    if (!nodeDegree) {
      nodeDegree = document.getElementById("nodeDegree").placeholder;
      document.getElementById("nodeDegree").value = nodeDegree;
    }
    let edgeWeight = document.getElementById("edgeWeight").value;
    if (!edgeWeight) {
      edgeWeight = document.getElementById("edgeWeight").placeholder;
      document.getElementById("edgeWeight").value = edgeWeight;
    }
    let graph = generateRandomGraph(numberOfNodes, nodeDegree, edgeWeight);
    setGraph(graph);
  }
  function run() {
    let startNode = document.getElementById("startNode").value;
    if (!startNode) {
      startNode = document.getElementById("startNode").placeholder;
    }
    shortPath(graph, "v" + startNode, { setVertex: (v, status) => { setVertex({ v: v, status: status }) } });
  }
  function pageContent() {
    return <form>
      <div className="fs-6">
        <div className="row text-info row-eq-height align-items-end">
          <div className="col">
            <label for="numberOfNodes">Number of Nodes:</label>
            <input type="text" style={{ width: "5em" }} className="form-control" id="numberOfNodes" placeholder="10" />
          </div>
          <div className="col ">
            <label className="sr-only" for="nodeDegree">Avg Degree:</label>
            <input type="text" style={{ width: "5em" }} className="form-control" id="nodeDegree" placeholder="3" />
          </div>
          <div className="col" style={{ verticalAlign: "bottom" }}>
            <div className='align-bottom' >
              <label className="sr-only" for="edgeWeight">Weight:</label>
              <input type="text" style={{ width: "5em" }} className="form-control" id="edgeWeight" placeholder="100" />
            </div>
          </div>
          <div className="col">
            <label className="sr-only" for="startNode">Start from:</label>
            <input type="text" style={{ width: "5em" }} className="form-control" id="startNode" placeholder="0" />
          </div>
        </div>
        <button type="button" style={{ width: "5em" }} onClick={init} className="btn btn-primary mt-2">Initialize</button>
        <button type="button" style={{ width: "5em" }} onClick={run} className="btn btn-primary mt-2 mx-2">Run</button>
        <button type="button" style={{ width: "5em" }} onClick={() => setGraph({})} className="btn btn-primary mt-2">Clear</button>
      </div>
    </form>
  }

  return (
    <>
      <div className='home'>
        <div className='container-fluid p-20'>
          <div className='row text-center'>
            <h3 className="display-1 text-primary">Dijkstra</h3>
          </div>
          <div className="row h-100">
            <div className="col-3">
              {pageContent()}
            </div>
            <div className="col-9">
              {(graph) ? <div id="algorithmContainer" style={{ width: "100%", height: "80%" }}><GraphLogicalView graph={graph} content={pageContent} title="Dijkstra"></GraphLogicalView> </div> : ""}
            </div>
          </div>
        </div>
      </div>
    </>
  );
}
