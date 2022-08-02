import React,{ useState, useEffect } from 'react';
import '../../css/App.css';
import DrawPanel from '../../controls/DrawPanel';

export default function Dijkstra() {
  const [loaded, setLoaded] = useState(false);
  useEffect(() => {    
  	// Update the document title using the browser API    
  	setLoaded (true);
  });
  return (
    <>
	    <div className='home'> 
          <div id="algorithmContainer" style={{width:"50%"}}><DrawPanel title="Dijkstra"></DrawPanel> </div>
      </div>
    </>
  );
}
