import React from 'react';
import '../../../../css/App.css';
import GraphLogicalView from '../view/GraphLogicalView';
import generateRandomGraph from '../util/RandomGraphGenerator'
import { useState } from 'react';

export default function Dijkstra(props) {
  const [graph, setGraph] = useState({});

  function init() {
    let numberOfNodes = document.getElementById("numberOfNodes").value;
    if (!numberOfNodes) {
      numberOfNodes = document.getElementById("numberOfNodes").placeholder;
      document.getElementById("numberOfNodes").value=numberOfNodes;
    }
    let nodeDegree = document.getElementById("nodeDegree").value;
    if (!nodeDegree) {
      nodeDegree = document.getElementById("nodeDegree").placeholder;
      document.getElementById("nodeDegree").value = nodeDegree;
    }
    let edgeWeight = document.getElementById("edgeWeight").value;
    if (!edgeWeight) {
      edgeWeight = document.getElementById("edgeWeight").placeholder;
      document.getElementById("edgeWeight").value=edgeWeight;
    }
    let graph = generateRandomGraph(numberOfNodes, nodeDegree, edgeWeight);
    setGraph (graph);
  }
  function run() {
    alert("run");
  }
  function pageContent() {
    return <form>
      <div className="fs-6">
        <div className="row text-info">
          <div className="col-3">
            <label for="numberOfNodes">Number of Nodes:</label>
            <input type="text" style={{ width: "5em" }} className="form-control" id="numberOfNodes" placeholder="10" />
          </div>
          <div className="col">
            <label className="sr-only" for="nodeDegree">Avg Degree:</label>
            <input type="text" style={{ width: "5em" }} className="form-control" id="nodeDegree" placeholder="3" />
          </div>
          <div className="col">
            <label className="sr-only" for="edgeWeight">Weight:</label>
            <input type="text" style={{ width: "5em" }} className="form-control" id="edgeWeight" placeholder="100" />
          </div>
          <div className="col">
            <label className="sr-only" for="startNode">Start from:</label>
            <input type="text" style={{ width: "5em" }} className="form-control" id="startNode" placeholder="0" />
          </div>
        </div>
        <button type="button" style={{ width: "5em" }} onClick={init} className="btn btn-primary mt-2">Initialize</button>
        <button type="button" style={{ width: "5em" }} onClick={run} className="btn btn-primary mt-2 mx-2">Run</button>
        <button type="button" style={{ width: "5em" }} onClick={()=>setGraph({})} className="btn btn-primary mt-2">Clear</button>
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
            <div className="col-4">
              {pageContent()}
            </div>
            <div className="col-8">
              { (graph)? <div id="algorithmContainer" style={{ width: "100%", height: "80%" }}><GraphLogicalView graph={graph} content={pageContent} title="Dijkstra"></GraphLogicalView> </div> : "" }
            </div>
          </div>
        </div>
      </div>
    </>
  );
}
