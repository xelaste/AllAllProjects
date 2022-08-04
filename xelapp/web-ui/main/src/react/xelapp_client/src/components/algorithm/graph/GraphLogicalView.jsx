import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import DrawPanel from '../../../controls/DrawPanel';
class DrawPanel extends React.Component {

    constructor(props) {
        super(props);
        this.graph = props.graph;
    }
   graph = {};
   drawGraph ()
   {

   }
   getCanvas()
   {
       return this.canvas; 
   }

   render ()
   {
       return <>
        <div id="graphLogicalContainer" style={{width:"50%",height:"70%"}}><DrawPanel parentObject={this} conainerId="graphLogicalContainer" title={this.props.title}></DrawPanel> </div>
       </>
   }

}