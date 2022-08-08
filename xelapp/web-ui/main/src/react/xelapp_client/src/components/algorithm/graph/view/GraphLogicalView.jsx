import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import DrawPanel from '../../../../controls/DrawPanel';
class GraphLogicalView extends React.Component {

    constructor(props) {
        super(props);
        this.graph = props.graph;
        this.state = {
            loaded:false,
            graph:this.props.graph
          };
    }
    drawGraph(_2dgraphics) {

    }

    render() {
        return <>
            <div id="graphLogicalContainer" style={{ width: "50%", height: "70%" }}><DrawPanel drawContent={this.drawGraph} conainerId="graphLogicalContainer" title={this.props.title}></DrawPanel> </div>
        </>
    }
    
    handleResize() {
        this.setState({ ...this.state,size:{width:window.innerWidth,height:window.innerHeight}});
     }
    componentDidMount() {
          this.setState({ ...this.state,loade:true});
          window.addEventListener('resize', this.handleResize);
    }
    componentDidUpdate(prevProps, prevState, snapshot) 
    {
    }
}
export default GraphLogicalView;