import React,{ useState, useEffect } from 'react';
import '../../../../css/App.css';
import GraphLogicalView from '../view/GraphLogicalView';
import Graph  from '../model/Graph';
 function buildGraph() {
  let graph = new Graph(6);
  let vertices = [ 'A', 'B', 'C', 'D', 'E', 'F' ];
  for (let i = 0; i < vertices.length; i++) {
    graph.addVertex(vertices[i]);
  }

  graph.addEdge('A', 'B');
  graph.addEdge('A', 'D');
  graph.addEdge('A', 'E');
  graph.addEdge('B', 'C');
  graph.addEdge('D', 'E');
  graph.addEdge('E', 'F');
  graph.addEdge('E', 'C');
  graph.addEdge('C', 'F');
};
 export default function Dijkstra(props) {
  const [loaded, setLoaded] = useState(false);
  const [setResize] = useState(null);
  const graph = this.prop.graph? this.prop.graph : buildGraph();
  
  useEffect(() => {   
    function handleResize() {
       let size = {width:window.innerWidth,height:window.innerHeight };
       setResize (size);
    }
  	// Update the document title using the browser API    
  	if (!loaded ) {
      setLoaded (true);
      window.addEventListener('resize', handleResize);
    } 
  }
  );
  return (
    <>
	    <div className='home'> 
          <div id="algorithmContainer" style={{width:"50%",height:"70%"}}><GraphLogicalView graph={graph} title="Dijkstra"></GraphLogicalView> </div>
      </div>
    </>
  );
}
