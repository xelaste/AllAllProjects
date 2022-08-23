import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import DrawPanel from '../../../../controls/DrawPanel';
import { halton2D, drawCircle, drawArrow } from '../../../../util/GraphicUtilities';
const vertexRadius = 10;
const vertexMargin = 50;
class GraphLogicalView extends React.Component {

    constructor(props) {
        super(props);
        this.graph = props.graph;
        this.state = {
            loaded: false,
            graph: this.props.graph
        };
        this.drawGraph = this.drawGraph.bind(this);
        this.drawVertices = this.drawVertices.bind(this);
        this.drawEdges = this.drawEdges.bind(this);
    }
    drawEdges(_2dgraphics, data) {
        let edges = this.graph.getEdges()
        edges.forEach((adjList, key, map) => {
            adjList.forEach((edge, key, map) => {
                let source = edge.getSource();
                let target = edge.getTarget();
                let sourcePoint = source.getAttributes().coordinates;
                let targetPoint = target.getAttributes().coordinates;
                let dx = targetPoint[0] - sourcePoint[0];
                let dy = targetPoint[1] - sourcePoint[1];
                let l = Math.sqrt(dx * dx + dy * dy);
                let arrowData = {
                    peak: { X: targetPoint[0] - dx * vertexRadius / l, Y: targetPoint[1] - dy * vertexRadius / l },
                    cosa: dx / l,
                    sina: dy / l,
                    strokeStyle: "#00c0c0",
                    fillStyle: "#00c0c0"
                };

                drawArrow(_2dgraphics, arrowData);
                _2dgraphics.beginPath();
                _2dgraphics.lineWidth = 1;
                _2dgraphics.strokeStyle = "#00c0c0";
                _2dgraphics.fillStyle = "##00c0c0";
                _2dgraphics.moveTo(sourcePoint[0] + dx * vertexRadius / l, sourcePoint[1] + dy * vertexRadius / l);
                _2dgraphics.lineTo(targetPoint[0] - dx * vertexRadius / l, targetPoint[1] - dy * vertexRadius / l);
                _2dgraphics.stroke();
                _2dgraphics.closePath();

                if (edge.getData() && edge.getData().weight) {
                    let circleData = {};
                    let centerx = sourcePoint[0] + dx / 2;
                    let centery = sourcePoint[1] + dy / 2;
                    console.log("sourcePoint[0]=" + sourcePoint[0], "sourcePoint[1]=" + sourcePoint[1], "dx=" + dx, "dy=" + dy);
                    circleData["center"] = { X: centerx, Y: centery };
                    circleData["style"] = { color: "#ffffff", lineWidth: 1, font: "8px Arial" };
                    circleData["radius"] = 7;
                    circleData["text"] = edge.getData().weight;
                    circleData["textColor"] = "#cc00ff";
                    drawCircle(_2dgraphics, circleData);
                }

            });
        });
    }
    drawVertices(_2dgraphics, data) {
        let vertices = this.graph.getVertices();
        let count = 0;
        vertices.forEach((vertex, key, map) => {
            const attributes = vertex.getAttributes();
            let item = halton2D(10 + count++, 2, 3, { width: data.range.width - vertexMargin, height: data.range.height - vertexMargin });
            item[0] += vertexMargin / 2;
            item[1] += vertexMargin / 2;
            attributes.coordinates = item
            let circleData = {};
            circleData["center"] = { X: item[0], Y: item[1] };
            circleData["style"] = { color: "#ffee00", lineWidth: 2, font: "12px Arial" };
            circleData["radius"] = vertexRadius;
            circleData["text"] = key;
            circleData["textColor"] = "#cc00ff";
            drawCircle(_2dgraphics, circleData);
        });
    }
    drawGraph(_2dgraphics, data) {
        this.drawVertices(_2dgraphics, data);
        this.drawEdges(_2dgraphics, data)
    }

    render() {
        return <>
                    <DrawPanel drawContent={this.drawGraph} conainerId="algorithmContainer" title={this.props.title}></DrawPanel>
        </>
    }
    componentDidMount() {
        this.setState({ ...this.state, loaded: true });
    }
    componentDidUpdate(prevProps, prevState, snapshot) {
    }
}
export default GraphLogicalView;