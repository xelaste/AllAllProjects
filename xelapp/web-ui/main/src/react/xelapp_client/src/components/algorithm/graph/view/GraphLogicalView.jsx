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
        this.handleResize = this.handleResize.bind(this);
    }
    drawEdges(_2dgraphics, data) {
        let edges = this.props.graph.getEdges()
        edges.forEach((adjList, key, map) => {
            adjList.forEach((edge, key, map) => {
                let source = edge.getSource();
                let target = edge.getTarget();
                let sourcePoint = source.getAttributes().coordinates;
                let targetPoint = target.getAttributes().coordinates;
                let selected = edge.getAttributes().selected;
                let dx = targetPoint[0] - sourcePoint[0];
                let dy = targetPoint[1] - sourcePoint[1];
                let l = Math.sqrt(dx * dx + dy * dy);
                let color = (selected) ? "#4c516d" : "#00c0c0";
                let arrowData = {
                    peak: { X: targetPoint[0] - dx * vertexRadius / l, Y: targetPoint[1] - dy * vertexRadius / l },
                    cosa: dx / l,
                    sina: dy / l,
                    strokeStyle: color,
                    fillStyle: color
                };

                drawArrow(_2dgraphics, arrowData);
                _2dgraphics.beginPath();
                _2dgraphics.lineWidth = selected ? 2 : 1;
                _2dgraphics.strokeStyle = color;
                _2dgraphics.fillStyle = color;
                _2dgraphics.moveTo(sourcePoint[0] + dx * vertexRadius / l, sourcePoint[1] + dy * vertexRadius / l);
                _2dgraphics.lineTo(targetPoint[0] - dx * vertexRadius / l, targetPoint[1] - dy * vertexRadius / l);
                _2dgraphics.stroke();
                _2dgraphics.closePath();

                if (edge.getData() && edge.getData().weight) {
                    if (!edge.getAttributes().labelPosition) {
                        let shift = Math.floor(3 * 14 * Math.random());
                        shift *= (shift % 2) === 0 ? -1 : 1;
                        let centerx = (shift * dx / l) + sourcePoint[0] + dx / 2;
                        let centery = (shift * dy / l) + sourcePoint[1] + dy / 2;
                        edge.getAttributes().labelPosition = { X: centerx, Y: centery }
                    }
                    let circleData = {};
                    circleData["center"] = edge.getAttributes().labelPosition;
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
        let vertices = this.props.graph.getVertices();
        let count = 0;
        vertices.forEach((vertex, key, map) => {
            const attributes = vertex.getAttributes();
            let done = attributes.done;
            let inqueue = attributes.inqueue;
            let item = halton2D(10 + count++, 2, 3, { width: data.range.width - vertexMargin, height: data.range.height - vertexMargin });
            item[0] += vertexMargin / 2;
            item[1] += vertexMargin / 2;
            attributes.coordinates = item
            let circleData = {};
            circleData["center"] = { X: item[0], Y: item[1] };
            circleData["style"] = { color: done ? "#388a73" : "#ffee00", lineWidth: 2, font: "12px Arial" };
            circleData["radius"] = vertexRadius;
            circleData["text"] = key;
            circleData["textColor"] = "#cc00ff";
            if (inqueue) {
                circleData["textColor"] = "#00ffff"
            }
            if (done) {
                circleData["textColor"] = "#ffc0cb";
            }
            drawCircle(_2dgraphics, circleData);
        });
    }
    drawGraph(_2dgraphics, data) {
        if (Object.keys(this.props.graph).length === 0) {
            return;
        }
        this.drawVertices(_2dgraphics, data);
        this.drawEdges(_2dgraphics, data)
    }

    render() {
        return <>
            <DrawPanel drawContent={this.drawGraph} handleContentResize={this.handleResize} conainerId="algorithmContainer" title={this.props.title}></DrawPanel>
        </>
    }
    componentDidMount() {
        this.setState({ ...this.state, loaded: true });
    }
    componentDidUpdate(prevProps, prevState, snapshot) {
    }
    handleResize() {
        if (Object.keys(this.props.graph).length === 0) {
            return;
        }
        let edges = this.props.graph.getEdges();
        edges.forEach((adjList, key, map) => {
            adjList.forEach((edge, key, map) => {
                edge.getAttributes().labelPosition = null;
            });
        });
    }
}
export default GraphLogicalView;