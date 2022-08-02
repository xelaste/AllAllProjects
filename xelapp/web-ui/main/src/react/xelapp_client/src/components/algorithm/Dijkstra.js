import React,{ useState, useEffect } from 'react';
import '../../css/App.css';
import DrawPanel from '../../controls/DrawPanel';

export default function Dijkstra() {
  const [loaded, setLoaded] = useState(false);
  const [resize, setResize] = useState(null);
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
    
  });
  return (
    <>
	    <div className='home'> 
          <div id="algorithmContainer" style={{width:"50%",height:"70%"}}><DrawPanel title="Dijkstra"></DrawPanel> </div>
      </div>
    </>
  );
}
