import React from 'react';
import '../../../../css/App.css';
import GraphLogicalView from '../view/GraphLogicalView';
import Graph  from '../model/Graph';
import Vertex from '../model/Vertex';

 function buildGraph() {
  console.log("build graph")
  let graph = new Graph(6);
  let vertices = [ 'A', 'B', 'C', 'D', 'E', 'F' ];
  for (let i = 0; i < vertices.length; i++) {
    let vertex = new Vertex(vertices[i])
    graph.addVertex(vertex);
  }
  graph.addEdge( graph.getVertex('A'), graph.getVertex('B'));
  graph.addEdge(graph.getVertex('A'), graph.getVertex('D'));
  graph.addEdge(graph.getVertex('A'), graph.getVertex('E'));
  graph.addEdge(graph.getVertex('B'), graph.getVertex('C'));
  graph.addEdge(graph.getVertex('D'), graph.getVertex('E'));
  graph.addEdge(graph.getVertex('E'), graph.getVertex('F'));
  graph.addEdge(graph.getVertex('E'), graph.getVertex('C'));
  graph.addEdge(graph.getVertex('C'), graph.getVertex('F'));
  console.log("end build graph")
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
