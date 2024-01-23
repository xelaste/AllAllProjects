import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
class DrawPanel extends React.Component {

    constructor(props) {
        super(props);
        this.handleResize = this.handleResize.bind(this);

    }
    handleResize() {
        let containerId = this.props.containerId ? this.props.containerId : "algorithmContainer";
        let container = document.getElementById(containerId);
        let width = container ? container.offsetWidth + "px" : "501px";
        let height = container ? container.offsetHeight + "px" : "381px";
        let size = { width: width, height: height };
        if (this.props.handleContentResize) {
            this.props.handleContentResize();
        }
        this.setState({ ...this.state, size: size });
    }
    getDimensions() {
        let c_canvas = document.getElementById("c");
        let width = c_canvas.offsetWidth - 10;
        let height = c_canvas.offsetHeight - 10;
        return { "width": width, "height": height };
    }
    get2DGraphics() {
        let c_canvas = document.getElementById("c");
        let context = c_canvas.getContext("2d");
        return context;
    }
    render() {
        let containerId = this.props.conainerId ? this.props.conainerId : "algorithmContainer";
        let container = document.getElementById(containerId);
        let width = container ? container.offsetWidth + "px" : "501px";
        let height = container ? container.offsetHeight + "px" : "381px";
        return <canvas id="c" width={width} height={height} className="border border-info border-3 bg-light"></canvas>
    }
    drawGrid() {
        let c_canvas = document.getElementById("c");

        let width = c_canvas.offsetWidth - 5;
        let height = c_canvas.offsetHeight - 5;
        width = width - width % 10 + 1;
        height = height - height % 10 + 1;
        let context = this.get2DGraphics();
        context.globalAlpha = 0.3
        for (var x = 0.5; x < width; x += 10) {
            context.moveTo(x, 0);
            context.lineTo(x, height);
        }

        for (var y = 0.5; y < height; y += 10) {
            context.moveTo(0, y);
            context.lineTo(width, y);
        }
        context.strokeStyle = "#d0d0d0";
        context.stroke();

        context.beginPath();
        for (let x = 0.5; x < width; x += 20) {
            context.moveTo(x, 0);
            context.lineTo(x, height);
        }

        for (let y = 0.5; y < height; y += 20) {
            context.moveTo(0, y);
            context.lineTo(width, y);
        }
        context.lineWidth = 2;
        context.strokeStyle = "#c0c0c0";
        context.stroke();
    }
    clearContent()
    {
        let c_canvas = document.getElementById("c");
        let context = c_canvas.getContext("2d");
        context.clearRect(0, 0, c_canvas.width, c_canvas.height);
    }
    drawContent() {
        if (this.props.drawContent) {
            this.get2DGraphics().globalAlpha = 1;
            this.props.drawContent(this.get2DGraphics(), { range: this.getDimensions() });
        }
    }
    componentDidMount() {
        window.addEventListener('resize', this.handleResize);
        if (!this.props.grid || !this.props.grid === true) {
            this.drawGrid();
        }
        this.drawContent();
    }
    componentDidUpdate(prevProps, prevState, snapshot) {
        this.clearContent();
        if (!this.props.grid || !this.props.grid === true) {
            this.drawGrid();
        }
        this.drawContent();
    }
}
export default DrawPanel;
