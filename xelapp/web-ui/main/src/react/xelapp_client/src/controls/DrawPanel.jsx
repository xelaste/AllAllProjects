import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
class DrawPanel extends React.Component {

    constructor(props) {
        super(props);
    }
    render() {
        let container = document.getElementById("algorithmContainer");
        let width=container?container.offsetWidth + "px":"501px";
        let height=container?container.offsetHeight+"px":"381px";
        return  <div className="text-center">
            {this.props.title ? <h1 className="display-1 text-primary">{this.props.title}</h1>:""}
            <canvas id="c" width={width} height={height} className="border border-secondary border-3"></canvas>
        </div>
    }
    drawGrid() {
        let c_canvas = document.getElementById("c");
        let width=c_canvas.offsetWidth - 5;
        let height=c_canvas.offsetHeight - 5;
        width = width - width % 10 + 1;
        height = height - height % 10 + 1;
        console.log("^^^^****************************");
        console.log(width);
        console.log(height);
        console.log("^^^^****************************");
        let context = c_canvas.getContext("2d");
        for (var x = 0.5; x < width; x += 10) {
            context.moveTo(x, 0);
            context.lineTo(x, height);
        }

        for (var y = 0.5; y < height; y += 10) {
            context.moveTo(0, y);
            context.lineTo(width, y);
        }
        context.strokeStyle = "#ddd";
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
        context.strokeStyle = "#ccc";
        context.stroke();
    }

    componentDidUpdate(prevProps, prevState, snapshot) {
        this.drawGrid();
    }

    componentDidMount()
    {
        this.drawGrid();
    }
}
export default DrawPanel;
