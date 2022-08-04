import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
class DrawPanel extends React.Component {

    constructor(props) {
        super(props);

    }
    getDimensions() {
        let c_canvas = document.getElementById("c");
        let width = c_canvas.offsetWidth - 5;
        let height = c_canvas.offsetHeight - 5;
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
        return <div className="text-center">
            {this.props.title ? <h1 className="display-1 text-primary">{this.props.title}</h1> : ""}
            <canvas id="c" width={width} height={height} className="border border-info border-3"></canvas>
        </div>
    }
    drawCircle(center, radius, style, text) {
        let context = this.getContext();
        context.beginPath();
        context.arc(center.X, center.Y, radius, 0, 2 * Math.PI, false);
        if (style) {
            if (style.color) {
                context.fillStyle = style.color;
                context.fill();
            }
            if (style.lineWidth) {
                context.lineWidth = style.lineWidth;
            }
            if (style.lineWidth) {
                context.lineWidth = style.lineWidth;
            }
            if (style.strokeStyle) {
                context.strokeStyle = style.strokeStyle;
            }
            
        }
        context.stroke();
        if (text)
        {
            if (style && style.font)
            {
                context.font = style.font;
            }    
            context.fillText(text, center.X - radius, center.Y,radius);
        }    
    }
    drawGrid() {
        let c_canvas = document.getElementById("c");
        let width = c_canvas.offsetWidth - 5;
        let height = c_canvas.offsetHeight - 5;
        width = width - width % 10 + 1;
        height = height - height % 10 + 1;
        let context = this.getContext();
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
    componentDidMount() {
        if (this.props.parentObject) {
            this.props.parentObject.drawPanel = this;
        }
    }
    componentDidUpdate(prevProps, prevState, snapshot) {
        if (!this.props.grid || !this.props.grid === true) {
            this.drawGrid();
        }
    }
}
export default DrawPanel;
