import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import DrawPanel from '../../../../controls/DrawPanel';
import {content as defaultContent,shuffle} from '../util/ContentProvider';
let margin=28
function SortLogicalView(props) {
    let handleResize = () => { };
    let content = props.content ? props.content : defaultContent;
    let drawContent = (_2dgraphics, data) => { 
        let selected = false;
        let width = data.range.width - margin;
        let height = data.range.height - margin 
        let color = (selected) ? "#4c516d" : "#00c0c0";
        _2dgraphics.beginPath();
        _2dgraphics.lineWidth = 2
        _2dgraphics.strokeStyle = color;
        _2dgraphics.fillStyle = color;
        _2dgraphics.moveTo(margin,height);
        _2dgraphics.lineTo(width  , height );
        _2dgraphics.stroke();
        _2dgraphics.closePath();
        let step = (width - margin)/content.length;
        let max = Math.max(...content);
        let min = Math.min (...content);
        shuffle(content)
        for (let i=0;i<content.length;i++)
        {
            let val = ( max - content[i] ) / max - min;
            _2dgraphics.beginPath();
            _2dgraphics.lineWidth = 2
            _2dgraphics.strokeStyle = color;
            _2dgraphics.fillStyle = color;
            _2dgraphics.moveTo( ( margin + 5) + step * i ,height);
            _2dgraphics.lineTo( ( margin + 5) + step * i  , height + (height - margin )* val );
            _2dgraphics.stroke();
            _2dgraphics.closePath();
    
        }
/*

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
      
*/
    };

    return <>
        <DrawPanel drawContent={drawContent}
            handleContentResize={handleResize}
            containerId="algorithmContainer" title={props.title}></DrawPanel>
    </>
}
export default SortLogicalView;