import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import DrawPanel from '../../../../controls/DrawPanel';
import { halton2D,drawCircle } from '../../../../util/GraphicUtilities';
class GraphLogicalView extends React.Component {

    constructor(props) {
        super(props);
        this.graph = props.graph;
        this.state = {
            loaded:false,
            graph:this.props.graph
          };
        this.drawGraph =  this.drawGraph.bind(this);
    }
    drawGraph(_2dgraphics,data) {
        let vertices = this.graph.getVertices(); 
        let size = vertices.size;
        let coordinates = new Set();
        for (let i=1;i<size + 1;i++)
        {
            coordinates.add(halton2D(i,2,3,data.range));
        }
        let n=0;
        for (const item of coordinates) {
            let circleData = {};
            circleData["center"] = {X:item[0],Y:item[1]};
            circleData["style"] = {color:"#00cf00",lineWidth:2,font:"12px Arial"};
            circleData["radius"] = 20;
            circleData["text"] = "<" + n + ">";
            circleData["textColor"] = "#cc00ff";
            drawCircle(_2dgraphics,circleData);
            n++;
          }
    }

    render() {
        return <>
            <DrawPanel drawContent={this.drawGraph} conainerId="algorithmContainer" title={this.props.title}></DrawPanel> 
        </>
    }
        componentDidMount() {
          this.setState({ ...this.state,loaded:true});
    }
    componentDidUpdate(prevProps, prevState, snapshot) 
    {
    }
}
export default GraphLogicalView;