import React from 'react';
import '../../../../css/App.css';
import GraphLogicalView from '../view/GraphLogicalView';
import generateRandomGraph from '../util/RandomGraphGenerator'

function buildGraph() {
  console.log("build graph")
  let graph = generateRandomGraph(10, 4, 100);
  return graph;
};
function pageContent() {
  return <form>
    <div className="display-4 fs-6">
      <label  for="inlineFormInput">Number of Nodes:</label>
      <input type="text"  id="inlineFormInput" placeholder="Jane Doe" />
      <label className="sr-only" for="inlineFormInputGroup">Username</label>
      <div className="input-group mb-2">
        <div className="input-group-prepend">
          <div className="input-group-text">@</div>
        </div>
        <input type="text" className="form-control" id="inlineFormInputGroup" placeholder="Username" />
      </div>
      <div className="form-check mb-2">
        <input className="form-check-input" type="checkbox" id="autoSizingCheck" />
        <label className="form-check-label" for="autoSizingCheck">
          Remember me
        </label>
      </div>
      <button type="submit" className="btn btn-primary mb-2">Submit</button>
    </div>
  </form>
}
export default function Dijkstra(props) {
  const graph = props.graph ? props.graph : buildGraph();
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
              <div id="algorithmContainer" style={{ width: "100%", height: "80%" }}><GraphLogicalView graph={graph} content={pageContent} title="Dijkstra"></GraphLogicalView> </div>
            </div>
          </div>
        </div>
      </div>
    </>
  );
}
