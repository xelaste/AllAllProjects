import React from 'react';
import '../../../../css/App.css';
import GraphLogicalView from '../view/GraphLogicalView';
import generateRandomGraph from '../util/RandomGraphGenerator'

 function buildGraph() {
  console.log("build graph")
  let graph = generateRandomGraph (10,4,100);
    return graph;
};
 export default function Dijkstra(props) {
  const graph = props.graph? props.graph : buildGraph();
  return (
    <>
	    <div className='home'> 
          <div id="algorithmContainer" style={{width:"50%",height:"70%"}}><GraphLogicalView graph={graph} title="Dijkstra"></GraphLogicalView> </div>
      </div>
    </>
  );
}
