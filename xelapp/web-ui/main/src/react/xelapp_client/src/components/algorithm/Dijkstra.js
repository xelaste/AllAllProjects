import React,{ useState, useEffect } from 'react';
import '../../css/App.css';
import DrawPanel from '../../controls/DrawPanel';
import Graph
 from './graph/Graph';
export default function Dijkstra() {
  const [loaded, setLoaded] = useState(false);
  const [resize, setResize] = useState(null);
  let graph = null;
  function buildGraph() {
    this.graph = new Graph(6);
    var vertices = [ 'A', 'B', 'C', 'D', 'E', 'F' ];
    for (var i = 0; i < vertices.length; i++) {
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
  }

  useEffect(() => {   
    function handleResize() {
       let size = {width:window.innerWidth,height:window.innerHeight };
       setResize (size);
    }
  	// Update the document title using the browser API    
  	if (!loaded ) {
      buildGraph();
      setLoaded (true);
      window.addEventListener('resize', handleResize);
    } 
    
  });
  return (
    <>
	    <div className='home'> 
          <div id="algorithmContainer" style={{width:"50%",height:"70%"}}><DrawPanel title="Dijkstra"></DrawPanel> </div>
      </div>
    </>
  );
}
