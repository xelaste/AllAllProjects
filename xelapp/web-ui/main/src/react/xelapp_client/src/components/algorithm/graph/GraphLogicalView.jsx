import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import DrawPanel from '../../../controls/DrawPanel';
class GraphLogicalView extends React.Component {

    constructor(props) {
        super(props);
        this.graph = props.graph;
        this.state = {
            loaded:false
          };

    }

    graph = {};
    drawGraph() {

    }
    getCanvas() {
        return this.canvas;
    }

    render() {
        return <>
            <div id="graphLogicalContainer" style={{ width: "50%", height: "70%" }}><DrawPanel parentObject={this} conainerId="graphLogicalContainer" title={this.props.title}></DrawPanel> </div>
        </>
    }
    
    handleResize() {
        let size = {width:window.innerWidth,height:window.innerHeight };
        this.state = {
            size: size
          };
     }
    componentDidMount() {
        this.state = {
            ...this.state,
            loaded:true
          };
          window.addEventListener('resize', handleResize);
    }
    componentDidUpdate(prevProps, prevState, snapshot) 
    {
    }
}
export default GraphLogicalView;