import React from 'react';
import '../../../../css/App.css';
import GraphLogicalView from '../view/GraphLogicalView';
import generateRandomGraph from '../util/RandomGraphGenerator'
import MinPriorityQueue from '../../datatypes/MinPriorityQueue';
import { useState } from 'react';

const shortPath = (G, s, props) => {
  const distTo = props.distTo;
  const edgeTo = props.edgeTo;
  let vertices = G.getVertices().keys();
  let pq = props.pq;
  let tick = 0;
  for (const vertex of vertices) {
    distTo.set(vertex, Number.POSITIVE_INFINITY);
  }
  distTo.set(s, 0.0);
  pq.insert(s, distTo.get(s));

  const relax = (edge) => {
    let v = edge.from().getId();
    let w = edge.to().getId();
    if (distTo.get(w) > distTo.get(v) + edge.getData().weight) {
      distTo.set(w, distTo.get(v) + edge.getData().weight);
      if (edgeTo.get(w)) {
        edgeTo.get(w).getAttributes().selected = false;
      }
      edgeTo.set(w, edge);
      edge.getAttributes().selected = true;
      if (pq.contains(w)) {
        pq.decreaseKey(w, distTo.get(w));
      }
      else {
        pq.insert(w, distTo.get(w));
        G.getVertex(w).getAttributes().inqueue = true;
      }
    }
  }
  const asyncProcessAdj = (values, v) => {
    let result = values.next();
    if (!result.done) {
      let edge = result.value;
      relax(edge)
      setTimeout(asyncProcessAdj, props.timeout, values, v);
    }
    else {
      v.getAttributes().done = true;
      setTimeout(asyncNextNodeCheck, props.timeout);
    }
    props.setTick(tick++);
  }
  const processNode = () => {
    let min = pq.delMin();
    let v = G.getVertex(min)
    v.getAttributes().inqueue = false;
    let adj = G.adj(min);
    if (props.timeout) {
      setTimeout(asyncProcessAdj, props.timeout, adj.values(), v);
    }
    else {
      for (let edge of adj.values()) {
        relax(edge);
      }
      v.getAttributes().done = true;
    }
  }
  const asyncNextNodeCheck = () => {
    if (!pq.isEmpty()) {
      processNode();
    }
    props.setTick(tick++);
  }

  if (props.timeout) {
    processNode();
    setTimeout(asyncNextNodeCheck, props.timeout);
  }
  else {
    while (!pq.isEmpty()) {
      processNode();
      props.setTick(tick++);
    }
  }
}

export default function Dijkstra(props) {
  const [graph, setGraph] = useState({});
  const [tick, setTick] = useState(0);
  const [state, setState] = useState({});

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
    let vertices = graph.getVertices();
    for (let v of vertices.values()) {
      v.getAttributes().done = false;
      v.getAttributes().inqueue = false;
      let adj = graph.adj(v.getId());
      for (let edge of adj.values()) {
        edge.getAttributes().selected = false;
      }
    }
    let newState = {
      ...state, distTo: new Map(),
      edgeTo: new Map(),
      pq: new MinPriorityQueue(graph.getVertices().keys().length)
    }
    setState(newState);
    shortPath(graph, "v" + startNode, {
      setTick: (tick) => { setTick(tick) },
      distTo: newState.distTo,
      edgeTo: newState.edgeTo,
      pq: newState.pq,
      timeout: 1000,
    });
  }
  function pageContent() {
    return <>
      <div className="card fs-6 mt-10 p-6 w-100 border-dark bg-secondary mb-3">
        <div className="card-header">
          <h3 className="text-white">Configuration</h3>
        </div>
        <div className="card-body">
          <form>
            <div className="fs-6y">
              <div className="row row-eq-height align-items-end">
                <div className="col">
                  <label htmlFor="numberOfNodes">Number of Nodes:</label>
                  <input type="text" style={{ width: "5em" }} className="form-control" id="numberOfNodes" placeholder="10" />
                </div>
                <div className="col ">
                  <label className="sr-only" htmlFor="nodeDegree">Avg Degree:</label>
                  <input type="text" style={{ width: "5em" }} className="form-control" id="nodeDegree" placeholder="3" />
                </div>
                <div className="col" style={{ verticalAlign: "bottom" }}>
                  <div className='align-bottom' >
                    <label className="sr-only" htmlFor="edgeWeight">Weight:</label>
                    <input type="text" style={{ width: "5em" }} className="form-control" id="edgeWeight" placeholder="100" />
                  </div>
                </div>
                <div className="col">
                  <label className="sr-only" htmlFor="startNode">Start from:</label>
                  <input type="text" style={{ width: "5em" }} className="form-control" id="startNode" placeholder="0" />
                </div>
              </div>
              <button type="button" style={{ width: "6em" }} onClick={init} className="btn btn-primary mt-2">Initialize</button>
              <button type="button" style={{ width: "6em" }} disabled={!graph || Object.keys(graph).length === 0} onClick={run} className="btn btn-primary mt-2 mx-2">Run</button>
              <button type="button" style={{ width: "6em" }} onClick={() => setGraph({})} className="btn btn-primary mt-2">Clear</button>
            </div>
          </form>
        </div>
      </div>
      <div className="card fs-6 mt-10 p-6 w-100 border-dark bg-info mb-3">
        <div className="card-header">
          <h3 className="text-dark">Results</h3>
        </div>
        <div className="card-body text-dark">
          <div className="row row-eq-height align-items-end">
            <div className="col">
              <label>Queue</label>
              {
                state.queue ? state.pq.getEntireQueue().map((v) => {
                  return <>
                    <span className="m-1">{v}</span>
                  </>
                }) : ""
              }

            </div>
          </div>
          <div className="row row-eq-height align-items-end">
            <div className="col">
              <label >DistTo</label>
              {
                state.distTo ? Array.from(state.distTo.keys()).map((key) => {
                  return <>
                    <span className="m-1">{key}:{state.distTo.get(key)}</span>
                  </>
                }) : ""
              }
            </div>
          </div>
          <div className="row row-eq-height align-items-end">
            <div className="col">
              <label >Back Tracking</label>
              {
                state.edgeTo ? Array.from(state.edgeTo.keys()).map((key) => {
                  return <>
                    <span className="m-1">{key}:{(state.edgeTo.get(key)).getSource().getId()}</span>
                  </>
                }) : ""
              }
            </div>
          </div>
        </div>
      </div>
    </>
  }

  return (
    <>
      <div className='home'>
        <div className='container-fluid p-20'>
          <div className='row text-center'>
            <h3 className="display-4 text-primary">Dijkstra</h3>
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
